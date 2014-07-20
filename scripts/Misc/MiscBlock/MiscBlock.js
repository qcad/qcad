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
 * \defgroup ecma_misc_block Misc block related tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc block tools..
 */
include("../Misc.js");

/**
 * \class MiscBlock
 * \ingroup ecma_misc_block
 * \brief Base class for misc block tools.
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
