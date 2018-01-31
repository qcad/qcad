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

include("scripts/View/View.js");


/**
 * Helper class to update grid button status when focus changes
 * (e.g. other view is activated).
 */
function ToggleGridFocusListener(action) {
    RViewFocusListenerAdapter.call(this);

    this.action = action;
}

ToggleGridFocusListener.prototype = new RViewFocusListenerAdapter();

ToggleGridFocusListener.prototype.updateFocus = function(view) {
    if (isNull(view)) {
        this.action.checked = false;
        return;
    }

    var doc = view.getDocument();
    if (isNull(doc)) {
        this.action.checked = false;
        return;
    }

    var gridOn = view.isGridVisible();
    this.action.checked = gridOn;
};



/**
 * \class ToggleGrid
 * \brief Toggles grid visibility.
 * \ingroup ecma_view
 */
function ToggleGrid(guiAction) {
    View.call(this, guiAction);
}

ToggleGrid.prototype = new View();

ToggleGrid.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (!isNull(view)) {
        var gridOn = view.isGridVisible();
        view.setGridVisible(!gridOn);
        view.regenerate();
    }

    this.terminate();
};

ToggleGrid.prototype.finishEvent = function() {
    View.prototype.finishEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (!isNull(view)) {
        var guiAction = this.getGuiAction();
        if (!isNull(guiAction)) {
            guiAction.setChecked(view.isGridVisible());
        }
    }
};

ToggleGrid.init = function(basePath) {
    var action = new RGuiAction(qsTr("&Grid"), RMainWindowQt.getMainWindow());
    action.setScriptFile(basePath + "/ToggleGrid.js");
    action.setRequiresDocument(true);
    action.setIcon(basePath + "/ToggleGrid.svg");
    action.setDefaultShortcut(new QKeySequence("g,r"));
    action.setNoState(true);
    action.setGroupSortOrder(3200);
    action.setSortOrder(100);
    action.setWidgetNames(["ViewMenu", "ViewToolBar", "ViewToolsPanel", "ViewMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    var fl = new ToggleGridFocusListener(action);
    appWin.addViewFocusListener(fl);
};
