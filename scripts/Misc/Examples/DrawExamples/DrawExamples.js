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
 * \defgroup ecma_misc_examples_draw Example Draw Scripts
 * \ingroup ecma_misc_examples
 *
 * \brief This module contains drawing related ECMAScript example.
 */
include("../Examples.js");

/**
 * \class DrawExamples
 * \brief Base class for all drawing examples.
 */
function DrawExamples(guiAction) {
    EAction.call(this, guiAction);
}

DrawExamples.prototype = new EAction();
DrawExamples.includeBasePath = includeBasePath;

DrawExamples.getMenu = function() {
    var menu = EAction.getSubMenu(
        Examples.getMenu(),
        70000, 300,
        DrawExamples.getTitle(),
        "DrawExamplesMenu"
        //DrawExamples.includeBasePath + "/DrawExamples.svg"
    );
    return menu;
};

DrawExamples.getTitle = function() {
    return qsTr("&Draw");
};

DrawExamples.prototype.getTitle = function() {
    return DrawExamples.getTitle();
};

DrawExamples.init = function() {
    DrawExamples.getMenu();
};
