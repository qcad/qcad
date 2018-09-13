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
 * \defgroup ecma_misc_development Misc development tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc development tools.
 */
include("scripts/Misc/Misc.js");

/**
 * \class MiscDevelopment
 * \ingroup ecma_misc_draw
 * \brief Base class for misc development tools.
 */
function MiscDevelopment(guiAction) {
    Misc.call(this, guiAction);
}

MiscDevelopment.prototype = new Misc();
MiscDevelopment.includeBasePath = includeBasePath;

MiscDevelopment.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        51150, 100,
        MiscDevelopment.getTitle(),
        "MiscDevelopmentMenu"
    );
    return menu;
};

MiscDevelopment.getToolBar = function() {
    var tb = EAction.getToolBar(qsTr("Misc") + " " + MiscDevelopment.getTitle(), "MiscDevelopmentToolBar", Qt.TopToolBarArea, Misc.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

MiscDevelopment.getCadToolBarPanel = function() {
    var mtb = Misc.getCadToolBarPanel();
    var actionName = "MiscDevelopmentToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Development Tools"), mtb);
        action.setScriptFile(MiscDevelopment.includeBasePath + "/MiscDevelopment.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        //action.setIcon(MiscDevelopment.includeBasePath + "/MiscDevelopment.svg");
        //action.setStatusTip(qsTr("Show misc development tools"));
        action.setNoState();
        action.setDefaultCommands(["miscdevelopmentmenu"]);
        action.setGroupSortOrder(90);
        action.setSortOrder(10000);
        action.setWidgetNames(["MiscToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        MiscDevelopment.getTitle(),
        "MiscDevelopmentToolsPanel",
        true
    );
    return tb;
};


MiscDevelopment.getTitle = function() {
    return qsTr("De&velopment");
};

MiscDevelopment.prototype.getTitle = function() {
    return MiscDevelopment.getTitle();
};

MiscDevelopment.init = function() {
    MiscDevelopment.getMenu();
    MiscDevelopment.getToolBar();
    MiscDevelopment.getCadToolBarPanel();
};
