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

#include <QtNetwork>
#if QT_VERSION >= 0x050000
#include <QTemporaryDir>
#endif

#include "RArc.h"
#include "RCircle.h"
#include "RDocumentInterface.h"
#include "REllipse.h"
#include "REntityPickEvent.h"
#include "RFileExporter.h"
#include "RFileExporterRegistry.h"
#include "RFileImporter.h"
#include "RFileImporterRegistry.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RLine.h"
#include "RLinkedStorage.h"
#include "RPolyline.h"
#include "RMainWindow.h"
#include "RMemoryStorage.h"
#include "ROperation.h"
#include "RPoint.h"
#include "RPolyline.h"
#include "RRestrictOrthogonal.h"
#include "RScriptAction.h"
#include "RScriptHandler.h"
#include "RScriptHandlerRegistry.h"
#include "RSelectionChangedEvent.h"
#include "RSettings.h"
#include "RSingleApplication.h"
#include "RSnap.h"
#include "RSnapRestriction.h"
#include "RSpatialIndexSimple.h"
#include "RSpline.h"
#include "RTextLabel.h"
#include "RTransaction.h"
#include "RTransactionEvent.h"
#include "RWheelEvent.h"

RDocumentInterface* RDocumentInterface::clipboard = NULL;


RDocumentInterface::RDocumentInterface(RDocument& document)
  : document(document),
    lastKnownViewWithFocus(NULL),
    defaultAction(NULL),
    currentSnap(NULL),
    currentSnapRestriction(NULL),
    relativeZero(RVector(0,0)),
    relativeZeroLocked(false),
    snapLocked(false),
    cursorPosition(RVector::invalid),
    suspended(false),
    allowUpdate(true),
    allowRegeneration(true),
    notifyGlobalListeners(true),
    deleting(false),
    cursorOverride(false),
    keepPreviewOnce(false),
    mouseTrackingEnabled(true) {
    //pressEvent(NULL) {

    RDebug::incCounter("RDocumentInterface");
}

RDocumentInterface::~RDocumentInterface() {
    RDebug::decCounter("RDocumentInterface");
    deleting = true;

    for (int i=currentActions.size()-1; i>=0; i--) {
        currentActions.at(i)->suspendEvent();
    }

//    if (currentSnap!=NULL) {
//        currentSnap->hideUiOptions();
//    }

    while (!currentActions.isEmpty()) {
        // make sure that UI options are removed, etc:
        currentActions.top()->suspendEvent();
        currentActions.top()->finishEvent();
        currentActions.top()->terminate();
        delete currentActions.pop();
    }

    if (defaultAction!=NULL) {
        defaultAction->suspendEvent();
        defaultAction->finishEvent();
        defaultAction->terminate();
        delete defaultAction;
        defaultAction = NULL;
    }

    while (queuedActions.size()>0) {
        delete queuedActions.dequeue();
    }

    while (!scenes.isEmpty()) {
        delete scenes.takeFirst();
    }

    if (currentSnap!=NULL) {
        currentSnap->hideUiOptions();
        delete currentSnap;
    }

    if (currentSnapRestriction!=NULL) {
        currentSnapRestriction->hideUiOptions();
        delete currentSnapRestriction;
    }

    QMapIterator<QString, RScriptHandler*> i(scriptHandlers);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
    scriptHandlers.clear();

    delete &document;
}

/**
 * Clears cached variables to ensure they are re-initialized before the next use.
 */
void RDocumentInterface::clearCaches() {
    for (int si=0; si<scenes.size(); si++) {
        QList<RGraphicsView*> views = scenes[si]->getGraphicsViews();
        for (int vi=0; vi<views.size(); vi++) {
            views[vi]->clearCaches();
        }
    }
}

void RDocumentInterface::killAllActions() {
    for (int i = 0; i < currentActions.size(); ++i) {
        RAction* a = currentActions.at(i);
        a->terminate();
    }
}


/**
 * \return Reference to underlying document.
 */
RDocument& RDocumentInterface::getDocument() {
    return document;
}

/**
 * \return Reference to underlying storage.
 */
RStorage& RDocumentInterface::getStorage() {
    return document.getStorage();
}

RScriptHandler* RDocumentInterface::getScriptHandler(const QString& extension) {
    if (!scriptHandlers.contains(extension)) {
        scriptHandlers[extension] = RScriptHandlerRegistry::createScriptHandler(extension);
    }
    return scriptHandlers[extension];
}

bool RDocumentInterface::isScriptRunning() {
    RScriptHandler* sh = getScriptHandler("js");
    if (sh!=NULL && sh->isRunning()) {
        return true;
    }

    return false;
}

/**
 * \return List of attached graphics scenes.
 */
QList<RGraphicsScene*> RDocumentInterface::getGraphicsScenes() {
    return scenes;
}

/**
 * Adds a listener for coordinate events. This can for example be a
 * document specific widget that displays the current coordinate, e.g. rulers.
 */
void RDocumentInterface::addCoordinateListener(RCoordinateListener* l) {
    coordinateListeners.push_back(l);
}

/**
 * Notifies all coordinate listeners that the coordinate has changed to \c position.
 */
void RDocumentInterface::notifyCoordinateListeners() {
    if (!notifyGlobalListeners) {
        return;
    }

    QList<RCoordinateListener*>::iterator it;
    for (it = coordinateListeners.begin(); it != coordinateListeners.end(); ++it) {
        (*it)->updateCoordinate(this);
    }

    if (RMainWindow::hasMainWindow()) {
        RMainWindow::getMainWindow()->notifyCoordinateListeners(this);
    }
}

void RDocumentInterface::addLayerListener(RLayerListener* l) {
    layerListeners.push_back(l);
}

void RDocumentInterface::removeLayerListener(RLayerListener* l) {
    layerListeners.removeAll(l);
}

/**
 * Notifies local layer listeners only interested in layer events from this
 * particular document. Used for layer lists other than the global one
 * (e.g. in preferences).
 */
void RDocumentInterface::notifyLayerListeners(QList<RLayer::Id>& layerIds) {
    QList<RLayerListener*>::iterator it;
    for (it = layerListeners.begin(); it != layerListeners.end(); ++it) {
        (*it)->updateLayers(this, layerIds);
    }
}

int RDocumentInterface::addTransactionListener(RTransactionListener* l) {
    // find first available key:
    for (int i=0; i<1e6; i++) {
        if (!transactionListeners.contains(i)) {
            transactionListeners[i] = l;
            return i;
        }
    }
    return -1;
}

void RDocumentInterface::removeTransactionListener(int key) {
    transactionListeners.remove(key);
}

void RDocumentInterface::removeTransactionListener(RTransactionListener* l) {
    QList<int> keys = transactionListeners.keys();
    for (int i=0; i<keys.length(); i++) {
        int key = keys[i];
        if (transactionListeners[key]==l) {
            transactionListeners.remove(key);
            break;
        }
    }
}

/**
 * Notifies local transaction listeners only interested in transaction events from this
 * particular document.
 */
void RDocumentInterface::notifyTransactionListeners(RTransaction* t) {
    QMap<int, RTransactionListener*>::iterator it;
    for (it = transactionListeners.begin(); it != transactionListeners.end(); ++it) {
        (*it)->updateTransactionListener(&document, t);
    }
}

/**
 * Resets the document to its original, empty state.
 */
void RDocumentInterface::clear(bool beforeLoad) {
    document.clear(beforeLoad);
    suspended = false;
    setCurrentBlock(RBlock::modelSpaceName);

    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->clear();
    }
    setRelativeZero(RVector(0,0));

    //qDebug() << "RDocumentInterface::clear: modified: " << document.isModified();
    document.setModified(false);
}

/**
 * \return The graphics view that currently has the focus or the
 *      first attached view or NULL if no view is attached.
 */
RGraphicsView* RDocumentInterface::getGraphicsViewWithFocus() {
    RGraphicsView* ret = lastKnownViewWithFocus;

    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        QList<RGraphicsView*> views = (*it)->getGraphicsViews();
        QList<RGraphicsView*>::iterator it2;
        for (it2=views.begin(); it2!=views.end(); it2++) {
            if (ret==NULL) {
                ret = *it2;
                continue;
            }
            if ((*it2)->hasFocus()) {
                ret = *it2;
            }
        }
    }

    return ret;
}

/**
 * \return The graphics scene that currently has the focus or the
 *      first attached scene or NULL if no scene is attached.
 */
RGraphicsScene* RDocumentInterface::getGraphicsSceneWithFocus() {
    RGraphicsView* view = getGraphicsViewWithFocus();
    if (view!=NULL) {
        return view->getScene();
    }

    return NULL;
}

/**
 * Sets the action that is active if no other action is active.
 */
void RDocumentInterface::setDefaultAction(RAction* action) {
    if (defaultAction!=NULL) {
        delete defaultAction;
        defaultAction = NULL;
    }

    defaultAction = action;

    if (defaultAction != NULL) {
        defaultAction->setDocumentInterface(this);
        defaultAction->beginEvent();
    }
}

RAction* RDocumentInterface::getDefaultAction() const {
    return defaultAction;
}

/**
 * Sets the current action. This action will receive all events
 * until it finishes.
 */
