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
 
function MenusAndToolBars(guiAction) {
    EAction.call(this, guiAction);
}

MenusAndToolBars.prototype = new EAction();

MenusAndToolBars.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    var appWin = EAction.getMainWindow();
    appWin.handleUserMessage(qsTr("MenusAndToolBars() is running..."));
    
    this.terminate();
};

MenusAndToolBars.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Menus and Toolbars"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/MenusAndToolBars.js");
    action.setGroupSortOrder(80100);
    action.setSortOrder(100);
    action.setWidgetNames(["TutorialsMenu"]);
};
