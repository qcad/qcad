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

function ColumnLayout(parent, toolBar, buttonSize) {
    QLayout.call(this, parent);

    var columns = RSettings.getIntValue("CadToolBar/Columns", 2);
    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);

    this.setContentsMargins(2,2,2,2);
    this.setProperty("toolBar", toolBar);
    this.setProperty("sHint", new QSize());
}

ColumnLayout.prototype = new QLayout();

/**
 * \param item A widget (e.g. QToolButton) with property "SortOrder" set to the
 *    desired sort order. Or a separator action, also with property "SortOrder"
 *    set.
 */
ColumnLayout.prototype.addItem = function(item) {
    var itemList = this.property("ItemList");

    if (typeof(itemList)=="undefined" || itemList.length==0) {
        this.setProperty("ItemList", new Array(item));
        return;
    }

    var so = ColumnLayout.getSortOrder(item);

    if (!isNull(so)) {
        for (var i=0; i<itemList.length; ++i) {
            if (typeof(itemList[i].property("SortOrder"))!="number") {
                continue;
            }

            var so2 = ColumnLayout.getSortOrder(itemList[i]);
            if (isNull(so2)) {
                continue;
            }
            if (so2>so) {
                itemList.splice(i, 0, item);
                this.setProperty("ItemList", itemList);
                return;
            }
        }
    }

    itemList.push(item);
    this.setProperty("ItemList", itemList);
};

ColumnLayout.getSortOrder = function(item) {
    if (typeof(item.property("SortOrderCadToolBar"))=="number") {
        return item.property("SortOrderCadToolBar");
    }
    if (typeof(item.property("SortOrder"))=="number") {
        return item.property("SortOrder");
    }
    return undefined;
};

ColumnLayout.prototype.sizeHint = function() {
    if (isNull(this.sHint)) {
        return new QSize(0,0);
    }

    this.setGeometry();
    qDebug("this.sHint", this.sHint);
    return this.sHint;

    /*
//    return new QSize(100,100);
//    qDebug("size hint: ", CadToolBar.getSizeHint(this.toolBar, this.sHint));
//    return CadToolBar.getSizeHint(this.toolBar, this.sHint);
    var columns = RSettings.getIntValue("CadToolBar/Columns", 2);
    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);
//    if (this.toolBar.orientation===Qt.Horizontal && !this.toolBar.floating) {
    if (this.toolBar.orientation===Qt.Horizontal) {
        return new QSize(this.toolBar.sHint.width(), columns * iconSize * 1.25);
//        return new QSize(100, 10);
//        this.sizeHintX = 300;
//        this.sizeHintY = columns * iconSize * 1.25;
    }
    else {
        return new QSize(columns * iconSize * 1.25, this.toolBar.sHint.height());
//        this.sizeHintX = columns * iconSize * 1.25;
//        this.sizeHintY = this.toolBar.floating ? 500 : 300;
    }
//    return new QSize(this.sizeHintX, this.sizeHintY);
    */
};

ColumnLayout.prototype.setGeometry = function(rect) {
    qDebug("ColumnLayout.prototype.setGeometry");
    qDebug("orientation: ", this.toolBar.orientation);
    //qDebug("movable: ", this.toolBar.movable);
    qDebug("floating: ", this.toolBar.floating);
    qDebug("is window: ", this.toolBar.isWindow());

    var itemList = this.property("ItemList");
    if (typeof(itemList)=="undefined") {
        return;
    }

    var columns = RSettings.getIntValue("CadToolBar/Columns", 2);

    var width = this.parentWidget().width;
    var height = this.parentWidget().height;

    //var horizontal = width>height;
//    var horizontal = (this.toolBar.orientation===Qt.Horizontal && !this.toolBar.floating);
    //var horizontal = this.toolBar.orientation===Qt.Horizontal;
    var horizontal = (this.toolBar.orientation===Qt.Horizontal && this.toolBar.verticalWhenFloating!==true);
    //qDebug("horizontal:", horizontal);
    var w = (horizontal && this.toolBar.movable) ? 2 : 0;
    var h = (!horizontal && this.toolBar.movable) ? 2 : 0;
    //qDebug("this.toolBar.movable", this.toolBar.movable);
    //qDebug("this.toolBar.floating", this.toolBar.floating);

//    if (horizontal) {
//        this.parentWidget().minimumWidth=x+this.buttonSizeX;
//        this.parentWidget().minimumHeight=2*this.buttonSizeY;
//    }
//    else {
//        this.parentWidget().minimumWidth=2*this.buttonSizeX;
//        this.parentWidget().minimumHeight=y+this.buttonSizeY;
//    }

    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);
    var buttonSize = iconSize * 1.25;
    var c=0;

    for (var i=0; i<itemList.length; ++i) {

        if (isOfType(itemList[i], QToolButton)) {
            itemList[i].iconSize = new QSize(iconSize, iconSize);
        }

        // back button at the top or left:
        if (itemList[i].objectName === "BackButton") {
            if (horizontal) {
                itemList[i].setGeometry(0,0, buttonSize*0.75,height);
                w+=buttonSize*0.75 + 8;
                h=0;
            }
            else {
                itemList[i].setGeometry(0,0, width,buttonSize*0.75);
                h+=buttonSize*0.75 + 8;
                w=0;
            }
            continue;
        }

        // separator:
        if (isFunction(itemList[i].isSeparator) && itemList[i].isSeparator()) {
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
            continue;
        }

        itemList[i].setGeometry(w,h, buttonSize,buttonSize);

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
    }

    if (horizontal) {
        h+=buttonSize;
    }
    else {
        w+=buttonSize;
    }

    //qDebug("size: ", w, h);
    this.setProperty("sHint", new QSize(w, h));
    //this.sizeHintX = x;
    //this.sizeHintY = y;
//    this.setProperty("sizeHintX", x);
//    this.setProperty("sizeHintY", y);

    //this.toolBar.updateGeometry();
};

ColumnLayout.prototype.itemAt = function(index) {
    var itemList = this.property("ItemList");
    if (typeof(itemList)=="undefined" || index>=itemList.length) {
        return undefined;
    }
    return itemList[index];
};