void RDocumentInterface::setCurrentAction(RAction* action) {
    if (action==NULL) {
        return;
    }

    action->setDocumentInterface(this);

    if (!action->getUniqueGroup().isNull()) {
        // kill all instances of same action:
        if (hasCurrentAction()) {
            if (getCurrentAction()->getUniqueGroup()==action->getUniqueGroup()) {
                getCurrentAction()->terminate();
            }
        }
    }

    deleteTerminatedActions();

    if (!action->isOverride() && !action->hasNoState()) {
        // suspend current action (not for overrides and stateless actions)
        if (hasCurrentAction()) {
            getCurrentAction()->suspendEvent();
        } else if (defaultAction != NULL) {
            defaultAction->suspendEvent();
        }
    }

    if (action->isOverride()) {
        if (hasCurrentAction()) {
            action->setOverrideBase(getCurrentAction());
        } else if (defaultAction != NULL) {
            action->setOverrideBase(defaultAction);
        }
    }

    // add new action to action stack:
    currentActions.push(action);

    action->beginEvent();

    deleteTerminatedActions();
}

void RDocumentInterface::queueAction(RAction* action) {
    queuedActions.enqueue(action);
}

void RDocumentInterface::terminateCurrentAction() {
    if (hasCurrentAction()) {
        getCurrentAction()->escapeEvent();
        deleteTerminatedActions();
    }
}

/**
 * \return Pointer to the current action or NULL. Used by
 *      script interfaces.
 */
RAction* RDocumentInterface::getCurrentAction() {
    if (hasCurrentAction()) {
        return currentActions.top();
    }

    return NULL;
}

/**
 * \return True if at least one action is active.
 */
bool RDocumentInterface::hasCurrentAction() const {
    if (currentActions.size()>0) {
        return true;
    }

    return false;
}

/**
 * \return First stateful action in action stack. This is the action that will
 * receive zoom change events.
 */
RAction* RDocumentInterface::getCurrentStatefulAction() {
    for (int i=currentActions.size()-1; i>=0; i--) {
        if (!currentActions.at(i)->hasNoState()) {
            return currentActions.at(i);
        }
    }

    return NULL;
}

/**
 * \return true if there are any stateful actions in the action stack.
 */
bool RDocumentInterface::hasCurrentStatefulAction() const {
    for (int i=currentActions.size()-1; i>=0; i--) {
        if (!currentActions.at(i)->hasNoState()) {
            return true;
        }
    }
    return false;
}

void RDocumentInterface::suspend() {
    if (hasCurrentAction()) {
        getCurrentAction()->suspendEvent();
    } else if (defaultAction != NULL) {
        defaultAction->suspendEvent();
    }

    if (currentSnap!=NULL) {
        currentSnap->suspendEvent();
    }
    if (currentSnapRestriction!=NULL) {
        currentSnapRestriction->hideUiOptions();
    }

    suspended = true;
}

void RDocumentInterface::resume() {
    if (currentSnap!=NULL) {
        currentSnap->showUiOptions();
    }

    if (hasCurrentAction()) {
        getCurrentAction()->resumeEvent();
    }
    else {
        if (defaultAction!=NULL) {
            defaultAction->resumeEvent();
        }
    }

    repaintViews();

    suspended = false;
}

/**
 * Deletes all actions that have been terminated.
 */
void RDocumentInterface::deleteTerminatedActions() {
    bool removed = false;
    bool removedHadNoState = false;

    RVector cp = cursorPosition;

    while (currentActions.size()>0 && currentActions.top()->isTerminated()) {
        cursorPosition = RVector::invalid;
        RAction* currentAction = currentActions.top();
        currentAction->finishEvent();

        // removed (20151216): breaks snap ui options:
        //setClickMode(RAction::PickingDisabled);

        // remember GUI action group:
        QString group;
        if (currentAction->getGuiAction()!=NULL &&
            !currentAction->getGuiAction()->getGroup().isEmpty() &&
            currentAction->isOverride()) {

            group = currentAction->getGuiAction()->getGroup();
        }

        currentActions.pop();
        removedHadNoState = currentAction->hasNoState();
        delete currentAction;

        if (!group.isEmpty()) {
            RGuiAction::triggerGroupDefault(group);
        }
        removed = true;
    }

    // restore cursor position (e.g. for direct distance entry):
    cursorPosition = cp;

    // if one or more actions (with state) have been terminated, resume previous action
    // or default action:
    if (removed && !removedHadNoState) {
        if (currentActions.size()>0) {
            currentActions.top()->resumeEvent();
        }
        else if (defaultAction!=NULL) {
            defaultAction->resumeEvent();
        }
    }

    // run next queued action:
    if (queuedActions.size()>0) {
        setCurrentAction(queuedActions.dequeue());
    }
}

/**
 * Sets the click mode of the current action to the given mode.
 *
 * \see ClickMode
 */
void RDocumentInterface::setClickMode(RAction::ClickMode m) {
    if (hasCurrentAction()) {
        getCurrentAction()->setClickMode(m);
    }
    else {
        if (defaultAction!=NULL) {
            defaultAction->setClickMode(m);
        }
    }

    if (currentSnap!=NULL) {
        if (m==RAction::PickCoordinate) {
            currentSnap->showUiOptions();
        }
        else {
            currentSnap->hideUiOptions();
        }
    }
    if (currentSnapRestriction!=NULL) {
        if (m==RAction::PickCoordinate) {
            currentSnapRestriction->showUiOptions();
        }
        else {
            currentSnapRestriction->hideUiOptions();
        }
    }
}

RAction::ClickMode RDocumentInterface::getClickMode() {
    if (hasCurrentAction()) {
        return getCurrentAction()->getClickMode();
    }
    else {
        if (defaultAction!=NULL) {
            return defaultAction->getClickMode();
        }
    }

    return RAction::PickingDisabled;
}

void RDocumentInterface::setCursor(const QCursor& cursor, bool global) {
    if (global) {
        // set cursor for all document interfaces:
        RMainWindow* appWin = RMainWindow::getMainWindow();
        if (appWin!=NULL) {
            appWin->setGraphicsViewCursor(cursor);
        }

        return;
    }

    // set cursor for this document interface and attached views:
    QList<RGraphicsScene*>::iterator it;
    for (it = scenes.begin(); it != scenes.end(); it++) {
        (*it)->setCursor(cursor);
    }
}

/**
 * Registers a scene with this document interface.
 */
void RDocumentInterface::registerScene(RGraphicsScene& scene) {
    scenes.push_back(&scene);
}

/**
 * Unregisters a scene from this document interface.
 */
void RDocumentInterface::unregisterScene(RGraphicsScene& scene) {
    scenes.removeOne(&scene);
}

void RDocumentInterface::enableUpdates() {
    allowUpdate = true;
}

void RDocumentInterface::disableUpdates() {
    allowUpdate = false;
}

void RDocumentInterface::enableRegeneration() {
    allowRegeneration = true;
}

void RDocumentInterface::disableRegeneration() {
    allowRegeneration = false;
}

void RDocumentInterface::enableMouseTracking() {
    mouseTrackingEnabled = true;
}

void RDocumentInterface::disableMouseTracking() {
    mouseTrackingEnabled = false;
}

/**
 * Marks all entities with any kind of caching as dirty, so they are
 * regenerated next time regenerate is called.
 */
void RDocumentInterface::updateAllEntities() {
    document.updateAllEntities();
}

/**
 * Regenerates all scenes attached to this document interface by exporting
 * the document into them.
 */
void RDocumentInterface::regenerateScenes(bool undone) {
    if (!allowUpdate) {
        return;
    }

    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->regenerate(undone);
    }
}

/**
 * Regenerates the given part of all scenes attached to this document
 * interface by exporting the given list of entities into them.
 */
void RDocumentInterface::regenerateScenes(QSet<REntity::Id>& entityIds, bool updateViews) {
    if (!allowUpdate) {
        return;
    }

    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->regenerate(entityIds, updateViews);
    }
}

/**
 * \overload
 */
void RDocumentInterface::regenerateScenes(REntity::Id entityId, bool updateViews) {
    if (!allowUpdate) {
        return;
    }

    QSet<RObject::Id> s;
    s.insert(entityId);
    regenerateScenes(s, updateViews);
}

void RDocumentInterface::updateSelectionStatus(QSet<REntity::Id>& entityIds, bool updateViews) {
    if (!allowUpdate) {
        return;
    }

    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->updateSelectionStatus(entityIds, updateViews);
    }
}

void RDocumentInterface::updateSelectionStatus(REntity::Id entityId, bool updateViews) {
    if (!allowUpdate) {
        return;
    }

    QSet<RObject::Id> s;
    s.insert(entityId);
    updateSelectionStatus(s, updateViews);
}

/**
 * Regenerates all views.
 */
void RDocumentInterface::regenerateViews(bool force) {
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->regenerateViews(force);
    }
}

void RDocumentInterface::regenerateViews(QSet<REntity::Id>& entityIds) {
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->regenerateViews(entityIds);
    }
}

/**
 * Repaints all views.
 */
void RDocumentInterface::repaintViews() {
    if (deleting) {
        return;
    }
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->repaintViews();
    }
}

