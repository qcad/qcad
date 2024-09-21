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
#include "RGraphicsScene.h"
#include "RGraphicsSceneQt.h"
#include "RGraphicsViewQt.h"
#include "RGraphicsViewImage.h"
#include "RGraphicsViewWorkerPainter.h"
#include "RLine.h"
#include "RSettings.h"
#include "RSnap.h"
#include "RSnapRestriction.h"
#include "RTextRenderer.h"
#include "RUnit.h"


RGraphicsViewImage::RGraphicsViewImage(QObject* parent)
    : QObject(parent), RGraphicsView(),
      numThreads(1),
      panOptimization(false),
      sceneQt(NULL),
      lastSize(0,0),
      lastOffset(RVector::invalid),
      lastFactor(-1.0),
      painter(NULL),
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
      showOnlyPlottable(false),
      decorationWorker(NULL) {

    currentScale = 1.0;
    saveViewport();
    graphicsBufferNeedsUpdate = true;
}

RGraphicsViewImage::~RGraphicsViewImage() {
    //qDebug() << "RGraphicsViewImage::~RGraphicsViewImage()";

    if (decorationWorker!=NULL) {
        delete decorationWorker;
    }
}

void RGraphicsViewImage::setNumThreads(int n) {
    if (n!=numThreads) {
        numThreads = n;
        //graphicsBufferThread.clear();
        //initWorkers();
        lastSize = QSize(0,0);
    }
}

void RGraphicsViewImage::clear() {
#ifdef RFUTURE
    for (int i=0; i<workers.length(); i++) {
        RGraphicsViewWorker* worker = workers[i];
        worker->clear();
    }
#endif

//    for (int i=0; i<graphicsBufferThread.length(); i++) {
//        QPainter painter(&graphicsBufferThread[i]);
//        // erase background to transparent:
//        painter.setCompositionMode(QPainter::CompositionMode_Clear);
//        painter.eraseRect(graphicsBufferThread[i].rect());
//    }
}

void RGraphicsViewImage::setCursor(Qt::CursorShape cursorShape) {
    if (widget!=NULL) {
        widget->setCursor(QCursor(cursorShape));
    }
}

void RGraphicsViewImage::setCursor(const QCursor& cursor) {
    if (widget!=NULL) {
        widget->setCursor(cursor);
    }
}

QCursor RGraphicsViewImage::getCursor() {
    if (widget!=NULL) {
        return widget->cursor();
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

    if (widget!=NULL) {
        // this calls updateImage:
        widget->update();
    }
}

/**
 * Triggers a paintEvent based on a buffered offscreen bitmap (very fast).
 */
void RGraphicsViewImage::repaintView() {
    if (widget!=NULL) {
        // this should call updateBitmap:
        widget->update();
    }
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
        // TODO: check if buffer is not updated unnecessarily:
        //RDebug::startTimer();

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
        initWorkers();
        //RDebug::stopTimer("initWorkers");

        //RDebug::startTimer();
        if (!workers.isEmpty()) {
            // fill first worker (bottom buffer) with background color:
            //paintErase(workers.first());

            // start painting (required e.g. for QPainter)
            for (int i=0; i<workers.length(); i++) {
                RGraphicsViewWorker* worker = workers[i];
                worker->begin();

                if (antialiasing) {
                    // must happen after begin as begin resets all settings:
                    worker->setAntialiasing(true);
                }
            }

            //paintErase(graphicsBuffer2);
            bool originBelowEntities = RSettings::getShowLargeOriginAxis();
            if (originBelowEntities) {
                paintOrigin(workers.first());
            }

            //RDebug::startTimer(700);
            paintDocument();
            //RDebug::stopTimer(700, "paintDocument");

            workers.last()->setClipping(false);

            if (gridVisible) {
                paintMetaGrid(workers.last());
                paintGrid(workers.last());
            }

            if (!originBelowEntities) {
                paintOrigin(workers.last());
            }

            // end paiting (required e.g. for QPainter)
            for (int i=0; i<workers.length(); i++) {
                RGraphicsViewWorker* worker = workers[i];
                worker->end();
            }
        }
        lastOffset = offset;
        lastFactor = factor;

        //qDebug() << "updateImage: OK";
        //RDebug::stopTimer("updateImage");

        //RDebug::startTimer();
        if (!workers.isEmpty()) {
            // first thread buffer has background color + first set of entities:
            graphicsBuffer = workers[0]->getImage();

            // merge buffers from all threads (transparent backgrounds):
            if (workers.length()>1) {
                QPainter p(&graphicsBuffer);
                p.setCompositionMode(QPainter::CompositionMode_SourceOver);
                for (int i=1; i<workers.length(); i++) {
                    p.drawImage(0, 0, workers[i]->getImage());
                }
            }
        }
        //RDebug::stopTimer("compose");

        // graphics buffer with drawing is now up to date:
        graphicsBufferNeedsUpdate = false;

    }


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

    //RDebug::startTimer(77);
    // compose the final buffer with preview, selection, highlights, etc.:
    graphicsBufferWithPreview = graphicsBuffer;
    //RDebug::stopTimer(77, "graphicsBufferWithPreview = graphicsBuffer");

    //RDebug::startTimer(77);
    decorationWorker->setImage(graphicsBufferWithPreview);
    //RDebug::stopTimer(77, "decorationWorker->setImage");
    decorationWorker->begin();
    if (antialiasing) {
        // must happen after begin as begin resets all settings:
        decorationWorker->setAntialiasing(true);
    }

    // draws the current preview on top of the buffer:
    // highlighted entities are also part of the preview
    // TODO: use worker for this, run in parallel

    //RDebug::startTimer(77);
    if (sceneQt->hasPreview()) {
        //initPainter(graphicsBufferWithPreview, false);

        //painterThread.clear();
        // TODO: add function RGraphicsViewImage:
        //painterThread.append(painter);
        //entityTransformThread.clear();
        //entityTransformThread.append(QStack<RTransform>());

        //bgColorLightness = getBackgroundColor().lightness();
        isSelected = false;
        QList<REntity::Id> ids = sceneQt->getPreviewEntityIds();
        for (int i=0; i<ids.length(); i++) {
            if (ids[i]!=REntity::INVALID_ID) {
                paintEntityThread(decorationWorker, ids[i], true);
            }
        }

        // anonymous previews (aux preview, etc.) on top of everything else:
        paintEntityThread(decorationWorker, REntity::INVALID_ID, true);

        //worker->end();
        // TODO: add function RGraphicsViewImage:
        //endPaint();
//        if (painter!=NULL) {
//            delete painter;
//        }
    }
    //RDebug::stopTimer(77, "preview");

    // painting the preview above might have enabled clipping
    // switch off clipping:
    decorationWorker->setClipping(false);

    //RDebug::startTimer(77);
    // paint reference points of selected entities:
    decorationWorker->save();
    QTransform t;
    decorationWorker->setTransform(t);
    QMap<REntity::Id, QList<RRefPoint> >& referencePoints = scene->getReferencePoints();
    if (getDocument()->countSelectedEntities()<RSettings::getMaxReferencePointEntitiesDisplay()) {
        //QPainter gbPainter(&graphicsBufferWithPreview);
        QMap<REntity::Id, QList<RRefPoint> >::iterator it;
        for (it = referencePoints.begin(); it != referencePoints.end(); ++it) {
            QList<RRefPoint>& list = it.value();
            for (int i=0; i<list.length(); i++) {
                RRefPoint p = list[i];
                RRefPoint pm = mapToView(p);
                pm.setFlags(p.getFlags());

                paintReferencePoint(decorationWorker, pm, false);
            }
        }
        //gbPainter.end();
    }
    // highlighting of closest reference point:
    if (scene->getHighlightedReferencePoint().isValid()) {
        RRefPoint p = scene->getHighlightedReferencePoint();
        RRefPoint pm = mapToView(p);
        //QPainter gbPainter(&graphicsBufferWithPreview);
        pm.setFlags(p.getFlags());
        paintReferencePoint(decorationWorker, pm, true);
        //gbPainter.end();
    }
    //RDebug::stopTimer(77, "ref points");

//    // overlay (painted after / on top of preview and highlighting):
//    if (!overlayDrawables.isEmpty()) {
//        //QPainter* painter = initPainter(graphicsBufferWithPreview, false);
//        //painter->setRenderHint(QPainter::Antialiasing);
//        paintOverlay(decorationWorker);
//        //painter->end();
//    }

    // snap label:
    //RDebug::startTimer(77);
    if (hasFocus() || this == di->getLastKnownViewWithFocus()) {
        if (di->getClickMode()==RAction::PickCoordinate) {
            RSnap* snap = di->getSnap();
            RSnapRestriction* snapRestriction = di->getSnapRestriction();

            // draw snap label:
            emitUpdateSnapInfo(snap, snapRestriction);

            // prevent snap to show "End" directly after snapping to grid:
            if (snap!=NULL) {
                snap->reset();
            }
            if (snapRestriction!=NULL) {
                snapRestriction->reset();
            }
        }
    }
    //RDebug::stopTimer(77, "snap label");


    // informational text labels:
    //RDebug::startTimer(77);
    for (int i=0; i<textLabels.size(); i++) {
        emitUpdateTextLabel(textLabels.at(i));
    }
    textLabels.clear();
    //RDebug::stopTimer(77, "info label");

    decorationWorker->restore();

    // cursor:
    //RDebug::startTimer(77);
    paintCursor(decorationWorker);
    //RDebug::stopTimer(77, "cursor");

    decorationWorker->save();
    decorationWorker->setTransform(t);

    // relative zero:
    //RDebug::startTimer(77);
    paintRelativeZero(decorationWorker);
    //RDebug::stopTimer(77, "rel zero");

    decorationWorker->restore();

    decorationWorker->end();

    //RDebug::startTimer(77);
    graphicsBufferWithPreview = decorationWorker->getImage();
    //RDebug::stopTimer(77, "graphicsBufferWithPreview = decorationWorker->getImage()");
}

