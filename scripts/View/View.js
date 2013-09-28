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
 * \defgroup ecma_view View Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * view tools.
 */
include("../EAction.js");

/**
 * \class View
 * \brief Base class for all view tools.
 * \ingroup ecma_view
 */
function View(guiAction) {
    EAction.call(this, guiAction);
}

View.prototype = new EAction();
View.includeBasePath = includeBasePath;

View.getMenu = function() {
    var menu = EAction.getMenu(View.getTitle(), "ViewMenu");
    menu.setProperty("scriptFile", View.includeBasePath + "/View.js");
    return menu;
};

View.getToolBar = function() {
    var tb = EAction.getToolBar(View.getTitle(), "ViewToolBar");
    return tb;
};

View.getTitle = function() {
    return qsTr("&View");
};

View.prototype.getTitle = function() {
    return View.getTitle();
};
