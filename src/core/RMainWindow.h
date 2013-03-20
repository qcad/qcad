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

#ifndef RMAINWINDOW_H
#define RMAINWINDOW_H

#include <QMutex>

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
class RLayerListener;
class RPenListener;
class RPropertyListener;
class RSelectionListener;
class RSnapListener;
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
class RMainWindow : public RProgressHandler, public RMessageHandler {

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

    /**
     * \return Pointer to the document interface of the document that is
     *      currently open and has the focus or NULL if no document is open.
     */
    virtual RDocumentInterface* getDocumentInterface() = 0;
    static RDocumentInterface* getDocumentInterfaceStatic();

    void notifyListeners(bool withNull = false);

    void addCoordinateListener(RCoordinateListener* l);
    void notifyCoordinateListeners(RDocumentInterface* documentInterface);

    void addSelectionListener(RSelectionListener* l);
    void notifySelectionListeners(RDocumentInterface* documentInterface);

    virtual void postSelectionChangedEvent() = 0;
    virtual void postTransactionEvent(
        bool onlyChanges=false,
        RS::EntityType entityTypeFilter = RS::EntityAll
    ) = 0;
    virtual void postCloseEvent() = 0;
    //virtual void postPropertyEvent() = 0;
//    virtual void postPropertyEvent(RPropertyTypeId propertyTypeId,
//        const QVariant& value,
//        RS::EntityType entityTypeFilter = RS::EntityAll
//    ) = 0;

    void addPropertyListener(RPropertyListener* l);
    void notifyPropertyListeners(
        RDocument* document,
        bool onlyChanges=false,
        RS::EntityType entityTypeFilter = RS::EntityAll
    );
    void notifyPropertyListeners(RDocument& document, REntity& entity);
    void notifyPropertyListeners();

    void addTransactionListener(RTransactionListener* l);
    void notifyTransactionListeners(RDocument* document);

    void addSnapListener(RSnapListener* l);
    void notifySnapListeners(RDocumentInterface* documentInterface);

    void addFocusListener(RFocusListener* l);
    void notifyFocusListeners(RDocumentInterface* documentInterface);

    void addViewFocusListener(RViewFocusListener* l);
    void notifyViewFocusListeners(RGraphicsView* view);

    void propertyChangeEvent(RPropertyEvent& event);

    void addUcsListener(RUcsListener* l);
    void notifyUcsListeners(RDocumentInterface* documentInterface);

    void addLayerListener(RLayerListener* l);
    void notifyLayerListeners(RDocumentInterface* documentInterface);

    void addBlockListener(RBlockListener* l);
    void notifyBlockListeners(RDocumentInterface* documentInterface);

    void addViewListener(RViewListener* l);
    void notifyViewListeners(RDocumentInterface* documentInterface);

    void addPenListener(RPenListener* l);
    void notifyPenListeners(RDocumentInterface* documentInterface);

    void ucsSetEvent(const QString& ucsName);

    //void commandEvent(const QString& command);

    virtual void escapeEvent() = 0;

    /**
     * Sets the cursor of all graphics views in all MDI children.
     * Necessary as workaround for Qt cursor bug (cursor inconsistent
     * with multiple widgets on top of each otehr in MDI area).
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
    virtual void close() = 0;

    /**
     * \nonscriptable
     */
    static void messageHandler(QtMsgType type, const char* msg);

    virtual void setCommandPrompt(const QString& text = "") = 0;
    virtual void setLeftMouseTip(const QString& text = "") = 0;
    virtual void setRightMouseTip(const QString& text = "") = 0;

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
    QList<RTransactionListener*> transactionListeners;
    QList<RSnapListener*> snapListeners;
    QList<RFocusListener*> focusListeners;
    QList<RViewFocusListener*> viewFocusListeners;

    QMutex mutex;
};

Q_DECLARE_METATYPE(RMainWindow*)

#endif
