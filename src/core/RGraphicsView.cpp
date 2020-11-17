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
#include "RGraphicsView.h"
#include "RAction.h"
#include "RDebug.h"
#include "RDocument.h"
#include "RGraphicsScene.h"
#include "RMouseEvent.h"
#include "RWheelEvent.h"
#include "RDocumentInterface.h"
#include "RSettings.h"
#include "RUnit.h"


RGraphicsView::RGraphicsView(RGraphicsScene* scene) :
      exporting(false),
      printing(false),
      printPreview(false),
      printPointSize(1.0, 1.0),
      colorMode(RGraphicsView::FullColor),
      hairlineMode(false),
      hairlineMinimumMode(false),
      scene(NULL),
      grid(NULL),
      navigationAction(NULL),
      offset(5,5),
      factor(10.0),
      previousOffset(5,5),
      previousFactor(0.0),
      displayOnlyCurrentUcs(false),
      margin(-1),
      currentStepScaleFactor(1.0),
      textHeightThresholdOverride(-1),
      textHeightThreshold(3),
      viewportNumber(-1),
      antialiasing(false),
      gridVisible(-1) {

    setScene(scene, false);

    lastKnownModelPosition = RVector::invalid;
    lastKnownScreenPosition = RVector::invalid;

    autoScalePatterns = RSettings::getAutoScalePatterns();

    RDebug::incCounter("RGraphicsView");
}



RGraphicsView::~RGraphicsView() {
    RDebug::decCounter("RGraphicsView");
    if (navigationAction!=NULL) {
        delete navigationAction;
    }
    if (grid!=NULL) {
        delete grid;
        grid = NULL;
    }
    if (scene!=NULL) {
        scene->unregisterView(this);
        scene = NULL;
    }
}

void RGraphicsView::clearCaches() {
    gridVisible = -1;
}

void RGraphicsView::setViewportNumber(int n) {
    viewportNumber = n;

    // changing the viewport number changes settings variable names (e.g. "Grid/DisplayGrid03"):
    clearCaches();
}

void RGraphicsView::setGridVisible(bool on) {
    gridVisible = (int)on;

    if (viewportNumber==-1) {
        return;
    }

    RDocument* doc = getDocument();
    if (doc==NULL) {
        return;
    }

    doc->setVariable(QString("Grid/DisplayGrid0%1").arg(viewportNumber), on);
}

bool RGraphicsView::isGridVisible() const {
    if (gridVisible==-1) {
        RDocument* doc = getDocument();
        if (doc==NULL) {
            return true;
        }
        gridVisible = (int)doc->getVariable(QString("Grid/DisplayGrid0%1").arg(viewportNumber), true, true).toBool();
    }
    return gridVisible;
}

void RGraphicsView::viewportChangeEvent() {
    if (grid == NULL) {
        return;
    }
    grid->update();
}

void RGraphicsView::saveViewport() {
    previousOffset = offset;
    previousFactor = factor;
}

void RGraphicsView::restoreViewport() {
    RVector tmpOffset = previousOffset;
    double tmpFactor = previousFactor;
    saveViewport();
    factor = tmpFactor;
    offset = tmpOffset;
    regenerate();
}

void RGraphicsView::setScene(RGraphicsScene* scene, bool regen) {
    this->scene = scene;
    if (scene != NULL) {
        scene->registerView(this, regen);
    }
}

/**
 * \return Reference to the graphics scene that is visualized by this view.
 */
RGraphicsScene* RGraphicsView::getScene() const {
    return scene;
}


/**
 * If \c on is true, only the current UCS and the entities that are in its range are
 * displayed. The range of a UCS is defined by the length of its axis vectors. This
 * can be used to display only one floor in an architecture application.
 */
void RGraphicsView::setDisplayOnlyCurrentUcs(bool on) {
    displayOnlyCurrentUcs = on;
}



/**
 * \return Reference to the document that is visualized by this view.
 */
RDocument* RGraphicsView::getDocument() const {
    if (scene == NULL) {
        return NULL;
    }
    return &scene->getDocument();
}



