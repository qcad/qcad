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

function ColumnLayout(parent, toolBar, buttonSize) {
    QLayout.call(this, parent);

    this.setContentsMargins(2,2,2,2);
    this.setProperty("toolBar", toolBar);
    this.setProperty("sHint", new QSize());
}

ColumnLayout.prototype = new QLayout();

ColumnLayout.prototype.removeAction = function(a) {
    var itemList = this.property("ItemList");

    if (isNull(itemList)) {
        return;
    }

    var index = -1;

    for (var i=0; i<itemList.length; ++i) {
        if (!isOfType(itemList[i], QToolButton)) {
            continue;
        }

        if (itemList[i].defaultAction()===a) {
            index = i;
        }
    }

    if (index!==-1) {
        itemList.splice(index, 1);
    }

    this.setProperty("ItemList", itemList);
};

/**
 * \param item A widget (e.g. QToolButton) with property "SortOrder" set to the
 *    desired sort order. Or a separator action, also with property "SortOrder"
 *    set.
 */
ColumnLayout.prototype.addItem = function(item) {
    var itemList = this.property("ItemList");

    if (typeof(itemList)=="undefined" || itemList.length===0) {
        this.setProperty("ItemList", new Array(item));
        return;
    }

    var so = ColumnLayout.getAccumulatedSortOrder(item, this.parent().objectName);

    if (so!==0) {
        for (var i=0; i<itemList.length; ++i) {
            if (typeof(itemList[i].property("SortOrder"))!="number") {
                continue;
            }

            var so2 = ColumnLayout.getAccumulatedSortOrder(itemList[i], this.parent().objectName);
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

ColumnLayout.getAccumulatedSortOrder = function(item, objectName) {
    return ColumnLayout.getSortOrder(item, objectName) + ColumnLayout.getGroupSortOrder(item, objectName)*100000;
};

ColumnLayout.getSortOrder = function(item, objectName) {
    var n = "SortOrderOverride" + objectName;
    if (typeof(item.property(n))=="number") {
        return item.property(n);
    }
    if (typeof(item.property("SortOrder"))=="number") {
        return item.property("SortOrder");
    }
    return 0;
};

ColumnLayout.getGroupSortOrder = function(item, objectName) {
    var n = "GroupSortOrderOverride" + objectName;
    if (typeof(item.property(n))=="number") {
        return item.property(n);
    }
    if (typeof(item.property("GroupSortOrder"))=="number") {
        return item.property("GroupSortOrder");
    }
    return 0;
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
    var dbg = false;
    if (this.parent().objectName==="MainToolsPanel") {
        dbg = true;
    }

    var itemList = this.property("ItemList");
    if (typeof(itemList)=="undefined") {
        return;
    }

    var columns = RSettings.getIntValue("CadToolBar/Columns", 2);

    var width = this.parentWidget().width;
    var height = this.parentWidget().height;

    var verticalWhenFloating = RSettings.getBoolValue("CadToolBar/VerticalWhenFloating", false);
    var horizontal = this.toolBar.orientation===Qt.Horizontal;
    if (this.toolBar.floating && verticalWhenFloating) {
        horizontal = false;
    }
    var iconSize = RSettings.getIntValue("CadToolBar/IconSize", 32);

    if (this.property("sHintColumns")===columns &&
        this.property("sHintWidth")===width &&
        this.property("sHintHeight")===height &&
        this.property("sHintVerticalWhenFloating")===verticalWhenFloating &&
        this.property("sHintHorizontal")===horizontal &&
        this.property("sHintIconSize")===iconSize) {

        return this.sHint;
    }

    var w = (horizontal && this.toolBar.movable) ? 2 : 0;
    var h = (!horizontal && this.toolBar.movable) ? 2 : 0;

    var buttonSize = iconSize * 1.25;
    var c=0;
    var groupOrder=-1;

    //if (dbg) qDebug("===============");
    //if (dbg) qDebug(itemList);

    for (var i=0; i<itemList.length; ++i) {
        if (isOfType(itemList[i], QToolButton)) {
            itemList[i].iconSize = new QSize(iconSize, iconSize);
            if (itemList[i].defaultAction().visible===false) {
                itemList[i].visible = false;
                continue;
            }
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
//            if (dbg) qDebug("BackButton");
            continue;
        }

        // separator:
        if (isFunction(itemList[i].isSeparator) && itemList[i].isSeparator()) {
//            if (dbg) qDebug("Separator");
            if (horizontal) {
                if (h===0) {
                    w+=8;
                }
                else {
                    w+=buttonSize+8;
                    h = 0;
                    c = 0;
                }
            }
            else {
                if (w===0) {
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

//        if (dbg) qDebug("Button");
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

    if (horizontal) {
        this.setProperty("sHint", new QSize(w, buttonSize*columns));
    }
    else {
        this.setProperty("sHint", new QSize(buttonSize*columns, h));
    }

    // store settings used for calculation, so we don't have to calcuate
    // size again if not necessary:
    this.setProperty("sHintColumns", columns);
    this.setProperty("sHintWidth", width);
    this.setProperty("sHintHeight", height);
    this.setProperty("sHintVerticalWhenFloating", verticalWhenFloating);
    this.setProperty("sHintHorizontal", horizontal);
    this.setProperty("sHintIconSize", iconSize);
};

ColumnLayout.prototype.itemAt = function(index) {
    var itemList = this.property("ItemList");
    if (typeof(itemList)=="undefined" || index>=itemList.length) {
        return undefined;
    }
    return itemList[index];
};