void RGraphicsViewImage::paintReferencePoint(RGraphicsViewWorker* worker, const RRefPoint& pos, bool highlight) {
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
        worker->setPen(p);
        worker->drawLine(QLineF(pos.x-size/2, pos.y, pos.x+size/2, pos.y));
        worker->drawLine(QLineF(pos.x, pos.y-size/2, pos.x, pos.y+size/2));
    }
    else {
        if (pos.isCenter() || pos.isArrow()) {
            // center or arrow:
            // round:
            worker->setBrush(color);
            worker->drawEllipse(QRectF(pos.x - size/2, pos.y - size/2, size, size));
        }
        else {
            // other:
            // rectangle:
            //??
            worker->setBrush(color);
            worker->fillRect(QRectF(pos.x - size/2, pos.y - size/2, size, size), color);
        }

        if (backgroundColor.value()<128) {
            if (highlight) {
                worker->setPen(QPen(Qt::white));
            }
            else {
                if (pos.isSelected()) {
                    worker->setPen(QPen(Qt::red));
                }
                else {
                    worker->setPen(QPen(Qt::gray));
                }
            }
        }
        else {
            if (highlight) {
                worker->setPen(QPen(Qt::black));
            }
            else {
                if (pos.isSelected()) {
                    worker->setPen(QPen(Qt::red));
                }
                else {
                    worker->setPen(QPen(Qt::gray));
                }
            }
        }
        if (pos.isCenter() || pos.isArrow()) {
            worker->drawEllipse(QRectF(pos.x - size/2, pos.y - size/2, size, size));
        }
        else {
            worker->drawRect(QRectF(pos.x - size/2, pos.y - size/2, size, size));
        }
    }
}

void RGraphicsViewImage::paintErase(RGraphicsViewWorker* worker, const QRect& rect) {
    //qDebug() << "RGraphicsViewImage::paintErase: " << rect;
    QRect r = rect;
    if (rect.isNull()) {
        r = QRect(0,0,getWidth(),getHeight());
    }
//    qDebug() << "RGraphicsViewImage::paintErase: r: " << r;

//    RVector c1 = mapFromView(RVector(r.left(),r.top()));
//    RVector c2 = mapFromView(RVector(r.left() + r.width(),r.top() + r.height()));
//    QRectF rf(c1.x, c1.y, c2.x-c1.x, c2.y-c1.y);

    //initPainter(worker, false, false, rect);
    worker->setBackground(getBackgroundColor());
    if (!r.isNull()) {
        worker->setClipRect(r);
    }
    if (backgroundColor.alpha()==0) {
        //worker->setCompositionMode(QPainter::CompositionMode_Clear);
    }

    qDebug() << "bg: " << getBackgroundColor();

    //worker->eraseRect(rf);
    worker->eraseRect(r);

    //delete painter;
    //painter = NULL;
}

