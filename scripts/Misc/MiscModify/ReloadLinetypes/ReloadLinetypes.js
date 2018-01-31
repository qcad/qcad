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

include("scripts/EAction.js");

/**
 * This action reloads all linetypes from
 */
function ReloadLinetypes(guiAction) {
    EAction.call(this, guiAction);
}

ReloadLinetypes.prototype = new EAction();

ReloadLinetypes.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var doc = this.getDocument();
    var di = this.getDocumentInterface();

    var lts = doc.getDefaultLinetypes();
    var op = new RAddObjectsOperation();
    for (var i=0; i<lts.length; i++) {
        op.addObject(lts[i]);
    }
    di.applyOperation(op);

    this.terminate();
};

ReloadLinetypes.init = function(basePath) {
    var action = new RGuiAction(qsTr("Reload Linetype Definitions"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(false);
    action.setScriptFile(basePath + "/ReloadLinetypes.js");
    action.setGroupSortOrder(56100);
    action.setSortOrder(300);
    action.setWidgetNames(["MiscModifyMenu", "MiscModifyToolBar", "MiscModifyToolsPanel"]);
};
