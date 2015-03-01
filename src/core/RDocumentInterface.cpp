/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
#include <QMutexLocker>

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
    actionStackMutex(QMutex::Recursive),
    lastKnownViewWithFocus(NULL),
    defaultAction(NULL),
    currentSnap(NULL),
    currentSnapRestriction(NULL),
    relativeZero(RVector(0,0)),
    relativeZeroLocked(false),
    cursorPosition(RVector::invalid),
    suspended(false),
    allowUpdate(true),
    allowRegeneration(true),
    notifyListeners(true),
    deleting(false),
    cursorOverride(false),
    keepPreviewOnce(false),
    mouseTrackingEnabled(true) {
}

RDocumentInterface::~RDocumentInterface() {
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
        delete currentActions.pop();
    }

    if (defaultAction!=NULL) {
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
    if (!notifyListeners) {
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

/**
 * Resets the document to its original, empty state.
 */
void RDocumentInterface::clear() {
    document.clear();
    suspended = false;
    setCurrentBlock(RBlock::modelSpaceName);

    QList<RGraphicsScene*>::iterator it;
    for (it=scenes.begin(); it!=scenes.end(); it++) {
        (*it)->clear();
    }
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
bool RDocumentInterface::hasCurrentAction() {
    if (currentActions.size()>0) {
        return true;
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
        currentSnap->hideUiOptions();
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

    QMutexLocker locker(&actionStackMutex);
    while (currentActions.size()>0 && currentActions.top()->isTerminated()) {
        cursorPosition = RVector::invalid;
        RAction* currentAction = currentActions.top();

        currentAction->finishEvent();
        setClickMode(RAction::PickingDisabled);
        // remember GUI action group:
        QString group;
        if (currentAction->getGuiAction() != NULL &&
            !currentAction->getGuiAction()->getGroup().isEmpty() &&
            currentAction->isOverride()) {

            group = currentAction->getGuiAction()->getGroup();
        }

        currentActions.pop();
        delete currentAction;

        if (!group.isEmpty()) {
            RGuiAction::triggerGroupDefault(group);
        }
        removed = true;

    }

    // if one or more actions have been terminated, resume previous action
    // or default action:
    if (removed) {
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
        RMainWindow* appWin = RMainWindow::getMainWindow();
        if (appWin!=NULL) {
            appWin->setGraphicsViewCursor(cursor);
        }

        return;
    }

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

/**
 * Repaints all views.
 */
void RDocumentInterface::repaintViews() {
    if (deleting) {
        return;
    }

    for (auto scene : scenes) {
        scene->repaintViews();
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

    //if (mouseTrackingEnabled) {
        repaintViews();
    //}
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
    // No lock needed for actions
    if (event.button() == Qt::LeftButton && event.modifiers() == Qt::NoModifier) {
        switch (action.getClickMode()) {
        case RAction::PickCoordinate: {
                RCoordinateEvent ce(snap(event),
                    event.getGraphicsScene(), event.getGraphicsView());
                if (ce.isValid()) {
                    cursorPosition = ce.getModelPosition();
                    action.coordinateEvent(ce);
                }
            }
            break;

        case RAction::PickEntity: {
                cursorPosition = RVector::invalid;
                REntity::Id entityId = getClosestEntity(event);
                REntityPickEvent pe(entityId, event.getModelPosition(),
                    event.getGraphicsScene(), event.getGraphicsView());
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
        case RAction::PickCoordinate: {
            RCoordinateEvent ce(snap(event),
                event.getGraphicsScene(), event.getGraphicsView());
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

RDocumentInterface::IoErrorCode RDocumentInterface::importUrl(const QUrl& url,
        bool notify) {
    // URL points to local file:
    if (url.scheme()=="file") {
        QString filePath = url.toLocalFile();
        return importFile(filePath, "", notify);
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get(QNetworkRequest(url));
    do {
        // dangerous: processing events here allows user to 'interrupt'
        // by sending events (mouse moves, etc)
        //QApplication::processEvents();
    } while (reply->isRunning());
    QByteArray data = reply->readAll();

    QString suffix = QFileInfo(url.path()).suffix();

    QTemporaryFile file(QDir::tempPath() + QDir::separator() + "qcad_XXXXXX." + suffix);
    if (file.open()) {
        file.write(data);
        file.close();
        return importFile(file.fileName(), "", notify);
    }
    return RDocumentInterface::IoErrorGeneralImportUrlError;
}

/**
 * Imports the given file if there is a file importer registered for that
 * file type.
 */
RDocumentInterface::IoErrorCode RDocumentInterface::importFile(
        const QString& fileName, const QString& nameFilter, bool notify) {

    RMainWindow* mainWindow = RMainWindow::getMainWindow();

    clearCaches();

    QFileInfo fi(fileName);
    if (fi.size()==0) {
        return RDocumentInterface::IoErrorZeroSize;
    }

    if (!fi.exists()) {
        return RDocumentInterface::IoErrorNotFound;
    }

    if (!fi.isReadable()) {
        return RDocumentInterface::IoErrorPermission;
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

    if (mainWindow!=NULL && notify==true && notifyListeners==true) {
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

    if (mainWindow!=NULL && notify==true && notifyListeners==true) {
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
    RFileExporter* fileExporter = RFileExporterRegistry::getFileExporter(
            fileName, fileVersion, document);
    if (fileExporter == NULL) {
        return false;
    }

    RMainWindow* mainWindow = RMainWindow::getMainWindow();

    if (mainWindow!=NULL && notifyListeners==true) {
        mainWindow->notifyExportListenersPre(this);
    }

    bool success = fileExporter->exportFile(fileName, fileVersion, resetModified);

    if (success) {
        // Note: exporter might set the file name of the document
        // to the new name if desired
        if (resetModified) {
            document.setFileVersion(fileVersion);
            document.setModified(false);
        }

        if (mainWindow!=NULL && notifyListeners==true) {
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

/**
 * Transaction based undo.
 */
void RDocumentInterface::undo() {
    clearPreview();

    QList<RTransaction> t = document.undo();
    for (int i=0; i<t.length(); i++) {
        QList<RObject::Id> objectIds = t[i].getAffectedObjects();
        objectChangeEvent(objectIds);

        if (RMainWindow::hasMainWindow()) {
            RMainWindow::getMainWindow()->postTransactionEvent(t[i]);
        }
    }
}

/**
 * Transaction based redo.
 */
void RDocumentInterface::redo() {
    clearPreview();

    QList<RTransaction> t = document.redo();

    for (int i=0; i<t.length(); i++) {
        QList<RObject::Id> objectIds = t[i].getAffectedObjects();
        objectChangeEvent(objectIds);

        if (RMainWindow::hasMainWindow()) {
            RMainWindow::getMainWindow()->postTransactionEvent(t[i]);
        }
    }
}

/**
 * Flush transactions.
 */
void RDocumentInterface::flushTransactions() {
    document.resetTransactionStack();
    document.getStorage().deleteTransactionsFrom(0);

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
        currentSnap->hideUiOptions();
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
RVector RDocumentInterface::snap(RMouseEvent& event) {
    if (currentSnap!=NULL) {
        RMouseEvent::setOriginalMousePos(event.globalPos());
        RVector ret = currentSnap->snap(event);
        RMouseEvent::resetOriginalMousePos();
        if (currentSnapRestriction!=NULL) {
            ret = currentSnapRestriction->restrictSnap(ret, getRelativeZero());
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

/**
 * \return ID of the entity that is the closest to the mouse cursor
 *      of the given event.
 *
 * The event is also used to determine the maximum distance from the
 * cursor to the entity in the view in which the event originated.
 */
REntity::Id RDocumentInterface::getClosestEntity(RMouseEvent& event) {
    RGraphicsView& view = event.getGraphicsView();
    RVector modelPosition = event.getModelPosition();

    // range is 10 pixels in model units:
    double modelRange = view.mapDistanceFromView(10);

    return getClosestEntity(modelPosition, modelRange);
}



REntity::Id RDocumentInterface::getClosestEntity(const RVector& position,
        double range, double strictRange, bool includeLockedLayers) {

    RGraphicsView* view = getLastKnownViewWithFocus();
    bool draft = false;
    if (view!=NULL) {
        RGraphicsScene* scene = view->getScene();
        if (scene!=NULL) {
            draft = scene->getDraftMode();
        }
    }

    return document.queryClosestXY(position, range, draft, strictRange, includeLockedLayers);
}

/**
 * \override
 */
void RDocumentInterface::highlightEntity(REntity::Id entityId) {
    QSharedPointer<REntity> entity = document.queryEntityDirect(entityId);
    if (entity.isNull()) {
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
void RDocumentInterface::highlightReferencePoint(const RVector& position) {
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
void RDocumentInterface::selectEntities(const QSet<REntity::Id>& entityIds, bool add) {
    QSet<RObject::Id> objectIds;
    document.selectEntities(entityIds, add, &objectIds);
    updateSelectionStatus(objectIds, true);

    if (RMainWindow::hasMainWindow() && allowUpdate) {
        RMainWindow::getMainWindow()->postSelectionChangedEvent();
    }
}

/**
 * Deselects the given entities and updates the scenes accordingly.
 */
void RDocumentInterface::deselectEntities(const QSet<REntity::Id>& entityIds) {
    QSet<RObject::Id> objectIds;
    document.deselectEntities(entityIds, &objectIds);
    updateSelectionStatus(objectIds, true);

    if (RMainWindow::hasMainWindow()) {
        RMainWindow::getMainWindow()->postSelectionChangedEvent();
    }
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
        entityIds = document.queryIntersectedEntitiesXY(box);
    }
    else {
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
    document.selectAllEntites(&entityIds);
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
    QList<RVector> boxCorners = box.getCorners();

    QList<RGraphicsScene*>::iterator it;
    for (it = scenes.begin(); it != scenes.end(); it++) {
        RGraphicsScene* scene = *it;
        scene->beginPreview();
        scene->setColor(RSettings::getColor("GraphicsViewColors/ZoomBoxColor", RColor(127,0,0)));
        scene->setLineweight(RLineweight::Weight000);
        scene->setStyle(Qt::DashLine);
        scene->setLinetypeId(document.getLinetypeId("CONTINUOUS"));
        //scene->setScreenBasedLinetypes(true);

        for (int i=0; i<4; ++i) {
            scene->exportLine(RLine(boxCorners[i], boxCorners[(i+1)%4]));
        }
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
        scene->setColor(color);
        scene->setBrush(brush);
        scene->setLineweight(lineweight);
        scene->setStyle(style);
        scene->setDashPattern(dashes.toVector());
        scene->setLinetypeId(document.getLinetypeId("CONTINUOUS"));

        RPoint* point = dynamic_cast<RPoint*> (&shape);
        if (point != NULL) {
            scene->exportPoint(*point);
        }

        RLine* line = dynamic_cast<RLine*> (&shape);
        if (line != NULL) {
            scene->exportLine(*line);
        }

        RArc* arc = dynamic_cast<RArc*> (&shape);
        if (arc != NULL) {
            scene->exportArc(*arc);
        }

        RCircle* circle = dynamic_cast<RCircle*> (&shape);
        if (circle != NULL) {
            scene->exportCircle(*circle);
        }

        REllipse* ellipse = dynamic_cast<REllipse*> (&shape);
        if (ellipse != NULL) {
            scene->exportEllipse(*ellipse);
        }

        RSpline* spline = dynamic_cast<RSpline*> (&shape);
        if (spline != NULL) {
            scene->exportSpline(*spline);
        }

        RPolyline* polyline = dynamic_cast<RPolyline*> (&shape);
        if (polyline != NULL) {
            scene->exportPolyline(*polyline);
        }

        // TODO: support other shapes (text, ...)

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
    if (RMainWindow::hasMainWindow() && notifyListeners) {
        RMainWindow::getMainWindow()->notifyPropertyListeners(document, entity);
    }
}

/**
 * Notifies all property listeners that no properties are relevant at this
 * point. This can for example clear the property editor and other property
 * listeners.
 */
void RDocumentInterface::clearProperties() {
    if (RMainWindow::hasMainWindow() && notifyListeners) {
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
void RDocumentInterface::previewOperation(const ROperation* operation) {
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

    QList<RGraphicsScene*>::iterator it;
    for (it = scenes.begin(); it != scenes.end(); it++) {
        (*it)->beginPreview();

        QList<RObject::Id> obj = transaction.getAffectedObjects();
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
RTransaction RDocumentInterface::applyOperation(const ROperation* operation) {
    if (operation==NULL) {
        qWarning() << "RDocumentInterface::applyOperation: operation is NULL";
        return RTransaction();
    }

    RTransaction transaction = operation->apply(document, false);
    if (transaction.isFailed()) {
        qWarning() << "RDocumentInterface::applyOperation: "
                "transaction failed";
        if (RMainWindow::hasMainWindow()) {
            RMainWindow::getMainWindow()->handleUserWarning("#transaction_failed");
        }
    }

    QList<RObject::Id> objectIds = transaction.getAffectedObjects();

    clearPreview();

    objectChangeEvent(objectIds);

    if (RMainWindow::hasMainWindow() && notifyListeners) {
        RMainWindow::getMainWindow()->postTransactionEvent(transaction,
                    transaction.hasOnlyChanges(), operation->getEntityTypeFilter());
    }

    delete operation;

    return transaction;
}

/**
 * Triggers an objectChangeEvent for every object in the given set.
 */
void RDocumentInterface::objectChangeEvent(QList<RObject::Id>& objectIds) {
    bool ucsHasChanged = false;
    bool linetypeHasChanged = false;
    bool layerHasChanged = false;
    bool blockHasChanged = false;
    bool viewHasChanged = false;
    bool entityHasChanged = false;

    QSet<REntity::Id> entityIdsToRegenerate;

    QList<RObject::Id>::iterator it;
    for (it=objectIds.begin(); it!=objectIds.end(); ++it) {
        QSharedPointer<RObject> object = document.queryObjectDirect(*it);
        if (object.isNull()) {
            continue;
        }

        QSharedPointer<RDocumentVariables> docVars = object.dynamicCast<RDocumentVariables> ();
        if (!docVars.isNull()) {
            ucsHasChanged = true;
            linetypeHasChanged = true;
            layerHasChanged = true;
            blockHasChanged = true;
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
            layerHasChanged = true;

            // deselect entities on locked layer:
            QSet<RObject::Id> ids = document.queryLayerEntities(*it);
            if (layer->isLocked() || layer->isFrozen()) {
                deselectEntities(ids);
            }
            continue;
        }

        QSharedPointer<RBlock> block = object.dynamicCast<RBlock> ();
        if (!block.isNull()) {
            if (block->getId()!=document.getModelSpaceBlockId()) {
                blockHasChanged = true;
                //document.queryBlockReferences(block->getId());
            }

            // deselect block reference entities of hidden block:
            QSet<RObject::Id> ids = document.queryBlockReferences(*it);
            if (block->isFrozen()) {
                deselectEntities(ids);
            }
            continue;
        }

        QSharedPointer<RView> view = object.dynamicCast<RView> ();
        if (!view.isNull()) {
            viewHasChanged = true;
            continue;
        }
    }

    // notify listeners if this is not the clipboard document interface:
    if (RMainWindow::hasMainWindow() && notifyListeners) {
        if (ucsHasChanged) {
            RMainWindow::getMainWindow()->notifyUcsListeners(this);
        }
        if (linetypeHasChanged) {
            // TODO:
            //RMainWindow::getMainWindow()->notifyLinetypeListeners(this);
        }
        if (layerHasChanged) {
            RMainWindow::getMainWindow()->notifyLayerListeners(this);
        }
        if (blockHasChanged) {
            RMainWindow::getMainWindow()->notifyBlockListeners(this);
        }
        if (viewHasChanged) {
            RMainWindow::getMainWindow()->notifyViewListeners(this);
        }
    }

    if (layerHasChanged || blockHasChanged || linetypeHasChanged) {
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

    regenerateViews(true);
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
    document.setCurrentLayer(layerName);
//    RTransaction transaction =
    if (RMainWindow::hasMainWindow() && notifyListeners) {
        RMainWindow::getMainWindow()->notifyLayerListeners(this);
//        RMainWindow::getMainWindow()->postTransactionEvent(transaction);
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
 * Sets the current block based on the given block name.
 */
void RDocumentInterface::setCurrentBlock(const QString& blockName) {
    clearSelection();
    document.setCurrentBlock(blockName);
    if (RMainWindow::hasMainWindow() && notifyListeners) {
        RMainWindow::getMainWindow()->notifyBlockListeners(this);
    }
    regenerateScenes();
}

/**
 * Sets the current block that is in use for all views attached to
 * this document interface.
 */
void RDocumentInterface::setCurrentBlock(const RBlock& block) {
    setCurrentBlock(block.getName());
}

/**
 * Sets the current view based on the given view name.
 */
void RDocumentInterface::setCurrentView(const QString& viewName) {
    document.setCurrentView(viewName);
    if (RMainWindow::hasMainWindow() && notifyListeners) {
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
    if (RMainWindow::hasMainWindow() && notifyListeners) {
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

RGraphicsView* RDocumentInterface::getLastKnownViewWithFocus() {
    return lastKnownViewWithFocus;
}

void RDocumentInterface::setLastKnownViewWithFocus(RGraphicsView* view) {
    lastKnownViewWithFocus = view;
}

QVariant RDocumentInterface::eval(const QString& ext, const QString& script) {
    RScriptHandler* handler = getScriptHandler(ext);
    if (handler==NULL) {
        return QVariant();
    }
    return handler->eval(script);
}
