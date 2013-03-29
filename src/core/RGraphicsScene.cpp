/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include "RDebug.h"
#include "RDocumentInterface.h"
#include "REntity.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"



RGraphicsScene::RGraphicsScene(RDocumentInterface& documentInterface)
    : RExporter(documentInterface.getDocument()),
      documentInterface(documentInterface),
      exportToPreview(false),
      previewIsEmpty(true),
      highlightedReferencePoint(RVector::invalid),
      gotDraftView(false),
      gotNormalView(false),
      deleting(false) {

    setVisualExporter(true);

    documentInterface.registerScene(*this);
}

RGraphicsScene::~RGraphicsScene() {
    deleting = true;
    while (!views.isEmpty()) {
        delete views.takeFirst();
    }
}

/**
 * \return Document interface this scene is attached to.
 */
RDocumentInterface& RGraphicsScene::getDocumentInterface() {
    return documentInterface;
}

/**
 * \return List of all views that are attached to this scene.
 */
QList<RGraphicsView*> RGraphicsScene::getGraphicsViews() {
    return views;
}

/**
 * Clears (resets) the scene contents.
 */
void RGraphicsScene::clear() {
    referencePoints.clear();
    previewIsEmpty = true;
    highlightedReferencePoint = RVector::invalid;
}

/**
 * Registers a view with this scene.
 */
void RGraphicsScene::registerView(RGraphicsView* view, bool regen) {
    if (view==NULL) {
        qWarning("RGraphicsScene::registerView: view is NULL");
        return;
    }
    views.push_back(view);
    if (documentInterface.getLastKnownViewWithFocus()==NULL) {
        documentInterface.setLastKnownViewWithFocus(view);
    }

    updateDraftStatus(regen);
}

/**
 * Removes the given view from this scene.
 */
void RGraphicsScene::unregisterView(RGraphicsView* view) {
    views.removeOne(view);
    updateDraftStatus();
}

void RGraphicsScene::beginPreview() {
    exportToPreview = true;
    previewIsEmpty = false;
}

void RGraphicsScene::endPreview() {
    exportToPreview = false;
}

/**
 * Clears the preview.
 */
void RGraphicsScene::clearPreview() {
    previewIsEmpty = true;
    highlightedReferencePoint = RVector::invalid;
}

bool RGraphicsScene::isPreviewEmpty() {
    return previewIsEmpty;
}

/**
 * Regenerates this scene from the entity data by exporting the whole document into
 * it. This can for example regenerate all painter paths or all triangles
 * of the scene. This is called if the scene changes fundamentally or when the
 * entities that are affected by an update are not known.
 */
void RGraphicsScene::regenerate(bool undone) {
    if (deleting) {
        return;
    }

    exportEntities(false, undone);
    regenerateViews(true);
}

/**
 * Regenerates part of this scene from the entity data by exporting the given
 * entities into it. This is called if the scene changes only partly and
 * the entities that are affected by the update are known.
 */
void RGraphicsScene::regenerate(QSet<REntity::Id>& affectedEntities, bool updateViews) {
    exportEntities(affectedEntities, false);
    if (updateViews) {
        regenerateViews(true);
    }
}

/**
 * Updates the selection status of the given entities. The default implementation
 * exports the entities again. May be overridden for performance reasons.
 */
void RGraphicsScene::updateSelectionStatus(QSet<REntity::Id>& affectedEntities, bool updateViews) {
    exportEntities(affectedEntities, false);
    if (updateViews) {
        regenerateViews(true);
    }
}

/**
 * Regenerates all views attached to this scene.
 */
void RGraphicsScene::regenerateViews(bool force) {
    QList<RGraphicsView*>::iterator it;
    for (it=views.begin(); it!=views.end(); it++) {
        (*it)->regenerate(force);
    }
}

/**
 * Repaints all views attached to this scene.
 */
void RGraphicsScene::repaintViews() {
    QList<RGraphicsView*>::iterator it;
    for (it=views.begin(); it!=views.end(); it++) {
        (*it)->repaintView();
    }
}

void RGraphicsScene::setCursor(const QCursor& cursor) {
    QList<RGraphicsView*>::iterator it;
    for (it = views.begin(); it != views.end(); it++) {
        (*it)->setCursor(cursor);
    }
}

void RGraphicsScene::handleTerminateEvent(RTerminateEvent& event) {
    documentInterface.terminateEvent(event);
}

