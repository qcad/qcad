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
 * \defgroup ecma_edit Editing Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of the editing tools
 * (copy, paste, undo, redo, delete, ...)
 */
include("scripts/EAction.js");

/**
 * \class Edit
 * \brief Base class for all editing tools.
 * \ingroup ecma_edit
 */
function Edit(guiAction) {
    EAction.call(this, guiAction);
}

Edit.prototype = new EAction();
Edit.includeBasePath = includeBasePath;

Edit.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="EditToolsPanelAction") {
        EAction.showCadToolBarPanel("EditToolsPanel");
        this.terminate();
    }
};

Edit.getMenu = function() {
    var menu = EAction.getMenu(Edit.getTitle(), "EditMenu");
    menu.setProperty("scriptFile", Edit.includeBasePath + "/Edit.js");
    return menu;
};

Edit.getToolBar = function() {
    var tb = EAction.getToolBar(Edit.getTitle(), "EditToolBar");
    return tb;
};

Edit.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "EditToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Edit Tools"), mtb);
        action.setScriptFile(Edit.includeBasePath + "/Edit.js");
        action.objectName = actionName;
        action.setRequiresDocument(false);
        action.setIcon(Edit.includeBasePath + "/Edit.svg");
        //action.setStatusTip(qsTr("Show edit tools"));
        action.setNoState();
        action.setDefaultCommands(["editmenu"]);
        action.setGroupSortOrder(10);
        action.setSortOrder(200);
        action.setWidgetNames(["!MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Edit.getTitle(),
        "EditToolsPanel",
        true
    );
    return tb;
};

Edit.getToolMatrixPanel = function() {
    RSettings.setValue("Edit/VisibleInMatrixPanel", false, false);
    return EAction.getToolMatrixPanel(Edit.getTitle(), "EditMatrixPanel", 20);
};

Edit.getTitle = function() {
    return qsTr("&Edit");
};

Edit.prototype.getTitle = function() {
    return Edit.getTitle();
};

Edit.init = function() {
    Edit.getMenu();
    Edit.getToolBar();
    Edit.getCadToolBarPanel();
    Edit.getToolMatrixPanel();
};