/**
 * \return Reference to the document interface.
 */
RDocumentInterface* RGraphicsView::getDocumentInterface() const {
    if (scene == NULL) {
        return NULL;
    }
    return &scene->getDocumentInterface();
}

void RGraphicsView::autoZoom(int margin, bool ignoreEmpty, bool ignoreLineweight) {
    RDocument* document = getDocument();
    if (document == NULL) {
        return;
    }
    RBox bb = document->getBoundingBox(true, ignoreEmpty);

    // add lineweight margin:
    if (!ignoreLineweight) {
        bb.growXY(
            RUnit::convert(
                document->getMaxLineweight()/100.0/2,
                RS::Millimeter,
                document->getUnit()
            )
        );
    }

    zoomTo(bb, (margin!=-1 ? margin : getMargin()));
}

bool RGraphicsView::zoomToSelection(int margin) {
    RDocument* document = getDocument();
    if (document == NULL) {
        return false;
    }
    RBox selectionBox = document->getSelectionBox();
    if (selectionBox.isValid() && (selectionBox.getWidth()>RS::PointTolerance || selectionBox.getHeight()>RS::PointTolerance)) {
        zoomTo(selectionBox, (margin!=-1 ? margin : getMargin()));
        return true;
    }
    return false;
}

bool RGraphicsView::zoomToEntities(const QSet<REntity::Id>& ids, int margin) {
    RDocument* document = getDocument();
    if (document == NULL) {
        return false;
    }
    RBox bb;
    QSet<REntity::Id>::const_iterator it;
    for (it=ids.constBegin(); it!=ids.constEnd(); it++) {
        REntity::Id id = *it;
        QSharedPointer<REntity> e = document->queryEntityDirect(id);
        if (!e.isNull()) {
            bb.growToInclude(e->getBoundingBox());
        }
    }
    if (bb.isValid() && (bb.getWidth()>RS::PointTolerance || bb.getHeight()>RS::PointTolerance)) {
        zoomTo(bb, (margin!=-1 ? margin : getMargin()));
        return true;
    }
    return false;
}

void RGraphicsView::zoomPrevious() {
    restoreViewport();
}

/**
 * Zooms in / out by the given factor towards / from the given center
 * in scene coordinates.
 */
void RGraphicsView::zoom(const RVector& center, double f) {
    saveViewport();

    RVector newOffset = offset - (center*f - center);
    newOffset/=f;

    setFactor(factor*f);

    setOffset(newOffset, true);
}



/**
 * Zooms in by factor 1.2. The center point is at the center of the view.
 */
void RGraphicsView::zoomIn() {
    zoomIn(mapFromView(RVector(getWidth()/2, getHeight()/2)));
}



/**
 * Zooms out by factor 1.2. The center point is at the center of the view.
 */
void RGraphicsView::zoomOut() {
    zoomOut(mapFromView(RVector(getWidth()/2, getHeight()/2)));
}



/**
 * Zooms in by factor 1.2. The given \c center point stays
 * at the same position.
 */
void RGraphicsView::zoomIn(const RVector& center, double factor) {
    zoom(center, factor);
}



/**
 * Zooms out by factor 1.0/1.2. The given \c center point stays
 * at the same position.
 */
void RGraphicsView::zoomOut(const RVector& center, double factor) {
    if (factor<RS::PointTolerance) {
        return;
    }
    zoom(center, 1.0/factor);
}



/**
 * Zooms the view in a way that the given window is visible and fills the view.
 * The view is updated.
 */
