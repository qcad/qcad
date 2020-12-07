/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
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

#if QT_VERSION >= 0x050000
#include <QtConcurrent>
#else
#include <qtconcurrentrun.h>
#endif

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
#include "RTextRenderer.h"
#include "RUnit.h"
#include "RWheelEvent.h"
#include "RViewportEntity.h"


RGraphicsViewImage::RGraphicsViewImage()
    : RGraphicsView(),
      numThreads(1),
      panOptimization(false),
      sceneQt(NULL),
      lastSize(0,0),
      lastOffset(RVector::invalid),
      lastFactor(-1.0),
      gridPainter(NULL),
      doPaintOrigin(true),
      isSelected(false),
      bgColorLightness(0),
      colorCorrectionOverride(-1),
      colorCorrection(false),
      colorThreshold(10),
      minimumLineweight(0.0),
      maximumLineweight(-1.0),
      drawingScale(1.0),
      alphaEnabled(false),
      showOnlyPlottable(false) {

    currentScale = 1.0;
    saveViewport();
    graphicsBufferNeedsUpdate = true;
}

RGraphicsViewImage::~RGraphicsViewImage() {
}

void RGraphicsViewImage::setNumThreads(int n) {
    numThreads = n;
    graphicsBufferThread.clear();
    updateGraphicsBuffer();
    lastSize = QSize(0,0);
}

void RGraphicsViewImage::clear() {
    for (int i=0; i<graphicsBufferThread.length(); i++) {
        QPainter painter(&graphicsBufferThread[i]);
        // erase background to transparent:
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.eraseRect(graphicsBufferThread[i].rect());
    }
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
    RDocument* doc = getDocument();
    if (di==NULL || doc==NULL || sceneQt==NULL) {
        return;
    }


    if (graphicsBufferNeedsUpdate) {
        //RDebug::startTimer(77);

        // update drawing scale from document setting:
        QString scaleString;
        if (doc->getCurrentBlockId()==doc->getModelSpaceBlockId()) {
            scaleString = doc->getVariable("PageSettings/Scale", "1:1").toString();
        }
        else {
            QSharedPointer<RBlock> blk = doc->queryCurrentBlock();
            if (!blk.isNull()) {
                scaleString = blk->getCustomProperty("QCAD", "PageSettings/Scale", "1:1").toString();
            }
        }

        if (scaleString!=lastScaleString) {
            drawingScale = RMath::parseScale(scaleString);
            if (RMath::isNaN(drawingScale) || drawingScale<1.0e-6) {
                drawingScale = 1.0;
            }
        }

        showOnlyPlottable = RSettings::getBoolValue("PrintPreviewPro/ShowOnlyPlottable", false);

        //RDebug::startTimer();
        updateGraphicsBuffer();
        graphicsBufferNeedsUpdate = false;

        bool displayGrid = gridVisible;

        // optimization for panning and scrolling:
        /*
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
        */
        if (!graphicsBufferThread.isEmpty()) {
            paintErase(graphicsBufferThread.first());
            //paintErase(graphicsBuffer2);
            bool originBelowEntities = RSettings::getShowLargeOriginAxis();
            if (originBelowEntities) {
                paintOrigin(graphicsBufferThread.first());
            }

            //RDebug::startTimer();
            paintDocument();
            //RDebug::stopTimer("paintDocument");

            if (displayGrid) {
                paintMetaGrid(graphicsBufferThread.last());
                paintGrid(graphicsBufferThread.last());
            }
            if (!originBelowEntities) {
                paintOrigin(graphicsBufferThread.last());
            }
        }
        lastOffset = offset;
        lastFactor = factor;

        //RDebug::stopTimer("update graphics view");
        //qDebug() << "updateImage: OK";
        //RDebug::stopTimer(77, "updateImage");
    }

    //RDebug::startTimer();

    if (!graphicsBufferThread.isEmpty()) {
        graphicsBufferWithPreview = graphicsBufferThread.first();
        QPainter p(&graphicsBufferWithPreview);
        p.setCompositionMode(QPainter::CompositionMode_SourceOver);
        for (int i=1; i<graphicsBufferThread.length(); i++) {
            p.drawImage(0, 0, graphicsBufferThread[i]);
        }
    }
    //RDebug::stopTimer("compose");

    // draws previewed texts:
//    QList<RTextBasedData> previewTexts = sceneQt->getPreviewTexts();
//    if (!previewTexts.isEmpty()) {
//        QPainter* painter = initPainter(graphicsBufferWithPreview, false);
//        bgColorLightness = getBackgroundColor().lightness();
//        isSelected = false;
//        for (int i=0; i<previewTexts.length(); i++) {
//            paintText(painter, previewTexts[i]);

//            // add painter paths (from CAD fonts) to preview:
//            QList<RTextLayout> tls = previewTexts[i].getTextLayouts();
//            QList<RPainterPath> pps = getTextLayoutsPainterPaths(previewTexts[i], tls);
//            qDebug() << "adding to preview: " << pps;
//            preview.append(pps);
//        }
//        painter->end();
//        delete painter;
//    }

    // draws the current preview on top of the buffer:
    // highlighted entities are also part of the preview
    if (sceneQt->hasPreview()) {
        QPainter* painter = initPainter(graphicsBufferWithPreview, false);

        painterThread.clear();
        painterThread.append(painter);
        entityTransformThread.clear();
        entityTransformThread.append(QStack<RTransform>());

        bgColorLightness = getBackgroundColor().lightness();
        isSelected = false;
        QList<REntity::Id> ids = sceneQt->getPreviewEntityIds();
        for (int i=0; i<ids.length(); i++) {
            paintEntityThread(0, ids[i], true);
        }
        painter->end();
        delete painter;
    }

    // paint reference points of selected entities:
    QMap<REntity::Id, QList<RRefPoint> >& referencePoints = scene->getReferencePoints();
    int num = scene->countReferencePoints();
    if (num!=0 && num<RSettings::getIntValue("GraphicsView/MaxReferencePoints", 100000)) {
        QPainter gbPainter(&graphicsBufferWithPreview);
        QMap<REntity::Id, QList<RRefPoint> >::iterator it;
        for (it = referencePoints.begin(); it != referencePoints.end(); ++it) {
            QList<RRefPoint>& list = it.value();
            for (int i=0; i<list.length(); i++) {
                RRefPoint p = list[i];
                RRefPoint pm = mapToView(p);
                pm.setFlags(p.getFlags());
                paintReferencePoint(gbPainter, pm, false);
            }
        }
        gbPainter.end();
    }

    // highlighting of closest reference point:
    if (scene->getHighlightedReferencePoint().isValid()) {
        RRefPoint p = scene->getHighlightedReferencePoint();
        RRefPoint pm = mapToView(p);
        QPainter gbPainter(&graphicsBufferWithPreview);
        pm.setFlags(p.getFlags());
        paintReferencePoint(gbPainter, pm, true);
        gbPainter.end();
    }

    // overlay (painted after / on top of preview and highlighting):
//    if (!overlayDrawables.isEmpty()) {
//        QPainter* painter = initPainter(graphicsBufferWithPreview, false);
//        painter->setRenderHint(QPainter::Antialiasing);
//        paintOverlay(painter);
//        painter->end();
//    }

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
}

