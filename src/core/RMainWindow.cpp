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
#include <QCoreApplication>
#include <QDir>
#include <QObject>
#include <QThread>

#include "RBlockListener.h"
#include "RCoordinateEvent.h"
#include "RCoordinateListener.h"
#include "RDebug.h"
#include "RDocumentInterface.h"
#include "RFocusListener.h"
#include "RFontList.h"
#include "RGraphicsView.h"
#include "RGuiAction.h"
#include "RLayerListener.h"
#include "RMainWindow.h"
#include "RPenListener.h"
#include "RPropertyListener.h"
#include "RSelectionListener.h"
#include "RSettings.h"
#include "RSnapListener.h"
#include "RUcsListener.h"
#include "RVector.h"
#include "RViewFocusListener.h"
#include "RViewListener.h"
#include "RViewListener.h"


RMainWindow* RMainWindow::mainWindow = NULL;

RMainWindow::RMainWindow() {
    mainWindow = this;
}

RMainWindow::~RMainWindow() {
    mainWindow = NULL;
}

RMainWindow* RMainWindow::getMainWindow() {
    return mainWindow;
}

bool RMainWindow::hasMainWindow() {
    return mainWindow != NULL;
}

void RMainWindow::installMessageHandler() {
#if QT_VERSION >= 0x050000
    qInstallMessageHandler(RMainWindow::messageHandler);
#else
    qInstallMsgHandler(RMainWindow::messageHandler);
#endif
}

#if QT_VERSION >= 0x050000
void RMainWindow::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message) {
    QByteArray localMsg = message.toLocal8Bit();

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "\033[36m%s:%u, %s:\033[0m\nDebug:    %s\n", context.file, context.line, context.function, localMsg.constData());
        fflush(stderr);
        break;
    case QtWarningMsg:
        if (localMsg.contains("changing class of non-QScriptObject not supported")) {
            break;
        }
        if (localMsg.startsWith("QPainter::")) {
            break;
        }
        fprintf(stderr, "\033[31m%s:%u, %s:\033[0m\nWarning:  %s\n", context.file, context.line, context.function, localMsg.constData());
        fflush(stderr);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "\033[31m%s:%u, %s\033[0m\nCritical: %s\n", context.file, context.line, context.function, localMsg.constData());
        fflush(stderr);
        break;
    case QtFatalMsg:
        fprintf(stderr, "\033[31m%s:%u, %s\033[0m\nFatal:    %s\n", context.file, context.line, context.function, localMsg.constData());
        fflush(stderr);
        abort();
    }
}
#else
void RMainWindow::messageHandler(QtMsgType type, const char* msg) {
    QByteArray localMsg = msg;

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug:    %s\n", localMsg.constData());
        fflush(stderr);
        break;
    case QtWarningMsg:
        if (localMsg.contains("changing class of non-QScriptObject not supported")) {
            break;
        }
        if (localMsg.startsWith("QPainter::")) {
            break;
        }
        fprintf(stderr, "Warning:  %s\n", localMsg.constData());
        fflush(stderr);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s\n", localMsg.constData());
        fflush(stderr);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal:    %s\n", localMsg.constData());
        fflush(stderr);
        abort();
    }
}
#endif

/**
 * \return Pointer to the document interface of the current document
 *      (e.g. the active MDI window) or NULL if no document is open.
 */
RDocumentInterface* RMainWindow::getDocumentInterfaceStatic() {
    if (mainWindow == NULL) {
        return NULL;
    }
    return mainWindow->getDocumentInterface();
}

void RMainWindow::notifyListeners(bool withNull) {
    RDocument* document = NULL;
    RDocumentInterface* di = NULL;
    RGraphicsView* view = NULL;

    if (!withNull) {
        document = getDocument();
        di = getDocumentInterface();
        if (di!=NULL) {
            view = di->getLastKnownViewWithFocus();
        }
    }

    notifyFocusListeners(di);
    notifyViewFocusListeners(view);
    notifyCoordinateListeners(di);
    notifySnapListeners(di);
    notifyTransactionListeners(document);
    notifyPropertyListeners(document);
    notifySelectionListeners(di);
    notifyLayerListeners(di);
    notifyPenListeners(di);
    notifyBlockListeners(di);
    notifyViewListeners(di);
}

