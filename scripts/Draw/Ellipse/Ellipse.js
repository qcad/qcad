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
 * \defgroup ecma_draw_ellipse Ellipse Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various ellipse drawing tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Ellipse
 * \brief Base class for all ellipse drawing tools.
 * \ingroup ecma_draw_ellipse
 */
function Ellipse(guiAction) {
    Draw.call(this, guiAction);
}

Ellipse.prototype = new Draw();
Ellipse.includeBasePath = includeBasePath;

/**
 * Ellipse shape post processing.
 * \return ellipseShape or, if configured polyline.
 */
Ellipse.postProcess = function(ellipseShape) {
    if (RSettings.getBoolValue("Ellipse/CreatePolyline", false)!==true) {
        return ellipseShape;
    }

    var ellipseSegments = RSettings.getIntValue("Explode/EllipseSegments", 32);

    return ellipseShape.approximateWithArcs(ellipseSegments);
};

Ellipse.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="EllipseToolsPanelAction") {
        EAction.showCadToolBarPanel("EllipseToolsPanel");
        this.terminate();
    }
};

Ellipse.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(), 
        20, 500,
        Ellipse.getTitle(), 
        "DrawEllipseMenu",
        Ellipse.includeBasePath + "/Ellipse.svg"
    );
    menu.setProperty("scriptFile", Ellipse.includeBasePath + "/Ellipse.js");
    return menu;
};

Ellipse.getToolBar = function() {
    var tb = EAction.getToolBar(Ellipse.getTitle(), "EllipseToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Ellipse.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "EllipseToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Ellipse Tools"), mtb);
        action.setScriptFile(Ellipse.includeBasePath + "/Ellipse.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Ellipse.includeBasePath + "/Ellipse.svg");
        //action.setStatusTip(qsTr("Show ellipse tools"));
        action.setDefaultShortcut(new QKeySequence("w,e"));
        action.setNoState();
        action.setDefaultCommands(["ellipsemenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(500);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(Ellipse.getTitle(), "EllipseToolsPanel", true);
    return tb;
};

Ellipse.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Ellipse.getTitle(), "EllipseMatrixPanel", 500);
};

Ellipse.getTitle = function() {
    return qsTr("&Ellipse");
};

Ellipse.prototype.getTitle = function() {
    return Ellipse.getTitle();
};

Ellipse.init = function() {
    Ellipse.getMenu();
    Ellipse.getToolBar();
    Ellipse.getCadToolBarPanel();
    Ellipse.getToolMatrixPanel();
};
