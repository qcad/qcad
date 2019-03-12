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

include("scripts/Modify/Modify.js");

/**
 * \defgroup ecma_draworder Draw order Tools
 * \ingroup ecma_modify
 *
 * \brief This module contains ECMAScript implementations of drawing order tools.
 */

/**
 * \class DrawOrder
 * \brief Base class for all draw order tools.
 * \ingroup ecma_draworder
 */
function DrawOrder(guiAction) {
    Modify.call(this, guiAction);
}

DrawOrder.prototype = new Modify();
DrawOrder.includeBasePath = includeBasePath;

DrawOrder.getMenu = function() {
    var menu = EAction.getSubMenu(
        Modify.getMenu(),
        13600, 100,
        DrawOrder.getTitle(),
        "ModifyDrawOrderMenu"
        //DrawOrder.includeBasePath + "/DrawOrder.svg"
    );
    menu.setProperty("scriptFile", DrawOrder.includeBasePath + "/DrawOrder.js");
    return menu;
};

/*
DrawOrder.getToolBar = function() {
    var tb = EAction.getToolBar(DrawOrder.getTitle(), "DrawOrderToolBar");
    tb.visible = false;
    return tb;
};
*/

/*
DrawOrder.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "DrawOrderToolsPanelAction";
    if (!isNull(mtb) && isNull(mtb.findChild(actionName))) {
        var action = new RGuiAction(qsTr("DrawOrder Tools"), mtb);
        action.setScriptFile(DrawOrder.includeBasePath + "/DrawOrder.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(DrawOrder.includeBasePath + "/DrawOrder.svg");
        //action.setStatusTip(qsTr("Show projection tools"));
        action.setDefaultShortcut(new QKeySequence("w,j"));
        action.setNoState();
        action.setDefaultCommands(["projectmenu"]);
        action.setGroupSortOrder(50);
        action.setSortOrder(100);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(DrawOrder.getTitle(), "DrawOrderToolsPanel", true);
    return tb;
};
*/

/*
DrawOrder.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(DrawOrder.getTitle(), "DrawOrderMatrixPanel", 3500);
};
*/

DrawOrder.getTitle = function() {
    return qsTr("&Draw Order");
};

DrawOrder.prototype.getTitle = function() {
    return DrawOrder.getTitle();
};

DrawOrder.init = function() {
    DrawOrder.getMenu();

    // make sure there's an action:
    var appWin = EAction.getMainWindow();
    var action = new RGuiAction(qsTr("Draw Order"), appWin);
    action.setScriptFile(DrawOrder.includeBasePath + "/DrawOrder.js");
    action.setWidgetNames([]);

    //DrawOrder.getToolBar();
    //DrawOrder.getCadToolBarPanel();
    //DrawOrder.getToolMatrixPanel();
};
