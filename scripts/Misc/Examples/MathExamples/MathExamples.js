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
 * \class MathExamples
 * \brief Base class for all math examples.
 */
function MathExamples(guiAction) {
    EAction.call(this, guiAction);
}

MathExamples.prototype = new EAction();
MathExamples.includeBasePath = includeBasePath;

MathExamples.getMenu = function() {
    var menu = EAction.getSubMenu(
        Examples.getMenu(),
        300,
        MathExamples.getTitle(),
        "mathExamples"
        //MathExamples.includeBasePath + "/MathExamples.svg"
    );
    return menu;
};

MathExamples.getToolBar = function() {
    var tb = EAction.getToolBar(MathExamples.getTitle(), "MathExamples");
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

MathExamples.getTitle = function() {
    return qsTr("&Mathematics");
};

MathExamples.prototype.getTitle = function() {
    return MathExamples.getTitle();
};
