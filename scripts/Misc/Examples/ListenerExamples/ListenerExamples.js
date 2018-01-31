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
 * \defgroup ecma_misc_examples_listenerexamples Example Layer Scripts
 * \ingroup ecma_misc_examples
 *
 * \brief This module contains listener related ECMAScript example.
 */
include("../Examples.js");

/**
 * \class ListenerExamples
 * \brief Base class for all event listener examples.
 */
function ListenerExamples(guiAction) {
    EAction.call(this, guiAction);
}

ListenerExamples.prototype = new EAction();
ListenerExamples.includeBasePath = includeBasePath;

ListenerExamples.getMenu = function() {
    var menu = EAction.getSubMenu(
        Examples.getMenu(),
        70000, 1000,
        ListenerExamples.getTitle(),
        "ListenerExamplesMenu"
    );
    return menu;
};

ListenerExamples.getTitle = function() {
    return qsTr("&Listeners");
};

ListenerExamples.prototype.getTitle = function() {
    return ListenerExamples.getTitle();
};

ListenerExamples.init = function() {
    ListenerExamples.getMenu();
};
