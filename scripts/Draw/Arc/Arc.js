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
 * \defgroup ecma_draw_arc Arc Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various arc drawing tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Arc
 * \brief Base class for all arc drawing tools.
 * \ingroup ecma_draw_arc
 */
function Arc(guiAction) {
    Draw.call(this, guiAction);
}

Arc.prototype = new Draw();
Arc.includeBasePath = includeBasePath;

Arc.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="ArcToolsPanelAction") {
        EAction.showCadToolBarPanel("ArcToolsPanel");
        this.terminate();
    }
};

Arc.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        20, 300,
        Arc.getTitle(),
        "DrawArcMenu",
        Arc.includeBasePath + "/Arc.svg"
    );
    menu.setProperty("scriptFile", Arc.includeBasePath + "/Arc.js");
    return menu;
};

Arc.getToolBar = function() {
    var tb = EAction.getToolBar(Arc.getTitle(), "ArcToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Arc.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "ArcToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Arc Tools"), mtb);
        action.setScriptFile(Arc.includeBasePath + "/Arc.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Arc.includeBasePath + "/Arc.svg");
        //action.setStatusTip(qsTr("Show arc tools"));
        action.setDefaultShortcut(new QKeySequence("w,a"));
        action.setNoState();
        action.setDefaultCommands(["arcmenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(300);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(Arc.getTitle(), "ArcToolsPanel", true);
    return tb;
};

Arc.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Arc.getTitle(), "ArcMatrixPanel", 300);
};

Arc.getTitle = function() {
    return qsTr("&Arc");
};

Arc.prototype.getTitle = function() {
    return Arc.getTitle();
};

Arc.init = function() {
    Arc.getMenu();
    Arc.getToolBar();
    Arc.getCadToolBarPanel();
    Arc.getToolMatrixPanel();
};