void RGraphicsViewImage::paintGrid(RGraphicsViewWorker* worker, const QRect& rect) {
    QRect r = rect;
    if (rect.isNull()) {
        r = QRect(0,0,getWidth(),getHeight());
    }

    RVector c1 = mapFromView(RVector(r.left(),r.top()));
    RVector c2 = mapFromView(RVector(r.left() + r.width(),r.top() + r.height()));
    QRectF rf(c1.x, c1.y, c2.x-c1.x, c2.y-c1.y);

    //initPainter(device, false, false, rect);
    bool a = worker->getAntialiasing();
    worker->setAntialiasing(false);
    if (!rect.isNull()) {
        worker->setClipRect(rf);
    }

    if (grid!=NULL) {
        QPen pen(RSettings::getGridColor());
        pen.setWidth(0);
        worker->setPen(pen);
        grid->paint();
    }

    worker->setAntialiasing(a);

//    delete painter;
//    painter = NULL;
}

void RGraphicsViewImage::paintGridPoint(const RVector& ucsPosition) {
    if (workers.isEmpty()) {
        qWarning("RGraphicsViewImage::paintGridPoint: no workers");
        return;
    }

    RGraphicsViewWorker* worker = workers.last();

    bool a = worker->getAntialiasing();
    worker->setAntialiasing(false);

    worker->drawPoint(QPointF(ucsPosition.x, ucsPosition.y));

    worker->setAntialiasing(a);
}

void RGraphicsViewImage::paintMetaGrid(RGraphicsViewWorker* worker, const QRect& rect) {
    QRect r = rect;
    if (rect.isNull()) {
        r = QRect(0,0,getWidth(),getHeight());
    }

    //initPainter(device, false, false, rect);
    worker->setBackground(getBackgroundColor());

    if (grid!=NULL) {
        worker->setPen(QPen(RSettings::getMetaGridColor(), 0, Qt::SolidLine));
//        painter->setPen(QPen(
//                RSettings::getColor("GraphicsViewColors/MetaGridColor", RColor(192,192,192,64)),
//                0, Qt::SolidLine));
        grid->paintMetaGrid();
    }

//    delete painter;
//    painter = NULL;
}

void RGraphicsViewImage::paintGridLine(const RLine& ucsPosition) {
    if (workers.isEmpty()) {
        qWarning("RGraphicsViewImage::paintGridLine: no workers");
        return;
    }

    RGraphicsViewWorker* worker = workers.last();

    worker->drawLine(
        QLineF(ucsPosition.startPoint.x, ucsPosition.startPoint.y, ucsPosition.endPoint.x, ucsPosition.endPoint.y)
    );
}

void RGraphicsViewImage::paintCursorLine(const RLine& ucsPosition) {
    if (decorationWorker==NULL) {
        qWarning("RGraphicsViewImage::paintCursorLine: worker is NULL");
        return;
    }

    bool a = decorationWorker->getAntialiasing();
    decorationWorker->setAntialiasing(false);

    QPen p = decorationWorker->getPen();
    int w = p.width();
    if (RSettings::getHighResolutionGraphicsView()) {
        p.setWidth(2);
        p.setCosmetic(true);
        decorationWorker->setPen(p);
    }

    decorationWorker->drawLine(
        QLineF(ucsPosition.startPoint.x, ucsPosition.startPoint.y, ucsPosition.endPoint.x, ucsPosition.endPoint.y)
        );

    decorationWorker->setAntialiasing(a);

    if (RSettings::getHighResolutionGraphicsView()) {
        p.setWidth(w);
        p.setCosmetic(false);
        decorationWorker->setPen(p);
    }
}

/**
 * Paints the absolute zero point (origin).
 */
void RGraphicsViewImage::paintOrigin(RGraphicsViewWorker* worker) {
    // bitmap export: paint origin if requested (e.g. dwg2bmp -origin)
    if (!doPaintOrigin || isPrinting()) {
        return;
    }

    //initPainter(device, false, false);

    QPen pen(RSettings::getOriginColor());
    pen.setWidth(0);

    if (RSettings::getShowLargeOriginAxis()) {
        RBox b = getBox();
        //pen.setStyle(Qt::DashDotDotLine);
        pen.setDashPattern(QVector<qreal>() << 9 << 3 << 3 << 3 << 3 << 3);
        //RVector z = mapToView(RVector(0,0));
        //pen.setDashOffset(-z.x);
        worker->setPen(pen);
        worker->drawLine(QLineF(b.c1.x, 0.0, b.c2.x, 0));
//        pen.setDashOffset(z.y);
//        painter->setPen(pen);
        worker->drawLine(QLineF(0.0, b.c1.y, 0.0, b.c2.y));
    }
    else {
        worker->setPen(pen);
        double r = mapDistanceFromView(20.0 * getDevicePixelRatio());
        worker->drawLine(QLineF(-r,0.0, r,0.0));
        worker->drawLine(QLineF(0.0,-r, 0.0,r));
    }

//    delete painter;
//    painter = NULL;
}

void RGraphicsViewImage::paintCursor(RGraphicsViewWorker* worker) {
    //qDebug() << "RGraphicsViewImage::paintCursor";

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
        crossHairColor = RSettings::getCrossHairColor();
    }
    else {
        crossHairColor = RSettings::getCrossHairColorInactive();
    }

    //initPainter(device, false, false);

    if (grid!=NULL) {
        worker->setPen(QPen(crossHairColor, 0, Qt::DashLine));
        grid->paintCursor(pos);
    }

//    delete painter;
//    painter = NULL;
}

