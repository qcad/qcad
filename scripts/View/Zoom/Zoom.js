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
 * \defgroup ecma_view_zoom Zoom Tools
 * \ingroup ecma_scripts
 *
 * \brief This module contains ECMAScript implementations of various
 * zoom tools.
 */
include("scripts/EAction.js");

/**
 * \class Zoom
 * \brief Base class for all zoom tools.
 * \ingroup ecma_view_zoom
 */
function Zoom(guiAction) {
    EAction.call(this, guiAction);
}

Zoom.prototype = new EAction();
Zoom.includeBasePath = includeBasePath;

Zoom.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="ZoomToolsPanelAction") {
        EAction.showCadToolBarPanel("ZoomToolsPanel");
        this.terminate();
    }
};

Zoom.getMenu = function() {
    var menu = EAction.getSubMenu(View.getMenu(), 3300, 100, qsTr("Zoom"), "ZoomMenu");
    menu.setProperty("scriptFile", Zoom.includeBasePath + "/Zoom.js");
    return menu;
};

Zoom.getToolBar = function() {
    //return EAction.getToolBar(Zoom.getTitle(), "ViewToolBar", undefined, undefined, View.getToolBar());
    return View.getToolBar();
};

Zoom.getCadToolBarPanel = function() {
    var mtb = EAction.getMainCadToolBarPanel();
    var actionName = "ZoomToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Zoom Tools"), mtb);
        action.setScriptFile(Zoom.includeBasePath + "/Zoom.js");
        action.objectName = actionName;
        action.setRequiresDocument(false);
        action.setIcon(Zoom.includeBasePath + "/Zoom.svg");
        //action.setStatusTip(qsTr("Show zoom tools"));
        action.setDefaultShortcut(new QKeySequence("w,z"));
        action.setNoState();
        action.setDefaultCommands(["zoommenu"]);
        action.setGroupSortOrder(10);
        action.setSortOrder(350);
        action.setWidgetNames(["!MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Zoom.getTitle(),
        "ZoomToolsPanel",
        true
    );
    return tb;
};

Zoom.getToolMatrixPanel = function() {
    RSettings.setValue("Zoom/VisibleInMatrixPanel", false, false);
    return EAction.getToolMatrixPanel(Zoom.getTitle(), "ZoomMatrixPanel", 30);
};

Zoom.getTitle = function() {
    return qsTr("&Zoom");
};

Zoom.prototype.getTitle = function() {
    return Zoom.getTitle();
};

Zoom.init = function() {
    Zoom.getMenu();
    Zoom.getToolBar();
    Zoom.getCadToolBarPanel();
    Zoom.getToolMatrixPanel();
};