void RDocumentInterface::terminateEvent(RTerminateEvent& event) {
    Q_UNUSED(event)

    deleteTerminatedActions();
}

void RDocumentInterface::keyPressEvent(QKeyEvent& event) {
    if (hasCurrentAction()) {
        getCurrentAction()->keyPressEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->keyPressEvent(event);
    } else {
        event.ignore();
    }
}

void RDocumentInterface::keyReleaseEvent(QKeyEvent& event) {
    if (hasCurrentAction()) {
        getCurrentAction()->keyReleaseEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->keyReleaseEvent(event);
    } else {
        event.ignore();
    }
}

/**
 * Forwards the given mouse move \c event to the current action.
 */
void RDocumentInterface::mouseMoveEvent(RMouseEvent& event) {
    if (suspended || deleting || !mouseTrackingEnabled) {
        return;
    }

    if (!keepPreviewOnce) {
        //if (mouseTrackingEnabled) {
            clearPreview();
        //}
    }
    else {
        keepPreviewOnce = false;
    }

    if (hasCurrentAction()) {
        getCurrentAction()->mouseMoveEvent(event);
        previewClickEvent(*getCurrentAction(), event);
    } else if (defaultAction != NULL) {
        defaultAction->mouseMoveEvent(event);
        previewClickEvent(*defaultAction, event);
    } else {
        event.ignore();
    }

    repaintViews();
}

/**
 * Forwards the given mouse press \c event to the current action.
 */
void RDocumentInterface::mousePressEvent(RMouseEvent& event) {
    if (!mouseTrackingEnabled) {
        return;
    }

    if (hasCurrentAction()) {
        getCurrentAction()->mousePressEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->mousePressEvent(event);
    } else {
        event.ignore();
    }
}

/**
 * Forwards the given mouse release \c event to the current action.
 */
void RDocumentInterface::mouseReleaseEvent(RMouseEvent& event) {
    if (!mouseTrackingEnabled) {
        return;
    }
    if (hasCurrentAction()) {
        getCurrentAction()->mouseReleaseEvent(event);
        handleClickEvent(*getCurrentAction(), event);
    } else if (defaultAction != NULL) {
        defaultAction->mouseReleaseEvent(event);
        handleClickEvent(*defaultAction, event);
    } else {
        event.ignore();
    }
}

/**
 * Forwards the given mouse double click \c event to the current action.
 */
void RDocumentInterface::mouseDoubleClickEvent(RMouseEvent& event) {
    if (!mouseTrackingEnabled) {
        return;
    }
    if (hasCurrentAction()) {
        getCurrentAction()->mouseDoubleClickEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->mouseDoubleClickEvent(event);
    } else {
        event.ignore();
    }
}

void RDocumentInterface::coordinateEvent(RCoordinateEvent& event) {
    if (!event.isValid()) {
        return;
    }
    if (hasCurrentAction()) {
        getCurrentAction()->coordinateEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->coordinateEvent(event);
    }
}

void RDocumentInterface::coordinateEventPreview(RCoordinateEvent& event) {
    if (!event.isValid()) {
        return;
    }
    if (hasCurrentAction()) {
        getCurrentAction()->coordinateEventPreview(event);
    } else if (defaultAction != NULL) {
        defaultAction->coordinateEventPreview(event);
    }

    cursorPosition = event.getModelPosition();
}

void RDocumentInterface::commandEvent(RCommandEvent& event) {
    if (hasCurrentAction()) {
        getCurrentAction()->commandEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->commandEvent(event);
    }
}

void RDocumentInterface::commandEventPreview(RCommandEvent& event) {
    if (hasCurrentAction()) {
        getCurrentAction()->commandEventPreview(event);
    } else if (defaultAction != NULL) {
        defaultAction->commandEventPreview(event);
    }
}

/**
 * Helper function for \ref mouseReleaseEvent. Triggers an appropriate
 * higher level event for mouse clicks for the given \c action.
 * The event type depends on the action's current \ref ClickMode.
 */
void RDocumentInterface::handleClickEvent(RAction& action, RMouseEvent& event) {
    if (event.button() == Qt::LeftButton &&
        (event.modifiers() == Qt::NoModifier ||
         event.modifiers() == Qt::AltModifier ||
         event.modifiers() == Qt::ShiftModifier)) {

        switch (action.getClickMode()) {
        case RAction::PickCoordinate:
        case RAction::PickCoordinateNoSnap: {
                RCoordinateEvent ce(RVector(), event.getGraphicsScene(), event.getGraphicsView());
                ce.setModifiers(event.modifiers());
                ce.setCursorPosition(event.getModelPosition());
                if (action.getClickMode()==RAction::PickCoordinateNoSnap) {
                    ce.setModelPosition(event.getModelPosition());
                }
                else {
                    ce.setModelPosition(snap(event, false));
                }
                // 20160811: send event even if it is invalid to make sure status is updated
                // fixes FS#1456 - Drag and drop: requires two clicks with auto snap
                //if (ce.isValid()) {
                    cursorPosition = ce.getModelPosition();
                    action.coordinateEvent(ce);
                //}
            }
            break;

        case RAction::PickEntity: {
                cursorPosition = RVector::invalid;
                REntity::Id entityId = getClosestEntity(event);
                REntityPickEvent pe(entityId, event.getModelPosition(),
                    event.getGraphicsScene(), event.getGraphicsView());
                pe.setModifiers(event.modifiers());
                action.entityPickEvent(pe);
            }
            break;

        case RAction::PickingDisabled: {
                cursorPosition = RVector::invalid;
            }
            break;
        }
    }
}

/**
 * Helper function for \ref mouseMoveEvent. Triggers an appropriate
 * preview event for the given action and the current click mode the
 * action is in.
 */
void RDocumentInterface::previewClickEvent(RAction& action, RMouseEvent& event) {
    switch (action.getClickMode()) {
        case RAction::PickCoordinate:
        case RAction::PickCoordinateNoSnap: {
            RCoordinateEvent ce(RVector(), event.getGraphicsScene(), event.getGraphicsView());
            ce.setModifiers(event.modifiers());
            ce.setCursorPosition(event.getModelPosition());
            if (action.getClickMode()==RAction::PickCoordinateNoSnap) {
                ce.setModelPosition(event.getModelPosition());
            }
            else {
                ce.setModelPosition(snap(event, true));
            }
            if (ce.isValid()) {
                cursorPosition = ce.getModelPosition();
                action.coordinateEventPreview(ce);

                if (RMainWindow::hasMainWindow()) {
                    notifyCoordinateListeners();
                }
            }
        }
        break;

        case RAction::PickEntity: {
            cursorPosition = event.getModelPosition();
            REntity::Id entityId = getClosestEntity(event);
            // trigger event even if entity ID is invalid:
            REntityPickEvent pe(entityId, event.getModelPosition(),
                event.getGraphicsScene(), event.getGraphicsView());
            pe.setModifiers(event.modifiers());
            action.entityPickEventPreview(pe);

            if (RMainWindow::hasMainWindow()) {
                notifyCoordinateListeners();
            }
        }
        break;

        case RAction::PickingDisabled: {
            cursorPosition = event.getModelPosition();

            if (RMainWindow::hasMainWindow()) {
                notifyCoordinateListeners();
            }
        }
        break;
    }
}

/**
 * Forwards the given mouse wheel \c event to the current action.
 */
void RDocumentInterface::wheelEvent(RWheelEvent& event) {
    if (hasCurrentAction()) {
        getCurrentAction()->wheelEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->wheelEvent(event);
    } else {
        event.ignore();
    }
}

/**
 * Forwards the given tablet \c event to the current action.
 */
void RDocumentInterface::tabletEvent(RTabletEvent& event) {
    if (hasCurrentAction()) {
        getCurrentAction()->tabletEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->tabletEvent(event);
    } else {
        event.ignore();
    }
}

/**
 * Forwards the given gesture to the current action.
 */
void RDocumentInterface::swipeGestureEvent(QSwipeGesture& gesture) {
    if (hasCurrentAction()) {
        getCurrentAction()->swipeGestureEvent(gesture);
    } else if (defaultAction != NULL) {
        defaultAction->swipeGestureEvent(gesture);
    }
}

/**
 * Forwards the given gesture to the current action.
 */
void RDocumentInterface::panGestureEvent(QPanGesture& gesture) {
    if (hasCurrentAction()) {
        getCurrentAction()->panGestureEvent(gesture);
    } else if (defaultAction != NULL) {
        defaultAction->panGestureEvent(gesture);
    }
}

/**
 * Forwards the given gesture to the current action.
 */
void RDocumentInterface::pinchGestureEvent(QPinchGesture& gesture) {
    if (hasCurrentAction()) {
        getCurrentAction()->pinchGestureEvent(gesture);
    } else if (defaultAction != NULL) {
        defaultAction->pinchGestureEvent(gesture);
    }
}

/**
 * Forwards the given \c event to the current action to signal that a
 * property value has been changed.
 */
void RDocumentInterface::propertyChangeEvent(RPropertyEvent& event) {
    if (hasCurrentAction()) {
        getCurrentAction()->propertyChangeEvent(event);
    } else if (defaultAction != NULL) {
        defaultAction->propertyChangeEvent(event);
    }
}

