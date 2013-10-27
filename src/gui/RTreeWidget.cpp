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
#include "RTreeWidget.h"
#include "RDebug.h"

#include <QContextMenuEvent>

/**
 * Default Constructor.
 */
RTreeWidget::RTreeWidget(QWidget* parent) :
    QTreeWidget(parent) {
    itemPressed = NULL;
#ifdef Q_OS_MAC
    iconOffset = 7;
#else
    iconOffset = 0;
#endif
}

/**
 * Destructor
 */
RTreeWidget::~RTreeWidget() {
}

void RTreeWidget::contextMenuEvent(QContextMenuEvent* e) {
    if (e != NULL) {
        QTreeWidgetItem* item = itemAt(e->pos());
        if (item != NULL) {
            setCurrentItem(item);
            emit itemClicked(item, 0);
        }
    }
    e->ignore();
}

void RTreeWidget::mousePressEvent(QMouseEvent* e) {
    if (e->x()-iconOffset < iconSize().width()) {
        itemPressed = itemAt(e->pos());
    } else {
        e->ignore();
        QTreeWidget::mousePressEvent(e);
    }
}

void RTreeWidget::mouseReleaseEvent(QMouseEvent* e) {
    if (e->x()-iconOffset < iconSize().width()) {
        QTreeWidgetItem* item = itemAt(e->pos());
        if (item != NULL && item == itemPressed) {
            emit iconClicked(e->x()-iconOffset, item);
        }
    } else {
        e->ignore();
        QTreeWidget::mouseReleaseEvent(e);
    }
}

void RTreeWidget::mouseMoveEvent(QMouseEvent* e) {
    if (e->x()-iconOffset < iconSize().width()) {
    } else {
        e->ignore();
        QTreeWidget::mouseMoveEvent(e);
    }
}
