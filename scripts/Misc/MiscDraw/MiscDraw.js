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
 * \defgroup ecma_misc_draw Misc drawing tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc drawing tools.
 */
include("../Misc.js");

/**
 * \class MiscDraw
 * \ingroup ecma_misc_draw
 * \brief Base class for misc drawing tools.
 */
function MiscDraw(guiAction) {
    Misc.call(this, guiAction);
}

MiscDraw.prototype = new Misc();
MiscDraw.includeBasePath = includeBasePath;

MiscDraw.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        10100,
        MiscDraw.getTitle(),
        "MiscDraw"
    );
    return menu;
};

MiscDraw.getToolBar = function() {
    var tb = EAction.getToolBar(MiscDraw.getTitle(), "MiscDrawToolBar");
    tb.visible = false;
    return tb;
};

MiscDraw.getCadToolBarPanel = function() {
    return EAction.getMainCadToolBarPanel();
};

MiscDraw.getTitle = function() {
    return qsTr("&Drawing");
};

MiscDraw.prototype.getTitle = function() {
    return MiscDraw.getTitle();
};
