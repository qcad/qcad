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
 * \class IsometricGridLeft
 * \brief Switches isometric grid to side view.
 * \ingroup ecma_view
 */
function IsometricGridLeft(guiAction) {
    IsometricGridTop.call(this, guiAction);
    this.proj = RS.IsoLeft;
}

IsometricGridLeft.prototype = new IsometricGridTop();

IsometricGridLeft.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Left Projection"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/IsometricGridLeft.js");
    action.setRequiresDocument(true);
    action.setIcon(basePath + "/IsometricGridLeft.svg");
    action.setDefaultShortcut(new QKeySequence("j,l"));
    action.setDefaultCommands(["isometricgridleft", "jl"]);
    action.setGroup("isometricProjection");
    action.setNoState(true);
    action.setGroupSortOrder(3500);
    action.setSortOrder(400);
    action.setWidgetNames(["ViewMenu", "IsometricViewToolBar", "ViewToolsPanel", "ViewMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    var fl = new ProjectionFocusListener(action, RS.IsoLeft);
    appWin.addViewFocusListener(fl);
};
