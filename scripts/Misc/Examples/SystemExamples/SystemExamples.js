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
 * \class SystemExamples
 * \brief Base class for all system examples.
 */
function SystemExamples(guiAction) {
    EAction.call(this, guiAction);
}

SystemExamples.prototype = new EAction();
SystemExamples.includeBasePath = includeBasePath;

SystemExamples.getMenu = function() {
    var menu = EAction.getSubMenu(
        Examples.getMenu(),
        400,
        SystemExamples.getTitle(),
        "systemExamples"
    );
    return menu;
};

SystemExamples.getToolBar = function() {
    var tb = EAction.getToolBar(SystemExamples.getTitle(), "SystemExamples");
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

SystemExamples.getTitle = function() {
    return qsTr("&System");
};

SystemExamples.prototype.getTitle = function() {
    return SystemExamples.getTitle();
};
