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
 * \defgroup ecma_draw Drawing Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of the
 * various drawing tools.
 */
include("scripts/EAction.js");

/**
 * \class Draw
 * \brief Base class for all drawing tools.
 */
function Draw(guiAction) {
    EAction.call(this, guiAction);
}

Draw.prototype = new EAction();
Draw.includeBasePath = includeBasePath;

Draw.getMenu = function() {
    var menu = EAction.getMenu(Draw.getTitle(), "DrawMenu");
    menu.setProperty("scriptFile", Draw.includeBasePath + "/Draw.js");
    return menu;
};

Draw.getToolBar = function() {
    var tb = EAction.getToolBar(Draw.getTitle(), "DrawToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Draw.getCadToolBarPanel = function() {
    return EAction.getMainCadToolBarPanel();
};

Draw.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Draw.getTitle(), "DrawMatrixPanel", 2000);
};

Draw.getContextMenuCategory = function() {
    return [qsTr("Draw")];
};

Draw.getTitle = function() {
    return qsTr("&Draw");
};

Draw.prototype.getTitle = function() {
    return Draw.getTitle();
};

Draw.init = function() {
    Draw.getMenu();
    Draw.getToolBar();
    Draw.getCadToolBarPanel();
    Draw.getToolMatrixPanel();

    // add action for the sake of configurability (tool preferences):
    var appWin = EAction.getMainWindow();
    var action = new RGuiAction(qsTr("Drawing Tools"), appWin);
    action.setScriptFile(Draw.includeBasePath + "/Draw.js");
    action.setGroupSortOrder(5);
    action.setSortOrder(100);
    action.setWidgetNames([]);
};
