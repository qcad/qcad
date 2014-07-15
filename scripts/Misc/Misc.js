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
 * \defgroup ecma_misc Misc Examples and Scripts
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript examples and uncategorized
 * scripts.
 */
include("../EAction.js");

/**
 * \class Misc
 * \brief Base class for misc scripts.
 * \ingroup ecma_misc
 */
function Misc(guiAction) {
    EAction.call(this, guiAction);
}

Misc.prototype = new EAction();
Misc.includeBasePath = includeBasePath;

Misc.getMenu = function() {
    var menu = EAction.getMenu(Misc.getTitle(), "MiscMenu");
    menu.setProperty("scriptFile", Misc.includeBasePath + "/Misc.js");
    return menu;
};

Misc.getToolBar = function() {
    var tb = EAction.getToolBar(Misc.getTitle(), "MiscToolBar");
    tb.visible = false;
    return tb;
};

Misc.getCadToolBarPanel = function() {
    return EAction.getMainCadToolBarPanel();
};

Misc.getTitle = function() {
    return qsTr("&Misc");
};

Misc.prototype.getTitle = function() {
    return Misc.getTitle();
};
