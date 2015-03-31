/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include <QtCore>
#include <QPainter>

#include "RDebug.h"
#include "RDocument.h"
#include "RDocumentInterface.h"
#include "RGuiAction.h"
#include "RGraphicsScene.h"
#include "RGraphicsSceneQt.h"
#include "RGraphicsViewImage.h"
#include "RLine.h"
#include "RMainWindowQt.h"
#include "RMdiChildQt.h"
#include "RMouseEvent.h"
#include "RSettings.h"
#include "RSnap.h"
#include "RSnapRestriction.h"
#include "RTerminateEvent.h"
#include "RUnit.h"
#include "RWheelEvent.h"


RGraphicsViewImage::RGraphicsViewImage()
    : RGraphicsView(),
      panOptimization(false),
      sceneQt(NULL),
      lastSize(0,0),
      lastOffset(RVector::invalid),
      lastFactor(-1.0),
      gridPainter(NULL),
      doPaintOrigin(true),
      isSelected(false),
      bgColorLightness(0),
      colorCorrectionOverride(false),
      colorCorrection(false),
      colorThreshold(10),
      drawingScale(1.0) {

    currentScale = 1.0;
    saveViewport();
    graphicsBufferNeedsUpdate = true;
}



RGraphicsViewImage::~RGraphicsViewImage() {
}

void RGraphicsViewImage::setPaintOrigin(bool val) {
    doPaintOrigin = val;
}

void RGraphicsViewImage::setBackgroundColor(const QColor& col) {
    RGraphicsView::setBackgroundColor(col);
    bgColorLightness = backgroundColor.lightness();
}

void RGraphicsViewImage::setScene(RGraphicsSceneQt* scene, bool regen) {
    sceneQt = scene;
    RGraphicsView::setScene(scene, regen);
}

void RGraphicsViewImage::invalidate(bool force) {
    graphicsBufferNeedsUpdate = true;
    if (force) {
        lastFactor = -1;
    }
}

/**
 * Regenerates the view from the underlying scene. 
 */
void RGraphicsViewImage::regenerate(bool force) {
    updateTransformation();
    invalidate(force);
    if (force && grid!=NULL) {
        grid->update(force);
    }
    repaintView();
    viewportChangeEvent();
}

/**
 * Triggers a paintEvent based on a buffered offscreen bitmap (very fast).
 */
void RGraphicsViewImage::repaintView() {
    updateImage();
}
    
void RGraphicsViewImage::saveViewport() {
    previousView = transform;
}

void RGraphicsViewImage::restoreViewport() {
    transform = previousView;
}

RVector RGraphicsViewImage::mapToView(const RVector& v) const {
    RVector projected = v;
    updateTransformation();
    QPointF t = transform.map(QPointF(projected.x, projected.y));
    RVector ret(t.x(), t.y());
    ret.valid = v.valid;
    return ret;
}

RVector RGraphicsViewImage::mapFromView(const RVector& v, double z) const {
    updateTransformation();
    QPointF p = transform.inverted().map(QPointF(v.x, v.y));
    RVector ret(p.x(), p.y(), z);
    ret.valid = v.valid;
    return ret;
}

double RGraphicsViewImage::mapDistanceToView(double d) const {
    return d * getFactor();
}

double RGraphicsViewImage::mapDistanceFromView(double d) const {
    return d / getFactor();
}

/**
 * Repaints the view. If the view has been invalidated before,
 * the view is redrawn from scratch. Otherwise, only a cached
 * buffer is drawn (very fast).
 *
 * \see invalidate
 */
