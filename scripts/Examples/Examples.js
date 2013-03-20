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

/**
 * \defgroup ecma_examples Example Scripts
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript examples.
 */
include("../EAction.js");

/**
 * \class Examples
 * \brief Base class for all example scripts.
 */
function Examples(guiAction) {
    EAction.call(this, guiAction);
}

Examples.prototype = new EAction();
Examples.includeBasePath = includeBasePath;

Examples.getMenu = function() {
    var menu = EAction.getMenu(Examples.getTitle(), "ExamplesMenu");
    menu.setProperty("scriptFile", Examples.includeBasePath + "/Examples.js");
    return menu;
};

Examples.getToolBar = function() {
    var tb = EAction.getToolBar(Examples.getTitle(), "ExamplesToolBar");
    tb.visible = false;
    return tb;
};

Examples.getCadToolBarPanel = function() {
    return EAction.getMainCadToolBarPanel();
};

Examples.getTitle = function() {
    return qsTr("&Examples");
};

Examples.prototype.getTitle = function() {
    return Examples.getTitle();
};
