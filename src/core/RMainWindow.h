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

#ifndef RMAINWINDOW_H
#define RMAINWINDOW_H

#include "core_global.h"

#include <QMutex>
class QKeyEvent;

#include "REntityExportListener.h"
#include "RExportListener.h"
#include "RImportListener.h"
#include "RInterTransactionListener.h"
#include "RTransactionListener.h"
#include "RPropertyEvent.h"
#include "RMessageHandler.h"
#include "RProgressHandler.h"
#include "RS.h"

class RBlockListener;
class RCoordinateListener;
class RDocument;
class RDocumentInterface;
class REntity;
class RFocusListener;
class RGraphicsView;
class RKeyListener;
class RLayerListener;
class RNewDocumentListener;
class RPaletteListener;
class RPenListener;
class RPropertyListener;
class RPreferencesListener;
class RSelectionListener;
class RSnapListener;
class RTransaction;
class RUcsListener;
class RVector;
class RViewFocusListener;
class RViewListener;

#ifndef RDEFAULT_MINUS_ONE
#define RDEFAULT_MINUS_ONE -1
#endif

/**
 * \brief Base class for an MDI main application window.
 *
 * \ingroup core
 * \scriptable
 */
class QCADCORE_EXPORT RMainWindow : public RProgressHandler, public RMessageHandler {

public:
    RMainWindow();
    virtual ~RMainWindow();

    static RMainWindow* getMainWindow();

    static bool hasMainWindow();

    static void installMessageHandler();

    /**
     * \return Pointer to the document that is currently open and has
     *      the focus or NULL if no document is open.
     */
    virtual RDocument* getDocument() = 0;

    virtual void disable() {}
    virtual void enable() {}

    /**
     * \return Pointer to the document interface of the document that is
     *      currently open and has the focus or NULL if no document is open.
     */
    virtual RDocumentInterface* getDocumentInterface() = 0;
    static RDocumentInterface* getDocumentInterfaceStatic();

    void notifyListeners(bool withNull = false);

    void addCoordinateListener(RCoordinateListener* l);
    void removeCoordinateListener(RCoordinateListener* l);
    void notifyCoordinateListeners(RDocumentInterface* documentInterface);

    void addSelectionListener(RSelectionListener* l);
    void removeSelectionListener(RSelectionListener* l);
    void notifySelectionListeners(RDocumentInterface* documentInterface);

    virtual void postSelectionChangedEvent() = 0;
    virtual void postTransactionEvent(
        RTransaction& t,
        bool onlyChanges=false,
        RS::EntityType entityTypeFilter = RS::EntityAll
    ) = 0;
    virtual void postCloseEvent() = 0;
    //virtual void postPropertyEvent() = 0;
    virtual void postPropertyEvent(RPropertyTypeId propertyTypeId,
        const QVariant& value,
        RS::EntityType entityTypeFilter = RS::EntityAll
    ) = 0;

    void addPropertyListener(RPropertyListener* l);
    void removePropertyListener(RPropertyListener* l);
    void notifyPropertyListeners(
        RDocument* document,
        bool onlyChanges=false,
        RS::EntityType entityTypeFilter = RS::EntityUnknown
    );
    void notifyPropertyListeners(RDocument& document, REntity& entity);
    void notifyPropertyListeners();

    void addExportListener(RExportListener* l);
    void removeExportListener(RExportListener* l);
    void notifyExportListenersPre(RDocumentInterface* documentInterface);
    void notifyExportListenersPost(RDocumentInterface* documentInterface);
    void notifyExportListenersEnd(RExporter* exporter);

    void addEntityExportListener(REntityExportListener* l);
    void removeEntityExportListener(REntityExportListener* l);
    void notifyEntityExportListeners(RExporter* exporter, REntity* entity);

    void addImportListener(RImportListener* l);
    void removeImportListener(RImportListener* l);
    void notifyImportListenersPre(RDocumentInterface* documentInterface);
    void notifyImportListenersPost(RDocumentInterface* documentInterface);

    void addTransactionListener(RTransactionListener* l);
    void removeTransactionListener(RTransactionListener* l);
    void notifyTransactionListeners(RDocument* document, RTransaction* transaction = NULL);

    void addInterTransactionListener(RInterTransactionListener* l);
    void removeInterTransactionListener(RInterTransactionListener* l);
    void notifyInterTransactionListeners(RDocument* document, RTransaction* transaction = NULL);

    void addNewDocumentListener(RNewDocumentListener* l);
    void removeNewDocumentListener(RNewDocumentListener* l);
    void notifyNewDocumentListeners(RDocument* document, RTransaction* transaction, bool beforeLoad);

    void addSnapListener(RSnapListener* l);
    void removeSnapListener(RSnapListener* l);
    void notifySnapListeners(RDocumentInterface* documentInterface);

    void addFocusListener(RFocusListener* l);
    void removeFocusListener(RFocusListener* l);
    void notifyFocusListeners(RDocumentInterface* documentInterface);

    void addKeyListener(RKeyListener* l);
    void removeKeyListener(RKeyListener* l);
    void notifyKeyListeners(QKeyEvent* event);