void RGraphicsViewImage::updateImage() {
    RDocumentInterface* di = getDocumentInterface();
    if (di==NULL || sceneQt==NULL) {
        return;
    }

    // update drawing scale from document setting:
    QString scaleString = getDocument()->getVariable("PageSettings/Scale", "1:1").toString();
    drawingScale = RMath::parseScale(scaleString);
    if (RMath::isNaN(drawingScale) || drawingScale<1.0e-6) {
        drawingScale = 1.0;
    }

    //RDebug::startTimer();

    if (graphicsBufferNeedsUpdate) {

        updateGraphicsBuffer();
        graphicsBufferNeedsUpdate = false;

        bool displayGrid = gridVisible;

        // optimization for panning and scrolling:
        if (panOptimization && lastFactor==factor) {
            Q_ASSERT(false);
            QImage lastBuffer = graphicsBuffer.copy();
            RVector o = mapToView(offset) - mapToView(lastOffset);
            int ox = RMath::mround(o.x);
            int oy = RMath::mround(o.y);

            if (ox!=0) {
                // fill gap at the right or left side:
                QRect rect(
                    ox<0 ? ox+getWidth() : 0,
                    0,
                    abs(ox),
                    getHeight()
                );
                rect.adjust(-1,-1,1,1);

                paintErase(graphicsBuffer, rect);
                if (displayGrid) {
                    paintMetaGrid(graphicsBuffer, rect);
                }
                paintDocument(rect);
                if (displayGrid) {
                    paintGrid(graphicsBuffer, rect);
                }
                paintOrigin(graphicsBuffer);
            }

            if (oy!=0) {
                // fill gap at the top or bottom:
                QRect rect(
                    qMax(ox, 0),
                    oy<0 ? oy+getHeight() : 0,
                    getWidth() - abs(ox),
                    abs(oy)
                );
                rect.adjust(-1,-1,1,1);
                paintErase(graphicsBuffer, rect);
                if (displayGrid) {
                    paintMetaGrid(graphicsBuffer, rect);
                }
                paintDocument(rect);
                if (displayGrid) {
                    paintGrid(graphicsBuffer, rect);
                }
                paintOrigin(graphicsBuffer);
            }

            QPainter gbPainter(&graphicsBuffer);
            gbPainter.drawImage(ox, oy, lastBuffer);
            gbPainter.end();
        }
        else {
            paintErase(graphicsBuffer);
            bool originBelowEntities = RSettings::getShowLargeOriginAxis();
            if (originBelowEntities) {
                paintOrigin(graphicsBuffer);
            }
            paintDocument();
            if (displayGrid) {
                paintMetaGrid(graphicsBuffer);
                paintGrid(graphicsBuffer);
            }
            if (!originBelowEntities) {
                paintOrigin(graphicsBuffer);
            }
        }
        lastOffset = offset;
        lastFactor = factor;
    }


    graphicsBufferWithPreview = graphicsBuffer;

    // draws the current preview on top of the buffer:
    QList<RPainterPath> preview = sceneQt->getPreviewPainterPaths();
    if (!preview.isEmpty()) {
        QPainter* painter = initPainter(graphicsBufferWithPreview, false);
        bgColorLightness = getBackgroundColor().lightness();
        isSelected = false;
        paintEntity(painter, -1);
        painter->end();
        delete painter;
    }

    // highlighting of closest reference point:
    if (scene->getHighlightedReferencePoint().isValid()) {
        RVector p = mapToView(scene->getHighlightedReferencePoint());
        QPainter gbPainter(&graphicsBufferWithPreview);
        paintReferencePoint(gbPainter, p, true);
        gbPainter.end();
    }

    // snap label:
    if (hasFocus() || this == di->getLastKnownViewWithFocus()) {
        if (di->getClickMode()==RAction::PickCoordinate) {
            RSnap* snap = di->getSnap();
            RSnapRestriction* snapRestriction = di->getSnapRestriction();
            emitUpdateSnapInfo(snap, snapRestriction);
            if (snap!=NULL) {
                snap->reset();
            }
            if (snapRestriction!=NULL) {
                snapRestriction->reset();
            }
        }
    }

    // informational text labels:
    for (int i=0; i<textLabels.size(); i++) {
        emitUpdateTextLabel(textLabels.at(i));
    }
    textLabels.clear();

    // cursor:
    paintCursor(graphicsBufferWithPreview);

    // relative zero:
    paintRelativeZero(graphicsBufferWithPreview);

    //RDebug::stopTimer("repaint");
}

void RGraphicsViewImage::paintReferencePoint(QPainter& painter, const RVector& pos, bool highlight) {
    RColor color = RSettings::getColor("GraphicsViewColors/ReferencePointColor", RColor(0,0,172));
    if (highlight) {
        color = RColor::getHighlighted(color, backgroundColor);
    }
    int size = RSettings::getIntValue("GraphicsView/ReferencePointSize", 10);
    int shape = RSettings::getIntValue("GraphicsView/ReferencePointShape", 0);

    if (shape==1) {
        QPen p(color);
        p.setWidth(3);
        painter.setPen(p);
        painter.drawLine(QPointF(pos.x-size/2, pos.y), QPointF(pos.x+size/2, pos.y));
        painter.drawLine(QPointF(pos.x, pos.y-size/2), QPointF(pos.x, pos.y+size/2));
    }
    else {
        painter.fillRect(QRect(pos.x - size/2, pos.y - size/2, size, size), color);
    }
}

void RGraphicsViewImage::paintErase(QPaintDevice& device, const QRect& rect) {
    QRect r = rect;
    if (rect.isNull()) {
        r = QRect(0,0,getWidth(),getHeight());
    }

    RVector c1 = mapFromView(RVector(r.left(),r.top()));
    RVector c2 = mapFromView(RVector(r.left() + r.width(),r.top() + r.height()));
    QRectF rf(c1.x, c1.y, c2.x-c1.x, c2.y-c1.y);

    gridPainter = initPainter(device, false, false, rect);
    gridPainter->setBackground(getBackgroundColor());
    if (!rect.isNull()) {
        gridPainter->setClipRect(rf);
    }
    gridPainter->eraseRect(rf);

    delete gridPainter;
    gridPainter = NULL;
}

