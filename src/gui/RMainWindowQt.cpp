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
#include <QComboBox>
#include <QLineEdit>
#include <QMenu>
#include <QMdiArea>
#include <QSettings>
#include <QScreen>
#include <QStatusBar>
#include <QTabBar>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QWindow>

#include <RSingleApplication.h>

#include "RCloseCurrentEvent.h"
#include "RCoordinateEvent.h"
#include "RDocument.h"
#include "RDocumentInterface.h"
#include "RGuiAction.h"
#include "RGraphicsViewImage.h"
#include "RGraphicsViewQt.h"
#include "RAccessibleToolTipFilter.h"
#include "RMainWindowQt.h"
#include "RMdiArea.h"
#include "RMdiChildQt.h"
#include "RPropertyEvent.h"
#include "RScriptHandler.h"
#include "RSelectionChangedEvent.h"
#include "RSettings.h"
#include "RTransactionEvent.h"

RMainWindowQt::RMainWindowQt(QWidget* parent, bool hasMdiArea) :
    QMainWindow(parent), RMainWindow(), mdiArea(NULL), disableCounter(0),
    dockWidgetStateValid(false), closingDown(false) {

// uncomment for unified tool bars under Mac:
//#if QT_VERSION >= 0x050201
//#ifdef Q_OS_MAC
//    setUnifiedTitleAndToolBarOnMac(true);
//#endif
//#endif

    if (hasMdiArea) {
        mdiArea = new RMdiArea(this);
        mdiArea->setObjectName("MdiArea");
        setCentralWidget(mdiArea);

        // combine into one slot, locked by mutex:
        connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(subWindowActivated(QMdiSubWindow*)));

        // part of the workaround for QMdiArea bug
        // with events filtering through all stacked windows:
        QTabBar* tabBar = getTabBar();
        if (tabBar!=NULL) {
            connect(tabBar, SIGNAL(currentChanged(int)),
                this, SLOT(currentTabChanged(int)));
            if (RSettings::getBoolValue("TabBar/ShowAddTabButton", false)) {
                tabBar->hide();
            }
        }
    }
    setWindowTitle("RMainWindowQt");

    // keep accessible descriptions (screen readers) free of HTML tool tip markup:
    qApp->installEventFilter(new RAccessibleToolTipFilter(this));

    RSingleApplication* singleApp = dynamic_cast<RSingleApplication*> (qApp);
    if (singleApp!=NULL) {
        singleApp->setActivationWindow(this);
    }
}

RMainWindowQt::~RMainWindowQt() {
}

/**
 * Part of the workaround for QMdiArea bug
 * with events filtering through all stacked windows:
 */
void RMainWindowQt::currentTabChanged(int index) {
    QTabBar* tabBar = getTabBar();
    if (tabBar!=NULL) {
        for (int i=0; i<tabBar->count(); i++) {
            tabBar->setTabEnabled(i, true);
        }
    }

    QList<QMdiSubWindow *> subWindows = mdiArea->subWindowList();
    if (index>=subWindows.size() || index<0) {
        qWarning() << "more tabs than documents";
        return;
    }

    RMdiChildQt* mdiChild = dynamic_cast<RMdiChildQt*>(subWindows.at(index));
    mdiChild->showMaximized();
    mdiArea->setActiveSubWindow(mdiChild);
}

void RMainWindowQt::subWindowActivated(QMdiSubWindow* sw) {
    updateScenes(sw);
    updateGuiActions(sw);
    notifyListenersSlot(sw);
    suspendAndResume(sw);
    if (RSettings::getBoolValue("TabBar/ShowAddTabButton", false)) {
        mdiArea->updateTabBar();
    }
}

void RMainWindowQt::handleUserMessage(const QString& message, bool escape) {
    emit userMessage(message, escape);
}

void RMainWindowQt::handleUserInfo(const QString& message, bool escape) {
    emit userInfo(message, escape);
}

void RMainWindowQt::handleUserWarning(const QString& message, bool messageBox, bool escape) {
    emit userWarning(message, messageBox, escape);
}

void RMainWindowQt::handleUserCommand(const QString& message, bool escape) {
    emit userCommand(message, escape);
}

