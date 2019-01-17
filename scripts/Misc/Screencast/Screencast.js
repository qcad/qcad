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
 * \defgroup ecma_misc_screencast Screencast support
 * \ingroup ecma_misc
 *
 * \brief This module contains ECMAScript screencast recording tools.
 */
include("scripts/Misc/Misc.js");

/**
 * \class Screencast
 * \ingroup ecma_misc_screencast
 */
function Screencast(guiAction) {
    Misc.call(this, guiAction);
}

Screencast.prototype = new Misc();
Screencast.includeBasePath = includeBasePath;

Screencast.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        10000,
        Screencast.getTitle(),
        "screencast"
    );
    return menu;
};

Screencast.getToolBar = function() {
    var tb = EAction.getToolBar(Screencast.getTitle(), "ScreencastToolBar");
    tb.visible = false;
    return tb;
};

Screencast.getCadToolBarPanel = function() {
    return EAction.getMainCadToolBarPanel();
};

Screencast.getTitle = function() {
    return "&Screencast";
};

Screencast.prototype.getTitle = function() {
    return Screencast.getTitle();
};