void RGraphicsViewImage::paintGrid(QPaintDevice& device, const QRect& rect) {
    QRect r = rect;
    if (rect.isNull()) {
        r = QRect(0,0,getWidth(),getHeight());
    }

    RVector c1 = mapFromView(RVector(r.left(),r.top()));
    RVector c2 = mapFromView(RVector(r.left() + r.width(),r.top() + r.height()));
    QRectF rf(c1.x, c1.y, c2.x-c1.x, c2.y-c1.y);

    gridPainter = initPainter(device, false, false, rect);
    gridPainter->setRenderHint(QPainter::Antialiasing, false);
    if (!rect.isNull()) {
        gridPainter->setClipRect(rf);
    }

    if (grid!=NULL) {
        QPen pen(RSettings::getColor("GraphicsViewColors/GridColor", RColor(192,192,192,192)));
        pen.setWidth(0);
        gridPainter->setPen(pen);
        grid->paint();
    }

    delete gridPainter;
    gridPainter = NULL;
}

void RGraphicsViewImage::paintGridPoint(const RVector& ucsPosition) {
    if (gridPainter==NULL) {
        qWarning("RGraphicsViewImage::paintGridPoint: gridPainter is NULL");
        return;
    }
    gridPainter->drawPoint(QPointF(ucsPosition.x, ucsPosition.y));
}

void RGraphicsViewImage::paintMetaGrid(QPaintDevice& device, const QRect& rect) {
    QRect r = rect;
    if (rect.isNull()) {
        r = QRect(0,0,getWidth(),getHeight());
    }

    gridPainter = initPainter(device, false, false, rect);
    gridPainter->setBackground(getBackgroundColor());

    if (grid!=NULL) {
        gridPainter->setPen(QPen(
                RSettings::getColor("GraphicsViewColors/MetaGridColor", RColor(192,192,192,64)),
                0, Qt::SolidLine));
        grid->paintMetaGrid();
    }

    delete gridPainter;
    gridPainter = NULL;
}

void RGraphicsViewImage::paintGridLine(const RLine& ucsPosition) {
    if (gridPainter==NULL) {
        qWarning("RGraphicsViewImage::paintGridLine: gridPainter is NULL");
        return;
    }
    gridPainter->drawLine(
        QPointF(ucsPosition.startPoint.x, ucsPosition.startPoint.y),
        QPointF(ucsPosition.endPoint.x, ucsPosition.endPoint.y)
    );
}

/**
 * Paints the absolute zero point (origin).
 */
void RGraphicsViewImage::paintOrigin(QPaintDevice& device) {
    if (!doPaintOrigin || isPrinting()) {
        return;
    }

    gridPainter = initPainter(device, false, false);

    QPen pen(RSettings::getColor("GraphicsViewColors/OriginColor", RColor(255,0,0,192)));
    pen.setWidth(0);

    if (RSettings::getShowLargeOriginAxis()) {
        RBox b = getBox();
        //pen.setStyle(Qt::DashDotDotLine);
        pen.setDashPattern(QVector<qreal>() << 9 << 3 << 3 << 3 << 3 << 3);
        gridPainter->setPen(pen);
        gridPainter->drawLine(QPointF(b.c1.x, 0.0), QPointF(b.c2.x, 0));
        gridPainter->drawLine(QPointF(0.0, b.c1.y), QPointF(0.0, b.c2.y));
    }
    else {
        gridPainter->setPen(pen);
        double r = mapDistanceFromView(20.0);
        gridPainter->drawLine(
            QPointF(-r,0.0),
            QPointF(r,0.0)
        );
        gridPainter->drawLine(
            QPointF(0.0,-r),
            QPointF(0.0,r)
        );
    }

    delete gridPainter;
    gridPainter = NULL;
}

void RGraphicsViewImage::paintCursor(QPaintDevice& device) {
    RDocumentInterface* di = getDocumentInterface();
    if (di==NULL) {
        return;
    }

    if (di->getClickMode()!=RAction::PickCoordinate && !di->getCursorOverride()) {
        return;
    }

    RVector pos = di->getCursorPosition();
    if (!pos.isValid()) {
        return;
    }

    if (!RSettings::getShowCrosshair()) {
        return;
    }

    RColor crossHairColor;
    if (hasFocus() || this == di->getLastKnownViewWithFocus()) {
        crossHairColor = RSettings::getColor("GraphicsViewColors/CrosshairColor", RColor(255,194,0,192));
    }
    else {
        crossHairColor = RSettings::getColor("GraphicsViewColors/CrosshairColorInactive", RColor(108,79,0,192));
    }

    gridPainter = initPainter(device, false, false);

    if (grid!=NULL) {
        gridPainter->setPen(QPen(crossHairColor, 0, Qt::DashLine));
        grid->paintCursor(pos);
    }

    delete gridPainter;
    gridPainter = NULL;
}