void RMainWindowQt::reloadXRefs(RDocumentInterface* di, const QSet<QString>& dirtyXRefPaths) {
    emit reloadXRefsSignal(di, dirtyXRefPaths.values());
}

void RMainWindowQt::postSelectionChangedEvent() {
    RSelectionChangedEvent* event = new RSelectionChangedEvent();
    QCoreApplication::postEvent(this, event);
}

void RMainWindowQt::postTransactionEvent(RTransaction& t, bool onlyChanges, RS::EntityType entityTypeFilter) {
    RTransactionEvent* event = new RTransactionEvent(t, onlyChanges, entityTypeFilter);
    QCoreApplication::postEvent(this, event);
}

void RMainWindowQt::postPropertyEvent(RPropertyTypeId propertyTypeId, const QVariant& value, RS::EntityType entityTypeFilter) {
    RPropertyEvent* event = new RPropertyEvent(propertyTypeId, value, entityTypeFilter);
    QCoreApplication::postEvent(this, event);
}

void RMainWindowQt::postCloseEvent() {
    QCloseEvent* event = new QCloseEvent();
    QCoreApplication::postEvent(this, event);
}

RMainWindowQt* RMainWindowQt::getMainWindow() {
    return (RMainWindowQt*)mainWindow;
}

void RMainWindowQt::notifyListenersSlot(QMdiSubWindow* mdiChild) {
    if (mdiChild==NULL) {
        RMainWindow::notifyListeners();
        return;
    }

    static QMdiSubWindow* lastMdiChild = NULL;

    if (lastMdiChild != mdiChild) {
        RMainWindow::notifyListeners();
        lastMdiChild = mdiChild;
    }
}

void RMainWindowQt::updateGuiActions(QMdiSubWindow*) {
    RDocument* document = getDocument();

    QList<RGuiAction*> actions = RGuiAction::getActions();
    for (int i = 0; i < actions.size(); ++i) {
        RGuiAction* a = actions.at(i);
        bool enabled = true;

        if (a->getRequiresDocument() && document==NULL) {
            enabled = false;
        }
        if (document!=NULL) {
            if (a->getRequiresUndoableTransaction() &&
                    !document->isUndoAvailable()) {
                enabled = false;
            }
            if (a->getRequiresRedoableTransaction() &&
                    !document->isRedoAvailable()) {
                enabled = false;
            }
            if (a->getRequiresSelection() && !document->hasSelection()) {
                enabled = false;
            }
        }

        a->setEnabledOverride(enabled, -1);
    }
}

void RMainWindowQt::initGuiActions() {
    QList<RGuiAction*> actions = RGuiAction::getActions();
    for (int i = 0; i < actions.size(); ++i) {
        RGuiAction* a = actions.at(i);
        a->init();
    }
}

void RMainWindowQt::suspendAndResume(QMdiSubWindow* mdiChild) {
    Q_UNUSED(mdiChild)

    // find the current drawing:
    RMdiChildQt* mdi = getMdiChild();
    if (mdi==NULL) {
        setWindowTitle(qApp->applicationName());
        return;
    }
    RDocumentInterface* di = mdi->getDocumentInterface();
    if (di==NULL) {
        return;
    }

    QList<QMdiSubWindow *> list = mdiArea->subWindowList();
    for (int i = 0; i < list.size(); ++i) {
        if (list.at(i)==NULL) {
            continue;
        }
        RMdiChildQt* mdiOther = dynamic_cast<RMdiChildQt*>(list.at(i));
        if (mdiOther==NULL) {
            continue;
        }
        if (mdiOther==mdi) {
            continue;
        }
        RDocumentInterface* diOther = mdiOther->getDocumentInterface();
        if (diOther==NULL || diOther==di) {
            continue;
        }

        diOther->suspend();

#ifndef Q_OS_WIN
#if (QT_VERSION < QT_VERSION_CHECK(4, 8, 0))
        // core part of the workaround for Qt 4.7.x QMdiArea bug
        // with events filtering through all stacked windows:
        mdiOther->hide();
#endif
#endif
    }

    di->resume();

    emit(resumedTab(mdi));
}