void RGraphicsView::zoomTo(const RBox& window, int margin) {
    if (!window.isValid()) {
        return;
    }

    saveViewport();

    RVector f(RMAXDOUBLE, RMAXDOUBLE);
    double w = window.getWidth();
    double h = window.getHeight();

    if (w<1.0e-6 && h<1.0e-6) {
        return;
    }

    if (w>1.0e-6) {
        f.x = (getWidth() - 2 * margin) / w;
    }
    if (h>1.0e-6) {
        f.y = (getHeight() - 2 * margin) / h;
    }

    f.x = f.y = qMin(f.x, f.y);

    if (RSettings::getLimitZoomAndScroll() && f.x < 1.0e-9) {
        //f.x = f.y = 1.0;
        return;
    }

    setFactor(f.x);

    /*
    RBox viewWindow = mapToView(window);
    qDebug() << "viewWindow: " << viewWindow;
    RVector size = viewWindow.getSize();
    RVector f;

    if (size.x > 1.0e-6) {
        f.x = (getWidth() - 2 * margin) / size.x;
    } else {
        f.x = RMAXDOUBLE;
    }

    if (size.y > 1.0e-6) {
        f.y = (getHeight() - 2 * margin) / size.y;
    } else {
        f.y = RMAXDOUBLE;
    }

    f.x = f.y = qMin(f.x, f.y);

    if (f.x < 1.0e-6 || f.x == RMAXDOUBLE) {
        f.x = f.y = 1.0;
    }

    setFactor(factor * f.x);
    */

    centerToBox(window);
}

double RGraphicsView::getFactor(bool includeStepFactor) const {
    if (includeStepFactor) {
        return factor * currentStepScaleFactor;
    }
    else {
        return factor;
    }
}

RVector RGraphicsView::getOffset(bool includeStepOffset) const {
    if (includeStepOffset) {
        return offset + currentStepOffset;
    }
    else {
        return offset;
    }
}

void RGraphicsView::setOffset(const RVector& offset, bool regen) {
    RVector o = offset;

    if (!o.isSane()) {
        o = RVector(0,0);
    }

    // 20111024: avoid overflows with weird behaviour when using track pad:
    if (RSettings::getLimitZoomAndScroll()) {
        if (offset.x < -1.0e8 || offset.x > 1.0e8) {
            o.x = 0.0;
        }
        if (offset.y < -1.0e8 || offset.y > 1.0e8) {
            o.y = 0.0;
        }
    }

    this->offset = o;

    // offset in pixels:
    //RVector ov(RMath::mround(offset.x*factor), RMath::mround(offset.y*factor));
    ////ov = RVector(RMath::mround(ov.x), RMath::mround(ov.y));
    ////this->offset = mapFromView(ov);
    //this->offset = RVector(ov.x/factor, ov.y/factor);

    if (regen) {
        regenerate();
        if (scene!=NULL) {
            // notify actions about zoom change:
            scene->getDocumentInterface().zoomChangeEvent(*this);
        }
    }
    //viewportChangeEvent();
}

void RGraphicsView::setFactor(double f, bool regen) {
    factor = f;

    if (!RMath::isNormal(factor)) {
        factor = 1.0;
    }

    if (RSettings::getLimitZoomAndScroll()) {
        if (factor>1.0e6) {
            factor = 1.0e6;
        }
        if (factor<1.0e-6) {
            factor = 1.0e-6;
        }
    }

    scene->setPixelSizeHint(mapDistanceFromView(1.0));

    if (regen) {
        regenerate();
        if (scene!=NULL) {
            // notify actions about zoom change:
            scene->getDocumentInterface().zoomChangeEvent(*this);
        }
    }
    //viewportChangeEvent();
}

void RGraphicsView::startPan() {
    saveViewport();
}

/**
 * Pans (scrolls) by the given amount \c delta which is a vector in screen
 * coordinates (pixels).
 */
void RGraphicsView::pan(const RVector& delta, bool regen) {
    double dx = mapDistanceFromView(delta.x);
    double dy = mapDistanceFromView(delta.y);
    setOffset(offset + RVector(dx, -dy), regen);
    //regenerate();
    //viewportChangeEvent();
}


/**
 * Centers the view on the given \c point. The view is updated.
 *
 * \param point Point to move into the center of the drawing in model coordinates.
 */
void RGraphicsView::centerToPoint(const RVector& point) {
    RVector boxCenter = mapFromView(RVector(getWidth(), getHeight())/2.0);
    setOffset(offset - (point - boxCenter));
}



