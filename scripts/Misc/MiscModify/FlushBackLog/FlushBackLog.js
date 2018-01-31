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
function FlushBackLog(guiAction) {
    EAction.call(this, guiAction);
}

FlushBackLog.prototype = new EAction();

FlushBackLog.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var di = this.getDocumentInterface();
    if (!isNull(di)) {
        var buttons = new QMessageBox.StandardButtons(QMessageBox.Yes, QMessageBox.Cancel);
        var ret = QMessageBox.warning(EAction.getMainWindow(),
            qsTr("Flush Undo History"),
            qsTr("Are you sure that you want to flush the undo / redo transaction history?") + " " +
            qsTr("This cannot be undone."),
            buttons
        );
        if (ret===QMessageBox.Yes) {
            di.flushTransactions();
        }
    }

    this.terminate();
};

FlushBackLog.init = function(basePath) {
    var action = new RGuiAction(qsTr("Flush &Undo History"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(false);
    action.setScriptFile(basePath + "/FlushBackLog.js");
    action.setGroupSortOrder(56100);
    action.setSortOrder(400);
    action.setWidgetNames(["MiscModifyMenu", "!MiscModifyToolBar", "!MiscModifyToolsPanel"]);
};