void RMainWindowQt::updateScenes(QMdiSubWindow* mdiChild) {
    static QMdiSubWindow* lastMdiChild = NULL;

    if (mdiChild == NULL) {
        //qWarning("RMainWindowQt::updateScenes: mdiChild=NULL");
        return;
    }

    if (lastMdiChild != mdiChild) {
        RDocumentInterface* documentInterface = getDocumentInterface();
        if (documentInterface == NULL) {
            //qWarning("RMainWindowQt::updateScenes: documentInterface=NULL");
            return;
        }

        documentInterface->regenerateScenes();

        lastMdiChild = mdiChild;
    }
}

/**
 * Part 2 of workaround for Qt bug:
 * dock widget closes before close dialog is shown
 * dock widget state not persistent between sessions
 * dock widget closes if user cancels close dialog
 *
 * Called by RDockWidget whenever a dock widget receives a close event,
 * i.e. before the dock widget is hidden by Qt.
 *
 * When the application is terminated, Qt closes all top level widgets
 * (QApplicationPrivate::tryCloseAllWidgetWindows). Floating dock widgets are
 * top level widgets, so they are closed (and hidden) as well. The order in
 * which this happens is the order of QApplication::topLevelWidgets(), which
 * is based on an unordered set and therefore arbitrary: if a floating dock
 * widget happens to come before the main window, it is already hidden when
 * closeEvent() / writeSettings() is called and saveState() would store it as
 * hidden for the next session. Docked (non-floating) dock widgets are not top
 * level widgets and are never affected, which is why only floating dock
 * widgets lose their visibility (and only sometimes).
 *
 * We therefore remember the dock widget state of the main window before the
 * first dock widget of a close operation is hidden. The remembered state is
 * discarded again as soon as control returns to the event loop: if the dock
 * widget was closed by the user (and not as part of closing the main window),
 * closeEvent() is never called and the state must not be reused.
 */
void RMainWindowQt::notifyDockWidgetClosed(QWidget* dockWidget) {
    if (dockWidget==NULL) {
        return;
    }

    if (!dockWidgetStateValid) {
        // first dock widget which is closed:
        // remember state while all dock widgets are still in their
        // pre-close state:
        dockWidgetState = saveState();
        dockWidgetStateValid = true;

        // forget the state again as soon as we are back in the event loop:
        QTimer::singleShot(0, this, SLOT(forgetDockWidgetState()));
    }

    if (dockWidget->isVisible()) {
        closedDockWidgets.append(QPointer<QWidget>(dockWidget));
        closedDockWidgetPositionsX.append(dockWidget->x());
    }
}

/**
 * Discards the dock widget state remembered by notifyDockWidgetClosed().
 */
void RMainWindowQt::forgetDockWidgetState() {
    if (closingDown) {
        // the main window is closing: keep the remembered state until it has
        // been stored by writeSettings(). Note that closeEvent may well return
        // to the event loop, e.g. to show a 'save changes?' dialog:
        return;
    }

    dockWidgetState.clear();
    dockWidgetStateValid = false;
    closedDockWidgets.clear();
    closedDockWidgetPositionsX.clear();
}

/**
 * Shows all dock widgets again which were closed by Qt as part of the
 * current (canceled) close operation.
 */
void RMainWindowQt::restoreClosedDockWidgets() {
    closingDown = false;

    for (int i=0; i<closedDockWidgets.length(); i++) {
        QWidget* w = closedDockWidgets[i];
        if (w==NULL) {
            continue;
        }
        w->setVisible(true);
#ifdef Q_OS_MAC
        // workaround for macOS bug:
        // floating dock widget moves when hidden and shown again:
        w->move(closedDockWidgetPositionsX[i], w->y());
#endif
    }
    forgetDockWidgetState();
}

