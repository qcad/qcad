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
#include "RAction.h"
#include "RDebug.h"
#include "RDocument.h"
#include "REntity.h"
#include "RGraphicsScene.h"
#include "RGraphicsView.h"
#include "RGuiAction.h"
#include "RMouseEvent.h"
#include "RTransaction.h"
#include "RWheelEvent.h"
#include "RMainWindow.h"
#include "RDocumentInterface.h"

RAction::RAction(RGuiAction* guiAction)
  : terminated(false),
    override(false),
    noState(false),
    clickMode(RAction::PickingDisabled),
    guiAction(NULL),
    overrideBase(NULL),
    documentInterface(NULL) {

    setGuiAction(guiAction);

    RDebug::incCounter("RAction");
//    qDebug() << "RAction " << QString("0x%1").arg((int)this, 0, 16);
}



RAction::~RAction() {
    RDebug::decCounter("RAction");
//    qDebug() << "~RAction " << QString("0x%1").arg((int)this, 0, 16);
}


/**
 * \return The GUI action which can be used to trigger this action
 *  or NULL.
 */
RGuiAction* RAction::getGuiAction() {
    return guiAction;
}


void RAction::setGuiAction(RGuiAction* guiAction) {
    this->guiAction = guiAction;
    if (guiAction!=NULL) {
        if (guiAction->isOverride()) {
            setOverride();
        }
        if (guiAction->hasNoState()) {
            setNoState();
        }
        setUniqueGroup(guiAction->getUniqueGroup());
    }
}


/**
 * Terminates the action. The action object will be deleted after calling this
 * method.
 */
void RAction::terminate() {
    terminated = true;

    if (getDocumentInterface()==NULL) {
        return;
    }
    RGraphicsView* view = getDocumentInterface()->getLastKnownViewWithFocus();
    QObject* obj = dynamic_cast<QObject*>(view);
    if (obj==NULL) {
        //qWarning() << "RAction::terminate: view is not a QObject";
        return;
    }

    RTerminateEvent* event = new RTerminateEvent();
    QCoreApplication::postEvent(obj, event);
}



/**
 * \return True if the action is terminated and can be deleted, false otherwise.
 */
bool RAction::isTerminated() {
    return terminated;
}

void RAction::setNoState(bool on) {
    noState = on;
}

bool RAction::hasNoState() {
    return noState;
}

void RAction::setOverride() {
    override = true;
}


bool RAction::isOverride() {
    return override;
}

void RAction::setUniqueGroup(const QString& ug) {
    uniqueGroup = ug;
}

QString RAction::getUniqueGroup() {
    return uniqueGroup;
}

void RAction::setOverrideBase(RAction* base) {
    overrideBase = base;
}

RAction* RAction::getOverrideBase() {
    return overrideBase;
}

/**
 * \return List of pointers to the graphics scenes which are attached to the
 *   document interface in which this action is active.
 */
QList<RGraphicsScene*> RAction::getGraphicsScenes() {
    RDocumentInterface* documentInterface = getDocumentInterface();
    if (documentInterface!=NULL) {
        return documentInterface->getGraphicsScenes();
    }
    else {
        return QList<RGraphicsScene*>();
    }
}



/**
 * \return Pointer to the graphics document or NULL if no document is open.
 */
RDocument* RAction::getDocument() {
    RDocumentInterface* documentInterface = getDocumentInterface();
    if (documentInterface!=NULL) {
        return &documentInterface->getDocument();
    }
    else {
        qWarning("RAction::getDocument: Action has no document.");
        return NULL;
    }
}



/**
 * \return Reference to the document interface that owns this action or NULL
 *      for actions that run on an application level (e.g. file - new).
 */
RDocumentInterface* RAction::getDocumentInterface() {
//    RMainWindow* mainWindow = RMainWindow::getMainWindow();
//    if (mainWindow==NULL) {
//        return NULL;
//    }
//
//    return mainWindow->getDocumentInterface();
    return documentInterface;
}


/**
 * \return Pointer to the storage or NULL if no document is open.
 */
RStorage* RAction::getStorage() {
    RDocumentInterface* documentInterface = getDocumentInterface();
    if (documentInterface != NULL) {
        return &documentInterface->getStorage();
    } else {
        qWarning("RAction::getStorage: Action has no document.");
        return NULL;
    }
}

/**
 * Sets the current click mode.
 *
 * \see ClickMode
 */
void RAction::setClickMode(RAction::ClickMode m) {
    clickMode = m;

    // if this is a class that overrides a base class,
    // set click mode in base class:
    if (isOverride()) {
        RAction* base = getOverrideBase();
        if (base) {
            base->setClickMode(m);
        }
    }
}

/**
 * Uses the currently active snap function to snap to the closest
 * object or grid point.
 */
RVector RAction::snap(RMouseEvent& event) {
    RDocumentInterface* documentInterface = getDocumentInterface();
    if (documentInterface!=NULL) {
        return documentInterface->snap(event);
    }
    else {
        return RVector();
    }
}