void RGraphicsViewImage::paintRelativeZero(RGraphicsViewWorker* worker) {
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

    //QPainter painter(&device);
    worker->setBrush(QBrush());
    worker->setPen(
        QPen(RSettings::getColor("GraphicsViewColors/RelativeZeroColor", RColor(162,36,36)), 0)
    );
    worker->drawLine(QLineF(screenPos.x-r, screenPos.y, screenPos.x+r, screenPos.y));
    worker->drawLine(QLineF(screenPos.x, screenPos.y-r, screenPos.x, screenPos.y+r));
    worker->drawEllipse(QRectF(screenPos.x-r, screenPos.y-r, 2*r, 2*r));
    //worker->end();
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
void RGraphicsViewImage::initWorkers() {
    //qDebug() << "RGraphicsViewImage::initWorkers";

    // not the right number of workers, re-init workers:
    if (workers.length()!=numThreads) {
        for (int i=0; i<workers.length(); i++) {
            delete workers[i];
        }
        workers.clear();

        for (int i=0; i<numThreads; i++) {
            RGraphicsViewWorker* worker = initWorker(i);
            if (i==0) {
                worker->setClearMode(RGraphicsViewWorker::ClearToBackground);
            }
            else {
                worker->setClearMode(RGraphicsViewWorker::ClearToTransparent);
            }
            workers.append(worker);
        }
    }

    double dpr = getDevicePixelRatio();
    QSize newSize;
    if (widget!=NULL) {
        newSize = QSize(int(widget->width()*dpr), int(widget->height()*dpr));
    }
    else {
        newSize = lastSize;
    }

    if (lastSize!=newSize && workers.first()->getImageSize()!=newSize) {
        for (int i=0; i<workers.length(); i++) {
            workers[i]->initImageBuffer(newSize);
        }
        lastFactor = -1;
    }

    lastSize = newSize;

    if (decorationWorker==NULL) {
        decorationWorker = initWorker(-1);
        decorationWorker->setClearMode(RGraphicsViewWorker::NoClear);
    }
}

RGraphicsViewWorker* RGraphicsViewImage::initWorker(int threadId) {
    return new RGraphicsViewWorkerPainter(*this, threadId);
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

    paintBackground(workers.first(), r);

    RVector c1 = mapFromView(RVector(r.left()-1,r.bottom()+1), -1e300);
    RVector c2 = mapFromView(RVector(r.right()+1,r.top()-1), 1e300);
    RBox queryBox(c1, c2);

    //RDebug::startTimer(800);
    paintEntitiesMulti(queryBox);
    //RDebug::stopTimer(800, "paintEntitiesMulti");

    // paint selected entities (omitted above) always on top:
    if (!selectedIds.isEmpty()) {
        isSelected = true;
        QList<REntity::Id> list = document->getStorage().orderBackToFront(selectedIds);
        QListIterator<RObject::Id> i(list);
        while (i.hasNext()) {
            paintEntityThread(workers.last(), i.next());
        }
    }

    // paint overlay:
    paintOverlay();
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

void RGraphicsViewImage::paintBackground(RGraphicsViewWorker* worker, const QRect& rect) {
    Q_UNUSED(rect)

    if (backgroundDecoration.isEmpty()) {
        return;
    }

    int boxWidth = 1000;
    int boxHeight = 30;

    QTransform savedTransform = worker->getTransform();
    worker->translate(backgroundOffset.x, backgroundOffset.y);
    worker->scale(backgroundFactor, backgroundFactor);

    for (int i=0; i<backgroundDecoration.size(); i++) {
        RGraphicsSceneDrawable d = backgroundDecoration[i];
        if (d.isPainterPath()) {
            RPainterPath& path = d.getPainterPath();
            worker->setPen(path.getPen());
            worker->setBrush(path.getBrush());
            worker->drawPath(path);
        }
        else if (d.isText()) {
            RTextBasedData& text = d.getText();
            RVector pos = text.getPosition();
            worker->setFont(QFont(text.getFontName(), text.getTextHeight()));
            worker->setPen(QPen(Qt::black));

            int flags = 0;
            double boxLeft;
            double boxTop;

            switch (text.getVAlign()) {
            default:
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
            default:
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
            worker->setTransform(t, true);
            worker->drawText(box, flags, text.getText());
            worker->setTransform(savedTransform2);
        }
    }

    worker->setTransform(savedTransform);
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

void RGraphicsViewImage::paintOverlay() {
    if (workers.isEmpty()) {
        qWarning() << "RGraphicsViewImage::paintOverlay: no workers";
        return;
    }

    RGraphicsViewWorker* worker = workers.last();

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

                    worker->setPen(pen);
                    worker->setBrush(path.getBrush());
                    worker->drawPath(path);
                }

                else if (drawable.getType()==RGraphicsSceneDrawable::Text) {
                    RTextBasedData text = drawable.getText();

                    if (drawable.getPixelUnit()) {
                        //text.scale(RVector(1/factor,1/factor), text.getAlignmentPoint());

                        if (!isPrinting() && !isPrintPreview()) {
                            text.scale(RVector(1/factor,1/factor), RVector(0,0));
                        }
                        else {
                            double f = RUnit::convert(0.22, RS::Millimeter, getDocument()->getUnit());
                            f/=getDevicePixelRatio();
                            text.scale(RVector(f,f), RVector(0,0));
                        }
                    }

                    text.move(drawable.getOffset());
                    text.move(paintOffset);

                    paintText(worker, text);
                }
                //painter->setPen(path.getPen());
                //painter->setBrush(path.getBrush());
                //painter->drawPath(path);
            }
        }
    }
}

void RGraphicsViewImage::initPainter(QPaintDevice& device, bool erase, bool screen, const QRect& rect) {
    painter = new QPainter(&device);
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
    //return painter;
}

