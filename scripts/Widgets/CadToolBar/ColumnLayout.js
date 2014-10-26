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

ColumnLayout.prototype.minimumSize = function() {
    return this.sizeHint();
};

ColumnLayout.prototype.sizeHint = function() {
    if (isNull(this.sHint)) {
        return new QSize(0,0);
    }

    this.setGeometry();
    return this.sHint;
};

ColumnLayout.prototype.setGeometry = function(rect) {
    var itemList = this.property("ItemList");
    if (typeof(itemList)=="undefined") {
        return;
    }

    var columns = RSettings.getIntValue("CadToolBar/Columns", 2);

    var width = this.parentWidget().width;
    var height = this.parentWidget().height;

    var verticalWhenFloating = RSettings.getBoolValue("CadToolBar/VerticalWhenFloating", false);
    var horizontal = (this.toolBar.orientation===Qt.Horizontal && verticalWhenFloating!==true);
    var w = (horizontal && this.toolBar.movable) ? 2 : 0;
    var h = (!horizontal && this.toolBar.movable) ? 2 : 0;

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

    this.setProperty("sHint", new QSize(w, h));
};

ColumnLayout.prototype.itemAt = function(index) {
    var itemList = this.property("ItemList");
    if (typeof(itemList)=="undefined" || index>=itemList.length) {
        return undefined;
    }
    return itemList[index];
};
