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

include("../Examples.js");

/**
 * \class BlockExamples
 * \brief Base class for all block examples.
 */
function BlockExamples(guiAction) {
    EAction.call(this, guiAction);
}

BlockExamples.prototype = new EAction();
BlockExamples.includeBasePath = includeBasePath;

BlockExamples.getMenu = function() {
    var menu = EAction.getSubMenu(
        Examples.getMenu(),
        100,
        BlockExamples.getTitle(),
        "blockExamples"
        //BlockExamples.includeBasePath + "/BlockExamples.svg"
    );
    return menu;
};

BlockExamples.getToolBar = function() {
    var tb = EAction.getToolBar(BlockExamples.getTitle(), "BlockExamples");
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

BlockExamples.getTitle = function() {
    return qsTr("&Block");
};

BlockExamples.prototype.getTitle = function() {
    return BlockExamples.getTitle();
};