void RGraphicsScene::handleKeyPressEvent(QKeyEvent& event) {
    documentInterface.keyPressEvent(event);
}

void RGraphicsScene::handleKeyReleaseEvent(QKeyEvent& event) {
    documentInterface.keyReleaseEvent(event);
}

/**
 * Forwards the given mouse event to the document interface.
 */
void RGraphicsScene::handleMouseMoveEvent(RMouseEvent& event) {
    documentInterface.mouseMoveEvent(event);
}

/**
 * Forwards the given mouse event to the document interface.
 */
void RGraphicsScene::handleMousePressEvent(RMouseEvent& event) {
    documentInterface.mousePressEvent(event);
}

/**
 * Forwards the given mouse event to the document interface.
 */
void RGraphicsScene::handleMouseReleaseEvent(RMouseEvent& event) {
    documentInterface.mouseReleaseEvent(event);
}

/**
 * Forwards the given mouse event to the document interface.
 */
void RGraphicsScene::handleMouseDoubleClickEvent(RMouseEvent& event) {
    documentInterface.mouseDoubleClickEvent(event);
}

/**
 * Forwards the given mouse event to the document interface.
 */
void RGraphicsScene::handleWheelEvent(RWheelEvent& event) {
    documentInterface.wheelEvent(event);
}

/**
 * Forwards the given tablet event to the document interface.
 */
void RGraphicsScene::handleTabletEvent(RTabletEvent& event) {
    documentInterface.tabletEvent(event);
}

/**
 * Forwards the given gesture to the document interface.
 */
void RGraphicsScene::handleSwipeGestureEvent(QSwipeGesture& gesture) {
    documentInterface.swipeGestureEvent(gesture);
}

/**
 * Forwards the given gesture to the document interface.
 */
void RGraphicsScene::handlePanGestureEvent(QPanGesture& gesture) {
    documentInterface.panGestureEvent(gesture);
}

/**
 * Forwards the given gesture to the document interface.
 */
void RGraphicsScene::handlePinchGestureEvent(QPinchGesture& gesture) {
    documentInterface.pinchGestureEvent(gesture);
}

/**
 * Adds the reference points of the entity that is currently being exported
 * to the internal \c referencePoints map.
 */
void RGraphicsScene::exportReferencePoints() {
    // don't change reference points if we're only dealing with a preview:
    if (exportToPreview) {
        return;
    }

    const REntity* entity = getBlockRefOrEntity();
    if (entity==NULL) {
        return;
    }

    // remove all previous reference points of this entity:
    referencePoints.remove(entity->getId());

    if (entity->isUndone() || entity->isSelected()==false) {
        return;
    }

    // get list of reference points:
    QList<RVector> ref = entity->getReferencePoints(getProjectionRenderingHint());

    // export reference points:
    QList<RVector>::iterator it;
    for (it=ref.begin(); it!=ref.end(); ++it) {
        referencePoints.insert(entity->getId(), *it);
    }
}

void RGraphicsScene::exportCurrentEntity(bool preview) {
    RExporter::exportCurrentEntity(preview);
    exportReferencePoints();
}

void RGraphicsScene::unexportEntity(REntity::Id entityId) {
    RExporter::unexportEntity(entityId);
    referencePoints.remove(entityId);
}

void RGraphicsScene::highlightReferencePoint(const RVector& position) {
    highlightedReferencePoint = position;
}

RVector RGraphicsScene::getHighlightedReferencePoint() {
    return highlightedReferencePoint;
}

/**
 * Called when a view changes its draft mode status or a new view is added.
 * Updates internal information about availability of draft / normal mode.
 */
void RGraphicsScene::updateDraftStatus(bool regen) {
    bool oldDraftView = gotDraftView;
    bool oldNormalView = gotNormalView;

    gotDraftView = false;
    gotNormalView = false;

    QList<RGraphicsView*>::iterator it;
    for (it = views.begin(); it != views.end(); it++) {
        bool dm = (*it)->getDraftMode();
        if (dm) {
            gotDraftView = true;
        }
        if (!dm) {
            gotNormalView = true;
        }
    }

    if (regen && (gotDraftView!=oldDraftView || gotNormalView!=oldNormalView)) {
        //regenerateViews(true);
        regenerate();
    }
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RGraphicsScene& gs) {
    dbg.nospace() << "RGraphicsScene(" << QString("%1").arg((long int)&gs, 0, 16) << ")";
    return dbg.space();
}