void RGraphicsViewImage::paintRelativeZero(QPaintDevice& device) {
    if (!doPaintOrigin || isPrinting()) {
        return;
    }

    RDocumentInterface* di = getDocumentInterface();
    if (di==NULL) {
        return;
    }

    RVector relativeZero = di->getRelativeZero();
    if (!relativeZero.isValid()) {
        return;
    }

    RVector screenPos = mapToView(relativeZero);
    double r = 5.0;

    QPainter painter(&device);
    painter.setPen(
        QPen(RSettings::getColor("GraphicsViewColors/RelativeZeroColor", RColor(162,36,36)), 0)
    );
    painter.drawLine(
        QPointF(screenPos.x-r, screenPos.y),
        QPointF(screenPos.x+r, screenPos.y)
    );
    painter.drawLine(
        QPointF(screenPos.x, screenPos.y-r),
        QPointF(screenPos.x, screenPos.y+r)
    );
    painter.drawEllipse(QPointF(screenPos.x, screenPos.y), r, r);
    painter.end();
}

void RGraphicsViewImage::updateTransformation() const {
    transform.reset();
    transform.scale(1, -1);
    transform.translate(0, -getHeight());
    double f = getFactor();
    transform.scale(f, f);
    RVector o = getOffset();
    transform.translate(o.x, o.y);
}

/**
 * Updates the graphics buffer from scratch. 
 * This can be relatively slow and is only called on view
 * port changes or document changes.
 */
void RGraphicsViewImage::updateGraphicsBuffer() {
    QSize newSize(getWidth(), getHeight());

    if (lastSize!=newSize && graphicsBuffer.size()!=newSize) {
        graphicsBuffer = QImage(newSize, QImage::Format_RGB32);
        lastFactor = -1;
    }

    lastSize = newSize;
}

void RGraphicsViewImage::paintDocument(const QRect& rect) {
    RDocument* document = getDocument();
    if (document == NULL) {
        return;
    }

    QRect r = rect;
    if (rect.isNull()) {
        r = QRect(0,0,getWidth(),getHeight());
    }
    
    bgColorLightness = getBackgroundColor().lightness();
    selectedIds.clear();

    QPainter* painter;
    painter = initPainter(graphicsBuffer, false, false, r);
    paintBackground(painter, r);
    RVector c1 = mapFromView(RVector(r.left()-1,r.bottom()+1), -1e300);
    RVector c2 = mapFromView(RVector(r.right()+1,r.top()-1), 1e300);
    RBox queryBox(c1, c2);

    paintEntities(painter, queryBox);

    // paint selected entities on top:
    if (!selectedIds.isEmpty()) {
        isSelected = true;
        QList<REntity::Id> list = document->getStorage().orderBackToFront(selectedIds);
        QListIterator<RObject::Id> i(list);
        while (i.hasNext()) {
            paintEntity(painter, i.next());
        }
    }

    painter->end();
    delete painter;

    // paint reference points of selected entities:
    QMultiMap<REntity::Id, RVector>& referencePoints =
            scene->getReferencePoints();
    if (!referencePoints.isEmpty() && referencePoints.count()<1000) {

        QPainter gbPainter(&graphicsBuffer);

        QMultiMap<REntity::Id, RVector>::iterator it;
        for (it = referencePoints.begin(); it != referencePoints.end(); ++it) {
            RVector p = mapToView(it.value());
            paintReferencePoint(gbPainter, p, false);
        }

        gbPainter.end();
    }
}

void RGraphicsViewImage::clearBackground() {
    backgroundDecoration.clear();
}

void RGraphicsViewImage::addToBackground(const RPainterPath& path) {
    backgroundDecoration.append(path);
}

void RGraphicsViewImage::setBackgroundTransform(double bgFactor, const RVector& bgOffset) {
    backgroundFactor = bgFactor;
    backgroundOffset = bgOffset;
}

void RGraphicsViewImage::paintBackground(QPainter* painter, const QRect& rect) {
    Q_UNUSED(rect);

    QTransform savedTransform = painter->transform();
    painter->translate(backgroundOffset.x, backgroundOffset.y);
    painter->scale(backgroundFactor, backgroundFactor);

    for (int i=0; i<backgroundDecoration.size(); i++) {
        RPainterPath path = backgroundDecoration.at(i);
        painter->setPen(path.getPen());
        painter->setBrush(path.getBrush());
        painter->drawPath(path);
    }

    painter->setTransform(savedTransform);
}

