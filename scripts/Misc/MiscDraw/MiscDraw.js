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
 * \defgroup ecma_misc_draw Misc drawing tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc drawing tools.
 */
include("scripts/Misc/Misc.js");
include("scripts/Draw/Line/Line.js");

/**
 * \class MiscDraw
 * \ingroup ecma_misc_draw
 * \brief Base class for misc drawing tools.
 */
function MiscDraw(guiAction) {
    Misc.call(this, guiAction);
}

MiscDraw.prototype = new Misc();
MiscDraw.includeBasePath = includeBasePath;

MiscDraw.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51100, 300,
        MiscDraw.getTitle(),
        "MiscDrawMenu"
    );
    return menu;
};

MiscDraw.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscDraw.getTitle(), "MiscDrawToolBar", Qt.TopToolBarArea, Misc.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

MiscDraw.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscDrawToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Drawing Tools"), mtb);
        action.setScriptFile(MiscDraw.includeBasePath + "/MiscDraw.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setIcon(MiscDraw.includeBasePath + "/MiscDraw.svg");
        //action.setStatusTip(qsTr("Show misc drawing tools"));
        action.setNoState();
        action.setDefaultCommands(["miscdrawmenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(300);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscDraw.getTitle(),
        "MiscDrawToolsPanel",
        true
    );
    return tb;
};

MiscDraw.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(qsTr("Misc Draw"), "MiscDrawMatrixPanel", 2050);
};

MiscDraw.getTitle = function() {
    return qsTr("&Draw");
};

MiscDraw.prototype.getTitle = function() {
    return MiscDraw.getTitle();
};

MiscDraw.init = function() {
    MiscDraw.getMenu();
    MiscDraw.getToolBar();
    MiscDraw.getCadToolBarPanel();
    MiscDraw.getToolMatrixPanel();
};
