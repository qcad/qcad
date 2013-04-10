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
#include <QtGui>
#include <QLabel>
#include <QTabBar>

#include <RSingleApplication.h>

#include "RDebug.h"
#include "RDocumentInterface.h"
#include "RGuiAction.h"
#include "RMainWindowQt.h"
#include "RMdiChildQt.h"
#include "RScriptHandler.h"
#include "RSelectionChangedEvent.h"
#include "RSettings.h"
#include "RTransactionEvent.h"

RMainWindowQt::RMainWindowQt(QWidget* parent, bool hasMdiArea) :
    QMainWindow(parent), RMainWindow(), mdiArea(NULL) {

    if (hasMdiArea) {
        mdiArea = new QMdiArea(this);
        mdiArea->setViewMode(QMdiArea::TabbedView);
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
        }
        else {
            qDebug() << "tabBar is NULL";
        }
    }
    setWindowTitle("RMainWindowQt");

    RSingleApplication* singleApp = dynamic_cast<RSingleApplication*> (qApp);
    if (singleApp!=NULL) {
        singleApp->setActivationWindow(this);
    }
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
        //Q_ASSERT(false);
        return;
    }

    RMdiChildQt* mdiChild = dynamic_cast<RMdiChildQt*>(subWindows.at(index));
    mdiChild->showMaximized();
    mdiArea->setActiveSubWindow(mdiChild);

    //QMdiSubWindow* subWindow = childWindows.at(index);
}

void RMainWindowQt::subWindowActivated(QMdiSubWindow* sw) {
    updateScenes(sw);
    updateGuiActions(sw);
    notifyListenersSlot(sw);
    suspendAndResume(sw);
}

//void RMainWindowQt::objectDestroyed(QObject* obj) {
//    qDebug() << "objectDestroyed: " << obj->objectName();
//    objectWasDestroyed = true;
//}

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

void RMainWindowQt::postTransactionEvent(bool onlyChanges, RS::EntityType entityTypeFilter) {
    RTransactionEvent* event = new RTransactionEvent(onlyChanges, entityTypeFilter);
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
    //RMdiChildQt* mdi = getMdiChild();
    //bool hasDocument = (mdi != NULL);
    RDocument* document = getDocument();
    //bool hasDocument = (document != NULL);

    //qDebug() << "RMainWindowQt::updateGuiActions: hasDocument: " << hasDocument;

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

#ifndef Q_OS_WIN32
#if (QT_VERSION < QT_VERSION_CHECK(4, 8, 0))
        // core part of the workaround for Qt 4.7.x QMdiArea bug
        // with events filtering through all stacked windows:
        mdiOther->hide();
#endif
#endif
    }

    di->resume();

    emit(resumedTab(mdi));

    //QString sep = " - ";
    //QString appWinTitle = windowTitle();
    //if (appWinTitle.contains(sep)) {
    //    appWinTitle = appWinTitle.right(appWinTitle.length() - appWinTitle.lastIndexOf(sep) - sep.length());
    //}
    //appWinTitle
    //setWindowTitle(mdi->windowTitle() + " - " + qApp->applicationName());
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

//void RMainWindowQt::disableTabBar(QMdiSubWindow* mdiChild) {
//    Q_UNUSED(mdiChild)

//    QTabBar* tabBar = getTabBar();
//    if (tabBar!=NULL) {
//        tabBar->setEnabled(false);
//    }
//}

//void RMainWindowQt::enableTabBar(QMdiSubWindow* mdiChild) {
//    Q_UNUSED(mdiChild)

//    QTabBar* tabBar = getTabBar();
//    if (tabBar!=NULL) {
//        tabBar->setEnabled(true);
//    }
//}

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
}

void RMainWindowQt::dragEnterEvent(QDragEnterEvent* event) {
    emit dragEnter(event);
}

void RMainWindowQt::dropEvent(QDropEvent* event) {
    emit drop(event);
}

