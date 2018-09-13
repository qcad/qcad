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
 * \defgroup ecma_modify Modification Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * modification tools.
 */
include("scripts/EAction.js");

/**
 * \class Modify
 * \brief Base class for all modification tools.
 * \ingroup ecma_modify
 */
function Modify(guiAction) {
    EAction.call(this, guiAction);
    
    this.autoRefresh = true;
    this.copies = 0;
}

Modify.prototype = new EAction();
Modify.includeBasePath = includeBasePath;

Modify.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="ModifyToolsPanelAction") {
        EAction.showCadToolBarPanel("ModifyToolsPanel");
        this.terminate();
    }
};

Modify.prototype.deleteSelectedEntities = function(msgEntitiesDeleted, msgNothingDeleted) {
    var di = EAction.getDocumentInterface();
    var doc = di.getDocument();
    var ids = doc.querySelectedEntities();
    var op = new RDeleteSelectionOperation();
    var trans = di.applyOperation(op);
    var count = ids.length;
    var appWin = EAction.getMainWindow();
    if (count === 0) {
        appWin.handleUserMessage(msgNothingDeleted);
    } else {
        appWin.handleUserMessage(msgEntitiesDeleted + ": " + count);
    }
    return count;
};

Modify.prototype.slotRefresh = function() {
    var di = EAction.getDocumentInterface();
    di.deselectAll();
    this.refresh();
};

Modify.prototype.slotClose = function() {
    this.terminate();
};

Modify.prototype.slotAutoRefreshChanged = function(checked) {
    this.autoRefresh = checked;
};

Modify.getMenu = function() {
    var menu = EAction.getMenu(Modify.getTitle(), "ModifyMenu");
    menu.setProperty("scriptFile", Modify.includeBasePath + "/Modify.js");
    return menu;
};

Modify.getToolBar = function() {
    var tb = EAction.getToolBar(Modify.getTitle(), "ModifyToolBar");
    tb.visible = false;
    return tb;
};

Modify.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "ModifyToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Modification Tools"), mtb);
        action.setScriptFile(Modify.includeBasePath + "/Modify.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Modify.includeBasePath + "/Modify.svg");
        //action.setStatusTip(qsTr("Show modification tools"));
        action.setDefaultShortcut(new QKeySequence("w,m"));
        action.setNoState();
        action.setDefaultCommands(["modifymenu"]);
        action.setGroupSortOrder(40);
        action.setSortOrder(100);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Modify.getTitle(),
        "ModifyToolsPanel",
        true
    );
    return tb;
};

Modify.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Modify.getTitle(), "ModifyMatrixPanel", 3000);
};

Modify.getTitle = function() {
    return qsTr("&Modify");
};

Modify.prototype.getTitle = function() {
    return Modify.getTitle();
};

Modify.init = function() {
    Modify.getMenu();
    Modify.getToolBar();
    Modify.getCadToolBarPanel();
    Modify.getToolMatrixPanel();
};