/**
 * Centers the view on the given \c box. The view is updated.
 *
 * \param box Box to move into the center of the drawing in model coordinates.
 */
void RGraphicsView::centerToBox(const RBox& box) {
    RVector center = box.getCenter();
    RVector boxCenter = mapFromView(RVector(getWidth(), getHeight())/2.0);
    setOffset(offset - (center - boxCenter));
    //regenerate();
    //viewportChangeEvent();
}



/**
 * \return Four vectors with the coordinates of the four corners of the
 *      view mapped to scene coordinates.
 */
QList<RVector> RGraphicsView::mapCornersFromView() const {
    QList<RVector> ret;

    ret.append(mapFromView(RVector(0,0,0)));
    ret.append(mapFromView(RVector(getWidth(),0,0)));
    ret.append(mapFromView(RVector(0,getHeight(),0)));
    ret.append(mapFromView(RVector(getWidth(),getHeight(),0)));

    return ret;
}



RBox RGraphicsView::getBox() const {
    QList<RVector> corners = mapCornersFromView();

    return RBox(
        RVector::getMinimum(
            RVector::getMinimum(corners[0], corners[1]),
            RVector::getMinimum(corners[2], corners[3])
        ),
        RVector::getMaximum(
            RVector::getMaximum(corners[0], corners[1]),
            RVector::getMaximum(corners[2], corners[3])
        )
    );
}



/**
 * \return The minimum coordinate that is currently visible in the view.
 */
RVector RGraphicsView::getMinimum() const {
    QList<RVector> corners = mapCornersFromView();

    return RVector::getMinimum(
        RVector::getMinimum(corners[0], corners[1]),
        RVector::getMinimum(corners[2], corners[3])
    );
}



/**
 * \return The maximum coordinate that is currently visible in the view.
 */
RVector RGraphicsView::getMaximum() const {
    QList<RVector> corners = mapCornersFromView();

    return RVector::getMaximum(
        RVector::getMaximum(corners[0], corners[1]),
        RVector::getMaximum(corners[2], corners[3])
    );
}

void RGraphicsView::handleTerminateEvent(RTerminateEvent& event) {
    if (scene == NULL) {
        return;
    }
    scene->handleTerminateEvent(event);
    event.ignore();
}

void RGraphicsView::handleKeyPressEvent(QKeyEvent& event) {
    if (scene == NULL) {
        return;
    }
    scene->handleKeyPressEvent(event);
    if (navigationAction != NULL) {
        navigationAction->keyPressEvent(event);
    }
}

void RGraphicsView::handleKeyReleaseEvent(QKeyEvent& event) {
    if (scene == NULL) {
        return;
    }
    scene->handleKeyReleaseEvent(event);
    if (navigationAction != NULL) {
        navigationAction->keyReleaseEvent(event);
    }
    event.ignore();
}


void RGraphicsView::simulateMouseMoveEvent() {
    if (lastKnownScreenPosition.isValid()) {
        RMouseEvent e(QEvent::MouseMove, lastKnownScreenPosition, Qt::NoButton, Qt::NoButton, Qt::NoModifier, *getScene(), *this);
        if (lastKnownModelPosition.isValid()) {
            e.setModelPosition(lastKnownModelPosition);
        }
        handleMouseMoveEvent(e);
    }
}

/**
 * This should be called by the mouse move event handler of a higher level
 * GUI toolkit. Events are forwarded to the scene and the navigation action
 * that is attached to this view.
 */
void RGraphicsView::handleMouseMoveEvent(RMouseEvent& event) {
    lastKnownModelPosition = event.getModelPosition();
    lastKnownScreenPosition = event.getScreenPosition();
    if (scene != NULL) {
        scene->handleMouseMoveEvent(event);
    }
    if (navigationAction != NULL) {
        navigationAction->mouseMoveEvent(event);
    }
}

/**
 * This should be called by the mouse press event handler of a higher level
 * GUI toolkit. Events are forwarded to the scene and the navigation action
 * that is attached to this view.
 */
