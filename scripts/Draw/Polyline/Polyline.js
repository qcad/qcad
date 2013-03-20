/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
include("../Draw.js");

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

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName=="PolylineMenu") {
        EAction.showCadToolBarPanel("PolylineToolsPanel");
        this.terminate();
    }
};

Polyline.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        700,
        Polyline.getTitle(),
        "polyline",
        Polyline.includeBasePath + "/Polyline.svg"
    );
    menu.setProperty("scriptFile", Polyline.includeBasePath + "/Polyline.js");
    return menu;
};

Polyline.getToolBar = function() {
    var tb = EAction.getToolBar(Polyline.getTitle(), "Polyline");
    tb.orientation = Qt.Vertical;
    tb.visible = false;
    return tb;
};

Polyline.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "PolylineMenu";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Polyline Tools"), mtb);
        action.setScriptFile(Polyline.includeBasePath + "/Polyline.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Polyline.includeBasePath + "/Polyline.svg");
        action.setStatusTip(qsTr("Show polyline tools"));
        action.setDefaultShortcut(new QKeySequence("w,o"));
        action.setNoState();
        action.setProperty("SortOrder", 700);
        action.setDefaultCommands(["polylinemenu"]);
        CadToolBarPanel.prototype.addAction.call(mtb, action);
    }

    var tb = EAction.getCadToolBarPanel(
        Polyline.getTitle(),
        "PolylineToolsPanel",
        true
    );
    return tb;
};

Polyline.getTitle = function() {
    return qsTr("&Polyline");
};

Polyline.prototype.getTitle = function() {
    return Polyline.getTitle();
};

Polyline.prototype.getClosestSegment = function(pos) {
    if (isNull(this.polylineEntity)) {
        return undefined;
    }

    var ret = -1;

    var minDistance = -1;
    var numSegments = this.polylineEntity.countSegments();
    for (var i=0; i<numSegments; i++) {
        var seg = this.polylineEntity.getSegmentAt(i);
        var distance = seg.getDistanceTo(pos);
        if (minDistance==-1 || distance < minDistance) {
            minDistance = distance;
            this.previousNode = seg.getStartPoint();
            this.nextNode = seg.getEndPoint();
            ret = i;
        }
    }

    return ret;
};
