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
 * \defgroup ecma_misc_block Misc I/O related tools
 * \ingroup ecma_misc
 *
 * \brief This module contains misc import export tools..
 */
include("../Misc.js");

/**
 * \class MiscIO
 * \ingroup ecma_misc_io
 * \brief Base class for misc import export tools.
 */
function MiscIO(guiAction) {
    Misc.call(this, guiAction);
}

MiscIO.prototype = new Misc();
MiscIO.includeBasePath = includeBasePath;

MiscIO.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        50,
        MiscIO.getTitle(),
        "MiscIO"
    );
    return menu;
};

MiscIO.getToolBar = function() {
    var tb = EAction.getToolBar(MiscIO.getTitle(), "MiscIOToolBar");
    tb.visible = false;
    return tb;
};

MiscIO.getCadToolBarPanel = function() {
    return EAction.getMainCadToolBarPanel();
};

MiscIO.getTitle = function() {
    return qsTr("&Import/Export");
};

MiscIO.prototype.getTitle = function() {
    return MiscIO.getTitle();
};
