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
 * \defgroup ecma_tutorials_cmd Command Line Tools Examples
 * \ingroup ecma_tutorials
 */
include("../Tutorials.js");

/**
 * \class CommandLineTools
 * \ingroup ecma_tutorials_cmd
 * \brief Base class for all command line tool examples.
 */
function CommandLineTools(guiAction) {
    Tutorials.call(this, guiAction);
}

CommandLineTools.prototype = new Tutorials();
CommandLineTools.includeBasePath = includeBasePath;

CommandLineTools.getMenu = function() {
    var menu = EAction.getSubMenu(
        Tutorials.getMenu(),
        0, 200,
        CommandLineTools.getTitle(),
        "commandLineTools",
        CommandLineTools.includeBasePath + "/CommandLineTools.svg"
    );
    return menu;
};

CommandLineTools.getTitle = function() {
    return qsTr("&Command Line Tools");
};

CommandLineTools.prototype.getTitle = function() {
    return CommandLineTools.getTitle();
};
