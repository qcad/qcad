/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
#include <QtGui>
#include <QLabel>
#include <QMenu>
#include <QMdiArea>
#include <QStatusBar>
#include <QTabBar>
#include <QToolBar>
#include <QToolButton>

#include <RSingleApplication.h>

#include "RDebug.h"
#include "RDocumentInterface.h"
#include "RGuiAction.h"
#include "RGraphicsViewQt.h"
#include "RMainWindowQt.h"
#include "RMdiArea.h"
#include "RMdiChildQt.h"
#include "RScriptHandler.h"
#include "RSelectionChangedEvent.h"
#include "RSettings.h"
#include "RTransactionEvent.h"

RMainWindowQt::RMainWindowQt(QWidget* parent, bool hasMdiArea) :
    QMainWindow(parent), RMainWindow(), mdiArea(NULL) {

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

void RMainWindowQt::handleUserMessage(const QString& message) {
    emit userMessage(message);
}

void RMainWindowQt::handleUserInfo(const QString& message) {
    emit userInfo(message);
}

void RMainWindowQt::handleUserWarning(const QString& message, bool messageBox) {
    emit userWarning(message, messageBox);
}

void RMainWindowQt::handleUserCommand(const QString& message) {
    emit userCommand(message);
}

void RMainWindowQt::postSelectionChangedEvent() {
    RSelectionChangedEvent* event = new RSelectionChangedEvent();
    QCoreApplication::postEvent(this, event);
}

void RMainWindowQt::postTransactionEvent(RTransaction& t, bool onlyChanges, RS::EntityType entityTypeFilter) {
    RTransactionEvent* event = new RTransactionEvent(t, onlyChanges, entityTypeFilter);
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

void RMainWindowQt::closeEvent(QCloseEvent* e) {
    if (mdiArea==NULL) {
        e->accept();
        return;
    }

    if (mdiArea->subWindowList().isEmpty()) {
        e->accept();
        return;
    }

    QList<QMdiSubWindow*> mdiChildren = mdiArea->subWindowList();
    for (int i=0; i<mdiChildren.size(); ++i) {
        QMdiSubWindow* mdiChild = mdiChildren.at(i);
        mdiArea->setActiveSubWindow(mdiChild);
        mdiChild->showMaximized();

        QCloseEvent closeEvent;
        QApplication::sendEvent(mdiChild, &closeEvent);

        if (!closeEvent.isAccepted()) {
            e->ignore();
            return;
        }

        delete mdiChild;
    }

    e->accept();
    writeSettings();

    QApplication::quit();
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

void RMainWindowQt::showContextMenu(RObject::Id entityId) {
    emit contextMenu((int)entityId);
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
        RMdiChildQt* mdiOther = dynamic_cast<RMdiChildQt*>(list.at(i));
        if (mdiOther==NULL) {
            continue;
        }
        RDocumentInterface* diOther = mdiOther->getDocumentInterface();
        if (diOther==NULL) {
            continue;
        }

        diOther->setCursor(cursor, false);
    }
}

/**
 * Restores the application window settings (size, position, ...).
 */
bool RMainWindowQt::readSettings() {
    bool ret = RMainWindow::readSettings();

    restoreState(RSettings::getQSettings()->value("Appearance/DockappWindows").toByteArray());

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

    return ret;
}

/**
 * Stores the application window settings (size, position, ...).
 */
void RMainWindowQt::writeSettings() {
    RMainWindow::writeSettings();
    RSettings::getQSettings()->setValue("Appearance/DockappWindows", saveState());
    RSettings::getQSettings()->setValue("Appearance/FullScreen", isFullScreen());
    RSettings::getQSettings()->setValue("Appearance/StatusBar", statusBar()->isVisible());
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

bool RMainWindowQt::event(QEvent* e) {
    if (e==NULL) {
        return false;
    }

    if (e->type()==QEvent::KeyPress) {
        QKeyEvent* ke = dynamic_cast<QKeyEvent*>(e);
        if (ke!=NULL) {
            if (ke->key()==Qt::Key_Enter || ke->key()==Qt::Key_Return) {
                QWidget* w = QApplication::focusWidget();
                if (w!=NULL) {
                    if (dynamic_cast<RGraphicsViewQt*>(w)!=NULL ||
                        dynamic_cast<RMainWindowQt*>(w)!=NULL ||
                        dynamic_cast<QToolButton*>(w)!=NULL) {

                        emit enterPressed();
                    }
                    QWidget* parent = w->parentWidget();
                    if (dynamic_cast<QToolBar*>(parent)!=NULL) {
                        emit enterPressed();
                    }
                }
            }
        }
    }

    RSelectionChangedEvent* sce = dynamic_cast<RSelectionChangedEvent*>(e);
    if (sce!=NULL) {
        notifyPropertyListeners(getDocument());
        notifySelectionListeners(getDocumentInterface());
        return true;
    }

    RTransactionEvent* te = dynamic_cast<RTransactionEvent*>(e);
    if (te!=NULL) {
        // combined properties might have changed (deleted entities):
        notifyPropertyListeners(getDocument(), te->hasOnlyChanges(), te->getEntityTypeFilter());
        // selection might have changed (deleted entities):
        notifySelectionListeners(getDocumentInterface());
        // notify transaction listeners:
        RTransaction t = te->getTransaction();
        notifyTransactionListeners(getDocument(), &t);
        return true;
    }

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

#if QT_VERSION < 0x050000 && (defined(Q_OS_MAC) || defined(Q_OS_WIN))
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
