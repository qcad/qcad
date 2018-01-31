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

//! [main]
//! [include]
include("scripts/WidgetFactory.js");
//! [include]
include("../Tutorials.js");

function PersistentWidgets(guiAction) {
    Tutorials.call(this, guiAction);
}

PersistentWidgets.prototype = new Tutorials();
PersistentWidgets.includeBasePath = includeBasePath;

//! [beginEvent]
PersistentWidgets.prototype.beginEvent = function() {
    Tutorials.prototype.beginEvent.call(this);

    // Create the dialog from the .ui file using the helper
    // function WidgetFactory.createWidget().
    var dialog = WidgetFactory.createWidget(
            PersistentWidgets.includeBasePath,
            "PersistentWidgets.ui");

    // Restore the previous user data or display default values as
    // set in Qt Designer:
    WidgetFactory.restoreState(dialog);

    // Display and execute the dialog:
    if (!dialog.exec()) {
        dialog.destroy();
        EAction.activateMainWindow();
        // User hit cancel:
        this.terminate();
        return;
    }

    // User hit OK. Store the new user input:
    WidgetFactory.saveState(dialog);
    var widgets = getWidgets(dialog);
    var positionX = widgets["PositionX"].text;
    var positionY = widgets["PositionY"].text;

    // Print the user input to the QCAD console:
    var appWin = EAction.getMainWindow();
    appWin.handleUserMessage("Position X: " + positionX);
    appWin.handleUserMessage("Position Y: " + positionY);
    
    dialog.destroy();
    EAction.activateMainWindow();
    this.terminate();
};
//! [beginEvent]

PersistentWidgets.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Persistent Widgets"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PersistentWidgets.js");
    action.setGroupSortOrder(80100);
    action.setSortOrder(200);
    action.setWidgetNames(["TutorialsMenu"]);
};
//! [main]
