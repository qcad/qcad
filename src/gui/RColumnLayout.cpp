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
#include "RColumnLayout.h"
#include "RSettings.h"

#include <QDebug>
#include <QAction>
#include <QToolButton>
#include <QLayoutItem>

RColumnLayout::RColumnLayout(QWidget* parent, QToolBar* toolBar, int buttonSize)
    : QLayout(parent),
    toolBar(toolBar),
    sHintColumns(0),
    sHintWidth(0),
    sHintHeight(0),
    sHintVerticalWhenFloating(false),
    sHintHorizontal(0),
    sHintIconSize(0) {

    setContentsMargins(2,2,2,2);
}

//void RColumnLayout::removeAction(QAction* a) {
    /*
    //qDebug("RColumnLayout::removeAction...");
    //var itemList = this.property("ItemList");

    int index = -1;

    for (int i=0; i<itemList.length(); ++i) {
        QToolButton* tb = qobject_cast<QToolButton*>(itemList[i].second);
        if (tb==NULL) {
            continue;
        }

        if (tb->defaultAction()==(QAction*)a) {
            index = i;
        }
    }

    if (index!=-1) {
        //itemList.splice(index, 1);
        itemList.removeAt(index);
    }

    //this.setProperty("ItemList", itemList);
    //qDebug("ColumnLayout.prototype.removeAction: DONE");
    */
//};

/**
 * \param item A widget (e.g. QToolButton) with property "SortOrder" set to the
 *    desired sort order. Or a separator action, also with property "SortOrder"
 *    set.
 */
void RColumnLayout::addItem(QLayoutItem* item) {
    QObject* par = parent();
    if (par==NULL) {
        return;
    }

    int so = getAccumulatedSortOrder(item->widget(), par->objectName());

    if (so!=0) {
        for (int i=0; i<itemList.length(); ++i) {
            QObject* other = itemList[i].first->widget();
            unsigned long int so2 = getAccumulatedSortOrder(other, par->objectName());
            if (so2>so) {
                itemList.insert(i, QPair<QLayoutItem*, unsigned long int>(item, so));
                return;
            }
        }
    }

    itemList.append(QPair<QLayoutItem*, unsigned long int>(item, so));
};

unsigned long int RColumnLayout::getAccumulatedSortOrder(QObject* item, const QString& objectName) {
    return getSortOrder(item, objectName) + getGroupSortOrder(item, objectName)*100000;
};

unsigned int RColumnLayout::getSortOrder(QObject* item, const QString& objectName) {
    if (item==NULL) {
        return 0;
    }

    QString n = "SortOrderOverride" + objectName;

    QVariant v = item->property((const char*)n.toLocal8Bit());
    if (v.canConvert<int>()) {
        return v.toUInt();
    }

    QVariant v2 = item->property("SortOrder");
    if (v2.canConvert<int>()) {
        return v2.toUInt();
    }

    return 0;
};

unsigned int RColumnLayout::getGroupSortOrder(QObject* item, const QString& objectName) {
    if (item==NULL) {
        return 0;
    }

    QString n = "GroupSortOrderOverride" + objectName;

    QVariant v = item->property((const char*)n.toLocal8Bit());
    if (v.canConvert<int>()) {
        return v.toUInt();
    }

    QVariant v2 = item->property("GroupSortOrder");
    if (v2.canConvert<int>()) {
        return v2.toUInt();
    }

    return 0;
};

QSize RColumnLayout::minimumSize() const {
    return sizeHint();
};

QSize RColumnLayout::sizeHint() const {
    if (!sHint.isValid()) {
        return QSize(0,0);
    }
    setGeometry();
    return sHint;
};

void RColumnLayout::setGeometry(const QRect& rect) {
    setGeometry();
}

