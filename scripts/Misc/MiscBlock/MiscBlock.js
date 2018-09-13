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
 * \defgroup ecma_misc_block Misc block related tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc block tools..
 */
include("scripts/Misc/Misc.js");

/**
 * \class MiscBlock
 * \ingroup ecma_misc_block
 * \brief Base class for misc block tools.
 */
function MiscBlock(guiAction) {
    Misc.call(this, guiAction);
}

MiscBlock.prototype = new Misc();
MiscBlock.includeBasePath = includeBasePath;

MiscBlock.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51100, 500,
        MiscBlock.getTitle(),
        "MiscBlockMenu"
    );
    return menu;
};

MiscBlock.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscBlock.getTitle(), "MiscBlockToolBar", Qt.TopToolBarArea, Misc.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

MiscBlock.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscBlockToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Block Tools"), mtb);
        action.setScriptFile(MiscBlock.includeBasePath + "/MiscBlock.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setIcon(MiscBlock.includeBasePath + "/MiscBlock.svg");
        //action.setStatusTip(qsTr("Show misc block tools"));
        action.setNoState();
        action.setDefaultCommands(["miscblockmenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(500);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscBlock.getTitle(),
        "MiscBlockToolsPanel",
        true
    );
    return tb;
};

MiscBlock.getTitle = function() {
    return qsTr("&Block");
};

MiscBlock.prototype.getTitle = function() {
    return MiscBlock.getTitle();
};

MiscBlock.init = function() {
    MiscBlock.getMenu();
    MiscBlock.getToolBar();
    MiscBlock.getCadToolBarPanel();
};