void RGraphicsViewImage::paintEntities(QPainter* painter, const RBox& queryBox) {
    //painterThread.clear();
    //painterThread.append(painter);
    //entityTransformThread.clear();
    //entityTransformThread.append(QStack<RTransform>());

    // save workers:
    QList<RGraphicsViewWorker*> workersOri = workers;
    int numThreadsOri = numThreads;

    // prepare for QPainter painting (printing / PDF export):
    workers.clear();
    numThreads = 1;
    RGraphicsViewWorkerPainter* w = new RGraphicsViewWorkerPainter(*this, -1);
    w->setPainter(painter);
    workers.append(w);

    paintEntitiesMulti(queryBox);

    delete w;
    workers.clear();

    // restore workers:
    workers = workersOri;
    numThreads = numThreadsOri;
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

    /*
    static QList<RGraphicsSceneDrawable> drawablesCache;

    // TOTO clear cache if
    // - document has changed since last call
    // - remember document modified state with counter instead of flag
    // - we're working with the preview
    // - zoom has changed significantly (regen arcs)

    if (drawablesCache.isEmpty()) {
        RDebug::startTimer(60);
        QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
        //QList<REntity::Id> list = ids.toList();
        RDebug::stopTimer(60, "ordering");


        RDebug::startTimer(60);
        for (int i=0; i<list.length(); i++) {
            REntity::Id id = list[i];

            // get drawables of the given entity:
            QList<RGraphicsSceneDrawable>* drawables = sceneQt->getDrawables(id);

            for (int k=0; k<drawables->length(); k++) {
                drawablesCache.append(drawables->at(k));
            }
        }
        RDebug::stopTimer(60, "caching");
    }
    */

    //RDebug::startTimer(60);
    QList<REntity::Id> list = document->getStorage().orderBackToFront(ids);
    //QList<REntity::Id> list = ids.toList();
    //RDebug::stopTimer(60, "ordering");

    // about 30ms for 50000:
//    RDebug::startTimer(60);
//    for (int i=0; i<list.length(); i++) {
//        REntity::Id id = list[i];

//        // get drawables of the given entity:
//        QList<RGraphicsSceneDrawable>* drawables = sceneQt->getDrawables(id);
//    }
//    RDebug::stopTimer(60, "getting drawables for each entity");

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
    //RDebug::startTimer(61);
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
            for (int p=0; p<drawables->size(); p++) {
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

                if (regen) {
                    break;
                }
            }
        }

        // regenerate arc, xline, block reference, etc.:
        if (regen) {
            // TODO: only regen part of block ref / viewport that needs regeneration:
            sceneQt->exportEntity(id, true);
        }
    }
    //RDebug::stopTimer(61, "regen");

    if (numThreads==1) {
        RGraphicsViewWorker* worker = workers[0];
        worker->init(list, 0, list.length());
        worker->paint();
        //qDebug() << "paintDrawablesThread";
//        RDebug::startTimer(62);
//        paintEntitiesThread(0, list, 0, list.length());
//        //paintDrawablesThread(0, drawablesCache, 0, drawablesCache.length());
//        RDebug::stopTimer(62, "paintEntitiesThread");
    }
    else {
        //Q_ASSERT(painterThread.length()==entityTransformThread.length());

        //RDebug::startTimer(100);
        //qDebug() << "list.length():" << list.length();
        int slice = int(floor(double(list.length())/numThreads));
        //QList<QFuture<void> > futureThread;

//        // not enough or too many workers:
//        if (workers.length()!=numThreads) {
//            for (int i=0; i<workers.length(); i++) {
//                delete workers[i];
//            }
//            workers.clear();

//            for (int i=0; i<numThreads; i++) {
//                RGraphicsViewWorkerPainter* worker = new RGraphicsViewWorkerPainter(*this);
//                workers.append(worker);
//            }
//        }

        //QList<RGraphicsViewWorker*> threads;
        for (int threadId=0; threadId<numThreads; threadId++) {
            int start = threadId*slice;
            int end = (threadId+1)*slice;
            if (threadId==numThreads-1) {
                end = (int)list.length();
            }
            //qDebug() << "slice:" << start << end;

            //futureThread.append(QtConcurrent::run(this, &RGraphicsViewImage::paintEntitiesThread, threadId, list, start, end));

            // Qt 6:
//            QFuture<void> future = QtConcurrent::run([this, threadId, list, start, end]() {
//                this->paintEntitiesThread(threadId, list, start, end);
//            });
//            futureThread.append(future);

            //QThread* thread = new QThread();
            RGraphicsViewWorker* worker = workers[threadId];
            //RGraphicsViewWorkerPainter* worker = dynamic_cast<RGraphicsViewWorkerPainter*>(workers[threadId]);
            //RGraphicsViewWorkerPainter* worker = new RGraphicsViewWorkerPainter(*this);
            worker->init(list, start, end);
            //RGraphicsViewWorkerPainter* worker = new RGraphicsViewWorkerPainter(threadId, list, start, end);
            //worker->setParent(thread);
            //worker->moveToThread(thread);
            //threads.append(worker);

//            QObject::connect(thread, &QThread::started, [worker]() {
//                worker->paint();
//            });

//            qDebug() << "connecting signals...";
            //connect(worker, &RGraphicsViewWorker::finished, );
//            QObject::connect(thread, &QThread::started, worker, &RGraphicsViewWorkerPainter::paint);
//            QObject::connect(worker, &RGraphicsViewWorkerPainter::finished, thread, &QThread::quit);

//            QObject::connect(thread, &QThread::started, [&worker]() {
//                qDebug() << "thread started: worker thread id: " << QThread::currentThreadId();
//            });
//            QObject::connect(thread, &QThread::finished, [&worker]() {
//                qDebug() << "thread finished: worker thread id: " << QThread::currentThreadId();
//            });
//            QObject::connect(worker, &RGraphicsViewWorkerPainter::finished, []() {
//                qDebug() << "worker finished: worker thread id: " << QThread::currentThreadId();
//            });
//            qDebug() << "connecting signals... DONE";

            //QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

            //qDebug() << "starting thread...";
            //thread->start();
            worker->start();
            //qDebug() << "starting thread...DONE";

            //paintDrawablesThread(threadId, drawablesCache, start, end);
            //paintEntitiesThread(threadId, list, start, end);
        }
        //RDebug::stopTimer(100, "launch threads");

        //RDebug::startTimer(100);
//        for (int i=0; i<futureThread.length(); i++) {
//            futureThread[i].waitForFinished();
//        }

//        bool running;
//        do {
//            running = false;
//            for (int i=0; i<workers.length(); i++) {
//                RGraphicsViewWorker* worker = threads[i];
//                running = running || worker->isRunning();
//                qDebug() << "thread " << i << " running: " << worker->isRunning();
//            }
//        } while (running);

        for (int i=0; i<workers.length(); i++) {
            RGraphicsViewWorker* worker = workers[i];
            worker->wait();
//            qDebug() << "waiting for thread:" << i << "...";
//            QThread* thread = threads[i];
//            thread->wait();
//            qDebug() << "waiting for thread:" << i << ": DONE";
        }
        //RDebug::stopTimer(100, "waitForFinished");
    }

}

//void RGraphicsViewImage::paintEntitiesThread(int threadId, const QList<REntity::Id>& list, int start, int end) {
//    for (int i=start; i<end; i++) {
//        paintEntityThread(threadId, list[i]);
//    }
//}

//void RGraphicsViewImage::paintDrawablesThread(int threadId, const QList<RGraphicsSceneDrawable>& list, int start, int end) {
//    qDebug() << "RGraphicsViewImage::paintDrawablesThread";
//    // TODO: clip rectangle of entity
//    RBox clipRectangle;
//    for (int i=start; i<end; i++) {
//        RGraphicsSceneDrawable d = list[i];
//        paintDrawableThread(d, clipRectangle);
//    }
//}

/**
 * Looks up entity drawable and paints it using the given worker.
 */
