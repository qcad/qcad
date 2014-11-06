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

include("../Misc.js");

/**
 * \class MiscModify
 * \brief Base class for misc modify tools.
 */
function MiscModify(guiAction) {
    EAction.call(this, guiAction);
}

MiscModify.prototype = new EAction();
MiscModify.includeBasePath = includeBasePath;

MiscModify.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        400,
        MiscModify.getTitle(),
        "MiscModify"
    );
    return menu;
};

MiscModify.getToolBar = function() {
    var tb = EAction.getToolBar(MiscModify.getTitle(), "MiscModify");
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

MiscModify.getTitle = function() {
    return qsTr("&Modify");
};

MiscModify.prototype.getTitle = function() {
    return MiscModify.getTitle();
};
