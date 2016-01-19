/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
 * \defgroup ecma_draw_shape Shape Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various
 * shape drawing tools.
 */
include("../Draw.js");

/**
 * \class Shape
 * \brief Base class for all shape drawing tools.
 * \ingroup ecma_draw_shape
 */
function Shape(guiAction) {
    Draw.call(this, guiAction);

    this.createPolyline = false;
}

Shape.prototype = new Draw();
Shape.includeBasePath = includeBasePath;

Shape.prototype.beginEvent = function() {
    Draw.prototype.beginEvent.call(this);

    if (!isNull(this.getGuiAction()) && this.getGuiAction().objectName==="ShapeToolsPanelAction") {
        EAction.showCadToolBarPanel("ShapeToolsPanel");
        this.terminate();
    }
};

Shape.getMenu = function() {
    var menu = EAction.getSubMenu(
        Draw.getMenu(),
        20, 800,
        Shape.getTitle(),
        "DrawShapeMenu",
        Shape.includeBasePath + "/Shape.svg"
    );
    menu.setProperty("scriptFile", Shape.includeBasePath + "/Shape.js");
    return menu;
};

Shape.getToolBar = function() {
    var tb = EAction.getToolBar(Shape.getTitle(), "ShapeToolBar", Qt.TopToolBarArea, Draw.getContextMenuCategory());
    tb.visible = false;
    return tb;
};

Shape.getCadToolBarPanel = function() {
    var mtb = Draw.getCadToolBarPanel();
    var actionName = "ShapeToolsPanelAction";
    if (!isNull(mtb) && mtb.findChild(actionName)==undefined) {
        var action = new RGuiAction(qsTr("Shape Tools"), mtb);
        action.setScriptFile(Shape.includeBasePath + "/Shape.js");
        action.objectName = actionName;
        action.setRequiresDocument(true);
        action.setIcon(Shape.includeBasePath + "/Shape.svg");
        action.setStatusTip(qsTr("Show shape tools"));
        action.setDefaultShortcut(new QKeySequence("w,h"));
        action.setNoState();
        action.setDefaultCommands(["shapemenu"]);
        action.setGroupSortOrder(20);
        action.setSortOrder(800);
        action.setWidgetNames(["MainToolsPanel"]);
    }

    var tb = EAction.getCadToolBarPanel(
        Shape.getTitle(),
        "ShapeToolsPanel",
        true
    );
    return tb;
};

Shape.getDockWidget = function() {
    var d = EAction.getDockWidget(Shape.getTitle(), "ShapeDockWidget", Qt.LeftDockWidgetArea, Draw.getContextMenuCategory());
    d.visible = false;
    return d;
};

Shape.getTitle = function() {
    return qsTr("&Shape");
};

Shape.prototype.getTitle = function() {
    return Shape.getTitle();
};

Shape.init = function() {
    Shape.getMenu();
    Shape.getToolBar();
    Shape.getCadToolBarPanel();
    //Shape.getDockWidget();
};

Shape.prototype.initUiOptions = function(resume, optionsToolBar) {
    Draw.prototype.initUiOptions.call(this, resume, optionsToolBar);

    this.createPolyline = RSettings.getBoolValue(this.settingsGroup + "/CreatePolyline", false);

    //var optionsToolBar = EAction.getOptionsToolBar();
    var w = optionsToolBar.findChild("CreatePolyline");
    if (!isNull(w)) {
        w.checked = this.createPolyline;
    }
};

Shape.prototype.hideUiOptions = function(saveToSettings) {
    Draw.prototype.hideUiOptions.call(this, saveToSettings);

    RSettings.setValue(this.settingsGroup + "/CreatePolyline", this.createPolyline);
};

Shape.prototype.slotCreatePolylineChanged = function(checked) {
    this.createPolyline = checked;
};

Shape.prototype.getShapes = function(vertices) {
    var i;
    if (this.createPolyline) {
        var pl = new RPolyline();
        for (i=0; i<vertices.length; ++i) {
            pl.appendVertex(vertices[i]);
        }
        pl.setClosed(true);
        return [pl];
    }
    else {
        var ret = [];
        for (i=0; i<vertices.length; ++i) {
            ret.push(new RLine(vertices[i], vertices[(i+1)%vertices.length]));
        }
        return ret;
    }
};
