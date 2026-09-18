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
#include "RSettings.h"
#include "RTreeWidget.h"

#include <QContextMenuEvent>
#include <QCoreApplication>
#include <QHeaderView>

namespace {

/**
 * \internal
 * Forwards key events of a list to its parent widget, so that the cursor keys
 * reach the main window (where they move the selected entities) instead of
 * navigating through the items of the list.
 *
 * Whether the keys are forwarded is decided for every single event, not once
 * when the filter is installed: a screen reader is usually only attached after
 * the widgets have been created, and it can be started and stopped at any
 * time (see RSettings::isKeyboardNavigationInListsEnabled).
 */
class RTreeWidgetKeyForwarder : public QObject {
public:
    explicit RTreeWidgetKeyForwarder(QObject* parent) : QObject(parent) {
    }

protected:
    bool eventFilter(QObject* obj, QEvent* e) override {
        if (e==NULL || (e->type()!=QEvent::KeyPress && e->type()!=QEvent::KeyRelease)) {
            return QObject::eventFilter(obj, e);
        }

        if (RSettings::isKeyboardNavigationInListsEnabled()) {
            // the list handles the key itself:
            return false;
        }

        QObject* parent = obj->parent();
        if (parent!=NULL) {
            QCoreApplication::sendEvent(parent, e);
            e->accept();
        }
        return true;
    }
};

} // namespace

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

    // unless keyboard navigation in lists is enabled, keyboard events are
    // forwarded to the parent. the filter is always installed and decides for
    // each event, so that lists become navigable as soon as a screen reader
    // is attached:
    installEventFilter(new RTreeWidgetKeyForwarder(this));
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

void RTreeWidget::scrollToData(const QString& data, Qt::ItemDataRole role){
    // scroll to item with given data:
    QTreeWidgetItemIterator it(this);
    while (*it) {
        if ((*it)->data(0, role).toString()==data) {
            scrollToItem(*it);
            break;
        }
        ++it;
    }
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

#if QT_VERSION >= 0x060000
void RTreeWidget::initViewItemOption(QStyleOptionViewItem *option) const {
    QTreeWidget::initViewItemOption(option);
    // always treat widget as active to keep item selection color and contrast with icons consistent:
    option->state |= QStyle::State_Active;
}
#endif