/**
 * Called immediately after the user has activated a new UCS to be used as current UCS.
 */
void RDocumentInterface::ucsSetEvent(const QString& ucsName) {
    setCurrentUcs(ucsName);
}

/**
 * Called if the zoom (factor, offset) changed in the given view.
 */
void RDocumentInterface::zoomChangeEvent(RGraphicsView& view) {
    if (hasCurrentStatefulAction()) {
        getCurrentStatefulAction()->zoomChangeEvent(view);
    } else if (defaultAction != NULL) {
        defaultAction->zoomChangeEvent(view);
    }
}

RDocumentInterface::IoErrorCode RDocumentInterface::importUrl(const QUrl& url,
        const QString& nameFilter, bool notify) {
    // URL points to local file:
#if QT_VERSION >= 0x040800
    if (url.isLocalFile()) {
        QString filePath = url.toLocalFile();
        qDebug() << "importing local file:" << filePath;
        return importFile(filePath, nameFilter, notify);
    }
#endif

    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply* reply = manager.get(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    QTimer::singleShot(10000, &loop, SLOT(quit()));
    loop.exec();
    if (reply->error()!=QNetworkReply::NoError) {
        qDebug() << "Cannot download " << url << ": "<< reply->errorString();
    }

    QByteArray data = reply->readAll();

    QString fileName;
#if QT_VERSION >= 0x050000
    // QTemporaryFile would not work here since Teigha wouldn't be
    // able to open the locked file that is produced:
    QTemporaryDir dir;
    fileName = "qcad_downloaded_file.dxf";
    if (!dir.isValid()) {
        qWarning() << "cannot create temporary directory:" << dir.path();
        return RDocumentInterface::IoErrorGeneralImportUrlError;
    }
#else
    // Clumsy port to Qt 4:
    QDir dir(RSettings::getTempLocation());
    qint64 ts = QDateTime::currentMSecsSinceEpoch();
    fileName = QString("qcad%1.dxf").arg(ts);
#endif

    RDocumentInterface::IoErrorCode ret = RDocumentInterface::IoErrorGeneralImportUrlError;

    QFile file(dir.path() + QDir::separator() + fileName);
    if (!file.setPermissions(QFile::ReadOwner | QFile::WriteOwner)) {
        qWarning() << "cannot set permissions for " << dir.path() + QDir::separator() + fileName;
    }

    if (file.open(QIODevice::WriteOnly)) {
        file.write(data);
        file.close();
        ret = importFile(file.fileName(), nameFilter, notify);
        if (!file.remove()) {
            qWarning() << "cannot remove file " << file.fileName();
        }
    }
    else {
        qWarning() << "cannot open file " << file.fileName();
    }

    return ret;
}

/**
 * Imports the given file if there is a file importer registered for that
 * file type.
 */
RDocumentInterface::IoErrorCode RDocumentInterface::importFile(
        const QString& fileName, const QString& nameFilter, bool notify) {

    // TODO: improve detection of downloadable URLs:
    if (fileName.toLower().startsWith("http://") ||
        fileName.toLower().startsWith("https://") ||
        fileName.toLower().startsWith("ftp://")) {

        qDebug() << "importing URL:" << fileName;
        return importUrl(QUrl(fileName), nameFilter, notify);
    }

    RMainWindow* mainWindow = RMainWindow::getMainWindow();

    // clear before loading
    // RNewDocumentListeners are notified that we're intending to load a document:
    clear(true);
    clearCaches();

    QFileInfo fi(fileName);
    if (!fi.exists()) {
        return RDocumentInterface::IoErrorNotFound;
    }

    if (RSettings::getBoolValue("SaveAs/OpenZeroSizeFile", false)==false) {
        if (fi.size()==0) {
            return RDocumentInterface::IoErrorZeroSize;
        }
    }

    if (!fi.isReadable()) {
        return RDocumentInterface::IoErrorPermission;
    }

    // import from compiled resource:
    if (fileName.startsWith(":scripts") || fileName.startsWith(":/scripts")) {
        QString resourceFileName = fileName;
        QString tmpPath;
#if QT_VERSION >= 0x050000
        // QTemporaryFile would not work here since Teigha wouldn't be
        // able to open the locked file that is produced:
        QTemporaryDir tmpDir;
        resourceFileName = "qcad_resource_file.dxf";
        if (!tmpDir.isValid()) {
            qWarning() << "cannot create temporary directory:" << tmpDir.path();
            qWarning() << "using current directory instead";
            //return RDocumentInterface::IoErrorGeneralImportUrlError;
            tmpPath = ".";
        }
        tmpPath = tmpDir.path();
#else
        // Clumsy port to Qt 4:
        QDir tmpDir(RSettings::getTempLocation());
        qint64 ts = QDateTime::currentMSecsSinceEpoch();
        resourceFileName = QString("qcad%1.dxf").arg(ts);
        tmpPath = tmpDir.path();
#endif
        resourceFileName = tmpPath + "/" + resourceFileName;
        if (QFile::exists(resourceFileName) && !QFile::remove(resourceFileName)) {
            qWarning() << "cannot remove file:" << resourceFileName;
            return RDocumentInterface::IoErrorGeneralImportUrlError;
        }
        if (!QFile::copy(fileName, resourceFileName)) {
            qWarning() << "cannot copy file from resource to temporary directory:" << resourceFileName;
            return RDocumentInterface::IoErrorGeneralImportUrlError;
        }
        return importFile(resourceFileName, nameFilter, notify);
    }

    RFileImporter* fileImporter = RFileImporterRegistry::getFileImporter(
        fileName, nameFilter, document, mainWindow, mainWindow);
    if (fileImporter == NULL) {
        qWarning() << QString("No file importer found for file %1").arg(fileName);
        return RDocumentInterface::IoErrorNoImporterFound;
    }
    RDocumentInterface::IoErrorCode ret = RDocumentInterface::IoErrorNoError;
    QString previousFileName = document.getFileName();
    document.setFileName(fileName);

    if (mainWindow!=NULL && notify==true && notifyGlobalListeners==true) {
        mainWindow->notifyImportListenersPre(this);
    }

    if (fileImporter->importFile(fileName, nameFilter)) {
        document.setModified(false);
    } else {
        document.setFileName(previousFileName);
        qWarning() << QString("Import for file %1 failed").arg(fileName);
        ret = RDocumentInterface::IoErrorGeneralImportError;
    }

    delete fileImporter;

    if (mainWindow!=NULL && notify==true && notifyGlobalListeners==true) {
        mainWindow->notifyListeners();
        mainWindow->notifyImportListenersPost(this);
    }
    return ret;
}

QString RDocumentInterface::getCorrectedFileName(const QString& fileName, const QString& fileVersion) {
    RFileExporter* fileExporter = RFileExporterRegistry::getFileExporter(
            fileName, fileVersion, document);
    if (fileExporter == NULL) {
        return fileName;
    }
    QString ret = fileExporter->getCorrectedFileName(fileName, fileVersion);
    delete fileExporter;
    return ret;
}

bool RDocumentInterface::exportFile(const QString& fileName, const QString& fileVersion, bool resetModified) {

    RFileExporter* fileExporter = RFileExporterRegistry::getFileExporter(fileName, fileVersion, document);
    if (fileExporter == NULL) {
        return false;
    }

    RMainWindow* mainWindow = RMainWindow::getMainWindow();

    if (mainWindow!=NULL && notifyGlobalListeners==true) {
        mainWindow->notifyExportListenersPre(this);
    }

    // set temporary variables to allow exporter to store additional information
    // not available as part of the document:
    RGraphicsView* view = getLastKnownViewWithFocus();
    if (view!=NULL) {
        RBox b = view->getBox();
        RVector c = b.getCenter();
        QVariant v;
        v.setValue(c);
        document.setVariable("ViewportCenter", v);
        document.setVariable("ViewportWidth", b.getWidth());
        document.setVariable("ViewportHeight", b.getHeight());
    }

    bool success = fileExporter->exportFile(fileName, fileVersion, resetModified);

    document.removeVariable("ViewportCenter");
    document.removeVariable("ViewportWidth");
    document.removeVariable("ViewportHeight");

    if (success) {
        // Note: exporter might set the file name of the document
        // to the new name if desired
        if (resetModified) {
            //document.setFileVersion(fileVersion);
            document.setModified(false);
        }

        if (mainWindow!=NULL && notifyGlobalListeners==true) {
            mainWindow->notifyExportListenersPost(this);
        }
    }
    else {
        qWarning() << "Export Error: " << fileExporter->getErrorMessage();
        if (RMainWindow::hasMainWindow()) {
            RMainWindow::getMainWindow()->handleUserWarning(fileExporter->getErrorMessage(), true);
        }
    }
    delete fileExporter;

    return success;
}

void RDocumentInterface::tagState(const QString& tag) {
    RStorage& storage = getStorage();
    tags.insert(tag, storage.getLastTransactionId());
}

/**
 * Rollback to given transaction ID:
 */
void RDocumentInterface::undoToTag(const QString& tag) {
    if (!tags.contains(tag)) {
        qWarning() << "tag not found: '" << tag << "'";
        return;
    }

    int tid = tags.value(tag);
    RStorage& storage = getStorage();
    while (storage.getLastTransactionId()>tid) {
        undo();
    }
}

/**
 * Transaction based undo.
 */
void RDocumentInterface::undo() {
    RMainWindow* mainWindow = RMainWindow::getMainWindow();
    clearPreview();

    QList<RTransaction> t = document.undo();
    for (int i=0; i<t.length(); i++) {
        t[i].setType(RTransaction::Undo);

        //QList<RObject::Id> objectIds = t[i].getAffectedObjects();
        objectChangeEvent(t[i]);

        if (RMainWindow::hasMainWindow()) {
            RMainWindow::getMainWindow()->postTransactionEvent(t[i]);
        }
        notifyTransactionListeners(&t[i]);

        if (i==0 && mainWindow!=NULL) {
            mainWindow->handleUserMessage(QString("Undo:") + " " + t[i].getText());
        }
    }
}

/**
 * Transaction based redo.
 */
void RDocumentInterface::redo() {
    RMainWindow* mainWindow = RMainWindow::getMainWindow();
    clearPreview();

    QList<RTransaction> t = document.redo();

    for (int i=0; i<t.length(); i++) {
        t[i].setType(RTransaction::Redo);

        //QList<RObject::Id> objectIds = t[i].getAffectedObjects();
        objectChangeEvent(t[i]);

        if (RMainWindow::hasMainWindow()) {
            RMainWindow::getMainWindow()->postTransactionEvent(t[i]);
        }
        notifyTransactionListeners(&t[i]);

        if (i==t.length()-1 && mainWindow!=NULL) {
            mainWindow->handleUserMessage(QString("Redo:") + " " + t[i].getText());
        }
    }
}

/**
 * Flush transactions.
 */
void RDocumentInterface::flushTransactions() {
    document.getStorage().deleteTransactionsFrom(0);
    document.resetTransactionStack();

    if (RMainWindow::hasMainWindow()) {
        //RMainWindow::getMainWindow()->postTransactionEvent();
        RMainWindow::getMainWindow()->notifyTransactionListeners(&document, NULL);
    }
}

/**
 * Flush redoable transactions.
 */
void RDocumentInterface::flushRedo() {
    int tid = document.getStorage().getLastTransactionId();
    document.getStorage().deleteTransactionsFrom(tid);

    if (RMainWindow::hasMainWindow()) {
        //RMainWindow::getMainWindow()->postTransactionEvent();
        RMainWindow::getMainWindow()->notifyTransactionListeners(&document, NULL);
    }
}

/**
 * Sets the current snap object.
 * The document interface takes ownership of the object.
 */
void RDocumentInterface::setSnap(RSnap* snap) {
    if (currentSnap!=NULL) {
        currentSnap->finishEvent();
        delete currentSnap;
    }

    currentSnap = snap;
    if (!suspended && currentSnap!=NULL) {
        currentSnap->showUiOptions();
    }
}

/**
 * Gets the current snap object.
 */
RSnap* RDocumentInterface::getSnap() {
    return currentSnap;
}

/**
 * Sets the current snap restriction object.
 * The document interface takes ownership of the object.
 */
void RDocumentInterface::setSnapRestriction(RSnapRestriction* snapRestriction) {
    if (currentSnapRestriction!=NULL) {
        currentSnapRestriction->hideUiOptions();
        delete currentSnapRestriction;
    }

    currentSnapRestriction = snapRestriction;
    if (!suspended && currentSnapRestriction!=NULL) {
        currentSnapRestriction->showUiOptions();
    }
}

RSnapRestriction* RDocumentInterface::getSnapRestriction() {
    return currentSnapRestriction;
}

/**
 * Uses the current snap to snap the given \c position
 * to a grid point, end point, etc.
 *
 * \return Coordinate to which was snapped.
 */
RVector RDocumentInterface::snap(RMouseEvent& event, bool preview) {
    if (currentSnap!=NULL) {
        // only allow interruption by mouse move if this is a preview and no buttons are pressed:
        //if (preview && (!RSettings::getPositionByMousePress() || event.buttons()==Qt::NoButton)) {
        if (preview) {
            RMouseEvent::setOriginalMousePos(event.globalPos());
        }
        RVector ret = currentSnap->snap(event);
        if (preview) {
            RMouseEvent::resetOriginalMousePos();
        }
        if (currentSnapRestriction!=NULL) {
            ret = currentSnapRestriction->restrictSnap(ret, getRelativeZero());
        }
        if (event.modifiers()==Qt::AltModifier) {
            ret = restrictOrtho(ret, getRelativeZero(), RS::Orthogonal);
        }
        
        QSet<REntity::Id> entityIds = currentSnap->getEntityIds();
        QSet<REntity::Id>::iterator it;
        for (it=entityIds.begin(); it!=entityIds.end(); ++it) {
            highlightEntity(*it);
        }

        return ret;
    }

    return event.getModelPosition();
}

RVector RDocumentInterface::restrictOrtho(const RVector& position, const RVector& relativeZero, RS::OrthoMode mode) {
    RVector ret;
    RVector retX;
    RVector retY;

    RGraphicsView* view = getLastKnownViewWithFocus();
    if (view==NULL) {
        return ret;
    }

    RGrid* grid = view->getGrid();
    RS::IsoProjectionType projection = RS::NoProjection;
    if (grid!=NULL) {
        projection = grid->getProjection();
    }

    //if (projection!=RS::NoProjection) {
    if (grid!=NULL && grid->isIsometric()) {
        double d1, d2;
        double a1, a2;

        switch (projection) {
        default:
        case RS::IsoTop:
            a1 = RMath::deg2rad(30);
            a2 = RMath::deg2rad(150);
            // d1 = x / cos(30):
            d1 = (position.x - relativeZero.x) / (sqrt(3.0)/2);
            d2 = -d1;
            break;
        case RS::IsoLeft:
            a1 = RMath::deg2rad(150);
            a2 = RMath::deg2rad(90);
            d1 = (position.x - relativeZero.x) / (-sqrt(3.0)/2);
            d2 = (position.y - relativeZero.y);
            break;
        case RS::IsoRight:
            a1 = RMath::deg2rad(30);
            a2 = RMath::deg2rad(90);
            d1 = (position.x - relativeZero.x) / (sqrt(3.0)/2);
            d2 = (position.y - relativeZero.y);
            break;
        }

        retX = relativeZero + RVector::createPolar(d1, a1);
        retY = relativeZero + RVector::createPolar(d2, a2);
    }
    else {
        retX = RVector(relativeZero.x, position.y);
        retY = RVector(position.x, relativeZero.y);
    }

    switch (mode) {
    case RS::OrthoVertical:
        ret = retX;
        break;
    case RS::OrthoHorizonal:
        ret = retY;
        break;
    case RS::Orthogonal:
        if (retX.getDistanceTo(position) > retY.getDistanceTo(position)) {
            ret = retY;
        }
        else {
            ret = retX;
        }
        break;
    }

    return ret;
}

/**
 * \return ID of the entity that is the closest to the mouse cursor
 *      of the given event or -1 if no entity is within range.
 *
 * The event is also used to determine the maximum distance from the
 * cursor to the entity in the view in which the event originated.
 */
REntity::Id RDocumentInterface::getClosestEntity(RInputEvent& event) {
    RGraphicsView& view = event.getGraphicsView();
    RVector modelPosition = event.getModelPosition();

    // range is N pixels in model units:
    double modelRange = view.mapDistanceFromView(RSettings::getPickRange());

    return getClosestEntity(modelPosition, modelRange);
}


/**
 * \return Entity closest to the given position within the given range.
 *
 * \param range Maximum range in drawing units.
 * \param strictRange Maximum range from either end point of the entity.
 *   Zero to only return distances that are strictly orthogonal to the entity.
 * \param includeLockedLayers Return entities on locked layers.
 * \param selectedOnly Only return selected entities.
 */
REntity::Id RDocumentInterface::getClosestEntity(const RVector& position,
        double range, double strictRange, bool includeLockedLayers, bool selectedOnly) {

    RGraphicsView* view = getLastKnownViewWithFocus();
    bool draft = false;
    if (view!=NULL) {
        RGraphicsScene* scene = view->getScene();
        if (scene!=NULL) {
            draft = scene->getDraftMode();
        }
    }

    return document.queryClosestXY(position, range, draft, strictRange, includeLockedLayers, selectedOnly);
}

void RDocumentInterface::highlightEntity(REntity::Id entityId) {
    QSharedPointer<REntity> entity = document.queryEntityDirect(entityId);
    if (entity.isNull()) {
        return;
    }

    if (entity->getType()==RS::EntityViewport && document.isLayerOffOrFrozen(entity->getLayerId())) {
        return;
    }

    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->highlightEntity(*entity);
    }
}

