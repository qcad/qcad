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
 * \defgroup ecma_snap Snap Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * snap tools.
 */
include("scripts/EAction.js");

/**
 * \class Snap
 * \brief Base class for all snap tools.
 * \ingroup ecma_snap
 */
function Snap(guiAction) {
    EAction.call(this, guiAction);
}

Snap.prototype = new EAction();
Snap.includeBasePath = includeBasePath;

Snap.getMenu = function() {
    var menu = EAction.getMenu(Snap.getTitle(), "SnapMenu");
    menu.setProperty("scriptFile", Snap.includeBasePath + "/Snap.js");
    return menu;
};

Snap.getToolBar = function() {
    var tb = EAction.getToolBar(Snap.getTitle(), "SnapToolBar");
    tb.visible = false;
    return tb;
};

Snap.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "SnapToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Snap Tools"), mtb);
        action.setScriptFile(Snap.includeBasePath + "/Snap.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Snap.includeBasePath + "/Snap.svg");
        //action.setStatusTip(qsTr("Show snap tools"));
        action.setNoState();
        action.setDefaultCommands(["snapmenu"]);
        action.setGroupSortOrder(40);
        action.setSortOrder(400);
        action.setWidgetNames(["!MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Snap.getTitle(),
        "SnapToolsPanel",
        true
    );
    return tb;
};

Snap.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Snap.getTitle(), "SnapMatrixPanel", 5000);
};

Snap.getTitle = function() {
    return qsTr("&Snap");
};

Snap.prototype.getTitle = function() {
    return Snap.getTitle();
};

Snap.init = function() {
    Snap.getMenu();
    Snap.getToolBar();
    Snap.getCadToolBarPanel();
    Snap.getToolMatrixPanel();
};

Snap.prototype.beginEvent = function() {
    if (!this.hasNoState()) {
        EAction.prototype.beginEvent.call(this);
        return;
    }

    if (!isNull(this.getGuiAction())) {
        this.getGuiAction().setChecked(true);
    }

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="SnapToolsPanelAction") {
        EAction.showCadToolBarPanel("SnapToolsPanel");
        this.terminate();
    }
};

Snap.prototype.finishEvent = function() {
    if (!this.hasNoState()) {
        EAction.prototype.finishEvent.call(this);
        return;
    }

    if (!isNull(this.getGuiAction()) && !isDeleted(this.getGuiAction())) {
        if (this.getGuiAction().getGroup().isEmpty()) {
            this.getGuiAction().setChecked(false);
        }
        if (this.getGuiAction().isOverride()) {
            this.getGuiAction().setChecked(false);
        }
    }
};

Snap.prototype.restrict = function(coord) {
    var di = this.getDocumentInterface();
    if (isNull(di)) {
        return coord;
    }

    var currentSnapRestriction = di.getSnapRestriction();
    if (!isNull(currentSnapRestriction)) {
        return currentSnapRestriction.restrictSnap(coord, di.getRelativeZero());
    }

    return coord;
};
