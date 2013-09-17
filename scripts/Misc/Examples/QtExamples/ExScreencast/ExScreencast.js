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

include("../QtExamples.js");

/**
 * This action creates a Qt main window.
 */
function ExScreencast(guiAction) {
    QtExamples.call(this, guiAction);
}

ExScreencast.prototype = new QtExamples();
ExScreencast.includeBasePath = includeBasePath;

ExScreencast.prototype.beginEvent = function() {
    QtExamples.prototype.beginEvent.call(this);

    var w = 1280;
    var h = 680;
    var x = 50;
    var y = 20;

    var appWin = RMainWindowQt.getMainWindow();
    appWin.resize(w,h);
    appWin.move(x,y);

    var pe = appWin.findChild("PropertyEditorDock");
    pe.show();
    pe.maximumWidth = 280;
    //pe.resize(300,h+5);
    //pe.move(x+w+10,y);

    var ll = appWin.findChild("LayerListDock");
    ll.show();
    ll.maximumWidth = 220;

    var bl = appWin.findChild("BlockListDock");
    bl.show();
    bl.maximumWidth = 220;

    //var ct = appWin.findChild("CamToolBar");
    //ct.hide();

    var cl = appWin.findChild("CommandLineDock");
    cl.hide();

    this.terminate();
};

/**
 * Adds a menu for this action to Examples/Math Examples/ExScreencast.
 */
ExScreencast.init = function(basePath) {
    var action = new RGuiAction("&Screen cast", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ExScreencast.js");
    action.setSortOrder(20);
    action.setDefaultCommands(["screencast"]);
    EAction.addGuiActionTo(action, QtExamples, true, false, false);
};