/**
 * Highlights the given reference point.
 */
void RDocumentInterface::highlightReferencePoint(const RRefPoint& position) {
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->highlightReferencePoint(position);
    }
}

/**
 * Selects the given entity and updates the scenes accordingly.
 *
 * \param add True to add to the current selection, false otherwise.
 *
 * \todo refactor into operations
 */
void RDocumentInterface::selectEntity(REntity::Id entityId, bool add) {
    QSet<REntity::Id> set;
    set.insert(entityId);
    selectEntities(set, add);
}

/**
 * Selects the given entities and updates the scenes accordingly.
 *
 * \param add True to add to the current selection, false otherwise.
 */
int RDocumentInterface::selectEntities(const QSet<REntity::Id>& entityIds, bool add) {
    QSet<RObject::Id> objectIds;
    int ret = document.selectEntities(entityIds, add, &objectIds);
    updateSelectionStatus(objectIds, true);

    if (RMainWindow::hasMainWindow() && allowUpdate) {
        RMainWindow::getMainWindow()->postSelectionChangedEvent();
    }

    return ret;
}

/**
 * Deselects the given entities and updates the scenes accordingly.
 */
int RDocumentInterface::deselectEntities(const QSet<REntity::Id>& entityIds) {
    QSet<RObject::Id> objectIds;
    int ret = document.deselectEntities(entityIds, &objectIds);
    updateSelectionStatus(objectIds, true);

    if (ret>0 && RMainWindow::hasMainWindow()) {
        RMainWindow::getMainWindow()->postSelectionChangedEvent();
    }

    return ret;
}