void RMainWindowQt::closeEvent(QCloseEvent* e) {
    // from here on, the dock widget state remembered by
    // notifyDockWidgetClosed() must not be discarded until it was stored by
    // writeSettings() (closeEvent may return to the event loop, e.g. to show
    // a 'save changes?' dialog):
    closingDown = true;

    if (mdiArea==NULL) {
        e->accept();
        return;
    }

    if (mdiArea->subWindowList().isEmpty()) {
        RSettings::setValue("OpenFile/OpenFiles", QStringList());
        RSettings::setValue("OpenFile/ActiveFile", QString());
        writeSettings();

        e->accept();
        return;
    }

    QStringList openFiles;
    QString activeFile;

    QMdiSubWindow* activeWindow = mdiArea->activeSubWindow();

    QList<QMdiSubWindow*> mdiChildren = mdiArea->subWindowList();
    for (int i=0; i<mdiChildren.size(); ++i) {
        QMdiSubWindow* mdiChild = mdiChildren.at(i);
        bool active = mdiChild==activeWindow;
        mdiArea->setActiveSubWindow(mdiChild);
        mdiChild->showMaximized();

        QString fileName;
        RMdiChildQt* rMdiChild = dynamic_cast<RMdiChildQt*>(mdiChild);
        if (rMdiChild!=NULL) {
            RDocument* doc = rMdiChild->getDocument();
            if (doc!=NULL) {
                fileName = doc->getFileName();
            }
        }

        QCloseEvent closeEvent;
        QApplication::sendEvent(mdiChild, &closeEvent);

        if (!closeEvent.isAccepted()) {
            e->ignore();
            // closing of app canceled:
            // show dock widgets again which were closed by Qt as part of
            // this close operation:
            restoreClosedDockWidgets();
            return;
        }

        if (!fileName.isEmpty()) {
            openFiles.append(fileName);
            if (active) {
                activeFile = fileName;
            }
        }

        delete mdiChild;
    }

    e->accept();

    RSettings::setValue("OpenFile/OpenFiles", openFiles);
    RSettings::setValue("OpenFile/ActiveFile", activeFile);

    writeSettings();

#if (QT_VERSION < 0x060900)
    // Crashes Qt 6.9:
    QApplication::quit();
#endif
}

void RMainWindowQt::dragEnterEvent(QDragEnterEvent* event) {
    emit dragEnter(event);
}

void RMainWindowQt::dropEvent(QDropEvent* event) {
    emit drop(event);
}

int RMainWindowQt::getWidth() {
    return width();
}

int RMainWindowQt::getHeight() {
    return height();
}

int RMainWindowQt::getPositionX() {
    return x();
}

int RMainWindowQt::getPositionY() {
    return y();
}

void RMainWindowQt::resize(int width, int height) {
    QMainWindow::resize(width, height);
}

void RMainWindowQt::move(int x, int y) {
    QMainWindow::move(x, y);
}

void RMainWindowQt::disable() {
    disableCounter++;
    if (disableCounter==1) {
        setEnabled(false);
    }
}

void RMainWindowQt::enable() {
    disableCounter--;
    if (disableCounter==0) {
        setEnabled(true);

#ifdef Q_OS_MAC
#if QT_VERSION == 0x050B00 || QT_VERSION == 0x050B01
        // workaround for Qt 5.10.0-5.11.1 bug
        // only small portion of app win is redrawn when enabled
        // redraw can only be forced with a resize
        resize(width(), height()+1);
        resize(width(), height()-1);
#endif
#endif
    }
}

void RMainWindowQt::quit() {
    emit closeRequested();
    QMainWindow::close();
}

RDocument* RMainWindowQt::getDocument() {
    RMdiChildQt* mdi = getMdiChild();
    if (mdi != NULL) {
        return mdi->getDocument();
    }
    return NULL;
}

RDocumentInterface* RMainWindowQt::getDocumentInterface() {
    RMdiChildQt* mdi = getMdiChild();
    if (mdi != NULL) {
        return mdi->getDocumentInterface();
    }
    return NULL;
}

RMdiChildQt* RMainWindowQt::getMdiChild() {
    if (mdiArea==NULL) {
        return NULL;
    }

    if (mdiArea->subWindowList().isEmpty()) {
        return NULL;
    }

    QMdiSubWindow* currentSubWindow = mdiArea->currentSubWindow();
    if (currentSubWindow!=NULL) {
        //return dynamic_cast<RMdiChildQt*> (currentSubWindow->widget());
        return dynamic_cast<RMdiChildQt*> (currentSubWindow);
    }

    // fall back: last window in stack:
    currentSubWindow = mdiArea->subWindowList(QMdiArea::StackingOrder).last();
    if (currentSubWindow == NULL) {
        return NULL;
    }

    //return dynamic_cast<RMdiChildQt*> (currentSubWindow->widget());
    return dynamic_cast<RMdiChildQt*> (currentSubWindow);
}