/**
 * Adds a listener for coordinate events. This can for example be a widget that
 * displays the current coordinate. 
 */
void RMainWindow::addCoordinateListener(RCoordinateListener* l) {
    coordinateListeners.push_back(l);
}

void RMainWindow::removeCoordinateListener(RCoordinateListener* l) {
    coordinateListeners.removeAll(l);
}

/**
 * Notifies all coordinate listeners that the coordinate has changed to \c position.
 */
void RMainWindow::notifyCoordinateListeners(RDocumentInterface* documentInterface) {
    QList<RCoordinateListener*>::iterator it;
    for (it = coordinateListeners.begin(); it != coordinateListeners.end(); ++it) {
        (*it)->updateCoordinate(documentInterface);
    }
}

/**
 * Adds a listener for selection events. This can for example be a widget that
 * displays the number of selected entities.
 */
void RMainWindow::addSelectionListener(RSelectionListener* l) {
    selectionListeners.push_back(l);
}

void RMainWindow::removeSelectionListener(RSelectionListener* l) {
    selectionListeners.removeAll(l);
}

/**
 * Notifies all selection listeners that the current selection has changed.
 */
void RMainWindow::notifySelectionListeners(RDocumentInterface* documentInterface) {
    QList<RSelectionListener*>::iterator it;
    for (it = selectionListeners.begin(); it != selectionListeners.end(); ++it) {
        (*it)->updateSelectionListener(documentInterface);
    }
}

/**
 * Adds a listener for transaction events. This can for example be an undo or
 * redo button.
 */
void RMainWindow::addTransactionListener(RTransactionListener* l) {
    if (l != NULL) {
        transactionListeners.push_back(l);
    } else {
        qWarning("RMainWindow::addTransactionListener(): Listener is NULL.");
    }
}

void RMainWindow::removeTransactionListener(RTransactionListener* l) {
    transactionListeners.removeAll(l);
}

/**
 * Notifies all transaction listeners.
 */
void RMainWindow::notifyTransactionListeners(RDocument* document, RTransaction* transaction) {
    QList<RTransactionListener*>::iterator it;
    for (it = transactionListeners.begin(); it != transactionListeners.end(); ++it) {
        (*it)->updateTransactionListener(document, transaction);
    }
}

/**
 * Adds a listener for transaction in progress events.
 */
void RMainWindow::addInterTransactionListener(RInterTransactionListener* l) {
    if (l != NULL) {
        interTransactionListeners.push_back(l);
    } else {
        qWarning("RMainWindow::addInterTransactionListener(): Listener is NULL.");
    }
}

void RMainWindow::removeInterTransactionListener(RInterTransactionListener* l) {
    interTransactionListeners.removeAll(l);
}

/**
 * Notifies all transaction in progress listeners.
 */
void RMainWindow::notifyInterTransactionListeners(RDocument* document, RTransaction* transaction) {
    QList<RInterTransactionListener*>::iterator it;
    for (it = interTransactionListeners.begin(); it != interTransactionListeners.end(); ++it) {
        (*it)->updateInterTransactionListener(document, transaction);
    }
}

/**
 * Adds a listener for snap mode changes. This can for example be 
 * a snap status widget.
 */
void RMainWindow::addSnapListener(RSnapListener* l) {
    if (l != NULL) {
        snapListeners.push_back(l);
    } else {
        qWarning("RMainWindow::addSnapListener(): Listener is NULL.");
    }
}

void RMainWindow::removeSnapListener(RSnapListener* l) {
    snapListeners.removeAll(l);
}

/**
 * Notifies all snap mode listeners.
 */