/**
 * Deselects the given entity and updates the scenes accordingly.
 */
void RDocumentInterface::deselectEntity(REntity::Id entityId) {
    QSet<REntity::Id> set;
    set.insert(entityId);
    deselectEntities(set);
}

void RDocumentInterface::selectBoxXY(const RBox& box, bool add) {
    QSet<REntity::Id> entityIds;

    if (box.c2.x<box.c1.x) {
        // cross selection:
        entityIds = document.queryIntersectedEntitiesXY(box);
    }
    else {
        // contained selection:
        entityIds = document.queryContainedEntitiesXY(box);
    }

    QSet<REntity::Id> affectedEntities;
    document.selectEntities(entityIds, add, &affectedEntities);
    updateSelectionStatus(affectedEntities, true);

    if (RMainWindow::hasMainWindow()) {
        RMainWindow::getMainWindow()->postSelectionChangedEvent();
    }
}

/**
 * Selects all and updates the scenes / views accordingly.
 */
void RDocumentInterface::selectAll() {
    QSet<REntity::Id> entityIds;
    document.selectAllEntities(&entityIds);
    updateSelectionStatus(entityIds, true);

    if (RMainWindow::hasMainWindow()) {
        RMainWindow::getMainWindow()->postSelectionChangedEvent();
    }
}

/**
 * De-select all entities, for convenience.
 * \see RDocumentInterface::clearSelection()
 */
void RDocumentInterface::deselectAll() {
    clearSelection();
}

/**
 * Clears the current selection and updates the scenes / views accordingly.
 *
 * \todo refactor into operations
 */
void RDocumentInterface::clearSelection() {
    QSet<REntity::Id> entityIds;
    document.clearSelection(&entityIds);
    updateSelectionStatus(entityIds, true);

    if (RMainWindow::hasMainWindow()) {
        RMainWindow::getMainWindow()->postSelectionChangedEvent();
    }
}

/**
 * \return True if the document has selected entities.
 */
bool RDocumentInterface::hasSelection() {
    return document.hasSelection();
}

/**
 * Adds a box to the preview that represents a zoom box displayed
 * while drawing a window to magnify an area.
 */
void RDocumentInterface::addZoomBoxToPreview(const RBox& box) {
    RPolyline pl = box.getPolyline2d();

    QList<RGraphicsScene*>::iterator it;
    for (it = scenes.begin(); it != scenes.end(); it++) {
        RGraphicsScene* scene = *it;
        scene->beginPreview();
        scene->setColor(RSettings::getColor("GraphicsViewColors/ZoomBoxColor", RColor(127,0,0)));
        scene->setBrush(Qt::NoBrush);
        scene->setLineweight(RLineweight::Weight000);
        scene->setStyle(Qt::DashLine);
        scene->setLinetypeId(document.getLinetypeId("CONTINUOUS"));
        scene->exportShape(QSharedPointer<RShape>(pl.clone()));
        scene->endPreview();
    }
}

void RDocumentInterface::addShapeToPreview(RShape& shape, const RColor& color,
        const QBrush& brush, RLineweight::Lineweight lineweight,
        Qt::PenStyle style, const QList<qreal>& dashes) {

    // preview shapes are added to scene:
    QList<RGraphicsScene*>::iterator it;
    for (it = scenes.begin(); it != scenes.end(); it++) {
        RGraphicsScene* scene = *it;
        scene->beginPreview();
        scene->beginNoColorMode();
        scene->setColor(color);
        scene->setBrush(brush);
        scene->setLineweight(lineweight);
        scene->setStyle(style);
        scene->setDashPattern(dashes.toVector());
        scene->setLinetypeId(document.getLinetypeId("CONTINUOUS"));
        // ignore color mode for this preview (selection rectangle, zoom box, etc):

        scene->exportShape(QSharedPointer<RShape>(shape.clone()));

        scene->endNoColorMode();
        scene->endPreview();
    }
}

/**
 * Exports the given shape to the preview.
 *
 * \todo Support other shapes.
 */
void RDocumentInterface::addAuxShapeToPreview(RShape& shape) {
    QList<qreal> dashes;
    dashes << 10 << 5 << 2 << 5;
    RDocumentInterface::addShapeToPreview(shape, RSettings::getColor(
            "GraphicsViewColors/AuxShapeColor", RColor(121,118,197,128)), Qt::NoBrush, RLineweight::Weight000,
            Qt::CustomDashLine, dashes);
}

/**
 * Adds the given entity to the preview of all scenes / view.
 */
void RDocumentInterface::addEntityToPreview(REntity& entity) {
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->beginPreview();
        (*it)->exportEntity(entity, true, false);
        (*it)->endPreview();
    }
}

void RDocumentInterface::addDrawableToPreview(RGraphicsSceneDrawable& drawable) {
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->addToPreview(REntity::INVALID_ID, drawable);
    }
}

/**
 * \return The relative zero position in model coordinates.
 */
RVector RDocumentInterface::getRelativeZero() const {
    return relativeZero;
}

/**
 * \return The last used position, even if the relative zero is locked in one position.
 */
RVector RDocumentInterface::getLastPosition() const {
    return lastPosition;
}

/**
 * Sets the position of the relative zero point to p and updates the graphics views.
 * If the relative zero position is locked it is not moved.
 */
void RDocumentInterface::setRelativeZero(const RVector& p) {
    // update last position, even if relative zero is locked:
    lastPosition = p;

    if (relativeZeroLocked) {
        return;
    }
    relativeZero = p;
    repaintViews();
}

/**
 * Locks the position of the relative zero point.
 */
void RDocumentInterface::lockRelativeZero() {
    relativeZeroLocked = true;
}

/**
 * Unlocks the position of the relative zero point.
 */
void RDocumentInterface::unlockRelativeZero() {
    relativeZeroLocked = false;
}

/**
 * \return true if the position of the relative zero point is locked.
 */
bool RDocumentInterface::isRelativeZeroLocked() const {
    return relativeZeroLocked;
}

/**
 * Locks the current snap function so it should not be changed automatically to auto snap.
 */
void RDocumentInterface::lockSnap() {
    snapLocked = true;
}

/**
 * Unlocks the current snap function so it should be changed automatically to auto snap
 * whenever a new tool is started.
 */
void RDocumentInterface::unlockSnap() {
    snapLocked = false;
}

/**
 * Toggles snap lock.
 */
void RDocumentInterface::toggleSnapLock() {
    snapLocked = !snapLocked;
}

/**
 * \return True if snap is locked and should never be changed automatically.
 */
bool RDocumentInterface::isSnapLocked() const {
    return snapLocked;
}

/**
 * \return The last known mouse cursor position in model coordinates.
 */
RVector RDocumentInterface::getCursorPosition() const {
    return cursorPosition;
}

void RDocumentInterface::setCursorPosition(const RVector& p) {
    cursorPosition = p;
}

/**
 * Force cursor to be shown. Used for e.g. snap to intersection manual where we
 * want to show the cursor eventhough we are in entity picking mode.
 */
void RDocumentInterface::setCursorOverride(bool on) {
    cursorOverride = on;
}

bool RDocumentInterface::getCursorOverride() const {
    return cursorOverride;
}

/**
 * After calling this function, all exports go into the preview of the
 * scene instead of the scene itself.
 *
 * \see endPreview
 */
void RDocumentInterface::beginPreview() {
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->beginPreview();
    }
}

/**
 * After calling this function, all exports go into the scene
 * again and not the preview anymore.
 *
 * \see beginPreview
 */
void RDocumentInterface::endPreview() {
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->endPreview();
    }
}

/**
 * Clears the preview of all scenes.
 */
void RDocumentInterface::clearPreview() {
    cursorPosition = RVector::invalid;
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->clearPreview();
    }
}

/**
 * \return True if the previews of all scenes are empty.
 * This is used to detect if the views needs to be redrawn
 * after a mouse move event.
 */
bool RDocumentInterface::isPreviewEmpty() {
    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        if ((*it)->isPreviewEmpty()==false) {
            return false;
        }
    }

    return true;
}