RMdiArea* RMainWindowQt::getMdiArea() {
    return mdiArea;
}

QTabBar* RMainWindowQt::getTabBar() {
    QTabBar* tb = mdiArea->findChild<QTabBar*>();
    return tb;
}

void RMainWindowQt::setProgress(int value) {
    if (!progressEnabled) {
        return;
    }
    static int lastProgress = -1;
    if (lastProgress==-1 || abs(value-lastProgress)>=5) {
        emit progress(value);
        lastProgress = value;
    }
}

void RMainWindowQt::cancelProgress() {
    emit progressCanceled();
}

void RMainWindowQt::setProgressEnd() {
    if (!progressEnabled) {
        return;
    }
    emit progressEnd();
}

void RMainWindowQt::setProgressText(const QString& text) {
    if (!progressEnabled) {
        return;
    }
    emit progressText(text);
}

void RMainWindowQt::setCommandPrompt(const QString& text) {
    emit commandPrompt(text);
}

void RMainWindowQt::setRightMouseTip(const QString& text) {
    emit rightMouseTip(text);
}

void RMainWindowQt::setLeftMouseTip(const QString& text) {
    emit leftMouseTip(text);
}

void RMainWindowQt::escapeEvent() {
    emit escape();
}

void RMainWindowQt::showContextMenu(RObject::Id entityId, const RVector& pos) {
    emit contextMenu((int)entityId, pos);
}

void RMainWindowQt::requestResourceBlockEditing(RObject::Id entityId, const RVector& pos) {
    emit editResourceBlock((int)entityId, pos);
}

void RMainWindowQt::setGraphicsViewCursor(const QCursor& cursor) {
    if (mdiArea==NULL) {
        return;
    }

    QList<QMdiSubWindow *> list = mdiArea->subWindowList();
    for (int i = 0; i < list.size(); ++i) {
        if (list.at(i)==NULL) {
            continue;
        }
        RMdiChildQt* mdi = dynamic_cast<RMdiChildQt*>(list.at(i));
        if (mdi==NULL) {
            continue;
        }
        RDocumentInterface* di = mdi->getDocumentInterface();
        if (di==NULL) {
            continue;
        }

        // false here prevents recursion:
        di->setCursor(cursor, false);
    }
}

/**
 * Restores the application window settings (size, position, ...).
 */
bool RMainWindowQt::readSettings() {
    bool ret = RMainWindow::readSettings();

    restoreState(RSettings::getQSettings()->value("Appearance/DockappWindows").toByteArray());

    bool maximized = RSettings::getQSettings()->value("Appearance/Maximized", false).toBool();
    if (bool(windowState() & Qt::WindowMaximized) != maximized) {
        if (maximized) {
            setWindowState(windowState() | Qt::WindowMaximized);
        } else {
            setWindowState(windowState() & ~Qt::WindowMaximized);
        }
    }

    bool fullScreen = RSettings::getQSettings()->value("Appearance/FullScreen", false).toBool();
    if (bool(windowState() & Qt::WindowFullScreen) != fullScreen) {
        if (fullScreen) {
            setWindowState(windowState() | Qt::WindowFullScreen);
        } else {
            setWindowState(windowState() & ~Qt::WindowFullScreen);
        }
    }

    bool statusBarOn = RSettings::getQSettings()->value("Appearance/StatusBar", true).toBool();
    if (!statusBarOn) {
        statusBar()->hide();
    }

    // sanity check:
    const QList<QScreen*> screens = QGuiApplication::screens();
    const QList<QWidget*> topLevelWidgets = QApplication::topLevelWidgets();

    for (int i=0; i<topLevelWidgets.length(); i++) {
        bool sane = false;
        QWidget* widget = topLevelWidgets[i];

        QRect widgetRect = widget->frameGeometry();
        for (int k=0; k<screens.length(); k++) {
            QScreen* screen = screens[k];
            if (screen->geometry().intersects(widgetRect)) {
                sane = true;
            }
        }

        if (!sane) {
            widget->move(0,0);
        }
    }

    return ret;
}