void RGraphicsView::handleMousePressEvent(RMouseEvent& event) {
    lastKnownModelPosition = event.getModelPosition();
    lastKnownScreenPosition = event.getScreenPosition();
    if (scene == NULL) {
        return;
    }
    scene->handleMousePressEvent(event);
    if (navigationAction!=NULL) {
        navigationAction->mousePressEvent(event);
    }

    // remember mouse press position to use for mouse release:
    //mousePressScreenPosition = event.getScreenPosition();
    //mousePressModelPosition = event.getModelPosition();
}



/**
 * This should be called by the mouse release event handler of a higher level
 * GUI toolkit. Events are forwarded to the scene and the navigation action
 * that is attached to this view.
 */
void RGraphicsView::handleMouseReleaseEvent(RMouseEvent& event) {
    // use mouse press position for release and final posisiton:
//    if (mousePressModelPosition.isValid()) {
//        event.setModelPosition(mousePressModelPosition);
//        mousePressModelPosition = RVector::invalid;
//    }
//    if (mousePressScreenPosition.isValid()) {
//        event.setScreenPosition(mousePressScreenPosition);
//        mousePressScreenPosition = RVector::invalid;
//    }

    lastKnownModelPosition = event.getModelPosition();
    lastKnownScreenPosition = event.getScreenPosition();
    if (scene == NULL) {
        return;
    }
    scene->handleMouseReleaseEvent(event);
    if (navigationAction!=NULL && !event.isAccepted()) {
        navigationAction->mouseReleaseEvent(event);
    }
}

/**
 * This should be called by the mouse double click event handler of a higher level
 * GUI toolkit. Events are forwarded to the scene and the navigation action
 * that is attached to this view.
 */
void RGraphicsView::handleMouseDoubleClickEvent(RMouseEvent& event) {
    lastKnownModelPosition = event.getModelPosition();
    lastKnownScreenPosition = event.getScreenPosition();
    if (scene == NULL) {
        return;
    }
    scene->handleMouseDoubleClickEvent(event);
    if (navigationAction!=NULL) {
        navigationAction->mouseDoubleClickEvent(event);
    }
}



/**
 * This should be called by the mouse wheel event handler of a higher level
 * GUI toolkit. Events are forwarded to the scene and the navigation action
 * that is attached to this view.
 */
void RGraphicsView::handleWheelEvent(RWheelEvent& event) {
    if (scene == NULL) {
        return;
    }
    scene->handleWheelEvent(event);
    if (navigationAction!=NULL) {
        navigationAction->wheelEvent(event);
    }
}

/**
 * This should be called by the tablet event handler of a higher level
 * GUI toolkit. Events are forwarded to the scene and the navigation action
 * that is attached to this view.
 */
void RGraphicsView::handleTabletEvent(RTabletEvent& event) {
    if (scene == NULL) {
        return;
    }
    scene->handleTabletEvent(event);
    if (navigationAction!=NULL) {
        navigationAction->tabletEvent(event);
    }
}

void RGraphicsView::handleSwipeGestureEvent(QSwipeGesture& gesture) {
    if (scene == NULL) {
        return;
    }
    scene->handleSwipeGestureEvent(gesture);
    if (navigationAction!=NULL) {
        navigationAction->swipeGestureEvent(gesture);
    }
}

void RGraphicsView::handlePanGestureEvent(QPanGesture& gesture) {
    if (scene == NULL) {
        return;
    }
    scene->handlePanGestureEvent(gesture);
    if (navigationAction!=NULL) {
        navigationAction->panGestureEvent(gesture);
    }
}

void RGraphicsView::handlePinchGestureEvent(QPinchGesture& gesture) {
    //qDebug() << "RGraphicsView::handlePinchGestureEvent";
    if (scene == NULL) {
        return;
    }
    scene->handlePinchGestureEvent(gesture);
    if (navigationAction!=NULL) {
        //qDebug() << "RGraphicsView::handlePinchGestureEvent: fwd to navigation action";
        navigationAction->pinchGestureEvent(gesture);
    }
}