/**
 * Makes sure that the current preview survives one mouse move.
 */
void RDocumentInterface::keepPreview() {
    keepPreviewOnce = true;
}

/**
 * Notifies all property listeners that the properties of the given entity should
 * be shown.
 */
void RDocumentInterface::showPropertiesOf(REntity& entity) {
    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        RMainWindow::getMainWindow()->notifyPropertyListeners(document, entity);
    }
}

/**
 * Notifies all property listeners that no properties are relevant at this
 * point. This can for example clear the property editor and other property
 * listeners.
 */
void RDocumentInterface::clearProperties() {
    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        RMainWindow::getMainWindow()->notifyPropertyListeners();
    }
}

/**
 * Zooms in at the view that currently has the focus.
 */
void RDocumentInterface::zoomIn() {
    RGraphicsView* view = getGraphicsViewWithFocus();
    if (view!=NULL) {
        view->zoomIn();
    }
}

/**
 * Zooms out at the view that currently has the focus.
 */
void RDocumentInterface::zoomOut() {
    RGraphicsView* view = getGraphicsViewWithFocus();
    if (view!=NULL) {
        view->zoomOut();
    }
}

/**
 * Auto zooms in the view that currently has the focus.
 */
void RDocumentInterface::autoZoom(int margin) {
    RGraphicsView* view = getGraphicsViewWithFocus();
    if (view != NULL) {
        view->autoZoom(margin, true);
    }
}

bool RDocumentInterface::zoomToSelection() {
    RGraphicsView* view = getGraphicsViewWithFocus();
    if (view != NULL) {
        return view->zoomToSelection();
    }
    return false;
}

/**
 * Zooms to the given \c region.
 */
void RDocumentInterface::zoomTo(const RBox& region, int margin) {
    RGraphicsView* view = getGraphicsViewWithFocus();
    if (view != NULL) {
        view->zoomTo(region, margin);
    }
}

/**
 * Zooms to the previously visible viewport.
 */
void RDocumentInterface::zoomPrevious() {
    RGraphicsView* view = getGraphicsViewWithFocus();
    if (view != NULL) {
        view->zoomPrevious();
    }
}

/**
 * Previews the given operation by applying the operation to a
 * temporary document that is linked to the (read only) document.
 */
void RDocumentInterface::previewOperation(ROperation* operation) {
    if (operation==NULL) {
        qWarning() << "RDocumentInterface::previewOperation: operation is NULL";
        return;
    }

    RSpatialIndexSimple* si = new RSpatialIndexSimple();
    RLinkedStorage* ls = new RLinkedStorage(document.getStorage());
    RDocument* previewDocument = new RDocument(*ls, *si);
    //previewDocument->setUnit(document.getUnit());

    // copy document settings (unit, current layer, etc) from source doc:
    QSharedPointer<RDocumentVariables> docVars = document.queryDocumentVariables();
    docVars->setDocument(previewDocument);
    ls->saveObject(docVars);

//    qDebug() << "prev unit: " << previewDocument->getUnit();
//    qDebug() << "prev layer: " << previewDocument->getCurrentLayerId();
//    qDebug() << "prev lintype: " << previewDocument->getCurrentLinetypeId();

    RTransaction transaction = operation->apply(*previewDocument, true);
    delete operation;

    QList<RObject::Id> obj = transaction.getAffectedObjects();

    QList<RGraphicsScene*>::iterator it;
    for (it = scenes.begin(); it != scenes.end(); it++) {
        (*it)->beginPreview();

        QList<RObject::Id>::iterator oit;
        for (oit=obj.begin(); oit!=obj.end(); ++oit) {
            QSharedPointer<REntity> e = previewDocument->queryEntity(*oit);

            if (e.isNull()) {
                continue;
            }

            e->setDocument(previewDocument);

            if (!ls->isInBackStorage(e->getBlockId())) {
                continue;
            }

            if (previewDocument->getCurrentBlockId()!=e->getBlockId()) {
                // ignore affected entities not on current block:
                continue;
            }

            (*it)->exportEntity(*e.data(), true /* preview */, false /* not all blocks*/);
        }

        (*it)->endPreview();
    }

    delete previewDocument;
}

/**
 * Applies the given operation to the document. The operation might
 * for example do something with the current selection.
 */
RTransaction RDocumentInterface::applyOperation(ROperation* operation) {
    if (operation==NULL) {
        qWarning() << "RDocumentInterface::applyOperation: operation is NULL";
        return RTransaction();
    }

    if (document.getAutoTransactionGroup()) {
        operation->setTransactionGroup(document.getTransactionGroup());
    }

    RTransaction transaction = operation->apply(document, false);
    transaction.setTypes(operation->getTransactionTypes());
    if (transaction.isFailed()) {
        qWarning() << "RDocumentInterface::applyOperation: "
                "transaction failed";
        if (RMainWindow::hasMainWindow()) {
            RMainWindow::getMainWindow()->handleUserWarning("#transaction_failed");
        }
    }

    //QList<RObject::Id> objectIds = transaction.getAffectedObjects();

    clearPreview();

    objectChangeEvent(transaction);

    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        RMainWindow::getMainWindow()->postTransactionEvent(transaction,
                    transaction.hasOnlyChanges(), operation->getEntityTypeFilter());
    }

    delete operation;

    notifyTransactionListeners(&transaction);

    return transaction;
}

/**
 * Triggers an objectChangeEvent for every object in the given set.
 */
void RDocumentInterface::objectChangeEvent(RTransaction& transaction) {
    if (transaction.getType(RTransaction::CurrentLayerChange) ||
        transaction.getType(RTransaction::CurrentLayerSelectionChange)) {

        // optimization for layer change / layer selection change:
        return;
    }

    bool ucsHasChanged = false;
    bool linetypeHasChanged = false;
    //bool layerHasChanged = false;
    QSet<RLayer::Id> changedLayerIds;
    bool blockHasChanged = false;
    bool layoutHasChanged = false;
    bool viewHasChanged = false;
    bool entityHasChanged = false;

    QList<RObject::Id> objectIds = transaction.getAffectedObjects();

    QSet<REntity::Id> entityIdsToRegenerate;

    QList<RObject::Id>::iterator it;
    for (it=objectIds.begin(); it!=objectIds.end(); ++it) {
        RObject::Id objectId = *it;
        QSharedPointer<RObject> object = document.queryObjectDirect(objectId);
        if (object.isNull()) {
            continue;
        }

        QSharedPointer<RDocumentVariables> docVars = object.dynamicCast<RDocumentVariables> ();
        if (!docVars.isNull()) {
            ucsHasChanged = true;
            linetypeHasChanged = true;
            //layerHasChanged = true;
            blockHasChanged = true;
            layoutHasChanged = true;
            viewHasChanged = true;
            continue;
        }

        QSharedPointer<REntity> entity = object.dynamicCast<REntity> ();
        if (!entity.isNull()) {
            entityHasChanged = true;
            entityIdsToRegenerate.insert(entity->getId());
            continue;
        }

        QSharedPointer<RUcs> ucs = object.dynamicCast<RUcs> ();
        if (!ucs.isNull()) {
            ucsHasChanged = true;
            continue;
        }

        QSharedPointer<RLinetype> linetype = object.dynamicCast<RLinetype> ();
        if (!linetype.isNull()) {
            linetypeHasChanged = true;
            continue;
        }

        QSharedPointer<RLayer> layer = object.dynamicCast<RLayer> ();
        if (!layer.isNull()) {
            //qDebug() << "layer changed";
            //layerHasChanged = true;
            changedLayerIds.insert(objectId);

            // deselect entities on locked or invisible layer:
            if (layer->isLocked() || layer->isOffOrFrozen()) {
                if (document.hasSelection()) {
                    QSet<RObject::Id> ids = document.queryLayerEntities(*it);
                    deselectEntities(ids);
                }
            }

            if (transaction.getType(RTransaction::LayerVisibilityStatusChange)) {
                //qDebug() << "layer visibility changed";
                // tag all block references as changed as they might contain entities on that layer:
                // TODO: only tag if they do contain entities on that layer
                QSet<RObject::Id> blockReferenceIds = document.queryAllBlockReferences();
                //qDebug() << "blockReferenceIds:" << blockReferenceIds;
                entityIdsToRegenerate.unite(blockReferenceIds);
    //            QSet<RObject::Id>::iterator it;
    //            for (it=blockReferenceIds.begin(); it!=blockReferenceIds.end(); it++) {
    //                RObject::Id id = *it;
    //                QSharedPointer<REntity> e = document.queryEntityDirect(id);
    //                if (e.isNull()) {
    //                    continue;
    //                }
    //                QSharedPointer<RBlockReferenceEntity> blockRef = e.dynamicCast<RBlockReferenceEntity>();
    //                QSet<REntity::Id> blockEntityIds = document.queryBlockEntities(blockRef->getReferencedBlockId());
    //            }
            }
            continue;
        }

        QSharedPointer<RBlock> block = object.dynamicCast<RBlock> ();
        if (!block.isNull()) {
            //if (block->getId()!=document.getModelSpaceBlockId()) {
            if (block->getId()!=document.getCurrentBlockId()) {
                blockHasChanged = true;
                //document.queryBlockReferences(block->getId());
            }
            else {
                QList<RPropertyChange> propertyChanges = transaction.getPropertyChanges(objectId);
                for (int i=0; i<propertyChanges.length(); i++) {
                    if (propertyChanges[i].getPropertyTypeId()==RBlock::PropertyName) {
                        // current block renamed (needs block list update):
                        blockHasChanged = true;
                    }
                }
            }

            // deselect block reference entities of hidden block:
            if (block->isFrozen()) {
                QSet<RObject::Id> ids = document.queryBlockReferences(*it);
                deselectEntities(ids);
            }
            continue;
        }

        QSharedPointer<RLayout> layout = object.dynamicCast<RLayout> ();
        if (!layout.isNull()) {
            layoutHasChanged = true;
            continue;
        }

        QSharedPointer<RView> view = object.dynamicCast<RView> ();
        if (!view.isNull()) {
            viewHasChanged = true;
            continue;
        }
    }

    QList<RLayer::Id> changedLayerIdList = changedLayerIds.toList();

    // notify local listeners:
    if (!changedLayerIds.isEmpty()) {
        notifyLayerListeners(changedLayerIdList);
    }

    // notify global listeners if this is not the clipboard document interface:
    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        if (ucsHasChanged) {
            RMainWindow::getMainWindow()->notifyUcsListeners(this);
        }
        if (linetypeHasChanged) {
            // TODO:
            //RMainWindow::getMainWindow()->notifyLinetypeListeners(this);
        }
        if (!changedLayerIds.isEmpty()) {
            RMainWindow::getMainWindow()->notifyLayerListeners(this, changedLayerIdList);
        }
        if (blockHasChanged || layoutHasChanged) {
            RMainWindow::getMainWindow()->notifyBlockListeners(this);
        }
        if (viewHasChanged) {
            RMainWindow::getMainWindow()->notifyViewListeners(this);
        }
    }

    if (transaction.getType(RTransaction::LayerLockStatusChange)) {
        // only lock status has changed, no regen:
        return;
    }

    if (transaction.getType(RTransaction::LayerVisibilityStatusChange)) {
        // only visibility has changed, regen block references only:
        // TODO: this can still be slow for drawings with many / complex block references
        // TODO: find out which block references really need a regen or store layer info with
        //       painter paths to switch off easily
        regenerateScenes(entityIdsToRegenerate, false);
        regenerateViews(entityIdsToRegenerate);
        return;
    }

    if (/*layerHasChanged ||*/ !changedLayerIds.isEmpty() || blockHasChanged || linetypeHasChanged) {
        if (allowRegeneration) {
            regenerateScenes(true);
        }
        else {
            regenerateScenes(entityIdsToRegenerate, false);
        }
    }
    else {
        regenerateScenes(entityIdsToRegenerate, false);
    }

    regenerateViews(entityIdsToRegenerate);
}

