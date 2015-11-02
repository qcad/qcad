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

include("scripts/EAction.js");

function ShowToolDialog(guiAction) {
    EAction.call(this, guiAction);
}

ShowToolDialog.prototype = new EAction();

ShowToolDialog.init = function(basePath) {
    var appWin = EAction.getMainWindow();

//    // TODO: breaks enter in command line
//    //var context = Qt.WidgetShortcut;
//    var context = Qt.WindowShortcut;
//    ShowToolDialog.shortcutReturn = new QShortcut(new QKeySequence(Qt.Key_Return.valueOf()), appWin, 0, 0, context);
//    ShowToolDialog.shortcutReturn.activated.connect(ShowToolDialog, "showDialog");
//    ShowToolDialog.shortcutReturn.activatedAmbiguously.connect(ShowToolDialog, "showDialog");
//    ShowToolDialog.shortcutEnter = new QShortcut(new QKeySequence(Qt.Key_Enter.valueOf()), appWin, 0, 0, context);
//    ShowToolDialog.shortcutEnter.activated.connect(ShowToolDialog, "showDialog");
//    ShowToolDialog.shortcutEnter.activatedAmbiguously.connect(ShowToolDialog, "showDialog");

//    var action = new RGuiAction(qsTranslate("ShowToolDialog", "&Show Tool Dialog"), RMainWindowQt.getMainWindow());
//    action.setScriptFile(basePath + "/ShowToolDialog.js");
//    action.setDefaultShortcuts(
//                [
//                    new QKeySequence(Qt.Key_Return.valueOf()),
//                    new QKeySequence(Qt.Key_Enter.valueOf()),
//                ]);
//    action.setNoState();
//    action.checkable = false;
//    action.setGroupSortOrder(3900);
//    action.setSortOrder(150);
//    action.setWidgetNames(["ViewMenu", "!ViewToolBar", "!ViewToolsPanel"]);
};

ShowToolDialog.showDialog = function() {
//ShowToolDialog.prototype.beginEvent = function() {
    var di = EAction.getDocumentInterface();
    if (isNull(di)) {
//        this.terminate();
        return;
    }

    var a = di.getCurrentAction();
    if (isNull(a)) {
//        this.terminate();
        return;
    }

    a.showDialog();
//    this.terminate();
};
