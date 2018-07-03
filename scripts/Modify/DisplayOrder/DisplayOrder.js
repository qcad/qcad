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
 * \defgroup ecma_projection Display order Tools
 * \ingroup ecma_modify
 *
 * \brief This module contains ECMAScript implementations of drawing order tools.
 */

/**
 * \class DisplayOrder
 * \brief Base class for all display order tools.
 * \ingroup ecma_projection
 */
function DisplayOrder(guiAction) {
    Modify.call(this, guiAction);
}

DisplayOrder.prototype = new Modify();
DisplayOrder.includeBasePath = includeBasePath;

DisplayOrder.getMenu = function() {
    var menu = EAction.getSubMenu(
        Modify.getMenu(),
        13600, 100,
        DisplayOrder.getTitle(),
        "ModifyDisplayOrderMenu"
        //DisplayOrder.includeBasePath + "/DisplayOrder.svg"
    );
    menu.setProperty("scriptFile", DisplayOrder.includeBasePath + "/DisplayOrder.js");
    return menu;
};

/*
DisplayOrder.getToolBar = function() {
    var tb = EAction.getToolBar(DisplayOrder.getTitle(), "DisplayOrderToolBar");
    tb.visible = false;
    return tb;
};
*/

/*
DisplayOrder.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "DisplayOrderToolsPanelAction";
    if (!isNull(mtb) && isNull(mtb.findChild(actionName))) {
        var action = new RGuiAction(qsTr("DisplayOrder Tools"), mtb);
        action.setScriptFile(DisplayOrder.includeBasePath + "/DisplayOrder.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(DisplayOrder.includeBasePath + "/DisplayOrder.svg");
        action.setStatusTip(qsTr("Show projection tools"));
        action.setDefaultShortcut(new QKeySequence("w,j"));
        action.setNoState();
        action.setDefaultCommands(["projectmenu"]);
        action.setGroupSortOrder(50);
        action.setSortOrder(100);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(DisplayOrder.getTitle(), "DisplayOrderToolsPanel", true);
    return tb;
};
*/

/*
DisplayOrder.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(DisplayOrder.getTitle(), "DisplayOrderMatrixPanel", 3500);
};
*/

DisplayOrder.getTitle = function() {
    return qsTr("&Display Order");
};

DisplayOrder.prototype.getTitle = function() {
    return DisplayOrder.getTitle();
};

DisplayOrder.init = function() {
    DisplayOrder.getMenu();
    //DisplayOrder.getToolBar();
    //DisplayOrder.getCadToolBarPanel();
    //DisplayOrder.getToolMatrixPanel();
};
