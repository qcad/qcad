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
 * \defgroup ecma_misc Misc Examples and Scripts
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript examples and uncategorized
 * scripts.
 */
include("scripts/EAction.js");

/**
 * \class Misc
 * \brief Base class for misc scripts.
 * \ingroup ecma_misc
 */
function Misc(guiAction) {
    EAction.call(this, guiAction);
}

Misc.prototype = new EAction();
Misc.includeBasePath = includeBasePath;

Misc.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="MiscToolsPanelAction") {
        EAction.showCadToolBarPanel("MiscToolsPanel");
        this.terminate();
    }
};

Misc.getMenu = function() {
    var menu = EAction.getMenu(Misc.getTitle(), "MiscMenu");
    menu.setProperty("scriptFile", Misc.includeBasePath + "/Misc.js");
    return menu;
};

Misc.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "MiscToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Misc Tools"), mtb);
        action.setScriptFile(Misc.includeBasePath + "/Misc.js");
        action.objectName = actionName;
        action.setRequiresDocument(false);
        action.setIcon(Misc.includeBasePath + "/Misc.svg");
        //action.setStatusTip(qsTr("Show misc tools"));
        action.setNoState();
        action.setDefaultCommands(["miscmenu"]);
        action.setGroupSortOrder(80);
        action.setSortOrder(100);
        action.setWidgetNames(["!MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Misc.getTitle(),
        "MiscToolsPanel",
        true
    );
    return tb;
};

Misc.getContextMenuCategory = function() {
    return [qsTr("Misc")];
};

Misc.getTitle = function() {
    return qsTr("&Misc");
};

Misc.prototype.getTitle = function() {
    return Misc.getTitle();
};

Misc.init = function() {
    Misc.getMenu();
    Misc.getCadToolBarPanel();
};