/**
 * Stores the application window settings (size, position, ...).
 */
void RMainWindowQt::writeSettings() {
    RMainWindow::writeSettings();

    // if Qt has already closed (and hidden) floating dock widgets as part of
    // the current close operation, store the state from before they were
    // closed, otherwise their visibility would be lost for the next session
    // (see notifyDockWidgetClosed):
    QByteArray state;
    if (dockWidgetStateValid) {
        state = dockWidgetState;
    }
    else {
        state = saveState();
    }
    RSettings::getQSettings()->setValue("Appearance/DockappWindows", state);
    RSettings::getQSettings()->setValue("Appearance/FullScreen", isFullScreen());
    RSettings::getQSettings()->setValue("Appearance/Maximized", isMaximized());
    RSettings::getQSettings()->setValue("Appearance/StatusBar", statusBar()->isVisible());

    // remember screen index for splash screen on next start up:
    if (windowHandle()!=NULL) {
        QScreen* screen = windowHandle()->screen();
        int screenIndex = QGuiApplication::screens().indexOf(screen);
        RSettings::getQSettings()->setValue("Appearance/Screen", screenIndex);
    }

    RSettings::getQSettings()->sync();
}

QWidget* RMainWindowQt::getChildWidget(const QString& name) {
    return findChild<QWidget*>(name);
}

QMenu* RMainWindowQt::createPopupMenu() {
    QMenu* menu = new QMenu();
    emit toolBarContextMenu(menu);
    if (menu->isEmpty()) {
        delete menu;
        menu = NULL;
    }
    return menu;
}

void RMainWindowQt::clearKeyLog() {
    keyLog.clear();
}

