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
 * Helper class to update AntialiasingMode button status when focus changes
 * (e.g. other view is activated).
 */
function ToggleAntialiasingModeFocusListener(action) {
    RViewFocusListenerAdapter.call(this);

    this.action = action;
}

ToggleAntialiasingModeFocusListener.prototype = new RViewFocusListenerAdapter();

ToggleAntialiasingModeFocusListener.prototype.updateFocus = function(view) {
    if (isNull(view)) {
        this.action.checked = false;
        return;
    }

    this.action.checked = view.getAntialiasing();
};




function AntialiasingMode(guiAction) {
    View.call(this, guiAction);
}

AntialiasingMode.prototype = new View();

AntialiasingMode.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (!isNull(view)) {
        view.setAntialiasing(!view.getAntialiasing());
        view.regenerate(true);
    }

    this.terminate();
};

AntialiasingMode.prototype.finishEvent = function() {
    View.prototype.finishEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (!isNull(view) && !isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(view.getAntialiasing());
    }
};

AntialiasingMode.init = function(basePath) {
    var action = new RGuiAction(qsTranslate("AntialiasingMode", "&Anti-aliasing"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AntialiasingMode.js");
    action.setIcon(basePath + "/AntialiasingMode.svg");
    action.setDefaultShortcut(new QKeySequence("n,t"));
    action.setDefaultCommands(["antialiasing", "nt"]);
    action.setNoState(true);
    action.setGroupSortOrder(3100);
    action.setSortOrder(300);
    action.setWidgetNames(["ViewMenu", "ViewToolBar", "ViewToolsPanel", "ViewMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    var fl = new ToggleAntialiasingModeFocusListener(action);
    appWin.addViewFocusListener(fl);
};