void RMainWindow::notifySnapListeners(RDocumentInterface* documentInterface) {
    QList<RSnapListener*>::iterator it;
    for (it = snapListeners.begin(); it != snapListeners.end(); ++it) {
        (*it)->updateSnap(documentInterface);
    }
}

/**
 * Adds a listener for focus changes.
 */
void RMainWindow::addFocusListener(RFocusListener* l) {
    if (l != NULL) {
        focusListeners.push_back(l);
    } else {
        qWarning("RMainWindow::addFocusListener(): Listener is NULL.");
    }
}

void RMainWindow::removeFocusListener(RFocusListener* l) {
    focusListeners.removeAll(l);
}

/**
 * Notifies all focus listeners.
 */
void RMainWindow::notifyFocusListeners(RDocumentInterface* documentInterface) {
    QList<RFocusListener*>::iterator it;
    for (it = focusListeners.begin(); it != focusListeners.end(); ++it) {
        (*it)->updateFocus(documentInterface);
    }
}

/**
 * Adds a listener for view focus changes.
 */
void RMainWindow::addViewFocusListener(RViewFocusListener* l) {
    if (l != NULL) {
        viewFocusListeners.push_back(l);
    } else {
        qWarning("RMainWindow::addViewFocusListener(): Listener is NULL.");
    }
}

void RMainWindow::removeViewFocusListener(RViewFocusListener* l) {
    viewFocusListeners.removeAll(l);
}

/**
 * Notifies all view focus listeners.
 */
void RMainWindow::notifyViewFocusListeners(RGraphicsView* view) {
    QList<RViewFocusListener*>::iterator it;
    for (it = viewFocusListeners.begin(); it != viewFocusListeners.end(); ++it) {
        (*it)->updateFocus(view);
    }
}

/**
 * Adds a listener for property events. This can for example be a widget that
 * displays the properties of selected entities or the current action.
 */
void RMainWindow::addPropertyListener(RPropertyListener* l) {
    propertyListeners.push_back(l);
}

void RMainWindow::removePropertyListener(RPropertyListener* l) {
    propertyListeners.removeAll(l);
}

/**
 * Notifies all property listeners that the current property has changed.
 */
void RMainWindow::notifyPropertyListeners(
    RDocument* document,
    bool onlyChanges,
    RS::EntityType entityTypeFilter) {

    QList<RPropertyListener*>::iterator it;
    for (it = propertyListeners.begin(); it != propertyListeners.end(); ++it) {
        (*it)->updateFromDocument(document, onlyChanges, entityTypeFilter);
    }
}

/**
 * Notifies all property listeners that the current property is the given entity.
 */
void RMainWindow::notifyPropertyListeners(RDocument& document, REntity& entity) {
    QList<RPropertyListener*>::iterator it;
    for (it = propertyListeners.begin(); it != propertyListeners.end(); ++it) {
        (*it)->updateFromObject((RObject*) &entity, &document);
    }
}

/**
 * Notifies all property listeners that no properties are currently relevant.
 */
void RMainWindow::notifyPropertyListeners() {
    QList<RPropertyListener*>::iterator it;
    for (it = propertyListeners.begin(); it != propertyListeners.end(); ++it) {
        (*it)->clearEditor();
    }
}

void RMainWindow::propertyChangeEvent(RPropertyEvent& event) {
    RDocumentInterface* documentInterface = getDocumentInterface();
    if (documentInterface == NULL) {
        return;
    }

    documentInterface->propertyChangeEvent(event);
}

/**
 * Adds a listener for UCS change / add / remove events. 
 * This can for example be a widget that displays all UCS objects.
 */
void RMainWindow::addUcsListener(RUcsListener* l) {
    ucsListeners.push_back(l);
}

void RMainWindow::removeUcsListener(RUcsListener* l) {
    ucsListeners.removeAll(l);
}

/**
 * Notifies all UCS listeners that at least one UCS object has changed.
 */
void RMainWindow::notifyUcsListeners(RDocumentInterface* documentInterface) {
    QList<RUcsListener*>::iterator it;
    for (it = ucsListeners.begin(); it != ucsListeners.end(); ++it) {
        (*it)->update(documentInterface);
    }
}

