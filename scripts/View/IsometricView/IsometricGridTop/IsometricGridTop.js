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

include("../IsometricView.js");

/**
 * Helper class to update grid button status when focus changes
 * (e.g. other view is activated).
 */
function ProjectionFocusListener(action, proj) {
    RViewFocusListenerAdapter.call(this);

    this.guiAction = action;
    this.proj = proj;
}

ProjectionFocusListener.prototype = new RViewFocusListenerAdapter();

ProjectionFocusListener.prototype.updateFocus = function(view) {
    if (isNull(view)) {
        this.guiAction.setChecked(false);
        return;
    }

    // isometric grid switched off:
    if (isNull(this.proj)) {
        this.guiAction.setChecked(!IsometricGridTop.isGridIsometric(view));
    }

    // isometric grid projection set:
    else {
        this.guiAction.setChecked(
            IsometricGridTop.isGridIsometric(view) &&
            IsometricGridTop.getProjection(view)===this.proj
        );
    }
};



/**
 * \class IsometricGridTop
 * \brief Switches isometric grid to top view.
 * \ingroup ecma_view
 */
function IsometricGridTop(guiAction) {
    IsometricView.call(this, guiAction);
    this.proj = RS.IsoTop;
}

IsometricGridTop.prototype = new IsometricView();

IsometricGridTop.prototype.beginEvent = function() {
    IsometricView.prototype.beginEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (isNull(view)) {
        this.terminate();
        return;
    }
    if (isNull(this.proj)) {
        IsometricGridTop.setIsometricGrid(view, false);
    }
    else {
        IsometricGridTop.setIsometricGrid(view, true);
        IsometricGridTop.setProjection(view, this.proj);
    }
    view.getGrid().update(true);
    view.regenerate();

    this.terminate();
};

IsometricGridTop.prototype.finishEvent = function() {
    IsometricView.prototype.finishEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (isNull(view)) {
        return;
    }
    var guiAction = this.getGuiAction();
    if (isNull(guiAction)) {
        return;
    }

    if (isNull(this.proj)) {
        guiAction.setChecked(!IsometricGridTop.isGridIsometric(view));
    }
    else {
        guiAction.setChecked(IsometricGridTop.getProjection(view)===this.proj);
    }
};

IsometricGridTop.isGridIsometric = function(view) {
    var grid = IsometricView.getGrid(view);
    if (isNull(grid)) {
        return false;
    }
    return grid.isIsometric();
};

IsometricGridTop.setIsometricGrid = function(view, status) {
    var grid = IsometricView.getGrid(view);
    if (isNull(grid)) {
        return;
    }
    return grid.setIsometric(status);
};

IsometricGridTop.getProjection = function(view) {
    var grid = IsometricView.getGrid(view);
    if (isNull(grid)) {
        return RS.IsoTop;
    }
    return grid.getProjection();
};

IsometricGridTop.setProjection = function(view, p) {
    var grid = IsometricView.getGrid(view);
    if (isNull(grid)) {
        return;
    }
    return grid.setProjection(p);
};

IsometricGridTop.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Top Projection"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/IsometricGridTop.js");
    action.setRequiresDocument(true);
    action.setIcon(basePath + "/IsometricGridTop.svg");
    action.setDefaultShortcut(new QKeySequence("j,t"));
    action.setDefaultCommands(["isometricgridtop", "jt"]);
    action.setGroup("isometricProjection");
    action.setNoState(true);
    action.setGroupSortOrder(3500);
    action.setSortOrder(100);
    action.setWidgetNames(["ViewMenu", "IsometricViewToolBar", "ViewToolsPanel", "ViewMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    var fl = new ProjectionFocusListener(action, RS.IsoTop);
    appWin.addViewFocusListener(fl);
};
