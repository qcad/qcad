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
#include "RDocument.h"
#include "RMainWindowQt.h"
#include "RMdiArea.h"
#include "RMdiChildQt.h"

#include <QDebug>
#include <QEvent>
#include <QTabBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QScrollArea>

/**
 * Default Constructor.
 */
RMdiArea::RMdiArea(QWidget* parent) :
    QMdiArea(parent), tabBarOri(NULL), tabBar(NULL), addTabButton(NULL) {

    if (RSettings::getBoolValue("TabBar/ShowAddTabButton", false)) {
        addTabButton = new QToolButton(this);
        addTabButton->hide();
    }

    if (RSettings::hasDarkGuiBackground()) {
        setBackground(QBrush(QColor("#1E1E1E")));
    }
}

/**
 * Destructor
 */
RMdiArea::~RMdiArea() {
}

void RMdiArea::resizeEvent(QResizeEvent* event) {
    QMdiArea::resizeEvent(event);

    if (!RSettings::getBoolValue("TabBar/ShowAddTabButton", false)) {
        return;
    }

    if (tabBarOri==NULL) {
        tabBarOri = findChild<QTabBar*>();
    }

    updateTabBarSize();
    updateAddButtonLocation();
}

void RMdiArea::keyPressEvent(QKeyEvent* event) {
    QMdiArea::keyPressEvent(event);

    // make sure arrow key events can be handled in main window:
    event->ignore();
}

void RMdiArea::updateTabBarSize() {
    if (tabBarOri==NULL || tabBar==NULL) {
        return;
    }

    QRect g = tabBarOri->geometry();
    // make room for add tab button:
    if (tabBarOri->tabRect(tabBarOri->count()-1).right() > width()-10) {
        g.setWidth(g.width()-g.height());
    }
    else {
        g.setWidth(g.width());
    }
    tabBar->setGeometry(g);
}

void RMdiArea::updateAddButtonLocation() {
    if (addTabButton==NULL || tabBar==NULL) {
        return;
    }

    int r = 0;
    QList<QToolButton*> buttons = tabBar->findChildren<QToolButton*>();
    for (int i=0; i<buttons.length(); i++) {
        if (buttons[i]->isVisible()) {
            r = qMax(buttons[i]->x()+buttons[i]->width(), r);
        }
    }
    QRect lastTabRect = tabBar->tabRect(tabBar->count()-1);
    r = qMax(lastTabRect.right(), r);
    int s = lastTabRect.height();
    addTabButton->setFixedSize(s, s);
    addTabButton->move(r, 0);
    addTabButton->raise();
    addTabButton->show();
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
            remove++;
            continue;
        }

        QString t = tabBarOri->tabText(i);
        t.replace("&", "&&");
        tabBar->setTabText(ti, t);
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
    tabBar->blockSignals(false);
    tabBar->update();

    updateAddButtonLocation();
}

void RMdiArea::closeTab(int i) {
    QList<QMdiSubWindow*> subWindows = subWindowList(CreationOrder);
    if (i>=subWindows.length()) {
        return;
    }
    subWindows[i]->close();
    updateTabBar();
}

void RMdiArea::activateTab(int i) {
    if (i<0) {
        return;
    }

    tabBar->blockSignals(true);
    QList<QMdiSubWindow*> subWindows = subWindowList(CreationOrder);
    if (i>=subWindows.length()) {
        return;
    }
    setActiveSubWindow(subWindows[i]);
    tabBar->blockSignals(false);
}
