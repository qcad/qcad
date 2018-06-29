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
 * \defgroup ecma_widgets Widgets
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various 
 * user interface widgets.
 */
include("scripts/EAction.js");

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
    include("scripts/View/View.js");
    return View.getMenu();
};

Widgets.getToolBar = function() {
    return EAction.getToolBar(Widgets.getTitle(), "WidgetsToolBar", Qt.RightToolBarArea);
};

Widgets.getToolMatrixPanel = function() {
    RSettings.setValue("Widgets/VisibleInMatrixPanel", false, false);
    return EAction.getToolMatrixPanel(Widgets.getTitle(), "WidgetsMatrixPanel", 40);
};

Widgets.getTitle = function() {
    return qsTr("&Widgets");
};

Widgets.prototype.getTitle = function() {
    return Widgets.getTitle();
};

//Widgets.getListContextMenuCategory = function() {
//    return [qsTr("Lists")];
//};

Widgets.init = function() {
    Widgets.getToolBar();
    Widgets.getToolMatrixPanel();

    // add action for the sake of configurability (tool preferences):
    var appWin = EAction.getMainWindow();
    var action = new RGuiAction("", appWin);
    action.setScriptFile(Widgets.includeBasePath + "/Widgets.js");
    action.setGroupSortOrder(5);
    action.setSortOrder(100);
    action.setWidgetNames([]);
};
