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
#include "RDocument.h"
#include "RMainWindowQt.h"
#include "RMdiArea.h"
#include "RMdiChildQt.h"

#include <QDebug>
#include <QEvent>
#include <QTabBar>
#include <QToolButton>

/**
 * Default Constructor.
 */
RMdiArea::RMdiArea(QWidget* parent) :
    QMdiArea(parent), tabBarOri(NULL), tabBar(NULL), addTabButton(NULL) {

    if (RSettings::getBoolValue("Appearance/ShowAddTabButton", false)) {
        addTabButton = new QToolButton(this);
        addTabButton->setFixedSize(20,20);
    }
    //connect(addTabButton, SIGNAL(clicked()), this, SLOT());

    //tabBar->move(0,0);

    //connect(this, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(updateTabBar()));
}

/**
 * Destructor
 */
RMdiArea::~RMdiArea() {
}

void RMdiArea::resizeEvent(QResizeEvent* event) {
    QMdiArea::resizeEvent(event);

    if (!RSettings::getBoolValue("Appearance/ShowAddTabButton", false)) {
        return;
    }

    if (tabBarOri==NULL) {
        tabBarOri = findChild<QTabBar*>();
    }

    updateTabBarSize();

    //tabBarOverride->setShape(QTabBar::TriangularNorth);
    //tabBar->move(0,0);
    //tabBar->setFixedSize();

//    QTabBar* tabBar = findChild<QTabBar*>();
    const QSize tabBarSizeHint = tabBarOri->sizeHint();
    int s = tabBarSizeHint.height();
    if (addTabButton!=NULL) {
        addTabButton->setFixedSize(s, s);
        addTabButton->move(width()-s, 0);
    }
}

void RMdiArea::updateTabBarSize() {
    if (tabBarOri==NULL || tabBar==NULL) {
        return;
    }

    QRect g = tabBarOri->geometry();
    // make room for add tab button:
    g.setWidth(g.width()-g.height());
    tabBar->setGeometry(g);
}

void RMdiArea::updateTabBar(RMdiChildQt* child) {
    if (tabBarOri==NULL) {
        return;
    }

    tabBarOri->hide();

    if (tabBar==NULL) {
        tabBar = new QTabBar(this);
        tabBar->setDocumentMode(tabBarOri->documentMode());
        tabBar->setTabsClosable(tabBarOri->tabsClosable());
        tabBar->setMovable(tabBarOri->isMovable());
        tabBar->setShape(tabBarOri->shape());
        tabBar->setElideMode(tabBarOri->elideMode());
        tabBar->setUsesScrollButtons(tabBarOri->usesScrollButtons());
        tabBar->setContextMenuPolicy(tabBarOri->contextMenuPolicy());
        tabBar->show();
        connect(tabBar, SIGNAL(currentChanged(int)), this, SLOT(activateTab(int)));
        connect(tabBar, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    }

    tabBar->blockSignals(true);

    updateTabBarSize();

    QList<QMdiSubWindow*> subWindows = subWindowList(CreationOrder);

    for (int i=0; i<subWindows.length()-tabBar->count(); i++) {
        tabBar->addTab("");
    }

    //qDebug() << "updating tab bar";
    int remove = 0;
    int ti = 0;
    for (int i=0; i<qMax(subWindows.length(), tabBar->count()); i++) {
        if (i>=subWindows.length()) {
            remove++;
            continue;
        }

        QMdiSubWindow* w = subWindows[i];
        RMdiChildQt* subWindow = dynamic_cast<RMdiChildQt*>(w);
        if (subWindow==NULL) {
            continue;
        }
        if (child!=NULL && child!=subWindow) {
            continue;
        }

        RDocumentInterface* di = subWindow->getDocumentInterface();
        if (di==NULL) {
            //qDebug() << "updating tab bar: remove";
            remove++;
            continue;
        }

        //qDebug() << "updating tab bar " << i << ": text: " << tabBarOri->tabText(i);
        tabBar->setTabText(ti, tabBarOri->tabText(i));
        tabBar->setTabIcon(ti, tabBarOri->tabIcon(i));
        tabBar->setTabToolTip(ti, tabBarOri->tabToolTip(i));
        disconnect(subWindow, SIGNAL(modifiedStatusChanged(RMdiChildQt*)), this, SLOT(updateTabBar(RMdiChildQt*)));
        connect(subWindow, SIGNAL(modifiedStatusChanged(RMdiChildQt*)), this, SLOT(updateTabBar(RMdiChildQt*)));
        ti++;
    }

    for (int i=0; i<remove; i++) {
        tabBar->removeTab(tabBar->count()-1);
    }

    tabBar->setCurrentIndex(tabBarOri->currentIndex());
    //tabBar->setScrollOffset(tabBarOri->scrollOffset());
    tabBar->blockSignals(false);
    tabBar->update();
}

void RMdiArea::closeTab(int i) {
    //RMainWindowQt* appWin = RMainWindowQt::getMainWindow();
    //RCloseCurrentEvent* closeEvent = new RCloseCurrentEvent();
    //QCoreApplication::postEvent(appWin, closeEvent);

    QList<QMdiSubWindow*> subWindows = subWindowList(CreationOrder);
    if (i>=subWindows.length()) {
        return;
    }
    //setActiveSubWindow(subWindows[i]);
    subWindows[i]->close();
    //closeActiveSubWindow();
    updateTabBar();
}

void RMdiArea::activateTab(int i) {
    qDebug() << "activateTab: " << i;
    if (i<0) {
        return;
    }

    tabBar->blockSignals(true);
    QList<QMdiSubWindow*> subWindows = subWindowList(CreationOrder);
    if (i>=subWindows.length()) {
        return;
    }
    setActiveSubWindow(subWindows[i]);
    //subWindows[i]->showMaximized();
    tabBar->blockSignals(false);
}