bool RMainWindowQt::event(QEvent* e) {
    if (e==NULL) {
        return false;
    }

    switch ((int)e->type()) {

    case QEvent::ScreenChangeInternal:
    {
        RDocumentInterface* di = getDocumentInterface();
        if (di!=NULL) {
            RGraphicsView* gv = di->getLastKnownViewWithFocus();
            if (gv!=NULL) {
                gv->regenerate();
            }
        }
    }
    break;


    case QEvent::WindowActivate:
    {
        // hand keyboard focus to grphics view for various key events (tab, entering number, options shortcuts):
        RDocumentInterface* di = getDocumentInterface();
        if (di!=NULL) {
            RGraphicsView* gv = di->getLastKnownViewWithFocus();
            if (gv!=NULL) {
                QWidget* w = gv->getWidget();
                if (w!=NULL) {
                    w->setFocus(Qt::ActiveWindowFocusReason);
                }
            }
        }
    }
    break;

    case QEvent::PaletteChange:
    case QEvent::ApplicationPaletteChange:
    {
        RSettings::resetDarkModeCache();

        static int darkMode = -1;
        if (darkMode!=(int)RSettings::isDarkMode()) {
            // mode has changed from dark to light or vice versa:
            RSettings::resetCache();
            RGuiAction::updateIcons();
            RGuiAction::updateToolTips();
            notifyPaletteListeners();
            update();
            darkMode = (int)RSettings::isDarkMode();
        }
    }
    break;

    case QEvent::KeyPress:
    {
        QKeyEvent* ke = dynamic_cast<QKeyEvent*>(e);
        if (ke!=NULL) {

            // notify key listeners,
            // e.g. for up / down / left / right keys
            notifyKeyListeners(ke);

            // enter:
            if (ke->key()==Qt::Key_Enter || ke->key()==Qt::Key_Return) {
                QWidget* w = QApplication::focusWidget();
                if (w!=NULL) {
                    // focus with view, main window or tool button:
                    // repeat last command:
                    if (dynamic_cast<RGraphicsViewQt*>(w)!=NULL ||
                        dynamic_cast<RMainWindowQt*>(w)!=NULL ||
                        dynamic_cast<QToolButton*>(w)!=NULL) {

                        emit enterPressed();
                        e->accept();
                    }
                    else {
                        // enter pressed in toolbar but NOT in a line edit:
                        QWidget* parent = w->parentWidget();
                        if (dynamic_cast<QToolBar*>(parent)!=NULL &&
                            dynamic_cast<QLineEdit*>(w)==NULL &&
                            dynamic_cast<QComboBox*>(w)==NULL) {

                            emit enterPressed();
                            e->accept();
                        }
                        else {
                            // enter pressed in a line edit in the options toolbar:
                            if (dynamic_cast<QLineEdit*>(w)!=NULL &&
                                dynamic_cast<QToolBar*>(parent)!=NULL) {

                                // move focus from options toolbar line edit to graphics view:
                                RDocumentInterface* di = getDocumentInterface();
                                if (di!=NULL) {
                                    RGraphicsView* gv = di->getLastKnownViewWithFocus();
                                    if (gv!=NULL) {
                                        QWidget* gvWidget = gv->getWidget();
                                        if (gvWidget!=NULL) {
                                            gvWidget->setFocus(Qt::OtherFocusReason);
                                        }
                                    }
                                }

                            }
                        }
                    }
                }
            }
            else {
                if (ke->key()<128) {
                    if (keyTimeOut.elapsed()>RSettings::getIntValue("Keyboard/Timeout", 2000)) {
                        keyLog.clear();
                    }
                    keyLog += QChar(ke->key());
                    //qDebug() << "keyLog:" << keyLog;

                    int actionState = -1;
                    RDocumentInterface* di = getDocumentInterface();
                    if (di!=NULL) {
                        RAction* action = di->getCurrentAction();
                        if (action!=NULL) {
                            actionState = action->getState();
                        }
                    }

                    if (mainWindowProxy && mainWindowProxy->handleOptionsShortcut(keyLog, actionState)) {
                        // shortcut for options toolbar:
                        keyLog.clear();
                    }
                    else if (RGuiAction::triggerByShortcut(keyLog)) {
                        // shortcut for tool:
                        keyLog.clear();
                    }
                    else {
                        // wait for additional keystrokes:
                        keyTimeOut.restart();
                    }
                }
            }
        }
    }
    break;


    case QEvent::IconDrag:
    {
        // TODO: never triggered on macOS when dragging title bar icon
        //    QIconDragEvent* ide = dynamic_cast<QIconDragEvent*>(e);
        //    if (ide!=NULL) {
        //        qDebug() << "QIconDragEvent";
        //        ide->accept();
        //        return true;
        //    }
    }


    case QEvent::User+100:
    {
        RSelectionChangedEvent* sce = dynamic_cast<RSelectionChangedEvent*>(e);
        if (sce!=NULL) {
            // selection changed: reset property editor filter to show all entities:
            notifyPropertyListeners(getDocument(), false, RS::EntityAll);
            notifySelectionListeners(getDocumentInterface());
            return true;
        }
    }
    break;


    case QEvent::User+201:
    {
        RCoordinateEvent* coe = dynamic_cast<RCoordinateEvent*>(e);
        if (coe!=NULL) {
            RDocumentInterface* di = getDocumentInterface();
            if (di!=NULL) {
                di->coordinateEvent(*coe);
            }
            return true;
        }
    }
    break;


    case QEvent::User+300:
    {
        RTransactionEvent* te = dynamic_cast<RTransactionEvent*>(e);
        if (te!=NULL) {
            // combined properties might have changed (deleted entities):
            notifyPropertyListeners(getDocument(), te->hasOnlyChanges());
            // selection might have changed (deleted entities):
            notifySelectionListeners(getDocumentInterface());
            // notify transaction listeners:
            RTransaction t = te->getTransaction();
            notifyTransactionListeners(getDocument(), &t);
            return true;
        }
    }
    break;


    case QEvent::User+400:
    {
        RCloseCurrentEvent* cce = dynamic_cast<RCloseCurrentEvent*>(e);
        if (cce!=NULL) {
            if (mdiArea==NULL) {
                return true;
            }

            // workaround for QMdiArea bug: last window cannot be closed sometimes:
            if (mdiArea->activeSubWindow()==NULL) {
                QList<QMdiSubWindow *> subWindows = mdiArea->subWindowList();
                if (subWindows.size()==1) {
                    //mdiArea->setActiveSubWindow(subWindows.at(0));
                    qDebug() << "RMainWindowQt::event: closing subwindow";
                    subWindows.at(0)->close();
                }
            }
            else {
                qDebug() << "RMainWindowQt::event: closing active subwindow";
                mdiArea->closeActiveSubWindow();
            }
            if (RSettings::getBoolValue("TabBar/ShowAddTabButton", false)) {
                mdiArea->updateTabBar();
            }
            return true;
        }
    }
    break;


    case QEvent::User+500:
    {
        RPropertyEvent* pe = dynamic_cast<RPropertyEvent*>(e);
        if (pe!=NULL) {
            RDocumentInterface* documentInterface = getDocumentInterface();
            if (documentInterface!=NULL) {
                // called when user changed a property in the property editor
                documentInterface->propertyChangeEvent(*pe);
            }
            return true;
        }
    }
    break;

    }

#if QT_VERSION < 0x050000 && (defined(Q_OS_MACOS) || defined(Q_OS_WIN))
    // Qt 4.x: prevent recursion:
    // (bug, probably in Qt script wrappers: recursion when displaying status tip)
    static bool running = false;
    if (running) {
        return true;
    }
    running = true;
    bool ret = QMainWindow::event(e);
    running = false;
    return ret;
#else
    bool ret = QMainWindow::event(e);
    return ret;
#endif
}