void RColumnLayout::setGeometry() const {
    if (parentWidget()==NULL || toolBar==NULL) {
        return;
    }

    int columns = RSettings::getIntValue("CadToolBar/Columns", 2);

    int width = parentWidget()->width();
    int height = parentWidget()->height();

    bool verticalWhenFloating = RSettings::getBoolValue("CadToolBar/VerticalWhenFloating", false);
    bool horizontal = toolBar->orientation()==Qt::Horizontal;
    if (toolBar->isFloating() && verticalWhenFloating) {
        horizontal = false;
    }
    int iconSize = RSettings::getIntValue("CadToolBar/IconSize", 32);

    if (sHintColumns==columns &&
        sHintWidth==width &&
        sHintHeight==height &&
        sHintVerticalWhenFloating==verticalWhenFloating &&
        sHintHorizontal==horizontal &&
        sHintIconSize==iconSize) {

        // nothing has changed:
        return;
    }

    int w = (horizontal && toolBar->isMovable()) ? 2 : 0;
    int h = (!horizontal && toolBar->isMovable()) ? 2 : 0;

    int buttonSize = (int)(iconSize * 1.25);
    int c=0;
    int groupOrder=-1;

    std::sort(itemList.begin(), itemList.end(), itemLessThan);

    int previousSo = -1;
    for (int i=0; i<itemList.length(); ++i) {
        QWidget* widget = itemList[i].first->widget();

        if (widget==NULL) {
            continue;
        }

        int so = itemList[i].second;

        QToolButton* tb = qobject_cast<QToolButton*>(widget);
        if (tb!=NULL) {
            tb->setIconSize(QSize(iconSize, iconSize));
            if (tb->defaultAction()!=NULL && tb->defaultAction()->isVisible()==false) {
                tb->setVisible(false);
                continue;
            }
        }

        // back button at the top or left:
        if (widget->objectName() == "BackButton") {
            QToolButton* tb = qobject_cast<QToolButton*>(widget);
            if (horizontal) {
                tb->setGeometry(0,0, buttonSize*0.75,height);
                w+=buttonSize*0.75 + 8;
                h=0;
            }
            else {
                tb->setGeometry(0,0, width,buttonSize*0.75);
                h+=buttonSize*0.75 + 8;
                w=0;
            }
//            if (dbg) qDebug("BackButton");
            continue;
        }

        // separator:
        if (previousSo!=-1 && so-previousSo>=100000) {
            if (horizontal) {
                if (h==0) {
                    w+=8;
                }
                else {
                    w+=buttonSize+8;
                    h = 0;
                    c = 0;
                }
            }
            else {
                if (w==0) {
                    h+=8;
                }
                else {
                    h+=buttonSize+8;
                    w = 0;
                    c = 0;
                }
            }
        }

        QWidget* wd = qobject_cast<QWidget*>(itemList[i].first->widget());
        wd->setGeometry(w,h, buttonSize,buttonSize);

        if (horizontal) {
            h+=buttonSize;
            c++;
            //if (y+buttonSize>height) {
            if (c>=columns) {
                h = 0;
                c = 0;
                w+=buttonSize;
            }
        }
        else {
            w+=buttonSize;
            c++;
            //if (x+buttonSize>width) {
            if (c>=columns) {
                w = 0;
                c = 0;
                h+=buttonSize;
            }
        }

        previousSo = so;
    }

    if (horizontal) {
        h+=buttonSize;
    }
    else {
        w+=buttonSize;
    }

    if (horizontal) {
        sHint = QSize(w, buttonSize*columns);
    }
    else {
        sHint = QSize(buttonSize*columns, h);
    }

    // store settings used for calculation, so we don't have to calculate
    // size again if not necessary:
    sHintColumns = columns;
    sHintWidth = width;
    sHintHeight = height;
    sHintVerticalWhenFloating = verticalWhenFloating;
    sHintHorizontal = horizontal;
    sHintIconSize = iconSize;

    //qDebug("ColumnLayout.prototype.setGeometry: DONE");
};

int RColumnLayout::count() const {
    qWarning() << "RColumnLayout::count: not implemented";
    return 0;
}

QLayoutItem* RColumnLayout::takeAt(int index) {
    qWarning() << "RColumnLayout::takeAt: not implemented";
    return NULL;
}

QLayoutItem* RColumnLayout::itemAt(int index) const {
    if (index>=itemList.length() || index<0) {
        return NULL;
    }
    return itemList[index].first;
};

