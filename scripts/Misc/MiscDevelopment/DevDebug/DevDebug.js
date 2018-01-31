/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * DirectDistanceEntry handling added 2013 by Robert S.
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

include("scripts/WidgetFactory.js");
include("scripts/simple.js");

function DevDebug(guiAction) {
    EAction.call(this, guiAction);
}

DevDebug.prototype = new EAction();

/**
 * Shows / hides the script shell widget.
 */
DevDebug.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var appWin = RMainWindowQt.getMainWindow();
    appWin.setProperty("Debug", true);
    EAction.handleUserMessage("Debug mode activated");
};

DevDebug.init = function(basePath) {
    var appWin = EAction.getMainWindow();

    var action = new RGuiAction(qsTr("&Debug Mode"), appWin);
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/DevDebug.js");
    action.setDefaultCommands(["debug"]);
    action.setGroupSortOrder(3800);
    action.setSortOrder(200);
    action.setWidgetNames(["!MiscDevelopmentMenu", "!MiscDevelopmentToolBar", "!MiscDevelopmentToolsPanel"]);
};
