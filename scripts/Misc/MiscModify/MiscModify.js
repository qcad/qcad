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

include("scripts/Misc/Misc.js");

/**
 * \class MiscModify
 * \brief Base class for misc modify tools.
 */
function MiscModify(guiAction) {
    EAction.call(this, guiAction);
}

MiscModify.prototype = new EAction();
MiscModify.includeBasePath = includeBasePath;

MiscModify.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51100, 350,
        MiscModify.getTitle(),
        "MiscModifyMenu"
    );
    return menu;
};

MiscModify.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscModify.getTitle(), "MiscModifyToolBar", Qt.TopToolBarArea, Misc.getContextMenuCategory());
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

MiscModify.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscModifyToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Modification Tools"), mtb);
        action.setScriptFile(MiscModify.includeBasePath + "/MiscModify.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setIcon(MiscModify.includeBasePath + "/MiscModify.svg");
        //action.setStatusTip(qsTr("Show misc modification tools"));
        action.setNoState();
        action.setDefaultCommands(["miscmodifymenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(350);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscModify.getTitle(),
        "MiscModifyToolsPanel",
        true
    );
    return tb;
};


MiscModify.getTitle = function() {
    return qsTr("&Modify");
};

MiscModify.prototype.getTitle = function() {
    return MiscModify.getTitle();
};

MiscModify.init = function() {
    MiscModify.getMenu();
    MiscModify.getToolBar();
    MiscModify.getCadToolBarPanel();
};