QPainter* RGraphicsViewImage::initPainter(QPaintDevice& device, bool erase, bool screen, const QRect& rect) {
    QPainter* painter = new QPainter(&device);
    if (antialiasing) {
        painter->setRenderHint(QPainter::Antialiasing);
    }
    if (erase) {
        QRect r = rect;
        if (rect.isNull()) {
            r = QRect(0,0,lastSize.width(),lastSize.height());
        }
        // erase background to transparent:
        painter->setCompositionMode(QPainter::CompositionMode_Clear);
        painter->eraseRect(r);
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    }

    //if (!rect.isNull()) {
        //painter->setClipRect(rect);
    //}

    if (!screen) {
        painter->setWorldTransform(transform);
    }
    //painter->setPen(QPen());
    return painter;
}

void RGraphicsViewImage::paintEntities(QPainter* painter, const RBox& queryBox) {
    RDocument* document = getDocument();
    if (document==NULL) {
        return;
    }

    colorCorrection = RSettings::getColorCorrection();
    colorThreshold = RSettings::getColorThreshold();

    updateTextHeightThreshold();

    //qDebug() << "RGraphicsViewImage::paintEntities: colorCorrection: " << colorCorrection;

    RBox qb(queryBox);
    qb.growXY(
        RUnit::convert(
            document->getMaxLineweight()/100.0,
            RS::Millimeter,
            document->getUnit()
        )
    );

    //RDebug::startTimer();
    mutexSi.lock();
    QSet<REntity::Id> ids;

    ids = document->queryIntersectedEntitiesXY(qb, true);

    //qDebug() << "RGraphicsViewImage::paintEntities: ids: " << ids.size();

    mutexSi.unlock();
    //RDebug::stopTimer("spatial index");

    // draw painter paths:
    isSelected = false;

    //RDebug::startTimer();
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
    //RDebug::stopTimer("ordering");

    //RDebug::startTimer();

    if (isPrinting()) {
        clipBox = RBox();
    }
    else {
        clipBox = getBox();
        clipBox.growXY(
                    RUnit::convert(
                        getDocument()->getMaxLineweight()/100.0,
                        RS::Millimeter,
                        getDocument()->getUnit()
                        )
                    );
    }

    QListIterator<REntity::Id> it(list);
    while (it.hasNext()) {
        paintEntity(painter, it.next());
    }

    //RDebug::stopTimer("painting");
}

