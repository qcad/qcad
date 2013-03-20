/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("../Edit.js");
include("../AbstractPreferences.js");

function DrawingPreferences(guiAction) {
    AbstractPreferences.call(this, guiAction, false);
}

DrawingPreferences.prototype = new AbstractPreferences();

DrawingPreferences.prototype.beginEvent = function() {
    AbstractPreferences.prototype.beginEvent.call(this);

    // regenerate scenes (various drawing settings affect the
    // rendering):
    var di = EAction.getDocumentInterface();
    if (!isNull(di)) {
        di.updateAllEntities();
        di.regenerateScenes();
        di.regenerateViews(true);
    }
};

DrawingPreferences.init = function(basePath) {
    var action = new RGuiAction(qsTr("Drawing &Preferences"),
            RMainWindowQt.getMainWindow());
    action.setDefaultCommands(["drawingpreferences"]);
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DrawingPreferences.js");
    action.setIcon(basePath + "/DrawingPreferences.svg");
    action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.Key_I));
    action.setDefaultCommands(["drawingpreferences"]);
    action.setSortOrder(89000);
    action.setNoState();
    EAction.addGuiActionTo(action, Edit, true, false, false, true);
};
