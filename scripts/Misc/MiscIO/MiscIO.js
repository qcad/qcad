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
 * \defgroup ecma_misc_block Misc I/O related tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc import export tools..
 */
include("scripts/Misc/Misc.js");

/**
 * \class MiscIO
 * \ingroup ecma_misc_io
 * \brief Base class for misc import export tools.
 */
function MiscIO(guiAction) {
    Misc.call(this, guiAction);
}

MiscIO.prototype = new Misc();
MiscIO.includeBasePath = includeBasePath;

MiscIO.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51100, 100,
        MiscIO.getTitle(),
        "MiscIOMenu"
    );
    return menu;
};

MiscIO.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscIO.getTitle(), "MiscIOToolBar", Qt.TopToolBarArea, Misc.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

MiscIO.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscIOToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Import / Export Tools"), mtb);
        action.setScriptFile(MiscIO.includeBasePath + "/MiscIO.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setIcon(MiscIO.includeBasePath + "/MiscIO.svg");
        //action.setStatusTip(qsTr("Show misc import / export tools"));
        action.setNoState();
        action.setDefaultCommands(["misciomenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(100);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscIO.getTitle(),
        "MiscIOToolsPanel",
        true
    );
    return tb;
};

MiscIO.getTitle = function() {
    return qsTr("&Import/Export");
};

MiscIO.prototype.getTitle = function() {
    return MiscIO.getTitle();
};

MiscIO.init = function() {
    MiscIO.getMenu();
    MiscIO.getToolBar();
    MiscIO.getCadToolBarPanel();
};
