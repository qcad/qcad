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
// MyAction.js

// Include base class definition:
include("../MyScripts.js");
 
// Constructor calls base class constructor:
function MyAction(guiAction) {
    MyScripts.call(this, guiAction);
}

// Derive class MyAction from class MyScripts:
MyAction.prototype = new MyScripts();

// This function is called immediately after the constructor when the user 
// starts this action. For actions that don't require any user input (for
// example auto zoom), beginEvent does everything and then terminates the
// action.
MyAction.prototype.beginEvent = function() {
    // call base class implementation of beginEvent:
    MyScripts.prototype.beginEvent.call(this);

    // get main application window:
    var appWin = EAction.getMainWindow();

    // print a message in the console of QCAD:
    appWin.handleUserMessage("MyAction() is running...");
    
    // terminate this action immediately:
    this.terminate();
};

// MyAction.init() is called by QCAD to initialize the action and create
// the menu / toolbar for it.
MyAction.init = function(basePath) {
    // Create a new RGuiAction (extended QAction):
    var action = new RGuiAction("&My Action", RMainWindowQt.getMainWindow());

    // This action requires a document to be open. If no document is
    // open, the menu and tool button are grayed out:
    action.setRequiresDocument(true);

    // Define the script file that is executed when this action is
    // launched:
    action.setScriptFile(basePath + "/MyAction.js");

    // Set the icon that is shown in the toolbar and on some platforms
    // also in the menu:
    action.setIcon(basePath + "/MyAction.svg");

    // Set the command(s) that can be used on the command line to 
    // launch this action:
    action.setDefaultCommands(["myaction"]);

    // Define the sort order of this action. Menus and tool buttons are
    // ordered by this value:
    action.setSortOrder(10);

    // This helper function adds the action to the menu and toolbar
    // and also creates the menu and toolbar if they don't exist already:
    EAction.addGuiActionTo(
        action, 
        MyScripts,             // class that defines what menu / toolbar to use
        true,                  // add this action to the menu
        true,                  // add this action to the toolbar
        false                  // don't add a separator before this action
    );
};