void RDocumentInterface::setCurrentColor(const RColor& color) {
    document.setCurrentColor(color);
}

RColor RDocumentInterface::getCurrentColor() {
    return document.getCurrentColor();
}

void RDocumentInterface::setCurrentLineweight(RLineweight::Lineweight lw) {
    document.setCurrentLineweight(lw);
}

RLineweight::Lineweight RDocumentInterface::getCurrentLineweight() {
    return document.getCurrentLineweight();
}

void RDocumentInterface::setCurrentLinetype(RLinetype::Id ltId) {
    document.setCurrentLinetype(ltId);
}

void RDocumentInterface::setCurrentLinetypePattern(const RLinetypePattern& p) {
    document.setCurrentLinetypePattern(p);
}

RLinetype::Id RDocumentInterface::getCurrentLinetypeId() {
    return document.getCurrentLinetypeId();
}

RLinetypePattern RDocumentInterface::getCurrentLinetypePattern() {
    return document.getCurrentLinetypePattern();
}

/**
 * Sets the current layer based on the given layer name.
 */
void RDocumentInterface::setCurrentLayer(const QString& layerName) {
    RLayer::Id previousLayerId = document.getCurrentLayerId();
    document.setCurrentLayer(layerName);
    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        RMainWindow::getMainWindow()->notifyLayerListenersCurrentLayer(this, previousLayerId);
    }
}

void RDocumentInterface::setCurrentLayer(RLayer::Id layerId) {
    RLayer::Id previousLayerId = document.getCurrentLayerId();
    document.setCurrentLayer(layerId);
    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        RMainWindow::getMainWindow()->notifyLayerListenersCurrentLayer(this, previousLayerId);
    }
}

/**
 * Sets the current Layer that is in use for all views attached to 
 * this document interface.
 */
void RDocumentInterface::setCurrentLayer(const RLayer& layer) {
    setCurrentLayer(layer.getName());
}

/**
 * Sets the current block that is in use for all views attached to
 * this document interface.
 */
void RDocumentInterface::setCurrentBlock(RBlock::Id blockId) {
    clearSelection();
    document.setCurrentBlock(blockId);
    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        RMainWindow::getMainWindow()->notifyBlockListenersCurrentBlock(this);
    }
    regenerateScenes();
}

/**
 * Sets the current block based on the given block name.
 */
void RDocumentInterface::setCurrentBlock(const QString& blockName) {
    setCurrentBlock(document.getBlockId(blockName));
}

/**
 * Sets the current block that is in use for all views attached to
 * this document interface.
 */
void RDocumentInterface::setCurrentBlock(const RBlock& block) {
    setCurrentBlock(block.getId());
}

void RDocumentInterface::setCurrentViewport(const RViewportEntity& viewport) {
    RViewportEntity::Id prevViewportId = document.getCurrentViewportId();

    document.setCurrentViewport(viewport.getId());

//    inputTransform.reset();

//    inputTransform.translate(viewport.getViewCenter().x, viewport.getViewCenter().y);
//    inputTransform.translate(viewport.getViewTarget().x, viewport.getViewTarget().y);

//    inputTransform.rotateRadians(-viewport.getRotation());
//    if (!RMath::fuzzyCompare(viewport.getScale(), RS::PointTolerance)) {
//        inputTransform.scale(1.0/viewport.getScale(), 1.0/viewport.getScale());
//    }

//    inputTransform.translate(-viewport.getPosition().x, -viewport.getPosition().y);

    regenerateScenes(prevViewportId, true);
    regenerateScenes(viewport.getId(), true);


//    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
//        RMainWindow::getMainWindow()->notifyBlockListeners(this);
//    }
}

void RDocumentInterface::unsetCurrentViewport() {
    RViewportEntity::Id prevViewportId = document.getCurrentViewportId();

    document.unsetCurrentViewport();

//    inputTransform.reset();

    regenerateScenes(prevViewportId, true);
}

/**
 * Sets the current view based on the given view name.
 */
void RDocumentInterface::setCurrentView(const QString& viewName) {
    document.setCurrentView(viewName);
    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        RMainWindow::getMainWindow()->notifyViewListeners(this);
    }
}

/**
 * Sets the current UCS based on the given UCS name.
 * \todo refactor to store current UCS in document / storage like layer
 */
void RDocumentInterface::setCurrentUcs(const QString& ucsName) {
    currentUcsName = ucsName;

    QSharedPointer<RUcs> ucs = document.queryUcs(ucsName);
    if (ucs.isNull()) {
        qWarning("RDocumentInterface::setCurrentUcs: "
            "UCS with name '%s' not found.", (const char*)ucsName.toUtf8());
        return;
    }

    setCurrentUcs(*ucs);
}

/**
 * Sets the current UCS (user coordinate system) that is in use
 * for all views attached to this document interface.
 */
void RDocumentInterface::setCurrentUcs(const RUcs& ucs) {
    currentUcs = ucs;
    regenerateViews(true);
    if (RMainWindow::hasMainWindow() && notifyGlobalListeners) {
        RMainWindow::getMainWindow()->notifyUcsListeners(this);
    }
}

/**
 * \return The current UCS (user coordinate system).
 */
RUcs RDocumentInterface::getCurrentUcs() {
    return currentUcs;
}

/**
 * \return The current UCS name.
 */
QString RDocumentInterface::getCurrentUcsName() {
    return currentUcsName;
}


RDocumentInterface& RDocumentInterface::getClipboard() {
    if (clipboard==NULL) {
        clipboard = new RDocumentInterface(RDocument::getClipboard());
        clipboard->setNotifyListeners(false);
    }

    return *clipboard;
}

void RDocumentInterface::deleteClipboard() {
    if (clipboard!=NULL) {
        delete clipboard;
        clipboard = NULL;
    }
}

RGraphicsView* RDocumentInterface::getLastKnownViewWithFocus() {
    return lastKnownViewWithFocus;
}

void RDocumentInterface::setLastKnownViewWithFocus(RGraphicsView* view) {
    if (view!=NULL && view->registerForFocus()) {
        lastKnownViewWithFocus = view;
    }
}

QVariant RDocumentInterface::eval(const QString& ext, const QString& script) {
    RScriptHandler* handler = getScriptHandler(ext);
    if (handler==NULL) {
        return QVariant();
    }
    return handler->eval(script);
}
