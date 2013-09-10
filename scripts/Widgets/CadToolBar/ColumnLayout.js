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

function ColumnLayout(parent, buttonSize) {
    QLayout.call(this, parent);
    this.setContentsMargins(2,2,2,2);
    //this.setButtonSize(buttonSize);
    //this.sizeHintX = 0;
    //this.sizeHintY = 0;
}

ColumnLayout.prototype = new QLayout();

//ColumnLayout.prototype.setButtonSize = function(s) {
//    this.setProperty("buttonSizeX", s);
//    this.setProperty("buttonSizeY", s);
//}

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

    //var itemList = this.itemList;
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
    //return new QSize(this.sizeHintX, this.sizeHintY);
    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);
    var buttonSize = iconSize * 1.25;
    return new QSize(buttonSize*2, buttonSize*2);
};

ColumnLayout.prototype.setGeometry = function(rect) {
    var itemList = this.property("ItemList");
    //QLayout.prototype.setGeometry.call(this, rect);
    if (typeof(itemList)=="undefined") {
        return;
    }

    var width = this.parentWidget().width;
    var height = this.parentWidget().height;

    var horizontal = width>height;
    var x=0;
    var y=1;

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

    for (var i=0; i<itemList.length; ++i) {

        if (isOfType(itemList[i], QToolButton)) {
            itemList[i].iconSize = new QSize(iconSize, iconSize);
        }

        // back button at the top or left:
        if (itemList[i].objectName == "BackButton") {
            if (horizontal) {
                itemList[i].setGeometry(0,0, buttonSize*0.75,height);
                x+=buttonSize*0.75 + 8;
                y=0;
            }
            else {
                itemList[i].setGeometry(0,0, width,buttonSize*0.75);
                y+=buttonSize*0.75 + 8;
                x=0;
            }
            continue;
        }

        // separator:
        if (itemList[i].isSeparator!=undefined && itemList[i].isSeparator()) {
            if (horizontal) {
                if (y==0) {
                    x+=8;
                }
                else {
                    x+=buttonSize+8;
                    y = 0;
                }
            }
            else {
                if (x==0) {
                    y+=8;
                }
                else {
                    y+=buttonSize+8;
                    x = 0;
                }
            }
            continue;
        }

        itemList[i].setGeometry(x,y, buttonSize,buttonSize);

        if (horizontal) {
            y+=buttonSize;
            if (y+buttonSize>height) {
                y = 0;
                x+=buttonSize;
            }
        }
        else {
            x+=buttonSize;
            if (x+buttonSize>width) {
                x = 0;
                y+=buttonSize;
            }
        }
    }

//    this.sizeHintX = x;
//    this.sizeHintY = y;
//    this.setProperty("sizeHintX", x);
//    this.setProperty("sizeHintY", y);
};

ColumnLayout.prototype.itemAt = function(index) {
    var itemList = this.property("ItemList");
    if (typeof(itemList)=="undefined" || index>=itemList.length) {
        return undefined;
    }
    return itemList[index];
};