void RGraphicsViewImage::paintEntityThread(RGraphicsViewWorker* worker, REntity::Id id, bool preview) {
    RDocument* doc = getDocument();
    if (!preview && !isPrintingOrExporting() && !isSelected && (doc->isSelected(id) || doc->isSelectedWorkingSet(id))) {
        static QMutex m;
        m.lock();
        // remember selected entities to overlay in the end:
        selectedIds.insert(id);
        m.unlock();
        return;
    }

    //qDebug() << "RGraphicsViewImage::paintEntityThread";

    //Q_ASSERT(threadId<painterThread.length());
    //Q_ASSERT(threadId<entityTransformThread.length());

    // TODO: set class member painter to use in other functions:
//    if (painterThread.length()>threadId) {
//        painter = painterThread[threadId];
//    }
//    else {
//        painter = NULL;
//    }

    // clipping of this particular entity:
    // TODO: should this be a drawable
    RBox clipRectangle = sceneQt->getClipRectangle(id, preview);
    if (clipRectangle.isValid()) {
        clipRectangle.move(paintOffset);

        if (worker!=NULL) {
            worker->setClipRect(QRectF(clipRectangle.getMinimum().x, clipRectangle.getMinimum().y, clipRectangle.getWidth(), clipRectangle.getHeight()));
        }
    }
    else {
        if (worker!=NULL) {
            worker->setClipping(false);
        }
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

        paintDrawableThread(worker, drawable, clipRectangle, preview);
    }
}