void RGraphicsViewImage::paintEntity(QPainter* painter, REntity::Id id) {
    if (!isPrinting() && !isSelected && getDocument()->isSelected(id)) {
        static QMutex m;
        m.lock();
        selectedIds.insert(id);
        m.unlock();
        return;
    }

    // TODO: PERFORMANCE: don't copy list, only get reference from scene

    QList<RPainterPath> painterPaths;

    // get painter paths for vector graphics entity:
    if (id == -1) {
        // get painter paths of the current preview:
        painterPaths = sceneQt->getPreviewPainterPaths();
    } else {
        // get painter paths of the given entity:
        painterPaths = sceneQt->getPainterPaths(id);

        // if at least one arc path is too detailed or not detailed enough,
        // or the path is an XLine or Ray, regen:

        // ideal pixel size for rendering arc at current zoom level:
        double ps = mapDistanceFromView(1.0);
        if (isPrinting()) {
            ps = getScene()->getPixelSizeHint();
        }

        // do we need to regen:
        bool regen = false;
        for (int p=0; p<painterPaths.size(); p++) {
            if (painterPaths[p].getAlwaysRegen()==true) {
                regen = true;
                break;
            }
            if (painterPaths[p].getAutoRegen()==true) {
                if (painterPaths[p].getPixelSizeHint()>RS::PointTolerance &&
                    (painterPaths[p].getPixelSizeHint()<ps/5 || painterPaths[p].getPixelSizeHint()>ps*5)) {

                    regen = true;
                    break;
                }
            }
        }

        // regen:
        if (regen) {
            sceneQt->exportEntity(id, true);
            painterPaths = sceneQt->getPainterPaths(id);
        }
    }

    // get image for raster image entity:
    if (sceneQt->hasImageFor(id)) {
        RImageData image = sceneQt->getImage(id);
        paintImage(painter, image);
    }

    // paint painter paths:
    QListIterator<RPainterPath> i(painterPaths);
    while (i.hasNext()) {
        RPainterPath path = i.next();
        RBox pathBB = path.getBoundingBox();

        // additional bounding box check for painter paths that are
        // part of one block reference entity:
        if (!isPrinting() && !clipBox.intersects(pathBB)) {
            continue;
        }

        // small texts might be invisible while their bounding box is displayed:
        if (!isPathVisible(path)) {
            continue;
        }

        QPen pen = path.getPen();
        QBrush brush = path.getBrush();

        if (pen.style() != Qt::NoPen) {
            if (isPrinting()) {
                if (hairlineMode) {
                    //pen.setWidthF(0.05 / drawingScale);
                    pen.setWidthF(0.0);
                    pen.setCosmetic(true);
                }
                else {
                    // printing: always use real, scaled line weight, no matter
                    // how thin:
                    pen.setWidthF(pen.widthF() / drawingScale);
                }
            }
            else if (isPrintPreview()) {
                if (!pen.isCosmetic()) {
                    // print preview: optimize thin lines to 0 (1 pixel):
                    if (pen.widthF() * getFactor() / drawingScale < 1.5) {
                        pen.setWidth(0);
                    }
                    else {
                        if (hairlineMode) {
                            //pen.setWidthF(0.05 / drawingScale);
                            pen.setWidthF(0.0);
                            pen.setCosmetic(true);
                        }
                        else {
                            pen.setWidthF(pen.widthF() / drawingScale);
                        }
                    }
                }
            }
            else {
                if (!pen.isCosmetic()) {
                    // for display, ignore drawing scale and optimize
                    // thin lines to 0:
                    if (pen.widthF() * getFactor() < 1.5) {
                        pen.setWidth(0);
                    }
                }
            }
        }

        // prevent black on black / white on white drawing
        if (colorCorrection || colorCorrectionOverride) {
            if (pen.color().lightness() <= colorThreshold && bgColorLightness <= colorThreshold) {
                pen.setColor(Qt::white);
            } else if (pen.color().lightness() >= 255-colorThreshold && bgColorLightness >= 255-colorThreshold) {
                pen.setColor(Qt::black);
            }

            if (brush.color().lightness() <= colorThreshold && bgColorLightness <= colorThreshold) {
                brush.setColor(Qt::white);
            } else if (brush.color().lightness() >= 255-colorThreshold && bgColorLightness >= 255-colorThreshold) {
                brush.setColor(Qt::black);
            }
        }

        // highlighted:
        if (!isPrinting() && path.isHighlighted()) {
            if (pen.style() != Qt::NoPen) {
                pen.setColor(RColor::getHighlighted(pen.color(), bgColorLightness));
            }
            if (brush.style() != Qt::NoBrush) {
                RColor ch = RColor::getHighlighted(brush.color(), bgColorLightness);
                ch.setAlpha(128);
                brush.setColor(ch);
            }
        }

        // color modes (b/w, grayscale):
        // TODO: move as much as possible to generation of painter paths:
        switch (colorMode) {
        case RGraphicsView::BlackWhite:
            // dark background: everything white:
            if (bgColorLightness < 64 && !isPrinting()) {
                if (pen.style() != Qt::NoPen) {
                    pen.setColor(Qt::white);
                }
                if (brush.style() != Qt::NoBrush) {
                    brush.setColor(Qt::white);
                }
            }
            // bright background: everything black:
            else {
                if (pen.style() != Qt::NoPen) {
                    pen.setColor(Qt::black);
                }
                if (brush.style() != Qt::NoBrush) {
                    brush.setColor(Qt::black);
                }
            }
            break;
        case RGraphicsView::GrayScale:
            if (pen.style() != Qt::NoPen) {
                int v = qGray(pen.color().rgb());
                pen.setColor(QColor(v, v, v));
            }
            if (brush.style() != Qt::NoBrush) {
                int v = qGray(brush.color().rgb());
                brush.setColor(QColor(v, v, v));
            }
            break;
        default:
            break;
        }

        painter->setBrush(brush);
        painter->setPen(pen);

        if (isPrinting() || clipBox.contains(pathBB)) {
            if (brush.style() != Qt::NoBrush) {
                painter->fillPath(path, brush);
            }

            // draw outline:
            if (pen.style() != Qt::NoPen) {
                painter->drawPath(path);
            }
        }
        else {
            // prevent overflows for simple lines:
            // TODO: make this an option for rendering:
            if (path.elementCount() == 2 &&
                path.elementAt(0).isMoveTo() &&
                path.elementAt(1).isLineTo()) {

                qreal x1 = path.elementAt(0).x;
                qreal y1 = path.elementAt(0).y;
                qreal x2 = path.elementAt(1).x;
                qreal y2 = path.elementAt(1).y;
                RLine line(RVector(x1,y1), RVector(x2,y2));
                if (!clipBox.contains(line.getBoundingBox())) {
                    line.clipToXY(clipBox);
                }

                if (line.isValid()) {
                    QLineF qLine(QPointF(line.startPoint.x, line.startPoint.y),
                                QPointF(line.endPoint.x, line.endPoint.y));
                    painter->drawLine(qLine);
                }
            }
            else {
                // draw fill:
                if (brush.style() != Qt::NoBrush) {
                    painter->fillPath(path, brush);
                }

                // draw outline:
                if (pen.style() != Qt::NoPen) {
                    // TODO: optional (more accurate, slower?):
                    qreal x, y;
                    for (int i=0; i<path.elementCount(); i++) {
                        QPainterPath::Element el = path.elementAt(i);
                        if (el.isMoveTo()) {
                            x = el.x;
                            y = el.y;
                            continue;
                        }

                        if (el.isLineTo()) {
                            RLine line(RVector(x,y), RVector(el.x,el.y));
                            if (!clipBox.contains(line.getBoundingBox())) {
                                line.clipToXY(clipBox);
                            }
                            if (line.isValid()) {
                                QLineF qLine(QPointF(line.startPoint.x, line.startPoint.y),
                                             QPointF(line.endPoint.x, line.endPoint.y));
                                painter->drawLine(qLine);
//                                if (pen2.style() != Qt::NoPen) {
//                                    painter->setPen(pen2);
//                                    painter->drawLine(qLine);
//                                    painter->setPen(pen);
//                                }
                            }
                            x = el.x;
                            y = el.y;
                            continue;
                        }

                        if (el.isCurveTo()) {
                            i++;
                            QPainterPath::Element del1 = path.elementAt(i);
                            i++;
                            QPainterPath::Element del2 = path.elementAt(i);

                            QPainterPath cubicCurve;
                            cubicCurve.moveTo(x, y);
                            cubicCurve.cubicTo(el.x, el.y, del1.x, del1.y, del2.x, del2.y);
                            painter->strokePath(cubicCurve, painter->pen());
                            //painter->strokePath(cubicCurve, pen2);
                            x = del2.x;
                            y = del2.y;
                            continue;
                        }
                    }
                }
            }
        }

        // draw points:
        if (path.hasPoints()) {
            double pSize = getDocument()->getKnownVariable(RS::PDSIZE, 0).toDouble();
            pSize = getPointSize(pSize);
            int pMode = getDocument()->getKnownVariable(RS::PDMODE, 0).toInt();

            // FS#481: for printing, point size does not depend on current viewing factor:
            if (isPrinting() || isPrintPreview()) {
                pMode = 0;
            }
            else {
                // When not printing, set pen width to zero so when zooming in
                // the lines don't turn into a blob
                QPen pen = painter->pen();
                pen.setWidth(0);
                painter->setPen(pen);

            }

            // if PDMODE = 1 nothing is drawn
            // we are in an while loop, so continue
            if (pMode == 1) {
                continue;
            }

            // do ANDs once, outside loop
            int rslt7 = pMode & 7;
            int rslt32 = pMode & 32;
            int rslt64 = pMode & 64;
            QList<RVector> points = path.getPoints();
            QList<RVector>::iterator it;
            for (it=points.begin(); it<points.end(); it++) {
                //int rslt = pMode & 7;
                if (rslt7 == 0) {
                    drawDot(painter, QPointF((*it).x, (*it).y));
                } else if (rslt7 == 2) {
                    drawPlus(painter, QPointF((*it).x, (*it).y), pSize);
                } else if (rslt7 == 3) {
                    drawEx(painter, QPointF((*it).x, (*it).y), pSize);
                } else if (rslt7 == 4) {
                    drawVBar(painter, QPointF((*it).x, (*it).y), pSize);
                }
                //rslt = pMode & 32;
                if (rslt32 == 32) {
                    drawCircle(painter, QPointF((*it).x, (*it).y), pSize);
                }
                //rslt = pMode & 64;
                if (rslt64 == 64) {
                    drawSquare(painter, QPointF((*it).x, (*it).y), pSize);
                }
            }
        }
    }
}

