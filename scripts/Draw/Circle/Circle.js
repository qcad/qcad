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

/**
 * \defgroup ecma_draw_circle Circle Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various circle drawing tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Circle
 * \brief Base class for all circle drawing tools.
 * \ingroup ecma_draw_circle
 */
function Circle(guiAction) {
    Draw.call(this, guiAction);
}

Circle.prototype = new Draw();
Circle.includeBasePath = includeBasePath;

Circle.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="CircleToolsPanelAction") {
        EAction.showCadToolBarPanel("CircleToolsPanel");
        this.terminate();
    }
};

Circle.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        20, 400,
        Circle.getTitle(),
        "DrawCircleMenu",
        Circle.includeBasePath + "/Circle.svg"
    );
    menu.setProperty("scriptFile", Circle.includeBasePath + "/Circle.js");
    return menu;
};

Circle.getToolBar = function() {
    var tb = EAction.getToolBar(Circle.getTitle(), "CircleToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Circle.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "CircleToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Circle Tools"), mtb);
        action.setScriptFile(Circle.includeBasePath + "/Circle.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Circle.includeBasePath + "/Circle.svg");
        //action.setStatusTip(qsTr("Show circle tools"));
        action.setDefaultShortcut(new QKeySequence("w,c"));
        action.setNoState();
        action.setDefaultCommands(["circlemenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(400);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(Circle.getTitle(), "CircleToolsPanel", true);
    return tb;
};

Circle.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Circle.getTitle(), "CircleMatrixPanel", 400);
};

Circle.getTitle = function() {
    return qsTr("&Circle");
};

Circle.prototype.getTitle = function() {
    return Circle.getTitle();
};

Circle.init = function() {
    Circle.getMenu();
    Circle.getToolBar();
    Circle.getCadToolBarPanel();
    Circle.getToolMatrixPanel();
};
