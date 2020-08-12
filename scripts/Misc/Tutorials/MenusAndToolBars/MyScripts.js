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
// MyScripts.js

// All actions are derived from class EAction, so we need to 
// include this class definition here:
include("scripts/EAction.js");

// Constructor calls base class constructor:
function MyScripts(guiAction) {
    EAction.call(this, guiAction);
}

// Derive class MyScripts from class EAction:
MyScripts.prototype = new EAction();

// This static function returns a new or existing QMenu object.
MyScripts.getMenu = function() {
    // EAction.getMenu is a helper function that returns an existing 
    // or new QMenu object with the given title and object name.
    // The object name (here "MyScriptMenu") must be unique. 
    return EAction.getMenu(MyScripts.getTitle(), "MyScriptsMenu");
};

// This static function returns a new or existing QToolBar object.
MyScripts.getToolBar = function() {
    // EAction.getToolBar is a helper function that returns an existing 
    // or new QToolBar object with the given title and object name.
    // The object name (here "MyScriptsToolBar") must be unique.
    return EAction.getToolBar(MyScripts.getTitle(), "MyScriptsToolBar");
};

// This static function defines and returns the title of the menu 
// and toolbar.
// The qsTr function marks the title as a translatable string.
MyScripts.getTitle = function() {
    return qsTr("My Scripts");
};

// Init creates the menu and toolbar on start.
MyScripts.init = function() {
    MyScripts.getMenu();
    MyScripts.getToolBar();
};