double RGraphicsViewImage::getPointSize(double pSize) {
    int ht = getHeight();
    if (pSize == 0) {
        return ht * 5 / 100;
    } else if (pSize < 0) {
        return fabs(ht * pSize / 100);
    } else {
        return pSize;
    }
}

void RGraphicsViewImage::drawDot(QPainter* painter, QPointF pt) {
    qreal r;
    if (isPrinting() || isPrintPreview()) {
        r = mapDistanceFromView(1.0);
    } else {
        r = mapDistanceFromView(1.5);
    }
    painter->setBrush(painter->pen().color());
    painter->drawEllipse(pt, r, r);
    painter->setBrush(Qt::NoBrush);
}

void RGraphicsViewImage::drawPlus(QPainter* painter, QPointF pt, double pSize) {
    qreal size = pSize / 2;
    size = mapDistanceFromView(size);
    painter->drawLine(
        QPointF(pt.x() - size, pt.y()),
        QPointF(pt.x() + size, pt.y())
    );
    painter->drawLine(
        QPointF(pt.x(), pt.y() - size),
        QPointF(pt.x(), pt.y() + size)
    );
}

void RGraphicsViewImage::drawEx(QPainter* painter, QPointF pt, double pSize) {
    qreal size = pSize / 2;
    size = mapDistanceFromView(size);
    painter->drawLine(
        QPointF(pt.x() - size, pt.y() + size),
        QPointF(pt.x() + size, pt.y() - size)
    );
    painter->drawLine(
        QPointF(pt.x() + size, pt.y() + size),
        QPointF(pt.x() - size, pt.y() - size)
    );
}

