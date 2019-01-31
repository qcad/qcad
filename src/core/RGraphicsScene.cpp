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
#include "RDebug.h"
#include "RDocumentInterface.h"
#include "REntity.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"



RGraphicsScene::RGraphicsScene(RDocumentInterface& documentInterface)
    : RExporter(documentInterface.getDocument()),
      documentInterface(documentInterface),
      exportToPreview(false),
      colorMode(true),
      previewIsEmpty(true),
      highlightedReferencePoint(RVector::invalid),
      deleting(false) {

    setVisualExporter(true);

    documentInterface.registerScene(*this);
}

RGraphicsScene::~RGraphicsScene() {
    deleting = true;
    while (!views.isEmpty()) {
        RGraphicsView* view = views.takeFirst();
        if (view!=NULL) {
            if (!view->isShared()) {
                delete view;
            }
            else {
                view->setScene(NULL);
            }
        }
    }

    // only delete views not based on QObject
    // (those are deleted when parent is deleted)
//    do {
//        found = false;
//        for (int i=0; i<views.length(); i++) {
//            QObject* obj = dynamic_cast<QObject*>(views.at(i));
//            if (obj==NULL) {
//                qDebug() << "deleting view";
//                //delete views.takeAt(i);
//                found = true;
//                break;
//            }
//        }
//    } while(found);
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
QList<RGraphicsView*> RGraphicsScene::getGraphicsViews() const {
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

    if (regen) {
        regenerate();
    }
}

/**
 * Removes the given view from this scene.
 */
void RGraphicsScene::unregisterView(RGraphicsView* view) {
    views.removeOne(view);
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
        regenerateViews(affectedEntities);
    }
}

/**
 * Updates the selection status of the given entities. The default implementation
 * exports the entities again. May be overridden for performance reasons.
 */
void RGraphicsScene::updateSelectionStatus(QSet<REntity::Id>& affectedEntities, bool updateViews) {
    exportEntities(affectedEntities, false);

    QSet<REntity::Id>::iterator it;
    for (it=affectedEntities.begin(); it!=affectedEntities.end(); it++) {
        if (referencePoints.contains(*it)) {
            if (!document->isSelected(*it)) {
                referencePoints.remove(*it);
            }
        }
    }

    if (updateViews) {
        regenerateViews(affectedEntities);
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

void RGraphicsScene::regenerateViews(QSet<REntity::Id>& affectedEntities) {
    QList<RGraphicsView*>::iterator it;
    for (it=views.begin(); it!=views.end(); it++) {
        (*it)->regenerate(affectedEntities);
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

int RGraphicsScene::countReferencePoints() const {
    int ret = 0;
    QMap<REntity::Id, QList<RRefPoint> >::const_iterator it;
    for (it = referencePoints.begin(); it != referencePoints.end(); ++it) {
        const QList<RRefPoint>& list = it.value();
        ret+=list.length();
    }
    return ret;
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

    if (entity->isUndone() || entity->isSelected()==false) {
        // remove all previous reference points of this entity:
        referencePoints.remove(entity->getId());
        return;
    }

    QList<RRefPoint> oldRps = referencePoints.value(entity->getId());
    //qDebug() << "oldRps:" << oldRps;

    // remove all previous reference points of this entity:
    referencePoints.remove(entity->getId());

    //qDebug() << "exportReferencePoints: " << entity->getId();
    //RDebug::printBacktrace();

    // get list of reference points:
    QList<RRefPoint> rps = entity->getReferencePoints(getProjectionRenderingHint());
    //qDebug() << "rps:" << rps;

    referencePoints.insert(entity->getId(), QList<RRefPoint>());

    // export reference points:
    for (int i=0; i<rps.length(); i++) {
        RRefPoint rp = rps[i];
        if (i<oldRps.length()) {
            RRefPoint oldRp = oldRps[i];
            if (RVector(oldRp).equalsFuzzy(RVector(rp))) {
                // reuse old reference point (might be selected):
                //qDebug() << "reuse old rp: " << oldRp;
                referencePoints[entity->getId()].append(oldRp);
                continue;
            }
            else {
                if (oldRp.isSelected()) {
                    rp.setSelected(true);
                }
            }
        }

        referencePoints[entity->getId()].append(rp);
    }
}

void RGraphicsScene::selectReferencePoints(const RBox& box, bool add) {
    QMap<REntity::Id, QList<RRefPoint> >::iterator it;
    for (it=referencePoints.begin(); it!=referencePoints.end(); ++it) {
        QList<RRefPoint>& list = it.value();
        for (int i=0; i<list.length(); i++) {
            if (box.contains(list[i])) {
                list[i].setSelected(true);
            }
            else if (!add) {
                list[i].setSelected(false);
            }
        }

    }

//    QMultiMap<REntity::Id, RRefPoint>::iterator it;
//    for (it=referencePoints.begin(); it!=referencePoints.end(); ++it) {
//        if (box.contains(it.value())) {
//            it.value().setSelected(true);
//        }
//        else if (!add) {
//            it.value().setSelected(false);
//        }
//    }
}

bool RGraphicsScene::hasSelectedReferencePoints() const {
    QMap<REntity::Id, QList<RRefPoint> >::const_iterator it;
    for (it=referencePoints.constBegin(); it!=referencePoints.constEnd(); ++it) {
        const QList<RRefPoint>& list = it.value();
        for (int i=0; i<list.length(); i++) {
            if (list[i].isSelected()) {
                return true;
            }
        }
    }
    return false;
}

void RGraphicsScene::exportCurrentEntity(bool preview, bool forceSelected) {
    RExporter::exportCurrentEntity(preview, forceSelected);
    exportReferencePoints();
}

void RGraphicsScene::unexportEntity(REntity::Id entityId) {
    RExporter::unexportEntity(entityId);
    referencePoints.remove(entityId);
}

/**
 * Highlights the reference point at the given position. This is typically
 * used to highlight reference point when the mouse hovers over them.
 */
void RGraphicsScene::highlightReferencePoint(const RRefPoint& position) {
    highlightedReferencePoint = position;
}

RRefPoint RGraphicsScene::getHighlightedReferencePoint() {
    return highlightedReferencePoint;
}

/**
 * Stream operator for QDebug
 */
QDebug operator<<(QDebug dbg, RGraphicsScene& gs) {
    dbg.nospace() << "RGraphicsScene(" << QString("%1").arg((long int)&gs, 0, 16) << ")";
    return dbg.space();
}
