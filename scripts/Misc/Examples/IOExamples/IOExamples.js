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
 * \defgroup ecma_misc_examples_ioexamples Example IO Scripts
 * \ingroup ecma_misc_examples
 *
 * \brief This module contains I/O related ECMAScript example.
 */
include("../Examples.js");

/**
 * \class IOExamples
 * \brief Base class for all IO examples.
 */
function IOExamples(guiAction) {
    EAction.call(this, guiAction);
}

IOExamples.prototype = new EAction();
IOExamples.includeBasePath = includeBasePath;

IOExamples.getMenu = function() {
    var menu = EAction.getSubMenu(
        Examples.getMenu(),
        70000, 100,
        IOExamples.getTitle(),
        "IOExamplesMenu"
        //IOExamples.includeBasePath + "/IOExamples.svg"
    );
    return menu;
};

IOExamples.getTitle = function() {
    return qsTr("&Import/Export");
};

IOExamples.prototype.getTitle = function() {
    return IOExamples.getTitle();
};

IOExamples.init = function() {
    IOExamples.getMenu();
};