    void addViewFocusListener(RViewFocusListener* l);
    void removeViewFocusListener(RViewFocusListener* l);
    void notifyViewFocusListeners(RGraphicsView* view);

    void addPreferencesListener(RPreferencesListener* l);
    void removePreferencesListener(RPreferencesListener* l);
    void notifyPreferencesListeners(RDocumentInterface* documentInterface);

    void propertyChangeEvent(RPropertyEvent& event);

    void addUcsListener(RUcsListener* l);
    void removeUcsListener(RUcsListener* l);
    void notifyUcsListeners(RDocumentInterface* documentInterface);

    void addLayerListener(RLayerListener* l);
    void removeLayerListener(RLayerListener* l);
    void notifyLayerListeners(RDocumentInterface* documentInterface, QList<RLayer::Id>& layerIds);
    void notifyLayerListenersCurrentLayer(RDocumentInterface* documentInterface, RLayer::Id previousLayerId);

    void addBlockListener(RBlockListener* l);
    void removeBlockListener(RBlockListener* l);
    void notifyBlockListeners(RDocumentInterface* documentInterface);
    void notifyBlockListenersCurrentBlock(RDocumentInterface* documentInterface);

    void addViewListener(RViewListener* l);
    void removeViewListener(RViewListener* l);
    void notifyViewListeners(RDocumentInterface* documentInterface);

    void addPenListener(RPenListener* l);
    void removePenListener(RPenListener* l);
    void notifyPenListeners(RDocumentInterface* documentInterface);

    void addPaletteListener(RPaletteListener* l);
    void removePaletteListener(RPaletteListener* l);
    void notifyPaletteListeners();

    void ucsSetEvent(const QString& ucsName);

    //void commandEvent(const QString& command);

    virtual void escapeEvent() = 0;

    /**
     * Sets the cursor of all graphics views in all MDI children.
     * Necessary as workaround for Qt cursor bug (cursor inconsistent
     * with multiple widgets on top of each other in MDI area).
     */
    virtual void setGraphicsViewCursor(const QCursor& cursor) = 0;

    /**
     * \return Width of the main application window.
     */
    virtual int getWidth() = 0;
    /**
     * \return Height of the main application window.
     */
    virtual int getHeight() = 0;
    /**
     * \return X position of the main application window
     *      (distance from left of screen).
     */
    virtual int getPositionX() = 0;
    /**
     * \return Y position of the main application window
     *      (distance from top of screen).
     */
    virtual int getPositionY() = 0;

    /**
     * Resizes the application window to the given \c width and \c height.
     */
    virtual void resize(int width, int height) = 0;
    /**
     * Moves the application window to the given \c x / \c y position.
     */
    virtual void move(int x, int y) = 0;
    /**
     * Closes the application window.
     */
    virtual void quit() = 0;

    virtual QWidget* getChildWidget(const QString& name) = 0;

    virtual void handleUserMessage(const QString& message, bool escape = true) {
        Q_UNUSED(escape);

        qDebug() << message;
    }

    virtual void handleUserInfo(const QString& message, bool escape = true) {
        Q_UNUSED(escape);

        qDebug() << message;
    }

    virtual void handleUserWarning(const QString& message, bool messageBox = false, bool escape = true) {
        Q_UNUSED(messageBox);
        Q_UNUSED(escape);

        qWarning() << message;
    }

    virtual void handleUserCommand(const QString& message, bool escape = true) {
        Q_UNUSED(escape);

        qDebug() << "Command: " << message;
    }

#if QT_VERSION >= 0x050000
    /**
     * \nonscriptable
     */
    static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message);
#else
    /**
     * \nonscriptable
     */
    static void messageHandler(QtMsgType type, const char* msg);
#endif

    virtual void setCommandPrompt(const QString& text = "") = 0;
    virtual void setLeftMouseTip(const QString& text = "") = 0;
    virtual void setRightMouseTip(const QString& text = "") = 0;

    QVariant eval(const QString& ext, const QString& script);

protected:
    virtual bool readSettings();
    virtual void writeSettings();

protected:
    static RMainWindow* mainWindow;

    QList<RCoordinateListener*> coordinateListeners;
    QList<RSelectionListener*> selectionListeners;
    QList<RPropertyListener*> propertyListeners;
    QList<RUcsListener*> ucsListeners;
    QList<RLayerListener*> layerListeners;
    QList<RBlockListener*> blockListeners;
    QList<RViewListener*> viewListeners;
    QList<RPenListener*> penListeners;
    QList<RPaletteListener*> paletteListeners;
    QList<REntityExportListener*> entityExportListeners;
    QList<RExportListener*> exportListeners;
    QList<RImportListener*> importListeners;
    QList<RTransactionListener*> transactionListeners;
    QList<RInterTransactionListener*> interTransactionListeners;
    QList<RNewDocumentListener*> newDocumentListeners;
    QList<RSnapListener*> snapListeners;
    QList<RKeyListener*> keyListeners;
    QList<RFocusListener*> focusListeners;
    QList<RViewFocusListener*> viewFocusListeners;
    QList<RPreferencesListener*> preferencesListeners;

    QMutex mutex;
};

Q_DECLARE_METATYPE(RMainWindow*)

#endif
