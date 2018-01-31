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
 * Helper class to update DraftMode button status when focus changes
 * (e.g. other view is activated).
 */
function ToggleDraftModeFocusListener(action) {
    RViewFocusListenerAdapter.call(this);

    this.action = action;
}

ToggleDraftModeFocusListener.prototype = new RViewFocusListenerAdapter();

ToggleDraftModeFocusListener.prototype.updateFocus = function(view) {
    if (isNull(view)) {
        this.action.checked = false;
        return;
    }

    var scene = view.getScene();
    if (isNull(scene)) {
        this.action.checked = false;
        return;
    }

    this.action.checked = scene.getDraftMode();
};




function DraftMode(guiAction) {
    View.call(this, guiAction);
}

DraftMode.prototype = new View();

DraftMode.prototype.beginEvent = function() {
    View.prototype.beginEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (!isNull(view)) {
        var scene = view.getScene();
        if (!isNull(scene)) {
            scene.toggleDraftMode();
            scene.regenerate();
        }
    }

    this.terminate();
};

DraftMode.prototype.finishEvent = function() {
    View.prototype.finishEvent.call(this);

    var view = this.getDocumentInterface().getLastKnownViewWithFocus();
    if (!isNull(view) && !isNull(this.getGuiAction())) {
        var scene = view.getScene();
        if (!isNull(scene)) {
            this.getGuiAction().setChecked(scene.getDraftMode());
        }
    }
};

DraftMode.init = function(basePath) {
    var action = new RGuiAction(qsTranslate("DraftMode", "&Draft Mode"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DraftMode.js");
    action.setIcon(basePath + "/DraftMode.svg");
    action.setDefaultShortcut(new QKeySequence("d,f"));
    action.setDefaultCommands(["draftmode", "df"]);
    action.setGroup("viewmodes");
    action.setNoState(true);
    action.setGroupSortOrder(3100);
    action.setSortOrder(100);
    action.setWidgetNames(["ViewMenu", "ViewToolBar", "ViewToolsPanel", "ViewMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    var fl = new ToggleDraftModeFocusListener(action);
    appWin.addViewFocusListener(fl);
};
