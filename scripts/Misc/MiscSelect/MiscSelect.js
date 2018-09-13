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
 * \defgroup ecma_misc_select Misc selection tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc selection tool.
 */
include("scripts/Misc/Misc.js");

/**
 * \class MiscSelect
 * \ingroup ecma_misc_select
 *
 * \brief Base class for misc selection tools.
 */
function MiscSelect(guiAction) {
    Misc.call(this, guiAction);
}

MiscSelect.prototype = new Misc();
MiscSelect.includeBasePath = includeBasePath;

MiscSelect.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51100, 200,
        MiscSelect.getTitle(),
        "MiscSelectMenu"
    );
    return menu;
};

MiscSelect.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscSelect.getTitle(), "MiscSelectToolBar", Qt.TopToolBarArea, Misc.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

MiscSelect.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscSelectToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Selection Tools"), mtb);
        action.setScriptFile(MiscSelect.includeBasePath + "/MiscSelect.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setIcon(MiscSelect.includeBasePath + "/MiscSelect.svg");
        //action.setStatusTip(qsTr("Show misc selection tools"));
        action.setNoState();
        action.setDefaultCommands(["miscselectmenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(200);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscSelect.getTitle(),
        "MiscSelectToolsPanel",
        true
    );
    return tb;
};


MiscSelect.getTitle = function() {
    return qsTr("&Select");
};

MiscSelect.prototype.getTitle = function() {
    return MiscSelect.getTitle();
};

MiscSelect.init = function() {
    MiscSelect.getMenu();
    MiscSelect.getToolBar();
    MiscSelect.getCadToolBarPanel();
};
