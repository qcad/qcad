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
#include "RListWidget.h"
#include "RMainWindowQt.h"

#include <QContextMenuEvent>

/**
 * Default Constructor.
 */
RListWidget::RListWidget(QWidget* parent) :
    QListWidget(parent), itemPressed(NULL), iconOffset(0) {
//#ifdef Q_OS_MAC
//    iconOffset = 7;
//#else
//    iconOffset = 0;
//#endif

    installEventFilter(new REventFilter(QEvent::KeyPress, true));
    installEventFilter(new REventFilter(QEvent::KeyRelease, true));
}

/**
 * Destructor
 */
RListWidget::~RListWidget() {
}

void RListWidget::contextMenuEvent(QContextMenuEvent* e) {
    if (e != NULL) {
        QListWidgetItem* item = itemAt(e->pos());
        if (item != NULL) {
            setCurrentItem(item);
            emit itemClicked(item);
        }
    }
    e->ignore();
}

void RListWidget::mousePressEvent(QMouseEvent* e) {
    if (e->x()-iconOffset < iconSize().width()) {
        itemPressed = itemAt(e->pos());
    } else {
        e->ignore();
        QListWidget::mousePressEvent(e);
    }
}

void RListWidget::mouseReleaseEvent(QMouseEvent* e) {
    if (e->x()-iconOffset < iconSize().width()) {
        QListWidgetItem* item = itemAt(e->pos());
        if (item != NULL && item == itemPressed) {
            emit iconClicked(e->x()-iconOffset, item);
        }
    } else {
        e->ignore();
        QListWidget::mouseReleaseEvent(e);
    }
}

void RListWidget::mouseMoveEvent(QMouseEvent* e) {
    if (e->x()-iconOffset < iconSize().width()) {
    } else {
        e->ignore();
        QListWidget::mouseMoveEvent(e);
    }
}
