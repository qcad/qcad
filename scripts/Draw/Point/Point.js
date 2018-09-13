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
 * \defgroup ecma_draw_point Point Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various point drawing tools.
 */
include("scripts/Draw/Draw.js");

/**
 * \class Point
 * \brief Base class for all point drawing tools.
 * \ingroup ecma_draw_point
 */
function Point(guiAction) {
    Draw.call(this, guiAction);
}

Point.prototype = new Draw();
Point.includeBasePath = includeBasePath;

Point.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="PointToolsPanelAction") {
        EAction.showCadToolBarPanel("PointToolsPanel");
        this.terminate();
    }
};

Point.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        20, 100,
        Point.getTitle(),
        "DrawPointMenu",
        Point.includeBasePath + "/Point.svg"
    );
    menu.setProperty("scriptFile", Point.includeBasePath + "/Point.js");
    return menu;
};

Point.getToolBar = function() {
    var tb = EAction.getToolBar(Point.getTitle(), "PointToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Point.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "PointToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Point Tools"), mtb);
        action.setScriptFile(Point.includeBasePath + "/Point.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Point.includeBasePath + "/Point.svg");
        //action.setStatusTip(qsTr("Show point tools"));
        action.setDefaultShortcut(new QKeySequence("w,p"));
        action.setNoState();
        action.setDefaultCommands(["pointmenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(100);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Point.getTitle(),
        "PointToolsPanel",
        true
    );
    return tb;
};

Point.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Point.getTitle(), "PointMatrixPanel", 100);
};

Point.getTitle = function() {
    return qsTr("&Point");
};

Point.prototype.getTitle = function() {
    return Point.getTitle();
};

Point.addPointsOnLine = function(doc, op, startPoint, endPoint, numberOfPoints) {
    var point = new RPointEntity(doc, new RPointData(startPoint));
    op.addObject(point);
    var dv = startPoint.operator_subtract(endPoint).operator_divide(numberOfPoints - 1);
    var v = startPoint;
    for ( var i = 1; i < numberOfPoints - 1; ++i) {
        point = new RPointEntity(doc, new RPointData(v.operator_subtract(dv.operator_multiply(i))));
        op.addObject(point);
    }
    point = new RPointEntity(doc, new RPointData(endPoint));
    op.addObject(point);
};

Point.init = function() {
    Point.getMenu();
    Point.getToolBar();
    Point.getCadToolBarPanel();
    Point.getToolMatrixPanel();
};
