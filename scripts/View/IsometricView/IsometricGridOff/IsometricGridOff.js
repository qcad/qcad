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

include("../IsometricGridTop/IsometricGridTop.js");

/**
 * \class IsometricGridOff
 * \brief Switches isometric grid off.
 * \ingroup ecma_view
 */
function IsometricGridOff(guiAction) {
    IsometricGridTop.call(this, guiAction);
    this.proj = undefined;
}

IsometricGridOff.prototype = new IsometricGridTop();

IsometricGridOff.init = function(basePath) {
    var action = new RGuiAction(qsTr("Isometric Grid &Off"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/IsometricGridOff.js");
    action.setRequiresDocument(true);
    action.setIcon(basePath + "/IsometricGridOff.svg");
    action.setDefaultShortcut(new QKeySequence("j,o"));
    action.setDefaultCommands(["isometricgridoff", "jo"]);
    action.setGroup("isometricProjection");
    action.setNoState(true);
    action.setGroupSortOrder(3500);
    action.setSortOrder(100);
    action.setWidgetNames(["ViewMenu", "IsometricViewToolBar", "ViewToolsPanel", "ViewMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    var fl = new ProjectionFocusListener(action, undefined);
    appWin.addViewFocusListener(fl);

    // add separator only to menu:
    var menu = IsometricView.getMenu();
    if (!isNull(menu)) {
        var separator = new RGuiAction("", RMainWindowQt.getMainWindow());
        separator.setSeparator(true);
        separator.setSortOrder(action.getSortOrder() - 1);
        separator.addToMenu(menu);
    }
};
