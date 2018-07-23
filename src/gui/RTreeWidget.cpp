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
#include "REventFilter.h"
#include "RSettings.h"
#include "RTreeWidget.h"

#include <QContextMenuEvent>
#include <QHeaderView>

/**
 * Default Constructor.
 */
RTreeWidget::RTreeWidget(QWidget* parent) :
    QTreeWidget(parent), indexPressed(-1), selectableColumn(0) {
//#ifdef Q_OS_MAC
//    iconOffset = 7;
//#else
//    iconOffset = 0;
//#endif

    if (RSettings::getBoolValue("Keyboard/EnableKeyboardNavigationInLists", false)!=true) {
        installEventFilter(new REventFilter(QEvent::KeyPress, true));
        installEventFilter(new REventFilter(QEvent::KeyRelease, true));
    }
}

/**
 * Destructor
 */
RTreeWidget::~RTreeWidget() {
}

/**
 * \return The active item. Either the selected or current item.
 * This is the item an action is applied for.
 */
QTreeWidgetItem* RTreeWidget::getActiveItem() {
    QList<QTreeWidgetItem*> sel = selectedItems();
    if (!sel.isEmpty()) {
        return sel[0];
    }

    return currentItem();
}

void RTreeWidget::contextMenuEvent(QContextMenuEvent* e) {
    if (e!=NULL) {
        QTreeWidgetItem* item = itemAt(e->pos());
        if (item!=NULL) {
            setCurrentItem(item);
            emit itemClicked(item, 0);

            int index = header()->logicalIndexAt(e->pos());
            emit contextMenuRequested(item, index);
        }
    }
    e->ignore();
}

void RTreeWidget::mousePressEvent(QMouseEvent* e) {
    QTreeWidgetItem* item = itemAt(e->pos());
    int index = header()->logicalIndexAt(e->pos());

    if (item!=NULL) {
        itemPressedData = item->data(0, Qt::UserRole);
    }
    indexPressed = index;

    if (indexPressed==selectableColumn || selectableColumn==-1) {
        //e->ignore();
        QTreeWidget::mousePressEvent(e);
    }
}

void RTreeWidget::mouseReleaseEvent(QMouseEvent* e) {
    QTreeWidgetItem* item = itemAt(e->pos());
    int index = header()->logicalIndexAt(e->pos());

    if (item!=NULL && item->data(0, Qt::UserRole)==itemPressedData && index==indexPressed) {
        emit itemColumnClicked(item, index);
    }

    if (index==selectableColumn || selectableColumn==-1) {
        //e->ignore();
        QTreeWidget::mouseReleaseEvent(e);
    }
}

void RTreeWidget::mouseMoveEvent(QMouseEvent* e) {
    QTreeWidgetItem* item = itemAt(e->pos());
    int index = header()->logicalIndexAt(e->pos());
    if (item!=NULL && item->data(0, Qt::UserRole)!=itemPressedData && index==0) {
        itemPressedData=item->data(0, Qt::UserRole);
        emit itemColumnClicked(item, index);
    }
    if (index==selectableColumn || selectableColumn==-1) {
        //e->ignore();
        QTreeWidget::mouseMoveEvent(e);
    }
}

void RTreeWidget::resizeEvent(QResizeEvent* event) {
    QTreeWidget::resizeEvent(event);
}
