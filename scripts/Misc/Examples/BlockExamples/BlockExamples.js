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
 * \defgroup ecma_misc_examples_block Example Block Scripts
 * \ingroup ecma_misc_examples
 *
 * \brief This module contains block related ECMAScript example.
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
        70000, 800,
        BlockExamples.getTitle(),
        "BlockExamplesMenu"
        //BlockExamples.includeBasePath + "/BlockExamples.svg"
    );
    return menu;
};

BlockExamples.getTitle = function() {
    return qsTr("&Block");
};

BlockExamples.prototype.getTitle = function() {
    return BlockExamples.getTitle();
};

BlockExamples.init = function() {
    BlockExamples.getMenu();
};
