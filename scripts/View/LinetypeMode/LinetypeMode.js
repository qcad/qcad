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
 * Helper class to update LinetypeMode button status when focus changes
 * (e.g. other view is activated).
 */
function ToggleLinetypeModeFocusListener(action) {
    RViewFocusListenerAdapter.call(this);

    this.action = action;
}

ToggleLinetypeModeFocusListener.prototype = new RViewFocusListenerAdapter();

ToggleLinetypeModeFocusListener.prototype.updateFocus = function(view) {
    if (isNull(view)) {
        this.action.checked = false;
        return;
    }

    var scene = view.getScene();
    if (isNull(scene)) {
        this.action.checked = false;
        return;
    }

    this.action.checked = scene.getScreenBasedLinetypes();
};




function LinetypeMode(guiAction) {
    View.call(this, guiAction);
}

LinetypeMode.prototype = new View();

LinetypeMode.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (!isNull(view)) {
        var scene = view.getScene();
        if (!isNull(scene)) {
            scene.toggleScreenBasedLinetypes();
            scene.regenerate();
        }
    }

    this.terminate();
};

LinetypeMode.prototype.finishEvent = function() {
    View.prototype.finishEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (!isNull(view) && !isNull(this.getGuiAction())) {
        var scene = view.getScene();
        if (!isNull(scene)) {
            this.getGuiAction().setChecked(scene.getScreenBasedLinetypes());
        }
    }
};

LinetypeMode.init = function(basePath) {
    var action = new RGuiAction(qsTranslate("LinetypeMode", "Screen-based Line&types"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LinetypeMode.js");
    action.setIcon(basePath + "/LinetypeMode.svg");
    action.setDefaultShortcut(new QKeySequence("n,l"));
    action.setDefaultCommands(["screenlinetype", "nl"]);
    action.setGroup("viewmodes");
    action.setNoState(true);
    action.setGroupSortOrder(3100);
    action.setSortOrder(200);
    action.setWidgetNames(["ViewMenu", "ViewToolBar", "ViewToolsPanel", "ViewMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    var fl = new ToggleLinetypeModeFocusListener(action);
    appWin.addViewFocusListener(fl);
};
