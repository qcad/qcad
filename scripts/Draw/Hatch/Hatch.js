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
 * \defgroup ecma_draw_hatch Hatch Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various 
 * hatch and fill drawing tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Hatch
 * \brief Base class for all hatch drawing tools.
 * \ingroup ecma_draw_hatch
 */
function Hatch(guiAction) {
    Draw.call(this, guiAction);
}

Hatch.prototype = new Draw();
Hatch.includeBasePath = includeBasePath;

Hatch.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="HatchToolsPanelAction") {
        EAction.showCadToolBarPanel("HatchToolsPanel");
        this.terminate();
    }
};

Hatch.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        20, 900,
        Hatch.getTitle(),
        "DrawHatchMenu",
        Hatch.includeBasePath + "/Hatch.svg"
    );
    menu.setProperty("scriptFile", Hatch.includeBasePath + "/Hatch.js");
    return menu;
};

Hatch.getToolBar = function() {
    var tb = EAction.getToolBar(Hatch.getTitle(), "HatchToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Hatch.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "HatchToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Hatch Tools"), mtb);
        action.setScriptFile(Hatch.includeBasePath + "/Hatch.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Hatch.includeBasePath + "/Hatch.svg");
        //action.setStatusTip(qsTr("Show hatch tools"));
        action.setDefaultShortcut(new QKeySequence("w,x"));
        action.setNoState();
        action.setDefaultCommands(["hatchmenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(900);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Hatch.getTitle(),
        "HatchToolsPanel",
        true
    );
    return tb;
};

Hatch.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Hatch.getTitle(), "HatchMatrixPanel", 900);
};

Hatch.getTitle = function() {
    return qsTr("&Hatch");
};

Hatch.prototype.getTitle = function() {
    return Hatch.getTitle();
};

Hatch.init = function() {
    Hatch.getMenu();
    Hatch.getToolBar();
    Hatch.getCadToolBarPanel();
    Hatch.getToolMatrixPanel();
};
