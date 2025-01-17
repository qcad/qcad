/**
 * Copyright (c) 2011-2022 by Andrew Mustun. All rights reserved.
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
#include <QStackedLayout>
#include <QMenu>

#include "RCadToolBar.h"
#include "RCadToolBarPanel.h"
#include "RMainWindowQt.h"
#include "RSettings.h"

RCadToolBar::RCadToolBar(const QString& title, QWidget* parent) :
    QToolBar(title, parent),
    widget(NULL) {

    int buttonSize = RSettings::getIntValue("CadToolBar/IconSize", 32) * 1.25;

    // widget inside toolbar is needed to allow two rows of
    // tool buttons in a layout:
    setObjectName("CadToolBar");
    setMinimumWidth(buttonSize);
    setMinimumHeight(buttonSize);

    widget = new QWidget(this);
    addWidget(widget);

    stackedLayout = new QStackedLayout();
    stackedLayout->setObjectName("StackedLayout");
    stackedLayout->setContentsMargins(0,0,0,0);
    widget->setLayout(stackedLayout);

    RMainWindowQt* appWin = RMainWindowQt::getMainWindow();
    if (appWin) {
        connect(appWin, SIGNAL(escape()), this, SLOT(back()));
    }
}

RCadToolBarPanel* RCadToolBar::getPanel(const QString& title, const QString& objectName, bool hasBackButton) {
    // find and return existing panel:
    RCadToolBarPanel* panel = findChild<RCadToolBarPanel*>(objectName);
    if (panel!=NULL) {
        return panel;
    }

    // create new panel:
    panel = new RCadToolBarPanel(this, hasBackButton);
    panel->setObjectName(objectName);
    stackedLayout->addWidget(panel);

    return panel;
}

bool RCadToolBar::back() {
    RCadToolBarPanel* panel = getCurrentPanel();
    if (panel==NULL) {
        return false;
    }

    // no back for main tools panel:
    if (panel->objectName()=="MainToolsPanel") {
        return false;
    }

    showPanel(panel->getBackMenuName(), true);

    return true;
}

RCadToolBarPanel* RCadToolBar::getCurrentPanel() const {
    if (stackedLayout->currentIndex()<0 || stackedLayout->currentIndex()>=stackedLayout->count()) {
        return NULL;
    }

    return qobject_cast<RCadToolBarPanel*>(stackedLayout->widget(stackedLayout->currentIndex()));
}

QString RCadToolBar::getCurrentPanelName() const {
    RCadToolBarPanel* panel = getCurrentPanel();
    if (panel==NULL) {
        return "";
    }

    return panel->objectName();
}

void RCadToolBar::showPanel(const QString& name, bool isBack) {
    if (name.isEmpty()) {
        return;
    }

    QString backMenuName = getCurrentPanelName();

    RCadToolBarPanel* panel = findChild<RCadToolBarPanel*>(name);
    if (panel==NULL) {
        qWarning() << "CadToolBar: panel does not exist: " << name;
        return;
    }

    for (int i=0; i<stackedLayout->count(); ++i) {
        QWidget* w = stackedLayout->widget(i);
        if (w!=NULL) {
            w->setMinimumHeight(0);
            w->setMinimumWidth(0);
        }
    }
    stackedLayout->setCurrentWidget(panel);

    if (!isBack && backMenuName!=panel->objectName() && backMenuName!="SnapToolsPanel") {
        panel->setBackMenuName(backMenuName);
    }
};

void RCadToolBar::contextMenuEvent(QContextMenuEvent* event) {
    QString panelName = getCurrentPanelName();
    if (panelName!="MainToolsPanel") {
        showPanel("MainToolsPanel");
    }
    else {
        // workaround for Qt 4:
        if (isFloating() && RSettings::getQtVersion()<0x050000) {
            QMenu* menu = new QMenu(this);
            menu->setObjectName("ContextMenu");
            // force tool bar to be vertical:
            QAction* action = menu->addAction(tr("Vertical/Horizontal"));
            connect(action, SIGNAL(triggered(bool)), this, SLOT(toggleVerticalWhenFloating(bool)));


            menu->exec(QCursor::pos());
        }
    }
};

void RCadToolBar::toggleVerticalWhenFloating(bool on) {
    bool verticalWhenFloating = RSettings::getBoolValue("CadToolBar/VerticalWhenFloating", false);
    RSettings::setValue("CadToolBar/VerticalWhenFloating", !verticalWhenFloating);

    updateIconSize();
}

void RCadToolBar::updateIconSize() {
    // workaround for QToolBar bug (not resizing when layout changes):
    if (isFloating()) {
        resize(sizeHint().width(), sizeHint().height());
    }
};