void RGraphicsViewImage::paintReferencePoint(QPainter& painter, const RRefPoint& pos, bool highlight) {
    RColor color;
    if (pos.isStart()) {
        color = RSettings::getStartReferencePointColor();
    }
    else if (pos.isEnd()) {
        color = RSettings::getEndReferencePointColor();
    }
    else if (pos.isSecondary()) {
        color = RSettings::getSecondaryReferencePointColor();
    }
    else if (pos.isTertiary()) {
        color = RSettings::getTertiaryReferencePointColor();
    }
    else {
        color = RSettings::getReferencePointColor();
    }
    if (highlight) {
        color = RColor::getHighlighted(color, backgroundColor, 100);
    }
    int size = RSettings::getReferencePointSize() * getDevicePixelRatio();
    int shape = RSettings::getReferencePointShape();

    if (shape==1) {
        // cross:
        QPen p(color);
        p.setWidth(3);
        painter.setPen(p);
        painter.drawLine(QPointF(pos.x-size/2, pos.y), QPointF(pos.x+size/2, pos.y));
        painter.drawLine(QPointF(pos.x, pos.y-size/2), QPointF(pos.x, pos.y+size/2));
    }
    else {
        if (pos.isCenter() || pos.isArrow()) {
            // center or arrow:
            // round:
            painter.setBrush(color);
            painter.drawEllipse(pos.x - size/2, pos.y - size/2, size, size);
        }
        else {
            // other:
            // rectangle:
            painter.setBrush(color);
            painter.fillRect(QRect(pos.x - size/2, pos.y - size/2, size, size), color);
        }

        if (backgroundColor.value()<128) {
            if (highlight) {
                painter.setPen(QPen(Qt::white));
            }
            else {
                if (pos.isSelected()) {
                    painter.setPen(QPen(Qt::red));
                }
                else {
                    painter.setPen(QPen(Qt::gray));
                }
            }
        }
        else {
            if (highlight) {
                painter.setPen(QPen(Qt::black));
            }
            else {
                if (pos.isSelected()) {
                    painter.setPen(QPen(Qt::red));
                }
                else {
                    painter.setPen(QPen(Qt::gray));
                }
            }
        }
        if (pos.isCenter() || pos.isArrow()) {
            painter.drawEllipse(pos.x - size/2, pos.y - size/2, size, size);
        }
        else {
            painter.drawRect(QRect(pos.x - size/2, pos.y - size/2, size, size));
        }
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
    if (backgroundColor.alpha()==0) {
        gridPainter->setCompositionMode(QPainter::CompositionMode_Clear);
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
    if (!doPaintOrigin || isPrintingOrExporting()) {
        return;
    }

    gridPainter = initPainter(device, false, false);

    QPen pen(RSettings::getColor("GraphicsViewColors/OriginColor", RColor(255,0,0,192)));
    pen.setWidth(0);

    if (RSettings::getShowLargeOriginAxis()) {
        RBox b = getBox();
        //pen.setStyle(Qt::DashDotDotLine);
        pen.setDashPattern(QVector<qreal>() << 9 << 3 << 3 << 3 << 3 << 3);
        //RVector z = mapToView(RVector(0,0));
        //pen.setDashOffset(-z.x);
        gridPainter->setPen(pen);
        gridPainter->drawLine(QPointF(b.c1.x, 0.0), QPointF(b.c2.x, 0));
//        pen.setDashOffset(z.y);
//        gridPainter->setPen(pen);
        gridPainter->drawLine(QPointF(0.0, b.c1.y), QPointF(0.0, b.c2.y));
    }
    else {
        gridPainter->setPen(pen);
        double r = mapDistanceFromView(20.0 * getDevicePixelRatio());
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
    if (!doPaintOrigin || isPrintingOrExporting()) {
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
    double r = 5.0 * getDevicePixelRatio();

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
    double dpr = getDevicePixelRatio();
    QSize newSize(int(getWidth()*dpr), int(getHeight()*dpr));

    if (graphicsBufferThread.isEmpty()) {
        for (int i=0; i<numThreads; i++) {
            graphicsBufferThread.append(QImage());
        }
    }

    if (lastSize!=newSize && graphicsBufferThread.first().size()!=newSize) {
        //graphicsBuffer = QImage(newSize, alphaEnabled ? QImage::Format_ARGB32 : QImage::Format_RGB32);
        //graphicsBuffer2 = QImage(newSize, QImage::Format_ARGB32);
        for (int i=0; i<graphicsBufferThread.length(); i++) {
            if (i==0) {
                graphicsBufferThread[i] = QImage(newSize, alphaEnabled ? QImage::Format_ARGB32 : QImage::Format_RGB32);
            }
            else {
                graphicsBufferThread[i] = QImage(newSize, QImage::Format_ARGB32);
            }
        }
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

    for (int i=1; i<graphicsBufferThread.length(); i++) {
        graphicsBufferThread[i].fill(qRgba(0,0,0,0));
    }

    //QList<QPainter*> painterThread;
    painterThread.clear();
    entityTransformThread.clear();
    for (int i=0; i<graphicsBufferThread.length(); i++) {
        painterThread.append(initPainter(graphicsBufferThread[i], false, false, r));
        entityTransformThread.append(QStack<RTransform>());
    }

    paintBackground(painterThread.first(), r);

    RVector c1 = mapFromView(RVector(r.left()-1,r.bottom()+1), -1e300);
    RVector c2 = mapFromView(RVector(r.right()+1,r.top()-1), 1e300);
    RBox queryBox(c1, c2);

    //RDebug::startTimer();
    paintEntitiesMulti(queryBox);
    //RDebug::stopTimer("paint");

    // paint selected entities on top:
    if (!selectedIds.isEmpty()) {
        isSelected = true;
        QList<REntity::Id> list = document->getStorage().orderBackToFront(selectedIds);
        QListIterator<RObject::Id> i(list);
        while (i.hasNext()) {
            paintEntityThread(painterThread.length()-1, i.next());
        }
    }

    // paint overlay:
    paintOverlay(painterThread.last());

    for (int i=0; i<painterThread.length(); i++) {
        painterThread[i]->end();
        delete painterThread[i];
        painterThread[i] = NULL;
    }
    painterThread.clear();
    entityTransformThread.clear();

//    painter->end();
//    painter2->end();
//    delete painter;
//    delete painter2;

//    // paint reference points of selected entities:
//    QMultiMap<REntity::Id, RRefPoint>& referencePoints = scene->getReferencePoints();
//    int num = referencePoints.count();
//    if (num!=0 && num<RSettings::getIntValue("GraphicsView/MaxReferencePoints", 100000)) {
//        QPainter gbPainter(&graphicsBuffer);
//        QMultiMap<REntity::Id, RRefPoint>::iterator it;

//        for (it = referencePoints.begin(); it != referencePoints.end(); ++it) {
//            RRefPoint p = it.value();
//            RRefPoint pm = mapToView(p);
//            pm.setFlags(p.getFlags());
//            paintReferencePoint(gbPainter, pm, false);
//        }

//        gbPainter.end();
//    }
}

void RGraphicsViewImage::clearBackground() {
    backgroundDecoration.clear();
}

void RGraphicsViewImage::addToBackground(const RGraphicsSceneDrawable& drawable) {
    backgroundDecoration.append(drawable);
}

void RGraphicsViewImage::setBackgroundTransform(double bgFactor, const RVector& bgOffset) {
    backgroundFactor = bgFactor;
    backgroundOffset = bgOffset;
}

void RGraphicsViewImage::paintBackground(QPainter* painter, const QRect& rect) {
    Q_UNUSED(rect)

    if (backgroundDecoration.isEmpty()) {
        return;
    }

    int boxWidth = 1000;
    int boxHeight = 30;

    QTransform savedTransform = painter->transform();
    painter->translate(backgroundOffset.x, backgroundOffset.y);
    painter->scale(backgroundFactor, backgroundFactor);

    for (int i=0; i<backgroundDecoration.size(); i++) {
        RGraphicsSceneDrawable d = backgroundDecoration[i];
        if (d.isPainterPath()) {
            RPainterPath& path = d.getPainterPath();
            painter->setPen(path.getPen());
            painter->setBrush(path.getBrush());
            painter->drawPath(path);
        }
        else if (d.isText()) {
            RTextBasedData& text = d.getText();
            RVector pos = text.getPosition();
            painter->setFont(QFont(text.getFontName(), text.getTextHeight()));
            painter->setPen(QPen(Qt::black));

            int flags = 0;
            double boxLeft;
            double boxTop;

            switch (text.getVAlign()) {
            case RS::VAlignTop:
                flags|=Qt::AlignTop;
                boxTop = -pos.y;
                break;
            case RS::VAlignBottom:
                flags|=Qt::AlignBottom;
                boxTop = -pos.y-boxHeight;
                break;
            }

            switch (text.getHAlign()) {
            case RS::HAlignLeft:
                flags|=Qt::AlignLeft;
                boxLeft = pos.x;
                break;
            case RS::HAlignCenter:
                flags|=Qt::AlignHCenter;
                boxLeft = pos.x-boxWidth/2;
                break;
            case RS::HAlignRight:
                flags|=Qt::AlignRight;
                boxLeft = pos.x-boxWidth;
                break;
            }

            QRectF box(boxLeft, boxTop, boxWidth,boxHeight);

            QTransform t;
            t.scale(1,-1);
            QTransform savedTransform2 = painter->transform();
            painter->setTransform(t, true);
            painter->drawText(box, flags, text.getText());
            painter->setTransform(savedTransform2);
        }
    }

    painter->setTransform(savedTransform);
}

void RGraphicsViewImage::clearOverlay(int overlayId) {
    if (overlayDrawables.contains(overlayId)) {
        overlayDrawables[overlayId].clear();
    }
}

void RGraphicsViewImage::clearOverlay(int overlayId, RObject::Id objectId) {
    if (overlayDrawables.contains(overlayId)) {
        if (overlayDrawables[overlayId].contains(objectId)) {
            overlayDrawables[overlayId].remove(objectId);
        }
    }
}

void RGraphicsViewImage::addToOverlay(int overlayId, RObject::Id objectId, const RGraphicsSceneDrawable& drawable) {
    if (!overlayDrawables.contains(overlayId)) {
        QMap<RObject::Id, QList<RGraphicsSceneDrawable> > map;
        map.insert(objectId, QList<RGraphicsSceneDrawable>());
    }
    if (!overlayDrawables[overlayId].contains(objectId)) {
        overlayDrawables[overlayId].insert(objectId, QList<RGraphicsSceneDrawable>());
    }

    overlayDrawables[overlayId][objectId].append(drawable);
}

void RGraphicsViewImage::paintOverlay(QPainter* painter) {
    QList<int> overlayIds = overlayDrawables.keys();
    //qSort(overlayIds);

    // iterate through all maps (each map represents an overlay):
    for (int n=0; n<overlayIds.length(); n++) {
        int overlayId = overlayIds[n];

        // iterate through object Ids for this overlay:
        QList<RObject::Id> objIds = overlayDrawables[overlayId].keys();
        for (int c=0; c<objIds.length(); c++) {
            RObject::Id objId = objIds[c];

            // iterate through list of drawables for this object:
            for (int i=0; i<overlayDrawables[overlayId][objId].length(); i++) {

                RGraphicsSceneDrawable drawable = overlayDrawables[overlayId][objId].at(i);
                if (drawable.getType()==RGraphicsSceneDrawable::PainterPath) {
                    RPainterPath path = drawable.getPainterPath();

                    //RVector sp = path.getBoundingBox().getCenter();
                    //path.move(-sp);
                    if (drawable.getPixelUnit() || path.getPixelUnit()) {
                        if (!isPrinting() && !isPrintPreview()) {
                            path.scale(1/factor,1/factor);
                        }
                        else {
                            double f = RUnit::convert(0.22, RS::Millimeter, getDocument()->getUnit());
                            f/=getDevicePixelRatio();
                            path.scale(f,f);
                        }
                    }
                    path.move(drawable.getOffset());
                    path.move(paintOffset);

                    QPen pen = path.getPen();
                    if (path.getPixelWidth()) {
                        pen.setWidthF(pen.widthF() / factor);
                    }

                    painter->setPen(pen);
                    painter->setBrush(path.getBrush());
                    painter->drawPath(path);
                }

                else if (drawable.getType()==RGraphicsSceneDrawable::Text) {
                    RTextBasedData text = drawable.getText();

                    if (drawable.getPixelUnit()) {
                        //text.scale(RVector(1/factor,1/factor), text.getAlignmentPoint());
                        text.scale(RVector(1/factor,1/factor), RVector(0,0));
                    }

                    text.move(drawable.getOffset());
                    text.move(paintOffset);

                    paintText(painter, text);
                }
                //painter->setPen(path.getPen());
                //painter->setBrush(path.getBrush());
                //painter->drawPath(path);
            }
        }
    }
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
    painterThread.clear();
    painterThread.append(painter);
    entityTransformThread.clear();
    entityTransformThread.append(QStack<RTransform>());

    paintEntitiesMulti(queryBox);
}

void RGraphicsViewImage::paintEntitiesMulti(const RBox& queryBox) {
    RDocument* document = getDocument();
    if (document==NULL) {
        return;
    }

    colorCorrection = RSettings::getColorCorrection();
    colorCorrectionDisableForPrinting = RSettings::getColorCorrectionDisableForPrinting();
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

    //RDebug::startTimer(60);
    //mutexSi.lock();
    QSet<REntity::Id> ids;
    ids = document->queryIntersectedEntitiesXYFast(qb);
    //qDebug() << "RGraphicsViewImage::paintEntities: ids: " << ids;
    //mutexSi.unlock();
    //RDebug::stopTimer(60, "spatial index");

    // draw painter paths:
    isSelected = false;

    //RDebug::startTimer(60);
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
    //QList<REntity::Id> list = ids.toList();
    //RDebug::stopTimer(60, "ordering");

    //RDebug::startTimer();

    if (isPrintingOrExporting()) {
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

    double ps = mapDistanceFromView(1.0);
    // ideal pixel size for rendering arc at current zoom level:
    if (isPrintingOrExporting()) {
        ps = getScene()->getPixelSizeHint();
    }

    // regen arcs, xlines, rays, block references if necessary:
    for (int i=0; i<list.length(); i++) {
        REntity::Id id = list[i];

        // get drawables of the given entity:
        QList<RGraphicsSceneDrawable>* drawables = sceneQt->getDrawables(id);

        // before multi threading:
        // if at least one arc path is too detailed or not detailed enough,
        // or the path is an XLine or Ray, regen:

        // do we need to regen the path?
        bool regen = false;
        if (drawables==NULL || drawables->isEmpty()) {
            // entity was last outside visible area, needs regen to reappear:
            regen = true;
        }
        else {
            for (int p=0; p<drawables->size() && !regen; p++) {
                RGraphicsSceneDrawable& drawable = drawables->operator[](p);

                if (drawable.isPainterPath()) {
                    if (drawable.getPainterPath().getAlwaysRegen()==true) {
                        regen = true;
                    }
                    else if (drawable.getPainterPath().getAutoRegen()==true) {
                        double psh = drawable.getPainterPath().getPixelSizeHint();
                        if (psh>RS::PointTolerance && (psh<ps/5 || psh>ps*5)) {
                            regen = true;
                        }
                    }
                }
            }
        }

        // regenerate arc, xline, block reference, etc.:
        if (regen) {
            sceneQt->exportEntity(id, true);
        }
    }

    Q_ASSERT(painterThread.length()==entityTransformThread.length());

    //RDebug::startTimer(100);
    //qDebug() << "list.length():" << list.length();
    int slice = int(floor(double(list.length())/painterThread.length()));
    QList<QFuture<void> > futureThread;
    for (int threadId=0; threadId<painterThread.length(); threadId++) {
        int start = threadId*slice;
        int end = (threadId+1)*slice;
        if (threadId==painterThread.length()-1) {
            end = list.length();
        }
        //qDebug() << "slice:" << start << end;
        futureThread.append(QtConcurrent::run(this, &RGraphicsViewImage::paintEntitiesThread, threadId, list, start, end));
    }
    //RDebug::stopTimer(100, "launch threads");

    //RDebug::startTimer(100);
    for (int i=0; i<futureThread.length(); i++) {
        futureThread[i].waitForFinished();
    }
    //RDebug::stopTimer(100, "waitForFinished");
}

void RGraphicsViewImage::paintEntitiesThread(int threadId, QList<REntity::Id>& list, int start, int end) {
    for (int i=start; i<end; i++) {
        paintEntityThread(threadId, list[i]);
    }
}

void RGraphicsViewImage::paintEntityThread(int threadId, REntity::Id id, bool preview) {
    if (!preview && !isPrintingOrExporting() && !isSelected && (getDocument()->isSelected(id) || getDocument()->isSelectedWorkingSet(id))) {
        static QMutex m;
        m.lock();
        // remember selected entities to overlay in the end:
        selectedIds.insert(id);
        m.unlock();
        return;
    }

    Q_ASSERT(threadId<painterThread.length());
    Q_ASSERT(threadId<entityTransformThread.length());

    QPainter* painter = painterThread[threadId];

    // clipping:
    RBox clipRectangle = sceneQt->getClipRectangle(id, preview);
    if (clipRectangle.isValid()) {
        clipRectangle.move(paintOffset);
        painter->setClipRect(QRectF(clipRectangle.getMinimum().x, clipRectangle.getMinimum().y, clipRectangle.getWidth(), clipRectangle.getHeight()));
    }
    else {
        painter->setClipping(false);
    }

    // paint image for raster image entity:
//    if (sceneQt->hasImageFor(id)) {
//        QList<RImageData> images = sceneQt->getImages(id);
//        for (int i=0; i<images.length(); i++) {
//            images[i].move(paintOffset);
//            paintImage(painter, images[i]);
//        }
//    }

    // paint text for text layout based entity:
//    QList<RTextBasedData> texts;
//    if (preview) {
//        // preview text:
//        //TODO if (sceneQt->hasPreviewTextsFor(id)) {
//            texts = sceneQt->getPreviewTexts(id);
//        //}
//    }
//    else {
//        if (sceneQt->hasTextsFor(id)) {
//            texts = sceneQt->getTexts(id);
//        }
//    }
//    for (int k=0; k<texts.length(); k++) {
//        texts[k].move(paintOffset);
//        //qDebug() << texts[k].getDrawOrder();
//        paintText(painter, texts[k]);
//    }

    // get drawables for vector graphics entity:
    QList<RGraphicsSceneDrawable>* drawables;
    if (preview) {
        // get drawables of the current preview:
        drawables = sceneQt->getPreviewDrawables(id);
    } else {
        // get drawables of the given entity:
        drawables = sceneQt->getDrawables(id);

//        // TODO: move to part before multi threading:
//        // if at least one arc path is too detailed or not detailed enough,
//        // or the path is an XLine or Ray, regen:

//        // ideal pixel size for rendering arc at current zoom level:
//        double ps = mapDistanceFromView(1.0);
//        if (isPrintingOrExporting()) {
//            ps = getScene()->getPixelSizeHint();
//        }

//        // do we need to regen the path?
//        bool regen = false;

//        for (int p=0; p<drawables.size(); p++) {
//            if (drawables.at(p).getType()==RGraphicsSceneDrawable::PainterPath) {
//                if (drawables.at(p).getPainterPath().getAlwaysRegen()==true) {
//                    regen = true;
//                    break;
//                }
//                if (drawables.at(p).getPainterPath().getAutoRegen()==true) {
//                    if (drawables.at(p).getPainterPath().getPixelSizeHint()>RS::PointTolerance &&
//                            (drawables.at(p).getPainterPath().getPixelSizeHint()<ps/5 || drawables.at(p).getPainterPath().getPixelSizeHint()>ps*5)) {

//                        regen = true;
//                        break;
//                    }
//                }
//            }
//        }

//        // regen:
//        if (regen) {
//            // TODO: breaks multithreading:
//            //sceneQt->exportEntity(id, true);
//            //drawables = sceneQt->getDrawables(id);
//        }
    }

    if (drawables==NULL) {
        return;
    }

    // paint drawables (painter paths, texts, images):
    QListIterator<RGraphicsSceneDrawable> i(*drawables);
    while (i.hasNext()) {
        RGraphicsSceneDrawable drawable = i.next();

        // drawable is not plottable (from layer for which plottable is off):
        if (drawable.getNoPlot() && (isPrinting() || (showOnlyPlottable && isPrintPreview()))) {
            continue;
        }

        bool workingSet = true;
        if (!isPrintingOrExporting() && !preview) {
            RDocument* doc = getDocument();
            if (doc->isEditingWorkingSet()) {
                if (!drawable.isWorkingSet()) {
                    // fade out entities not in working set:
                    workingSet = false;
                }
            }
        }

        // image:
        if (drawable.isImage()) {
            if (clipRectangle.isValid()) {
                // re-enable clipping for image if a path switched it off:
                painter->setClipping(true);
            }
            RImageData image = drawable.getImage();
            image.move(drawable.getOffset());

            if (entityTransformThread[threadId].isEmpty()) {
                image.move(paintOffset);
            }
            else {
                // transform (image in block reference):
                painter->save();
                for (int k=0; k<entityTransformThread[threadId].size(); k++) {
                    if (k==0) {
                        // paintOffset must be applied here to get the correct placement for
                        // texts with non-uniform scale:
                        QTransform tt;
                        tt.translate(paintOffset.x, paintOffset.y);
                        painter->setTransform(tt, true);
                    }

                    RTransform t = entityTransformThread[threadId][k];
                    painter->setTransform(t, true);
                }
            }

            paintImage(painter, image, workingSet);

            if (!entityTransformThread[threadId].isEmpty()) {
                painter->restore();
            }
        }

        // TTF text block (CAD text block is painter path):
        else if (drawable.isText()) {
            RTextBasedData text = drawable.getText();

            if (drawable.getPixelUnit()) {
                text.scale(RVector(1/factor,1/factor), text.getAlignmentPoint());
            }

            text.move(drawable.getOffset());

            if (entityTransformThread[threadId].isEmpty()) {
                text.move(paintOffset);
            }
            else {
//                RVector p = text.getPosition();
//                RVector ap = text.getAlignmentPoint();
//                RVector anglePoint = ap + RVector::createPolar(1.0, text.getAngle());
//                bool readable = RMath::isAngleReadable(text.getAngle());
//                text.update();
//                RVector centerPoint = text.getBoundingBox().getCenter();
//                qDebug() << "centerPoint before:" << centerPoint;

                // transform (text in block reference):
                painter->save();
                for (int k=0; k<entityTransformThread[threadId].size(); k++) {
                    if (k==0) {
                        // paintOffset must be applied here to get the correct placement for
                        // texts with non-uniform scale:

                        QTransform tt;
                        tt.translate(paintOffset.x, paintOffset.y);

                        //text.move(paintOffset);
                        painter->setTransform(tt, true);
//                        p.transform2D(tt);
//                        ap.transform2D(tt);
//                        anglePoint.transform2D(tt);
//                        centerPoint.transform2D(tt);
                    }

                    RTransform t = entityTransformThread[threadId][k];
//                    QList<RTransformOp> ops = t.getOps();
//                    for (int n=ops.length()-1; n>=0; n--) {
//                        RTransformOp op = ops[n];
//                        if (op.type==RTransformOp::Translation) {
//                            text.move(RVector(op.d1, op.d2));
//                        }
//                        else if (op.type==RTransformOp::Scale) {
//                            text.scale(RVector(op.d1, op.d2), RVector(0,0));
//                        }
//                        else if (op.type==RTransformOp::Rotation) {
//                            text.rotate(op.d1, RVector(0,0));
//                        }
//                    }

//                    p.transform2D(t);
//                    ap.transform2D(t);
//                    anglePoint.transform2D(t);
//                    centerPoint.transform2D(t);
                    painter->setTransform(t, true);

                    //qDebug() << "m11:" << t.m11();
                    //qDebug() << "m22:" << t.m22();
                }

//                text.setPosition(p);
//                text.setAlignmentPoint(ap);

//                text.update();

//                qDebug() << "centerPoint after:" << centerPoint;
//                qDebug() << "text center after:" << text.getBoundingBox().getCenter();
//                qDebug() << "d:" << text.getBoundingBox().getCenter().getDistanceTo(centerPoint);

//                bool corr = false;
//                double angle = RMath::makeAngleReadable(ap.getAngleTo(anglePoint), readable, &corr);
//                text.setAngle(angle);

                // TODO: fix alignment and angle of text to make readable:

//                if (text.getBoundingBox().getCenter().getDistanceTo(centerPoint)>0.1) {
//                    bool corr = false;
//                    double angle = RMath::makeAngleReadable(ap.getAngleTo(anglePoint), readable, &corr);
//                    text.setAngle(angle);

//                    if (corr) {
//                        if (text.getHAlign()==RS::HAlignLeft) {
//                            text.setHAlign(RS::HAlignRight);
//                        } else if (text.getHAlign()==RS::HAlignRight) {
//                            text.setHAlign(RS::HAlignLeft);
//                        }
//                    }
//                    else {
//                        if (text.getVAlign()==RS::VAlignTop) {
//                            text.setVAlign(RS::VAlignBase);
//                        } else if (text.getVAlign()==RS::VAlignBase) {
//                            text.setVAlign(RS::VAlignTop);
//                        }
//                    }
//                }
            }

            paintText(painter, text, workingSet);

            if (!entityTransformThread[threadId].isEmpty()) {
                painter->restore();
            }
        }

        // Transform:
        else if (drawable.getType()==RGraphicsSceneDrawable::Transform) {
            RTransform transform = drawable.getTransform();
            entityTransformThread[threadId].push(transform);
        }

        else if (drawable.getType()==RGraphicsSceneDrawable::EndTransform) {
            if (!entityTransformThread[threadId].isEmpty()) {
                entityTransformThread[threadId].pop();
            }
            else {
                qWarning() << "pop transform: stack empty";
            }
        }

        // unknown drawable or already handled (image, text, transform, end transform):
        if (!drawable.isPainterPath()) {
            continue;
        }

        // painter path:
        RPainterPath path = drawable.getPainterPath();
        if (!path.isSane()) {
            continue;
        }

        // local transform of entity (e.g. block reference transforms):
        if (!entityTransformThread[threadId].isEmpty()) {
            for (int k=entityTransformThread[threadId].size()-1; k>=0; k--) {
                path.transform(entityTransformThread[threadId][k]);
            }
        }

        if (drawable.getPixelUnit() || path.getPixelUnit()) {
            // path is displayed in pixels, not drawing unit:
            //RVector sp = path.getStartPoint();
            RVector sp = path.getBoundingBox().getCenter();
            path.move(-sp);
            path.scale(1/factor,1/factor);
            path.move(sp);
        }

        path.move(drawable.getOffset());
        path.move(paintOffset);
        RBox pathBB = path.getBoundingBox();

        // additional bounding box check for painter paths that are
        // part of one block reference entity:
        if (!isPrintingOrExporting() && !clipBox.intersects(pathBB)) {
            continue;
        }

        // small texts might be invisible while their bounding box is displayed:
        if (!isPathVisible(path)) {
            continue;
        }

        // individual paths might disable clipping:
        if (clipRectangle.isValid()) {
            painter->setClipping(!path.getNoClipping());
        }

        QPen pen = path.getPen();
        QBrush brush = path.getBrush();

        if (pen.style() != Qt::NoPen) {
            if (path.getPixelWidth()) {
                // use width of path pen
                pen.setWidthF(pen.widthF() / getFactor());
            }
            else if (isPrinting()) {
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

            // hairline minimum mode:
            // ensure a line weight of at least 1 device pixel (e.g. bitmap export):
            if (hairlineMinimumMode && pen.widthF()*getFactor()<1.0) {
                pen.setWidth(0);
            }
        }

        // prevent black on black / white on white drawing
        applyColorCorrection(pen);
        applyColorCorrection(brush);

        // apply minimum line weight:
        applyMinimumLineweight(pen);

        // highlighted:
        if (!isPrintingOrExporting() && path.isHighlighted()) {
            if (pen.style() != Qt::NoPen) {
                pen.setColor(RColor::getHighlighted(pen.color(), QColor((QRgb)bgColorLightness), 100));
            }
            if (brush.style() != Qt::NoBrush) {
                RColor ch = RColor::getHighlighted(brush.color(), QColor((QRgb)bgColorLightness), 100);
                ch.setAlpha(128);
                brush.setColor(ch);
            }
        }

        if (!workingSet) {
            if (!path.isSelected()) {
                if (pen.style() != Qt::NoPen) {
                    // fade out entities not in working set:
                    pen.setColor(RColor::getFaded(pen.color(), getBackgroundColor(), RSettings::getFadingFactor()));
                }
                if (brush.style() != Qt::NoBrush) {
                    brush.setColor(RColor::getFaded(brush.color(), getBackgroundColor(), RSettings::getFadingFactor()));
                }
            }
        }

        if (!path.getNoColorMode()) {
            applyColorMode(pen);
            applyColorMode(brush);
        }

        painter->setBrush(brush);
        painter->setPen(pen);

        if (scene->getDraftMode() || isPrintingOrExporting() /*|| clipBox.contains(pathBB)*/) {
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

                QLineF qLine(QPointF(line.startPoint.x, line.startPoint.y),
                             QPointF(line.endPoint.x, line.endPoint.y));

                if (line.startPoint.equalsFuzzy(line.endPoint, 1e-5)) {
                    // draw zero length line as one pixel long line:
                    double d = mapDistanceFromView(1.0);
                    qLine.setP2(QPointF(line.endPoint.x + d, line.endPoint.y));
                }
                if (line.isValid()) {
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
                    qreal x=0.0;
                    qreal y=0.0;
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
                                if (line.startPoint.equalsFuzzy(line.endPoint, 1e-5)) {
                                    // draw zero length line as one pixel long line:
                                    double d = mapDistanceFromView(1.0);
                                    qLine.setP2(QPointF(line.endPoint.x + d, line.endPoint.y));
                                }
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
            if (path.getSimplePointDisplay()) {
                double ps = getScene()->getPixelSizeHint();
                // simple point mode for hatch patterns:
                // force point display as points:
                QList<RVector> points = path.getPoints();
                QList<RVector>::iterator it;
                for (it=points.begin(); it<points.end(); it++) {
                    RVector p = *it;

                    // draws lines at higher zoom levels:
                    //drawDot(painter, QPointF(p.x, p.y));

                    painter->drawLine(QLineF(p.x, p.y, p.x + ps, p.y));
                }
                continue;
            }

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
                // This also applies when exporting (e.g. to bitmap):
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
                RVector p = *it;
                //int rslt = pMode & 7;
                if (rslt7 == 0) {
                    drawDot(painter, QPointF(p.x, p.y));
                } else if (rslt7 == 2) {
                    drawPlus(painter, QPointF(p.x, p.y), pSize);
                } else if (rslt7 == 3) {
                    drawEx(painter, QPointF(p.x, p.y), pSize);
                } else if (rslt7 == 4) {
                    drawVBar(painter, QPointF(p.x, p.y), pSize);
                }
                //rslt = pMode & 32;
                if (rslt32 == 32) {
                    drawCircle(painter, QPointF(p.x, p.y), pSize);
                }
                //rslt = pMode & 64;
                if (rslt64 == 64) {
                    drawSquare(painter, QPointF(p.x, p.y), pSize);
                }
            }
        }
    }
}

QList<RPainterPath> RGraphicsViewImage::getTextLayoutsPainterPaths(const RTextBasedData& text, const QList<RTextLayout>& textLayouts) {
    Q_UNUSED(text)
    QList<RPainterPath> ret;

    for (int t=0; t<textLayouts.length(); t++) {
        for (int k=0; k<textLayouts[t].painterPaths.length(); k++) {
            RPainterPath pp = textLayouts[t].painterPaths[k];
            pp.transform(textLayouts[t].transform);
            ret.append(pp);
        }
    }

    return ret;
}

void RGraphicsViewImage::applyMinimumLineweight(QPen& pen) {
    if (minimumLineweight>1.0e-6 && pen.widthF()<minimumLineweight) {
        pen.setWidthF(minimumLineweight);
    }
    if (maximumLineweight>-0.1 && pen.widthF()>maximumLineweight) {
        pen.setWidthF(maximumLineweight);
    }
}

void RGraphicsViewImage::applyColorCorrection(QPen& pen) {
    if (colorCorrectionDisableForPrinting && (printing || printPreview)) {
        return;
    }

    bool colCorr = colorCorrection;
    if (colorCorrectionOverride!=-1) {
        colCorr = (colorCorrectionOverride!=0);
    }

    if (colCorr) {
        if (pen.color().lightness() <= colorThreshold && bgColorLightness <= colorThreshold) {
            pen.setColor(Qt::white);
        } else if (pen.color().lightness() >= 255-colorThreshold && bgColorLightness >= 255-colorThreshold) {
            pen.setColor(Qt::black);
        }
    }
}

void RGraphicsViewImage::applyColorCorrection(QBrush& brush) {
    if (colorCorrectionDisableForPrinting && (printing || printPreview)) {
        return;
    }

    bool colCorr = colorCorrection;
    if (colorCorrectionOverride!=-1) {
        colCorr = (colorCorrectionOverride!=0);
    }

    if (colCorr) {
        if (brush.color().lightness() <= colorThreshold && bgColorLightness <= colorThreshold) {
            brush.setColor(Qt::white);
        } else if (brush.color().lightness() >= 255-colorThreshold && bgColorLightness >= 255-colorThreshold) {
            brush.setColor(Qt::black);
        }
    }
}

void RGraphicsViewImage::applyColorMode(QPen& pen) {
    // color modes (b/w, grayscale):
    // TODO: move as much as possible to generation of painter paths:
    switch (colorMode) {
    case RGraphicsView::BlackWhite:
        // dark background: everything white:
        if (bgColorLightness < 64 && !isPrinting()) {
            if (pen.style() != Qt::NoPen) {
                pen.setColor(Qt::white);
            }
        }
        // bright background or printing: everything black:
        else {
            if (pen.style() != Qt::NoPen) {
                pen.setColor(Qt::black);
            }
        }
        break;
    case RGraphicsView::GrayScale:
        if (pen.style() != Qt::NoPen) {
            int v = qGray(pen.color().rgb());
            pen.setColor(QColor(v, v, v));
        }
        break;
    default:
        break;
    }
}

void RGraphicsViewImage::applyColorMode(QBrush& brush) {
    // color modes (b/w, grayscale):
    // TODO: move as much as possible to generation of painter paths:
    switch (colorMode) {
    case RGraphicsView::BlackWhite:
        // dark background: everything white:
        if (bgColorLightness < 64 && !isPrinting()) {
            if (brush.style() != Qt::NoBrush) {
                brush.setColor(Qt::white);
            }
        }
        // bright background: everything black:
        else {
            if (brush.style() != Qt::NoBrush) {
                brush.setColor(Qt::black);
            }
        }
        break;
    case RGraphicsView::GrayScale:
        if (brush.style() != Qt::NoBrush) {
            int v = qGray(brush.color().rgb());
            brush.setColor(QColor(v, v, v));
        }
        break;
    default:
        break;
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
        RDocument* doc = getDocument();
        r = RUnit::convert(doc->getVariable("PageSettings/PointSize", 0.5, true).toDouble()/2.0, RS::Millimeter, doc->getUnit());
    } else {
        // screen rendering / (bitmap) exporting
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

void RGraphicsViewImage::paintImage(QPainter* painter, RImageData& image, bool workingSet) {
    if (scene==NULL) {
        return;
    }

    if (!scene->getDraftMode()) {
        if (image.getFade()==100) {
            // 100% transparent:
            return;
        }
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
        double opacity = 1.0;
        if (image.getFade()>0 && image.getFade()<100) {
            opacity = 1.0 - ((double)image.getFade()/100);
        }
        if (!workingSet) {
            opacity *= 0.5;
        }
        painter->setOpacity(opacity);
        painter->drawImage(0,-qImage.height(), qImage);
        painter->setOpacity(1.0);
        painter->restore();
    }

    // draw image in draft mode / selected mode (border in black or white):
    if (scene->getDraftMode() || image.isSelected()) {
        if (image.isSelected()) {
            painter->setPen(QPen(QBrush(RSettings::getSelectionColor()), 0));
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

void RGraphicsViewImage::paintText(QPainter* painter, RTextBasedData& text, bool workingSet) {
    if (scene==NULL) {
        return;
    }

    //RDebug::startTimer(0);

#ifdef Q_OS_LINUX
    // linux text rendering bug (tiny text displayed very large):
    if (text.getTextHeight()*factor<0.05) {
        return;
    }
#endif

    if (isPrintingOrExporting()) {
        text.update(true);
    }
    QList<RTextLayout> textLayouts = text.getTextLayouts();

    for (int i=0; i<textLayouts.length(); i++) {
        RTextLayout& textLayout = textLayouts[i];
        QTransform t = textLayout.transform;
        //double h = text.getTextHeight();

        // CAD font text block:
//        if (textLayout.layout.isNull()) {
             // painter paths:
//            QList<RPainterPath> pps = textLayout.painterPaths;
//            for (int k=0; k<pps.length(); k++) {
//                if (pps[k].getFeatureSize()<0) {
//                    continue;
//                }
//                pps[k].transform(t);
//                QPen pen = pps[k].getPen();
//                //qDebug() << "pen: " << pps[k].getPen();
//                //qDebug() << "brush: " << pps[k].getBrush();
//                pen.setCapStyle(Qt::RoundCap);
//                pen.setJoinStyle(Qt::RoundJoin);
//                pen.setWidthF(text.getLineweight()/100.0);
//                if (text.isSelected()) {
//                    pen.setColor(RSettings::getSelectionColor());
//                }
//                painter->setPen(pen);
//                painter->setBrush(Qt::NoBrush);
//                painter->drawPath(pps[k]);
//            }
//        }

        // TTF font text block:
//        else {
        if (!textLayout.layout.isNull()) {
            painter->save();
            painter->setTransform(t, true);

            QTextOption o;
            if (text.isSelected()) {
                o.setFlags(QTextOption::SuppressColors);
                painter->setPen(QPen(RSettings::getSelectionColor()));
            }
            else {
                o.setFlags(QTextOption::SuppressColors);
                //painter->setPen(QPen(QString("#%1%10000").arg(255-i*10, 0, 16)));
                //painter->setPen(QPen("red"));
                //if (textLayout.color==RColor::CompatByLayer) {
                //    painter->setPen(QPen(text.getLayerId()));
                //}
                //painter->setPen(QPen(textLayout.color));
                //QPen pen(text.getColor());
                QColor col = textLayout.color;
                QPen pen;
                if (col.isValid() && col!=RColor::CompatByLayer && col!=RColor::CompatByBlock) {
                    pen.setColor(col);
                }
                else {
                    pen.setColor(text.getColor());
                }
                applyColorCorrection(pen);
                applyColorMode(pen);

                if (!isPrintingOrExporting()) {
                    if (text.isHighlighted()) {
                        pen.setColor(RColor::getHighlighted(pen.color(), bgColorLightness, 100));
                    }

                    if (!workingSet) {
                        // fade out entities not in working set:
                        pen.setColor(RColor::getFaded(pen.color(), getBackgroundColor(), RSettings::getFadingFactor()));
                    }
                }

                painter->setPen(pen);
            }
            textLayout.layout->setTextOption(o);

            // TODO: should be reentrant but crashes if not locked:
            {
                RTextRenderer::lockForDrawing();
                textLayout.layout->draw(painter, QPoint(0,0));
                RTextRenderer::unlockForDrawing();
            }

            painter->restore();
        }

    }
    //RDebug::stopTimer(0, "draw layouts");
}


int RGraphicsViewImage::getWidth() const {
    if (graphicsBufferThread.isEmpty()) {
        return 100;
    }
    return graphicsBufferThread.first().width();
}

int RGraphicsViewImage::getHeight() const {
    if (graphicsBufferThread.isEmpty()) {
        return 100;
    }
    return graphicsBufferThread.first().height();
}

void RGraphicsViewImage::resizeImage(int w, int h) {
    //graphicsBuffer = QImage(QSize(w,h), alphaEnabled ? QImage::Format_ARGB32 : QImage::Format_RGB32);

    for (int i=0; i<graphicsBufferThread.length(); i++) {
        if (i==0) {
            graphicsBufferThread[i] = QImage(QSize(w,h), alphaEnabled ? QImage::Format_ARGB32 : QImage::Format_RGB32);
        }
        else {
            graphicsBufferThread[i] = QImage(QSize(w,h), QImage::Format_ARGB32);
        }
    }
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