/**
 * Adds a listener for layer change / add / remove events.
 */
void RMainWindow::addLayerListener(RLayerListener* l) {
    layerListeners.push_back(l);
}

void RMainWindow::removeLayerListener(RLayerListener* l) {
    layerListeners.removeAll(l);
}

/**
 * Notifies all layer listeners that at least one layer object has changed.
 */
void RMainWindow::notifyLayerListeners(RDocumentInterface* documentInterface) {
    QList<RLayerListener*>::iterator it;
    for (it = layerListeners.begin(); it != layerListeners.end(); ++it) {
        (*it)->updateLayers(documentInterface);
    }
}

/**
 * Adds a listener for block change / add / remove events.
 */
void RMainWindow::addBlockListener(RBlockListener* l) {
    blockListeners.push_back(l);
}

void RMainWindow::removeBlockListener(RBlockListener* l) {
    blockListeners.removeAll(l);
}

/**
 * Notifies all block listeners that at least one block object has changed.
 */
void RMainWindow::notifyBlockListeners(RDocumentInterface* documentInterface) {
    QList<RBlockListener*>::iterator it;
    for (it = blockListeners.begin(); it != blockListeners.end(); ++it) {
        (*it)->updateBlocks(documentInterface);
    }
}

/**
 * Adds a listener for view change / add / remove events.
 */
void RMainWindow::addViewListener(RViewListener* l) {
    viewListeners.push_back(l);
}

void RMainWindow::removeViewListener(RViewListener* l) {
    viewListeners.removeAll(l);
}

/**
 * Notifies all view listeners that at least one view object has changed.
 */
void RMainWindow::notifyViewListeners(RDocumentInterface* documentInterface) {
    QList<RViewListener*>::iterator it;
    for (it = viewListeners.begin(); it != viewListeners.end(); ++it) {
        (*it)->updateViews(documentInterface);
    }
}

/**
 * Adds a listener for pen change events.
 */
void RMainWindow::addPenListener(RPenListener* l) {
    penListeners.push_back(l);
}

void RMainWindow::removePenListener(RPenListener* l) {
    penListeners.removeAll(l);
}

/**
 * Notifies all pen listeners that the current pen has changed.
 */
void RMainWindow::notifyPenListeners(RDocumentInterface* documentInterface) {
    QList<RPenListener*>::iterator it;
    for (it = penListeners.begin(); it != penListeners.end(); ++it) {
        (*it)->updatePen(documentInterface);
    }
}

/**
 * Called immediately after the user has activated a new UCS to be used as current UCS.
 */
void RMainWindow::ucsSetEvent(const QString& ucsName) {
    RDocumentInterface* documentInterface = getDocumentInterface();
    if (documentInterface == NULL) {
        return;
    }

    documentInterface->ucsSetEvent(ucsName);
}

/**
 * Restores the application window settings (size, position, ...).
 */
bool RMainWindow::readSettings() {
    bool ret = false;

    int x = RSettings::getQSettings()->value("Appearance/Position.X", -1).toInt();
    int y = RSettings::getQSettings()->value("Appearance/Position.Y", -1).toInt();
    int width = RSettings::getQSettings()->value("Appearance/Width", 1024).toInt();
    int height = RSettings::getQSettings()->value("Appearance/Height", 800).toInt();
    if (x != -1 && y != -1) {
        move(x, y);
        ret = true;
    }

    resize(width, height);
    return ret;
}

/**
 * Stores the application window settings (size, position, ...).
 */
void RMainWindow::writeSettings() {
    RSettings::getQSettings()->setValue("Appearance/Position.X", getPositionX());
    RSettings::getQSettings()->setValue("Appearance/Position.Y", getPositionY());
    RSettings::getQSettings()->setValue("Appearance/Width", getWidth());
    RSettings::getQSettings()->setValue("Appearance/Height", getHeight());
}