void RGraphicsViewImage::drawVBar(QPainter* painter, QPointF pt, double pSize) {
    qreal size = (pSize * 0.8) / 2 ;
    size = mapDistanceFromView(size);
    painter->drawLine(
        QPointF(pt.x(), pt.y()),
        QPointF(pt.x(), pt.y() + size)
    );
}

void RGraphicsViewImage::drawCircle(QPainter* painter, QPointF pt, double pSize) {
    qreal size = (pSize * 0.8) / 2;
    size = mapDistanceFromView(size);
    painter->drawEllipse(pt, size, size);
}

void RGraphicsViewImage::drawSquare(QPainter* painter, QPointF pt, double pSize) {
    qreal size = (pSize * 0.8) / 2;
    size = mapDistanceFromView(size);
    painter->drawLine(
        QPointF(pt.x() - size, pt.y() + size),
        QPointF(pt.x() + size, pt.y() + size)
    );
    painter->drawLine(
        QPointF(pt.x() + size, pt.y() + size),
        QPointF(pt.x() + size, pt.y() - size)
    );
    painter->drawLine(
        QPointF(pt.x() + size, pt.y() - size),
        QPointF(pt.x() - size, pt.y() - size)
    );
    painter->drawLine(
        QPointF(pt.x() - size, pt.y() - size),
        QPointF(pt.x() - size, pt.y() + size)
    );
}

void RGraphicsViewImage::paintImage(QPainter* painter, RImageData& image) {
    if (scene==NULL) {
        return;
    }

    if (!scene->getDraftMode()) {
        QImage qImage = image.getImage();
        if (qImage.isNull()) {
            return;
        }
        RVector scale; // = image.getScaleFactor();
        scale.x = image.getUVector().getMagnitude();
        scale.y = image.getVVector().getMagnitude();

        if (RMath::getAngleDifference180(image.getUVector().getAngle(), image.getVVector().getAngle()) < 0.0) {
            scale.y *= -1;
        }

        double angle = image.getUVector().getAngle();

        painter->save();
        QMatrix wm = painter->matrix();
        wm.translate(image.getInsertionPoint().x, image.getInsertionPoint().y);
        wm.rotate(RMath::rad2deg(angle));
        wm.scale(scale.x, -scale.y);
        painter->setMatrix(wm);
        painter->drawImage(0,-qImage.height(), qImage);
        painter->restore();
    }

    // draw image in draft mode / selected mode (border in black or white):
    if (scene->getDraftMode() || image.isSelected()) {
        if (image.isSelected()) {
            RColor selectionColor = RSettings::getColor("GraphicsViewColors/SelectionColor", RColor(164,70,70,128));
            painter->setPen(QPen(QBrush(selectionColor), 0));
        }
        else {
            if (backgroundColor.value()<128) {
                painter->setPen(QPen(QBrush(QColor(Qt::white)), 0));
            }
            else {
                painter->setPen(QPen(QBrush(QColor(Qt::black)), 0));
            }
        }
        QList<RLine> edges = image.getEdges();
        for (int i=0; i<edges.count(); i++) {
            RLine l = edges[i];
            painter->drawLine(QPointF(l.getStartPoint().x, l.getStartPoint().y),
                              QPointF(l.getEndPoint().x, l.getEndPoint().y));
        }
    }

}


int RGraphicsViewImage::getWidth() const {
    return graphicsBuffer.width();
}

int RGraphicsViewImage::getHeight() const {
    return graphicsBuffer.height();
}

void RGraphicsViewImage::resizeImage(int w, int h) {
    graphicsBuffer = QImage(QSize(w,h), QImage::Format_RGB32);
}

void RGraphicsViewImage::setPanOptimization(bool on) {
    panOptimization = on;
}

bool RGraphicsViewImage::getPanOptimization() {
    return panOptimization;
}

QImage RGraphicsViewImage::getBuffer() const {
    return graphicsBufferWithPreview;
}

QTransform RGraphicsViewImage::getTransform() const {
    return transform;
}