/**
 * Sets an action object that is typically used to handle all
 * navigation interaction (zooming, panning, ...). All events that are
 * received by this view are first sent to the graphics scene
 * and then to this action if they were not consumed yet.
 */
void RGraphicsView::setNavigationAction(RAction* action) {
    if (navigationAction!=NULL) {
        navigationAction->suspendEvent();
        navigationAction->finishEvent();
        delete navigationAction;
    }

    navigationAction = action;

    if (navigationAction!=NULL) {
        navigationAction->beginEvent();
        navigationAction->setGraphicsView(this);
    }
}



/**
 * Finds the reference point that is the closest to the given screen
 * coordinate (in pixels).
 *
 * \param range Maximum distance in pixels.
 *
 * \return The closest referecene point in model coordinates.
 */
RRefPoint RGraphicsView::getClosestReferencePoint(const RVector& screenPosition, int range) {
    RRefPoint ret = RVector::invalid;
    if (scene == NULL) {
        return ret;
    }

    double minDist = (double) range;

    QMap<REntity::Id, QList<RRefPoint> >& referencePoints = scene->getReferencePoints();
    QMap<REntity::Id, QList<RRefPoint> >::iterator it;
    for (it = referencePoints.begin(); it != referencePoints.end(); it++) {
        QList<RRefPoint>& list = it.value();

        for (int i=0; i<list.length(); i++) {
            RVector rp = mapToView(list[i]);

            double dist = screenPosition.getDistanceTo(rp);
            if (dist < minDist) {
                minDist = dist;
                ret = list[i];
            }
        }
    }

    return ret;
}



/**
 * \overload
 */
RRefPoint RGraphicsView::getClosestReferencePoint(REntity::Id entityId, const RVector& screenPosition) {
    RRefPoint ret = RVector::invalid;
    double minDist = RMAXDOUBLE;

    if (scene == NULL) {
        return ret;
    }

    if (getDocument() == NULL) {
        return ret;
    }
    QSharedPointer<REntity> entity = getDocument()->queryEntity(entityId);
    if (entity.isNull()) {
        return ret;
    }

    QList<RRefPoint> referencePoints = entity->getReferencePoints(scene->getProjectionRenderingHint());
    QList<RRefPoint>::iterator it;
    for (it=referencePoints.begin(); it!=referencePoints.end(); it++) {
        RVector rp = mapToView(*it);

        double dist = screenPosition.getDistanceTo(rp);
        if (dist<minDist) {
            minDist = dist;
            ret = (*it);
        }
    }

    return ret;
}



/**
 * Finds the entity that is the closest to the given screen
 * coordinate (in pixels).
 *
 * \param range Maximum distance in pixels.
 *
 * \return The closest entity or NULL.
 */
REntity::Id RGraphicsView::getClosestEntity(const RVector& screenPosition, int range, int strictRange, bool includeLockedLayers, bool selectedOnly) {

    RVector modelPosition = mapFromView(screenPosition);
    double modelRange = mapDistanceFromView(range);
    double modelStrictRange = mapDistanceFromView(strictRange);

    if (getDocumentInterface() == NULL) {
        return REntity::INVALID_ID;
    }
    return getDocumentInterface()->getClosestEntity(modelPosition, modelRange, modelStrictRange, includeLockedLayers, selectedOnly);
}



/**
 * Finds the entity that is the closest to the given screen
 * coordinate (in pixels) and inside the current UCS (read floor).
 *
 * \param range Maximum distance in pixels.
 *
 * \return The closest entity or NULL.
 */
/*
REntity::Id RGraphicsView::getClosestEntityInUcs(
    const RVector& screenPosition, int range) {

    RVector modelPosition = mapFromView(screenPosition);
    double modelRange = mapDistanceFromView(range);

    if (getDocumentInterface()==NULL) {
        return REntity::INVALID_ID;
    }
    return getDocumentInterface()->getClosestEntityInUcs(modelPosition, modelRange);
}
*/



