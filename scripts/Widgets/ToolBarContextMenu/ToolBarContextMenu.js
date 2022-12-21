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

function ToolBarContextMenu() {
}

ToolBarContextMenu.getSubMenu = function(menu, categories) {
    if (isNull(categories) || categories.length===0) {
        return menu;
    }

    var m;

    var actions = menu.actions();
    for (var k=0; k<actions.length; k++) {
        var action = actions[k];
        m = action.menu();
        if (!isNull(m) && m.title===categories[0]) {
            categories.shift();
            return ToolBarContextMenu.getSubMenu(m, categories);
        }
    }

    // menu not found: create it:
    m = menu;
    for (var i=0; i<categories.length; i++) {
        m = m.addMenu(categories[i]);
    }
    return m;
};

ToolBarContextMenu.sort = function(a,b) {
    var catA = a.property("Category");
    var catB = b.property("Category");

    if (isNull(catA) && !isNull(catB)) {
        return -1;
    }
    if (!isNull(catA) && isNull(catB)) {
        return 1;
    }
    if (!isNull(catA) && !isNull(catB)) {
        return catA.toString().localeCompare(catB.toString());
    }

    // no category:
    var titleA = a.windowTitle.replace("&", "");
    var titleB = b.windowTitle.replace("&", "");

    return titleA.localeCompare(titleB);
};

ToolBarContextMenu.createMenu = function(menu) {
    var appWin = RMainWindowQt.getMainWindow();

    var tbs = appWin.getToolBars();
    var dws = appWin.getDockWidgets();
    var i, a, m, cat;

    dws.sort(ToolBarContextMenu.sort);
    tbs.sort(ToolBarContextMenu.sort);

    for (i = 0; i<dws.length; i++) {
        var dw = dws[i];
        cat = dw.property("Category");
        if (isNull(cat)) {
            cat = [];
        }
        cat.unshift(qsTr("Widgets"));
        m = ToolBarContextMenu.getSubMenu(menu, cat);
        if (!isNull(m)) {
            a = dw.toggleViewAction();
            RGuiAction.addToWidget(a, m);
        }
    }

    for (i = 0; i<tbs.length; i++) {
        var tb = tbs[i];
        cat = tb.property("Category");
        if (isNull(cat)) {
            cat = [];
        }
        cat.unshift(qsTr("Toolbars"));
        m = ToolBarContextMenu.getSubMenu(menu, cat);
        if (!isNull(m)) {
            a = tb.toggleViewAction();
            RGuiAction.addToWidget(a, m);
        }
    }
};

ToolBarContextMenu.init = function(basePath) {
    var appWin = RMainWindowQt.getMainWindow();
    appWin.toolBarContextMenu.connect(ToolBarContextMenu.createMenu);
};
