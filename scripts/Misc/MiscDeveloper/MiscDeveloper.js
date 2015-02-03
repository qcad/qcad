/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
 * \defgroup ecma_misc_developer Misc developer tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc developer tools.
 */
include("../Misc.js");

/**
 * \class MiscDeveloper
 * \ingroup ecma_misc_draw
 * \brief Base class for misc developer tools.
 */
function MiscDeveloper(guiAction) {
    Misc.call(this, guiAction);
}

MiscDeveloper.prototype = new Misc();
MiscDeveloper.includeBasePath = includeBasePath;

MiscDeveloper.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51150, 100,
        MiscDeveloper.getTitle(),
        "MiscDeveloperMenu"
    );
    return menu;
};

MiscDeveloper.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscDeveloper.getTitle(), "MiscDeveloperToolBar");
    tb.visible = false;
    return tb;
};

MiscDeveloper.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscDeveloperToolsPanelButton";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Developer Tools"), mtb);
        action.setScriptFile(MiscDeveloper.includeBasePath + "/MiscDeveloper.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setIcon(MiscDeveloper.includeBasePath + "/MiscDeveloper.svg");
        action.setStatusTip(qsTr("Show misc developer tools"));
        action.setNoState();
        action.setDefaultCommands(["miscdevelopermenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(10000);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscDeveloper.getTitle(),
        "MiscDeveloperToolsPanel",
        true
    );
    return tb;
};


MiscDeveloper.getTitle = function() {
    return qsTr("De&veloper");
};

MiscDeveloper.prototype.getTitle = function() {
    return MiscDeveloper.getTitle();
};

MiscDeveloper.init = function() {
    MiscDeveloper.getMenu();
    MiscDeveloper.getToolBar();
    MiscDeveloper.getCadToolBarPanel();
};
