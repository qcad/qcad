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
 * \defgroup ecma_draw_polyline Polyline Drawing Tools
 * \ingroup ecma_draw
 * 
 * \brief This module contains ECMAScript implementations of various polyline 
 * drawing and modification tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Polyline
 * \brief Base class for all polyline drawing tools.
 * \ingroup ecma_draw_polyline
 */
function Polyline(guiAction) {
    Draw.call(this, guiAction);
}

Polyline.prototype = new Draw();
Polyline.includeBasePath = includeBasePath;

Polyline.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="PolylineToolsPanelAction") {
        EAction.showCadToolBarPanel("PolylineToolsPanel");
        this.terminate();
    }
};

Polyline.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        20, 700,
        Polyline.getTitle(),
        "DrawPolylineMenu",
        Polyline.includeBasePath + "/Polyline.svg"
    );
    menu.setProperty("scriptFile", Polyline.includeBasePath + "/Polyline.js");
    return menu;
};

Polyline.getToolBar = function() {
    var tb = EAction.getToolBar(Polyline.getTitle(), "PolylineToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    //tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

Polyline.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "PolylineToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Polyline Tools"), mtb);
        action.setScriptFile(Polyline.includeBasePath + "/Polyline.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Polyline.includeBasePath + "/Polyline.svg");
        //action.setStatusTip(qsTr("Show polyline tools"));
        action.setDefaultShortcut(new QKeySequence("w,o"));
        action.setNoState();
        action.setDefaultCommands(["polylinemenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(700);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Polyline.getTitle(),
        "PolylineToolsPanel",
        true
    );
    return tb;
};

Polyline.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Polyline.getTitle(), "PolylineMatrixPanel", 700);
};

Polyline.getTitle = function() {
    return qsTr("&Polyline");
};

Polyline.prototype.getTitle = function() {
    return Polyline.getTitle();
};

Polyline.init = function() {
    Polyline.getMenu();
    Polyline.getToolBar();
    Polyline.getCadToolBarPanel();
    Polyline.getToolMatrixPanel();
};

Polyline.prototype.getClosestSegment = function(pos) {
    if (isNull(this.polylineEntity)) {
        return undefined;
    }

    var i = this.polylineEntity.getClosestSegment(pos);
    if (i<0) {
        return undefined;
    }

    var seg = this.polylineEntity.getSegmentAt(i);
    if (isNull(seg)) {
        return undefined;
    }

    this.previousNode = seg.getStartPoint();
    this.nextNode = seg.getEndPoint();

    return i;
};