/**
 * Moves the keyboard focus to the next (or previous) widget in the
 * focus chain of this main window, starting at widget \c from
 * (default: current focus widget). This is the standard Tab / Shift+Tab
 * behavior, used by widgets which handle Tab themselves (graphics view,
 * options tool bar) to continue the focus chain when they cannot handle it.
 *
 * Unlike QWidget::focusNextPrevChild, this skips ancestors of \c from:
 * QMdiSubWindow is focusable but immediately passes the focus back to its
 * child widget (the graphics view), which would trap the focus.
 */
bool RMainWindowQt::focusNextPrevWidget(bool next, QWidget* from) {
    if (from==NULL) {
        from = QApplication::focusWidget();
    }
    if (from==NULL) {
        return QMainWindow::focusNextPrevChild(next);
    }

    QWidget* w = from;
    for (int i=0; i<100000; i++) {
        w = next ? w->nextInFocusChain() : w->previousInFocusChain();
        if (w==NULL || w==from) {
            break;
        }
        if ((w->focusPolicy() & Qt::TabFocus)!=Qt::TabFocus) {
            continue;
        }
        if (w->focusProxy()!=NULL) {
            continue;
        }
        if (!isAncestorOf(w)) {
            continue;
        }
        if (w->isAncestorOf(from)) {
            // e.g. QMdiSubWindow: would give focus back to child:
            continue;
        }
        if (!isFocusReachable(w)) {
            continue;
        }
        w->setFocus(next ? Qt::TabFocusReason : Qt::BacktabFocusReason);
        return true;
    }

    return false;
}

/**
 * \return True if the given widget can be reached with the keyboard (Tab):
 * enabled, visible and not covered, e.g. by another dock widget in the same
 * tab stack (such dock widgets report isVisible() true but have an empty
 * visible region). Widgets in scroll areas are checked at the level of the
 * scroll area, since they might be scrolled out of view temporarily.
 */
bool RMainWindowQt::isFocusReachable(QWidget* w) const {
    if (w==NULL || !w->isEnabled() || !w->isVisibleTo(const_cast<RMainWindowQt*>(this))) {
        return false;
    }

    // widget in scroll area (e.g. property editor): check outermost scroll area:
    QWidget* check = w;
    for (QWidget* p = w->parentWidget(); p!=NULL && p!=this; p = p->parentWidget()) {
        if (qobject_cast<QAbstractScrollArea*>(p)!=NULL) {
            check = p;
        }
    }

    // covered (dock widget tab not on top of stack) or zero size:
    if (check->visibleRegion().isEmpty()) {
        return false;
    }

    return true;
}

/**
 * Standard Tab / Shift+Tab handling of the main window, using
 * focusNextPrevWidget to skip widgets which are not reachable
 * (e.g. in dock widgets not on top of their tab stack).
 */
bool RMainWindowQt::focusNextPrevChild(bool next) {
    if (focusNextPrevWidget(next)) {
        return true;
    }
    return QMainWindow::focusNextPrevChild(next);
}