/**
 * Maps the given \c box (e.g. a 3d bounding box) to a 2d box
 * in view coordinates (pixels).
 */
RBox RGraphicsView::mapToView(const RBox& box) const {
    QList<RVector> boxCorners = box.getCorners();

    RVector minView(RMAXDOUBLE, RMAXDOUBLE, RMAXDOUBLE);
    RVector maxView(RMINDOUBLE, RMINDOUBLE, RMINDOUBLE);
    RVector corner;

    for (int i=0; i<8; i++) {
        corner = mapToView(boxCorners[i]);
        minView = RVector::getMinimum(corner, minView);
        maxView = RVector::getMaximum(corner, maxView);
    }

    return RBox(minView, maxView);
}


void RGraphicsView::setBackgroundColor(const QColor& col) {
    backgroundColor = col;
}

QColor RGraphicsView::getBackgroundColor() {
    if (!backgroundColor.isValid()) {
        backgroundColor = RSettings::getColor("GraphicsViewColors/BackgroundColor", RColor(0,0,0));
    }
    return backgroundColor;
}

void RGraphicsView::setMargin(int m) {
    margin = m;
}

int RGraphicsView::getMargin() {
    if (margin==-1) {
        margin = RSettings::getValue("GraphicsView/Margin", 25).toInt();
    }
    return margin;
}

void RGraphicsView::setExporting(bool on) {
    exporting = on;
}

bool RGraphicsView::isExporting() const {
    return exporting;
}

bool RGraphicsView::isPrintingOrExporting() const {
    return isPrinting() || isExporting();
}

void RGraphicsView::setPrinting(bool on) {
    printing = on;
}

bool RGraphicsView::isPrinting() const {
    return printing;
}

void RGraphicsView::setPrintPreview(bool on) {
    printPreview = on;
}

bool RGraphicsView::isPrintPreview() const {
    return printPreview;
}

void RGraphicsView::setPrintPointSize(const RVector& s) {
    printPointSize = s;
}

void RGraphicsView::setColorMode(RGraphicsView::ColorMode cm) {
    colorMode = cm;
}

RGraphicsView::ColorMode RGraphicsView::getColorMode() {
    return colorMode;
}

void RGraphicsView::setHairlineMode(bool on) {
    hairlineMode = on;
}

bool RGraphicsView::getHairlineMode() {
    return hairlineMode;
}

void RGraphicsView::setHairlineMinimumMode(bool on) {
    hairlineMinimumMode = on;
}

bool RGraphicsView::getHairlineMinimumMode() {
    return hairlineMinimumMode;
}

QList<RTextLabel> RGraphicsView::getTextLabels() {
    return textLabels;
}

void RGraphicsView::clearTextLabels() {
    textLabels.clear();
}

void RGraphicsView::addTextLabel(const RTextLabel& textLabel) {
    textLabels.append(textLabel);
}

bool RGraphicsView::isPathVisible(const RPainterPath &path) const {
    double featureSize = path.getFeatureSize();

    // no feature size given, always visible:
    if (fabs(featureSize)<RS::PointTolerance) {
        return true;
    }

    int featureSizePx = (int)mapDistanceToView(fabs(featureSize));

    if (featureSize>RS::PointTolerance) {
        // paths feature size is too small to be displayed (display real text):
        if (!isPrintingOrExporting() && featureSizePx<=textHeightThreshold) {
            return false;
        }
    }
    else if (featureSize<-RS::PointTolerance) {
        // paths feature size is too large to be displayed (bounding box):
        if (isPrintingOrExporting() || featureSizePx>textHeightThreshold) {
            return false;
        }
    }

    return true;
}

void RGraphicsView::updateTextHeightThreshold() {
    if (textHeightThresholdOverride!=-1) {
        textHeightThreshold = textHeightThresholdOverride;
    }
    else {
        textHeightThreshold = RSettings::getTextHeightThreshold();
    }
}

void RGraphicsView::setAntialiasing(bool val) {
    antialiasing = val;
}

bool RGraphicsView::getAntialiasing() const {
    return antialiasing;
}