/*
void RMainWindowQt::keyPressEvent(QKeyEvent* e) {
    static QTime ts;
    static QString firstKey;

    switch (e->key()) {
    case Qt::Key_Shift:
    case Qt::Key_Control:
    case Qt::Key_Alt:
    case Qt::Key_AltGr:
    case Qt::Key_CapsLock:
    case Qt::Key_Meta:
    case Qt::Key_Menu:
    case Qt::Key_Space:
    case Qt::Key_Return:
        QMainWindow::keyPressEvent(e);
        return;
        break;
    case Qt::Key_Escape:
        firstKey = "";
        QMainWindow::keyPressEvent(e);
        return;
        break;
    default:
        e->ignore();
        break;
    }

    QString keyString = QKeySequence(e->key()).toString().toLower();
    qDebug(QString("RMainWindowQt::keyPressEvent: keyString: '%1'").arg(keyString));
    QTime now = QTime::currentTime();

    if (ts.msecsTo(now) < 2000) {
        QString code = firstKey + keyString;
        qDebug(QString("RMainWindowQt::keyPressEvent: code: '%1'").arg(code));
        if (RGuiAction::triggerByKeycode(code)) {
            firstKey = "";
            return;
        } else {
            ts = now;
            firstKey = code;
            if (code.length() >= 3) {
                firstKey = "";
                return;
            }
        }
    } else {
        ts = now;
        firstKey = keyString;
        if (RGuiAction::triggerByKeycode(firstKey)) {
            firstKey = "";
            return;
        }
    }
    QMainWindow::keyPressEvent(e);
}
*/

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

void RMainWindowQt::close() {
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

QMdiArea* RMainWindowQt::getMdiArea() {
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
            //statusBar()->hide();
            //menuBar()->hide();
        } else {
            setWindowState(windowState() & ~Qt::WindowFullScreen);
            //menuBar()->show();
            //statusBar()->show();
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

bool RMainWindowQt::event(QEvent* e) {
    if (e==NULL) {
        return false;
    }

    RSelectionChangedEvent* sce = dynamic_cast<RSelectionChangedEvent*>(e);
    if (sce!=NULL) {
        notifyPropertyListeners(getDocument());
        notifySelectionListeners(getDocumentInterface());
        return true;
    }

//    RPropertyEvent* pce = dynamic_cast<RPropertyEvent*>(e);
//    if (pce!=NULL) {
//        RDocumentInterface* documentInterface = getDocumentInterface();
//        if (documentInterface == NULL) {
//            return true;
//        }

//        documentInterface->propertyChangeEvent(*pce);
//    }

    RTransactionEvent* te = dynamic_cast<RTransactionEvent*>(e);
    if (te!=NULL) {
        // combined properties might have changed (delete):
        notifyPropertyListeners(getDocument(), te->hasOnlyChanges(), te->getEntityTypeFilter());
        // selection might have changed (delete):
        notifySelectionListeners(getDocumentInterface());
        notifyTransactionListeners(getDocument());
        return true;
    }

    RCloseCurrentEvent* cce = dynamic_cast<RCloseCurrentEvent*>(e);
    if (cce!=NULL) {
        if (mdiArea==NULL) {
            return true;
        }

        // workaround for QMdiArea bug: last window cannot be closed sometimes:
//#ifndef Q_OS_WIN32
        if (mdiArea->activeSubWindow()==NULL) {
            QList<QMdiSubWindow *> subWindows = mdiArea->subWindowList();
            if (subWindows.size()==1) {
                //mdiArea->setActiveSubWindow(subWindows.at(0));
                subWindows.at(0)->close();
            }
        }
        else {
            mdiArea->closeActiveSubWindow();
        }
//#else
//        mdiArea->closeActiveSubWindow();
//#endif
        return true;
    }

#if defined(Q_OS_MAC) || defined(Q_OS_WIN32)
    // prevent recursion:
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
    //qDebug() << "RMainWindowQt::event: OK: " << e->type();
    bool ret = QMainWindow::event(e);
    //if (e->type()!=QEvent::Close) {
        //unlock("RMainWindowQt::event");
    //}
    return ret;
#endif
}
