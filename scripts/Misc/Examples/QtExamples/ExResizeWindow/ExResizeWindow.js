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

include("../QtExamples.js");

/**
 * \ingroup ecma_misc_examples_qtexamples
 * \class ExResizeWindow
 * This action resizes the main application window to common 
 * screencast / screenshot sizes.
 */
function ExResizeWindow(guiAction) {
    QtExamples.call(this, guiAction);
}

ExResizeWindow.prototype = new QtExamples();
ExResizeWindow.includeBasePath = includeBasePath;

ExResizeWindow.prototype.beginEvent = function() {
    QtExamples.prototype.beginEvent.call(this);

    var dialog = WidgetFactory.createDialog(ExResizeWindow.includeBasePath, "ExResizeWindow.ui");

    dialog.exec();

    var size = dialog.findChild("Size").currentText;

    var match = new RegExp("(\\d*)x(\\d*)").exec(size);
    if (match.length===3) {
        var appWin = RMainWindowQt.getMainWindow();
        var titleBarHeight = 22;
        appWin.resize(parseInt(match[1], 10), parseInt(match[2], 10) - titleBarHeight);
    }

    dialog.destroy();
    EAction.activateMainWindow();
    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/ExResizeWindow.
 */
ExResizeWindow.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Resize Window"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ExResizeWindow.js");
    action.setGroupSortOrder(79600);
    action.setSortOrder(400);
    action.setWidgetNames(["QtExamplesMenu"]);
};
