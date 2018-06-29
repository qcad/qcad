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
 * \defgroup ecma_misc_tutorials Tutorial scripts
 * \ingroup ecma_misc
 *
 * \brief This module contains ECMAScript example tutorials.
 */
include("scripts/Misc/Misc.js");

/**
 * \class Tutorials
 * \ingroup ecma_misc_tutorials
 * \brief Base class for all tutorial style examples.
 */
function Tutorials(guiAction) {
    Misc.call(this, guiAction);
}

Tutorials.prototype = new Misc();
Tutorials.includeBasePath = includeBasePath;

Tutorials.getMenu = function() {
    var menu = EAction.getSubMenu(
        Misc.getMenu(),
        80000, 100,
        Tutorials.getTitle(),
        "TutorialsMenu"
        //Tutorials.includeBasePath + "/Tutorials.svg"
    );
    return menu;
};

Tutorials.getCadToolBarPanel = function() {
    return EAction.getMainCadToolBarPanel();
};

Tutorials.getTitle = function() {
    return qsTr("Script &Tutorials");
};

Tutorials.prototype.getTitle = function() {
    return Tutorials.getTitle();
};

Tutorials.init = function() {
    Tutorials.getMenu();
};