// TODO: remove threadId:
void RGraphicsViewImage::paintDrawableThread(RGraphicsViewWorker* worker, RGraphicsSceneDrawable& drawable, const RBox& clipRectangle, bool preview) {

    // drawable is not plottable (from layer for which plottable is off):
    if (drawable.getNoPlot() && (isPrinting() || (showOnlyPlottable && isPrintPreview()))) {
        // always export transforms (viewports):
        if (drawable.getType()!=RGraphicsSceneDrawable::Transform && drawable.getType()!=RGraphicsSceneDrawable::EndTransform) {
            return;
        }
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
            // TODO: add function to RGraphicsViewImage:
            worker->setClipping(true);
        }
        RImageData image = drawable.getImage();
        image.move(drawable.getOffset());

        //if (entityTransformThread[threadId].isEmpty()) {
        if (!worker->hasTransforms()) {
            image.move(paintOffset);
        }
        else {
            // transform (image in block reference):
            // TODO: add function to RGraphicsViewImage:
            worker->save();
            QStack<RTransform> entityTransformStack = worker->getEntityTransformStack();
            //for (int k=0; k<entityTransformThread[threadId].size(); k++) {
            for (int k=0; k<entityTransformStack.size(); k++) {
                if (k==0) {
                    // paintOffset must be applied here to get the correct placement for
                    // texts with non-uniform scale:
                    QTransform tt;
                    tt.translate(paintOffset.x, paintOffset.y);

                    // TODO: add function to RGraphicsViewImage:
                    worker->setTransform(tt, true);
                }

                //RTransform t = entityTransformThread[threadId][k];
                RTransform t = entityTransformStack[k];

                // TODO: add function to RGraphicsViewImage:
                worker->setTransform(t, true);
            }
        }

        // TODO: add function to RGraphicsViewImage:
        // TODO: remove painter:
        worker->paintImage(image, workingSet);

        //if (!entityTransformThread[threadId].isEmpty()) {
        if (worker->hasTransforms()) {
            // TODO: add function to RGraphicsViewImage:
            worker->restore();
        }
    }

    // TTF text block (CAD text block is painter path):
    else if (drawable.isText()) {
        RTextBasedData text = drawable.getText();

        if (drawable.getPixelUnit()) {
            text.scale(RVector(1/factor,1/factor), text.getAlignmentPoint());
        }

        text.move(drawable.getOffset());

        //if (entityTransformThread[threadId].isEmpty()) {
        if (!worker->hasTransforms()) {
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
            // TODO: add function to RGraphicsViewImage:
            worker->save();
            QStack<RTransform> entityTransformStack = worker->getEntityTransformStack();
            //for (int k=0; k<entityTransformThread[threadId].size(); k++) {
            for (int k=0; k<entityTransformStack.size(); k++) {
                if (k==0) {
                    // paintOffset must be applied here to get the correct placement for
                    // texts with non-uniform scale:

                    QTransform tt;
                    tt.translate(paintOffset.x, paintOffset.y);

                    //text.move(paintOffset);
                    // TODO: add function to RGraphicsViewImage:
                    worker->setTransform(tt, true);
//                        p.transform2D(tt);
//                        ap.transform2D(tt);
//                        anglePoint.transform2D(tt);
//                        centerPoint.transform2D(tt);
                }

                //RTransform t = entityTransformThread[threadId][k];
                RTransform t = entityTransformStack[k];
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
                // TODO: add function to RGraphicsViewImage:
                worker->setTransform(t, true);

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

        // skip rendering of text with nominal height below threshold:
        if (forceTextHeightThreshold) {
            QTransform t = worker->getTransform();
            double maxScale = qMax(t.m11(), t.m22());
            int featureSizePx = (int)mapDistanceToView(fabs(text.getTextHeight() * maxScale));
            if (featureSizePx<=textHeightThreshold) {
                if (worker->hasTransforms()) {
                    worker->restore();
                }
                return;
            }
        }

        worker->paintText(text, workingSet);

        //if (!entityTransformThread[threadId].isEmpty()) {
        if (worker->hasTransforms()) {
            worker->restore();
        }
    }

    // Transform:
    else if (drawable.getType()==RGraphicsSceneDrawable::Transform) {
        RTransform transform = drawable.getTransform();
        //entityTransformThread[threadId].push(transform);
        worker->pushTransform(transform);
    }

    else if (drawable.getType()==RGraphicsSceneDrawable::EndTransform) {
        //if (!entityTransformThread[threadId].isEmpty()) {
        if (worker->hasTransforms()) {
            //entityTransformThread[threadId].pop();
            worker->popTransform();
        }
        else {
            qWarning() << "pop transform: stack empty";
        }
    }

    // unknown drawable or already handled (image, text, transform, end transform):
    if (!drawable.isPainterPath()) {
        return;
    }

    // painter path:
    RPainterPath path = drawable.getPainterPath();
    if (!path.isSane()) {
        return;
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
        return;
    }

    // small texts might be invisible while their bounding box is displayed:
    if (!isPathVisible(path)) {
        return;
    }

    // individual paths might disable clipping:
    if (clipRectangle.isValid()) {
        // TODO: add function to RGraphicsViewImage:
        //if (painter!=NULL) {
            worker->setClipping(!path.getNoClipping());
        //}
    }

    QPen pen = path.getPen();
    QBrush brush = path.getBrush();

    if (path.getWipeout()) {
        brush.setColor(backgroundColor);
    }

    if (pen.style() != Qt::NoPen) {
        if (path.getPixelWidth()) {
            // use width of path pen:
            if (scene->getScreenBasedLinetypes() || path.getScreenBasedLinetype()) {
                pen.setWidthF(pen.widthF());
            }
            else {
                pen.setWidthF(pen.widthF() / getFactor());
            }
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
    if (!path.getWipeout()) {
        applyColorCorrection(brush);
    }

    // apply minimum line weight:
    applyMinimumLineweight(pen);

    // highlighted:
    // don't highlight when printing
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

    if (path.getWipeout()) {
        if (path.getFrameless() && (path.isHighlighted() || path.isSelected() || preview)) {
            // highlighted or selected wipeout: always show frame outline:
            QList<qreal> dashes;
            dashes << 10 << 5 << 2 << 5;

            pen.setStyle(Qt::CustomDashLine);
            pen.setDashPattern(dashes.toVector());
            pen.setWidth(1);
            pen.setCosmetic(true);
        }

        if (path.isHighlighted()) {
            brush.setStyle(Qt::NoBrush);
        }

        if (path.isSelected() || preview) {
            // preview wipeout is rendered on top: make transparent:
            QColor col = brush.color();
            col.setAlphaF(0.5);
            brush.setColor(col);
        }
    }

    if (!path.getNoColorMode()) {
        applyColorMode(pen);
        applyColorMode(brush);
    }

    worker->setBrush(brush);
    worker->setPen(pen);

    // 20210903: make sure screen-based linetypes are rendered as path to keep pattern visible:
    if (scene->getScreenBasedLinetypes() || path.getScreenBasedLinetype() || scene->getDraftMode() || isPrintingOrExporting() /*|| clipBox.contains(pathBB)*/) {
        if (brush.style() != Qt::NoBrush) {
            // TODO: add function to RGraphicsViewImage:
            worker->fillPath(path, brush);
        }

        // draw outline:
        if (pen.style() != Qt::NoPen) {
            // TODO: add function to RGraphicsViewImage:
            worker->drawPath(path);
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
                //qDebug() << "calling drawLine";
                worker->drawLine(qLine);
            }
        }
        else {
            // draw fill:
            if (brush.style() != Qt::NoBrush) {
                // TODO: add function to RGraphicsViewImage:
                worker->fillPath(path, brush);
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

                            worker->drawLine(qLine);
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
                        // TODO: add function to RGraphicsViewImage:
                        //worker->strokePath(cubicCurve, painter->pen());
                        worker->strokePath(cubicCurve, worker->getPen());
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
        // simple point display for hatches (don't apply point styles):
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

                // TODO: add function to RGraphicsViewImage:
                worker->drawLine(QLineF(p.x, p.y, p.x + ps, p.y));
            }
            return;
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
            //QPen pen = painter->pen();
            QPen pen = worker->getPen();
            if (!RSettings::getApplyLineweightToPoints()) {
                pen.setWidth(0);
            }
            // TODO: add function to RGraphicsViewImage:
            worker->setPen(pen);
        }

        // if PDMODE = 1 nothing is drawn
        // we are in an while loop, so continue
        if (pMode == 1) {
            return;
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
                // TODO: add function to RGraphicsViewImage:
                drawDot(worker, QPointF(p.x, p.y));
            } else if (rslt7 == 2) {
                drawPlus(worker, QPointF(p.x, p.y), pSize);
            } else if (rslt7 == 3) {
                drawEx(worker, QPointF(p.x, p.y), pSize);
            } else if (rslt7 == 4) {
                drawVBar(worker, QPointF(p.x, p.y), pSize);
            }
            //rslt = pMode & 32;
            if (rslt32 == 32) {
                drawCircle(worker, QPointF(p.x, p.y), pSize);
            }
            //rslt = pMode & 64;
            if (rslt64 == 64) {
                drawSquare(worker, QPointF(p.x, p.y), pSize);
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

void RGraphicsViewImage::drawDot(RGraphicsViewWorker* worker, QPointF pt) {
    qreal r;
    if (isPrinting() || isPrintPreview()) {
        RDocument* doc = getDocument();
        r = RUnit::convert(doc->getVariable("PageSettings/PointSize", 0.5, true).toDouble()/2.0, RS::Millimeter, doc->getUnit());
    } else {
        // screen rendering / (bitmap) exporting
        r = mapDistanceFromView(1.5);
    }
    worker->setBrush(worker->getPen().color());
    worker->drawEllipse(pt, r, r);
    worker->setBrush(Qt::NoBrush);
}

void RGraphicsViewImage::drawPlus(RGraphicsViewWorker* worker, QPointF pt, double pSize) {
    qreal size = pSize / 2;
    size = mapDistanceFromView(size);
    worker->drawLine(
        QLineF(pt.x() - size, pt.y(), pt.x() + size, pt.y())
    );
    worker->drawLine(
        QLineF(pt.x(), pt.y() - size, pt.x(), pt.y() + size)
    );
}

void RGraphicsViewImage::drawEx(RGraphicsViewWorker* worker, QPointF pt, double pSize) {
    qreal size = pSize / 2;
    size = mapDistanceFromView(size);
    worker->drawLine(
        QLineF(pt.x() - size, pt.y() + size, pt.x() + size, pt.y() - size)
    );
    worker->drawLine(
        QLineF(pt.x() + size, pt.y() + size, pt.x() - size, pt.y() - size)
    );
}

void RGraphicsViewImage::drawVBar(RGraphicsViewWorker* worker, QPointF pt, double pSize) {
    qreal size = (pSize * 0.8) / 2 ;
    size = mapDistanceFromView(size);
    worker->drawLine(
        QLineF(pt.x(), pt.y(), pt.x(), pt.y() + size)
    );
}

void RGraphicsViewImage::drawCircle(RGraphicsViewWorker* worker, QPointF pt, double pSize) {
    qreal size = (pSize * 0.8) / 2;
    size = mapDistanceFromView(size);
    worker->drawEllipse(pt, size, size);
}

void RGraphicsViewImage::drawSquare(RGraphicsViewWorker* worker, QPointF pt, double pSize) {
    qreal size = (pSize * 0.8) / 2;
    size = mapDistanceFromView(size);
    worker->drawLine(
        QLineF(pt.x() - size, pt.y() + size, pt.x() + size, pt.y() + size)
    );
    worker->drawLine(
        QLineF(pt.x() + size, pt.y() + size, pt.x() + size, pt.y() - size)
    );
    worker->drawLine(
        QLineF(pt.x() + size, pt.y() - size, pt.x() - size, pt.y() - size)
    );
    worker->drawLine(
        QLineF(pt.x() - size, pt.y() - size, pt.x() - size, pt.y() + size)
    );
}

void RGraphicsViewImage::paintImage(RGraphicsViewWorker* worker, const RImageData& image, bool workingSet) {
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

        worker->save();
        /*
        QMatrix wm = painter->matrix();
        wm.translate(image.getInsertionPoint().x, image.getInsertionPoint().y);
        wm.rotate(RMath::rad2deg(angle));
        wm.scale(scale.x, -scale.y);
        painter->setMatrix(wm);
        */

        QTransform t = worker->getWorldTransform();
        t.translate(image.getInsertionPoint().x, image.getInsertionPoint().y);
        t.rotate(RMath::rad2deg(angle));
        t.scale(scale.x, -scale.y);
        worker->setWorldTransform(t);

        double opacity = 1.0;
        if (image.getFade()>0 && image.getFade()<100) {
            opacity = 1.0 - ((double)image.getFade()/100);
        }
        if (!workingSet) {
            opacity *= 0.5;
        }
        worker->setOpacity(opacity);
        worker->drawImage(0,-qImage.height(), qImage);
        worker->setOpacity(1.0);
        worker->restore();
    }

    // draw image in draft mode / selected mode (border in black or white):
    if (scene->getDraftMode() || image.isSelected()) {
        if (image.isSelected()) {
            worker->setPen(QPen(QBrush(RSettings::getSelectionColor()), 0));
        }
        else {
            if (backgroundColor.value()<128) {
                worker->setPen(QPen(QBrush(QColor(Qt::white)), 0));
            }
            else {
                worker->setPen(QPen(QBrush(QColor(Qt::black)), 0));
            }
        }
        QList<RLine> edges = image.getEdges();
        for (int i=0; i<edges.count(); i++) {
            RLine l = edges[i];
            worker->drawLine(QLineF(l.getStartPoint().x, l.getStartPoint().y, l.getEndPoint().x, l.getEndPoint().y));
        }
    }

}

void RGraphicsViewImage::paintText(RGraphicsViewWorker* worker, const RTextBasedData& text, bool workingSet) {
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
            worker->save();
            worker->setTransform(t, true);

            QTextOption o;
            if (text.isSelected()) {
                o.setFlags(QTextOption::SuppressColors);
                worker->setPen(QPen(RSettings::getSelectionColor()));
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

                worker->setPen(pen);
            }
            textLayout.layout->setTextOption(o);

            // TODO: should be reentrant but crashes if not locked:
            {
                RTextRenderer::lockForDrawing();
                //textLayout.layout->draw(painter, QPoint(0,0));
                worker->drawTextLayout(*textLayout.layout);
                RTextRenderer::unlockForDrawing();
            }

            worker->restore();
        }

    }
    //RDebug::stopTimer(0, "draw layouts");
}


int RGraphicsViewImage::getWidth() const {
    if (widget!=NULL) {
        double dpr = getDevicePixelRatio();
        return (int)(widget->width() * dpr);
    }
    //if (graphicsBufferThread.isEmpty()) {
    if (workers.isEmpty()) {
        return 100;
    }
    //return graphicsBufferThread.first().width();
    return workers.first()->getImage().width();
}

int RGraphicsViewImage::getHeight() const {
    if (widget!=NULL) {
        double dpr = getDevicePixelRatio();
        return (int)(widget->height() * dpr);
    }
    //if (graphicsBufferThread.isEmpty()) {
    if (workers.isEmpty()) {
        return 100;
    }
    //return graphicsBufferThread.first().height();
    return workers.first()->getImage().height();
}

void RGraphicsViewImage::resizeImage(int w, int h) {
    if (workers.isEmpty()) {
        initWorkers();
    }
    for (int i=0; i<workers.length(); i++) {
        workers[i]->initImageBuffer(QSize(w,h));
    }
}

void RGraphicsViewImage::setPanOptimization(bool on) {
    panOptimization = on;
}

bool RGraphicsViewImage::getPanOptimization() {
    return panOptimization;
}

QImage RGraphicsViewImage::getBuffer() const {
    return graphicsBuffer;
}

QTransform RGraphicsViewImage::getTransform() const {
    return transform;
}

void RGraphicsViewImage::viewportChangeEvent() {
    RGraphicsView::viewportChangeEvent();
    emit viewportChanged();
}

void RGraphicsViewImage::emitUpdateSnapInfo(RSnap* snap, RSnapRestriction* restriction) {
    if (receivers(SIGNAL(updateSnapInfo(RGraphicsViewWorker*, RSnap*, RSnapRestriction*))) > 0) {
        //QPainter gbPainter(&graphicsBufferWithPreview);
        emit(updateSnapInfo(decorationWorker, snap, restriction));
        //gbPainter.end();
    }
}

void RGraphicsViewImage::emitUpdateTextLabel(const RTextLabel& textLabel) {
    if (receivers(SIGNAL(updateTextLabel(RGraphicsViewWorker*, const RTextLabel&))) > 0) {
        //QPainter gbPainter(&graphicsBufferWithPreview);
        emit(updateTextLabel(decorationWorker, textLabel));
        //gbPainter.end();
    }
}

void RGraphicsViewImage::giveFocus() {
    if (widget!=NULL) {
        widget->setFocus(Qt::OtherFocusReason);
    }
}

bool RGraphicsViewImage::hasFocus() {
    if (widget!=NULL) {
        return widget->hasFocus();
    }
    return true;
}

void RGraphicsViewImage::removeFocus() {
    if (widget!=NULL) {
        RGraphicsViewQt* view = qobject_cast<RGraphicsViewQt*>(widget);
        if (view!=NULL) {
            view->removeFocus();
        }
    }
    return;
}

void RGraphicsViewImage::simulateMouseMoveEvent() {
    if (widget!=NULL) {
        RGraphicsViewQt* view = qobject_cast<RGraphicsViewQt*>(widget);
        if (view!=NULL) {
            view->simulateMouseMoveEvent();
        }
    }

    RGraphicsView::simulateMouseMoveEvent();
}

double RGraphicsViewImage::getDevicePixelRatio() const {
    if (RSettings::getHighResolutionGraphicsView()) {
#if QT_VERSION >= 0x050000
        if (widget!=NULL) {
            return widget->devicePixelRatio();
        }
#endif
    }

    return 1;
}

void RGraphicsViewImage::endPaint() const {
    if (painter==NULL) {
        return;
    }

    painter->end();
}

void RGraphicsViewImage::setBrush(const QBrush& brush) const {
    if (painter==NULL) {
        return;
    }
    painter->setBrush(brush);
}

void RGraphicsViewImage::setPen(const QPen& pen) const {
    if (painter==NULL) {
        return;
    }
    painter->setPen(pen);
}

void RGraphicsViewImage::drawLine(const QLineF& line) const {
    if (painter==NULL) {
        return;
    }
    painter->drawLine(line);
}
