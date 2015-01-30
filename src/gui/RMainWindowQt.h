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

#ifndef RMAINWINDOWQT_H
#define RMAINWINDOWQT_H

#include "gui_global.h"

#include <QMainWindow>
#include <QKeyEvent>

#include "RCloseCurrentEvent.h"
#include "RMainWindow.h"

class QMdiArea;
class QMdiSubWindow;

class RBlockListener;
class RCoordinateListener;
class RDocument;
class RDocumentInterface;
class RFocusListener;
class RGraphicsView;
class RLayerListener;
class RMdiArea;
class RMdiChildQt;
class RNewDocumentListener;
class RPenListener;
class RPropertyListener;
class RSelectionListener;
class RSnapListener;
class RUcsListener;
class RViewFocusListener;
class RViewListener;

/**
 * \brief Base class for a Qt based MDI main application window.
 *
 * \ingroup gui
 *
 * \scriptable
 */
class QCADGUI_EXPORT RMainWindowQt: public QMainWindow, public RMainWindow {
Q_OBJECT

public:
    RMainWindowQt(QWidget* parent = 0, bool hasMdiArea = true);
    virtual ~RMainWindowQt();
    static RMainWindowQt* getMainWindow();
    virtual int getWidth();
    virtual int getHeight();
    virtual int getPositionX();
    virtual int getPositionY();
    virtual void resize(int width, int height);
    virtual void move(int x, int y);
    virtual RDocument* getDocument();
    virtual RDocumentInterface* getDocumentInterface();

    virtual void handleUserMessage(const QString& message);
    virtual void handleUserInfo(const QString& message);
    virtual void handleUserWarning(const QString& message, bool messageBox = false);
    virtual void handleUserCommand(const QString& message);

    virtual void postSelectionChangedEvent();
    virtual void postTransactionEvent(
        RTransaction& t,
        bool onlyChanges=false,
        RS::EntityType entityTypeFilter = RS::EntityAll
    );
    virtual void postCloseEvent();

    RMdiChildQt* getMdiChild();
    QTabBar* getTabBar();
    RMdiArea* getMdiArea();

    virtual void cancelProgress();
    virtual void setProgress(int value);
    virtual void setProgressEnd();
    virtual void setProgressText(const QString& text = "");

    virtual void setCommandPrompt(const QString& text = "");
    virtual void setLeftMouseTip(const QString& text = "");
    virtual void setRightMouseTip(const QString& text = "");

    virtual void escapeEvent();

    virtual void setGraphicsViewCursor(const QCursor& cursor);

    virtual bool readSettings();
    virtual void writeSettings();

    virtual QWidget* getChildWidget(const QString& name);

public slots:
    void quit();
    void currentTabChanged(int index);
    void subWindowActivated(QMdiSubWindow* sw);
    //void objectDestroyed(QObject *obj);

signals:
    /**
     * Emmitted when the command prompt is requested to change.
     */
    void commandPrompt(const QString& text);

    /**
     * Emmitted when the left mouse button tip is requested to change.
     */
    void leftMouseTip(const QString& message);

    /**
     * Emmitted when the right mouse button tip is requested to change.
     */
    void rightMouseTip(const QString& message);

    void progress(int value);
    void progressEnd();
    void progressText(const QString& label);
    void progressCanceled();
    void userMessage(const QString& message);
    void userInfo(const QString& message);
    void userWarning(const QString& message, bool messageBox);
    void userCommand(const QString& message);
    void escape();
    void drop(QDropEvent* event);
    void dragEnter(QDragEnterEvent* event);

    void resumedTab(RMdiChildQt* mdiChild);

    void closeRequested();

protected:
    virtual void closeEvent(QCloseEvent* e);
    virtual void dropEvent(QDropEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent* event);

    virtual bool event(QEvent* e);

protected slots:
    void updateGuiActions(QMdiSubWindow* mdiChild = NULL);
    void initGuiActions();
    void updateScenes(QMdiSubWindow* mdiChild);
    void notifyListenersSlot(QMdiSubWindow* mdiChild);
    void suspendAndResume(QMdiSubWindow* mdiChild);

protected:
    RMdiArea* mdiArea;

//private:
//    bool objectWasDestroyed;
};

Q_DECLARE_METATYPE(RMainWindowQt*)

#endif
