/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
 * \defgroup ecma_widgets Widgets
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various 
 * user interface widgets.
 */
include("../EAction.js");
include("../View/View.js");

/**
 * \class Widgets
 * \brief Base class for widget related tools.
 * \ingroup ecma_widgets
 */
function Widgets(guiAction) {
    EAction.call(this, guiAction);
}

Widgets.prototype = new EAction();
Widgets.includeBasePath = includeBasePath;

Widgets.getMenu = function() {
    return View.getMenu();
};

Widgets.getToolBar = function() {
    var tb = EAction.getToolBar(Widgets.getTitle(), "WidgetsToolBar", Qt.RightToolBarArea);
    //tb.visible = false;
    return tb;
};

Widgets.getTitle = function() {
    return qsTr("&Widgets");
};

Widgets.prototype.getTitle = function() {
    return Widgets.getTitle();
};

Widgets.getListContextMenuCategory = function() {
    return [qsTr("Lists")];
};

Widgets.init = function() {
    Widgets.getToolBar();
};
