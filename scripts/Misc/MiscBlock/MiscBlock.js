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
 * \brief This module contains ECMAScript example tutorials.
 */
include("../Misc.js");

/**
 * \class MiscBlock
 * \brief Base class for all tutorial style examples..
 */
function MiscBlock(guiAction) {
    Misc.call(this, guiAction);
}

MiscBlock.prototype = new Misc();
MiscBlock.includeBasePath = includeBasePath;

MiscBlock.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        10100,
        MiscBlock.getTitle(),
        "MiscBlock"
    );
    return menu;
};

MiscBlock.getToolBar = function() {
    var tb = EAction.getToolBar(MiscBlock.getTitle(), "MiscBlockToolBar");
    tb.visible = false;
    return tb;
};

MiscBlock.getCadToolBarPanel = function() {
    return EAction.getMainCadToolBarPanel();
};

MiscBlock.getTitle = function() {
    return qsTr("&Block");
};

MiscBlock.prototype.getTitle = function() {
    return MiscBlock.getTitle();
};
