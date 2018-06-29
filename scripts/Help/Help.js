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

/**
 * \defgroup ecma_help Help Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of
 * the help menu entries.
 */
include("scripts/EAction.js");

/**
 * \class Help
 * \brief Base class for all help menu entries.
 * \ingroup ecma_help
 */
function Help(guiAction) {
    EAction.call(this, guiAction);
}

Help.prototype = new EAction();
Help.includeBasePath = includeBasePath;

Help.openUrl = function(url) {
    QDesktopServices.openUrl(new QUrl(url));
};

Help.getMenu = function() {
    var menu = EAction.getMenu(Help.getTitle(), "HelpMenu");
    menu.setProperty("scriptFile", Help.includeBasePath + "/Help.js");
    return menu;
};

Help.getToolBar = function() {
    var tb = EAction.getToolBar(Help.getTitle(), "HelpToolBar");
    if (tb.property("Initialized")!==true) {
        tb.visible = false;
    }
    return tb;
};

Help.getTitle = function() {
    return qsTr("&Help");
};

Help.prototype.getTitle = function() {
    return Help.getTitle();
};

Help.init = function() {
    Help.getMenu();
    Help.getToolBar();
};
