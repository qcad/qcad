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

    //setProperty("toolBar", toolBar);
    //setProperty("sHint", QSize());
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
    //qDebug("ColumnLayout.prototype.addItem...");

    //var itemList = this.property("ItemList");

//    if (typeof(itemList)=="undefined" || itemList.length===0) {
//        qDebug("item: " + item);
//        qDebug("item array: " + new Array(item));
//        this.setProperty("ItemList", new Array(item));
//        qDebug("ColumnLayout.prototype.addItem: DONE");
//        return;
//    }

    QObject* par = parent();
    if (par==NULL) {
        return;
    }

//    QObject* w = item->widget();
//    if (w==NULL) {
//        qWarning() << "item not a widget";
//        return;
//    }

    int so = getAccumulatedSortOrder(item->widget(), par->objectName());
    //qDebug() << "so:" << so;

    if (so!=0) {
        for (int i=0; i<itemList.length(); ++i) {
//            if (typeof(itemList[i]->property("SortOrder"))!="number") {
//                continue;
//            }

            QObject* other = itemList[i].first->widget();
            int so2 = getAccumulatedSortOrder(other, par->objectName());
            //qDebug() << "so2:" << so2;
//            if (isNull(so2)) {
//                continue;
//            }
            if (so2>so) {
                //itemList.splice(i, 0, item);
                itemList.insert(i, QPair<QLayoutItem*, int>(item, so));
                //this.setProperty("ItemList", itemList);
                return;
            }
        }
    }

    itemList.append(QPair<QLayoutItem*, int>(item, so));
    //this.setProperty("ItemList", itemList);

    ///qDebug("ColumnLayout.prototype.addItem: DONE");

    //qDebug() << "itemList:" << itemList;
};

//void RColumnLayout::addSeparator(int sortOrder, int groupSortOrder) {
//    qDebug() << "RColumnLayout::addSeparator";
//    // TODO
//}

int RColumnLayout::getAccumulatedSortOrder(QObject* item, const QString& objectName) {
    return getSortOrder(item, objectName) + getGroupSortOrder(item, objectName)*100000;
};

int RColumnLayout::getSortOrder(QObject* item, const QString& objectName) {
    if (item==NULL) {
        return 0;
    }

    QString n = "SortOrderOverride" + objectName;

    QVariant v = item->property((const char*)n.toLocal8Bit());
    if (v.canConvert<int>()) {
        return v.toInt();
    }

    QVariant v2 = item->property("SortOrder");
    if (v2.canConvert<int>()) {
        return v2.toInt();
    }

    return 0;
};

int RColumnLayout::getGroupSortOrder(QObject* item, const QString& objectName) {
    if (item==NULL) {
        return 0;
    }

    QString n = "GroupSortOrderOverride" + objectName;

    QVariant v = item->property((const char*)n.toLocal8Bit());
    if (v.canConvert<int>()) {
        return v.toInt();
    }

    QVariant v2 = item->property("GroupSortOrder");
    if (v2.canConvert<int>()) {
        return v2.toInt();
    }

    return 0;
};

QSize RColumnLayout::minimumSize() const {
    //qDebug("ColumnLayout.prototype.minimumSize");
    return sizeHint();
};

QSize RColumnLayout::sizeHint() const {
    //qDebug("ColumnLayout.prototype.sizeHint");
    if (!sHint.isValid()) {
        //qDebug("ColumnLayout.prototype.sizeHint: DONE");
        return QSize(0,0);
    }

    //QRect r;
    //setGeometry(r);

    //qDebug("ColumnLayout.prototype.sizeHint: DONE");
    return sHint;
};

void RColumnLayout::setGeometry(const QRect& rect) {
    qDebug("ColumnLayout.prototype.setGeometry...");
//    var dbg = false;
//    if (this.parent().objectName==="MainToolsPanel") {
//        dbg = true;
//    }

//    var itemList = this.property("ItemList");
//    if (typeof(itemList)=="undefined") {
//        return;
//    }

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

    //if (dbg) qDebug("===============");
    //if (dbg) qDebug(itemList);

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
//        QAction* a = qobject_cast<QAction*>(itemList[i].first->widget());
//        if (a!=NULL && a->isSeparator()) {
//            if (dbg) qDebug("Separator");
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
            //continue;
        }

//        if (dbg) qDebug("Button");
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
        //qWarning() << "RColumnLayout::itemAt: index out of range: " << index;
        //qWarning() << "RColumnLayout::itemAt: itemList.length:" << itemList.length();
        return NULL;
    }
    //qDebug("ColumnLayout.prototype.itemAt...");
    //var itemList = this.property("ItemList");
//    if (typeof(itemList)=="undefined" || index>=itemList.length) {
//        return undefined;
//    }
    //qDebug("ColumnLayout.prototype.itemAt: " + itemList[index]);
    //qDebug("ColumnLayout.prototype.itemAt: DONE");
    return itemList[index].first;
};

