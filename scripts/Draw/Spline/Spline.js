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
 * \defgroup ecma_draw_spline Spline Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various spline drawing tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Spline
 * \brief Base class for all spline drawing tools.
 * \ingroup ecma_draw_spline
 */
function Spline(guiAction) {
    Draw.call(this, guiAction);
}

Spline.prototype = new Draw();
Spline.includeBasePath = includeBasePath;

Spline.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="SplineToolsPanelAction") {
        EAction.showCadToolBarPanel("SplineToolsPanel");
        this.terminate();
    }
};

Spline.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        20, 600,
        Spline.getTitle(),
        "SplineMenu",
        Spline.includeBasePath + "/Spline.svg"
    );
    menu.setProperty("scriptFile", Spline.includeBasePath + "/Spline.js");
    return menu;
};

Spline.getToolBar = function() {
    var tb = EAction.getToolBar(Spline.getTitle(), "SplineToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

Spline.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "SplineToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Spline Tools"), mtb);
        action.setScriptFile(Spline.includeBasePath + "/Spline.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Spline.includeBasePath + "/Spline.svg");
        //action.setStatusTip(qsTr("Show spline tools"));
        action.setDefaultShortcut(new QKeySequence("w,n"));
        action.setNoState();
        action.setDefaultCommands(["splinemenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(600);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Spline.getTitle(),
        "SplineToolsPanel",
        true
    );
    return tb;
};

Spline.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Spline.getTitle(), "SplineMatrixPanel", 600);
};

Spline.getTitle = function() {
    return qsTr("&Spline");
};

Spline.prototype.getTitle = function() {
    return Spline.getTitle();
};

Spline.init = function() {
    Spline.getMenu();
    Spline.getToolBar();
    Spline.getCadToolBarPanel();
    Spline.getToolMatrixPanel();
};
