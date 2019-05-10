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
 * \defgroup ecma_draw_shape Shape Drawing Tools
 * \ingroup ecma_draw
 *
 * \brief This module contains ECMAScript implementations of various
 * shape drawing tools.
 */
include("scripts/Draw/Draw.js");
include("scripts/Modify/Round/Round.js");

/**
 * \class Shape
 * \brief Base class for all shape drawing tools.
 * \ingroup ecma_draw_shape
 */
function Shape(guiAction) {
    Draw.call(this, guiAction);

    this.createPolyline = false;
    this.fill = false;
    this.roundCorners = false;
    this.radius = 1.0;
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
        //action.setStatusTip(qsTr("Show shape tools"));
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

Shape.getToolMatrixPanel = function() {
    return EAction.getToolMatrixPanel(Shape.getTitle(), "ShapeMatrixPanel", 800);
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
    Shape.getToolMatrixPanel();
};

Shape.prototype.initUiOptions = function(resume, optionsToolBar) {
    Draw.prototype.initUiOptions.call(this, resume, optionsToolBar);

    this.createPolyline = RSettings.getBoolValue(this.settingsGroup + "/CreatePolyline", false);
    this.fill = RSettings.getBoolValue(this.settingsGroup + "/Fill", false);
    this.roundCorners = RSettings.getBoolValue(this.settingsGroup + "/RoundCorners", false);
    this.radius = RSettings.getDoubleValue(this.settingsGroup + "/Radius", 1.0);

    var w = optionsToolBar.findChild("CreatePolyline");
    if (!isNull(w)) {
        w.checked = this.createPolyline;
    }

    w = optionsToolBar.findChild("Fill");
    if (!isNull(w)) {
        w.checked = this.fill;
    }

    w = optionsToolBar.findChild("RoundCorners");
    if (!isNull(w)) {
        w.checked = this.roundCorners;
    }

    w = optionsToolBar.findChild("Radius");
    if (!isNull(w)) {
        w.setValue(this.radius);
    }
};

Shape.prototype.hideUiOptions = function(saveToSettings) {
    Draw.prototype.hideUiOptions.call(this, saveToSettings);

    RSettings.setValue(this.settingsGroup + "/CreatePolyline", this.createPolyline);
    RSettings.setValue(this.settingsGroup + "/Fill", this.fill);
    RSettings.setValue(this.settingsGroup + "/RoundCorners", this.roundCorners);
    RSettings.setValue(this.settingsGroup + "/Radius", this.radius);
};

Shape.prototype.slotCreatePolylineChanged = function(checked) {
    Shape.slotCreatePolylineChanged(this, checked);
};

Shape.slotCreatePolylineChanged = function(action, checked) {
    action.createPolyline = checked;
    action.updatePreview(true);
};

Shape.prototype.slotFillChanged = function(checked) {
    Shape.slotFillChanged(this, checked);
};

Shape.slotFillChanged = function(action, checked) {
    action.fill = checked;
    action.updatePreview(true);
};

Shape.prototype.slotRoundCornersChanged = function(checked) {
    Shape.slotRoundCornersChanged(this, checked);
};

Shape.slotRoundCornersChanged = function(action, checked) {
    action.roundCorners = checked;
    action.updatePreview(true);
};

Shape.prototype.slotRadiusChanged = function(v) {
    Shape.slotRadiusChanged(this, v);
};

Shape.slotRadiusChanged = function(action, v) {
    action.radius = v;
    action.updatePreview(true);
};

Shape.prototype.getShapes = function(vertices) {
    return Shape.getShapes(this, vertices);
};

Shape.getShapes = function(action, vertices) {
    var i;
    var shapes = [];

    for (i=0; i<vertices.length; ++i) {
        shapes.push(new RLine(vertices[i], vertices[(i+1)%vertices.length]));
    }

    if (action.roundCorners===true && isNumberGreaterZero(action.radius)) {
        var newShapes = [];
        var cursor = undefined;
        for (i=0; i<shapes.length; ++i) {
            var s1 = shapes[i];
            var clickPos1 = s1.getPointWithDistanceToEnd(s1.getLength()/3);
            var s2 = shapes[(i+1)%shapes.length];
            var clickPos2 = s2.getPointWithDistanceToStart(s2.getLength()/3);
            var pos = RVector.getAverage(clickPos1, clickPos2);
            var res = RShape.roundShapes(s1, clickPos1, s2, clickPos2, true, false, action.radius, pos);
            if (res.length>2) {
                if (!isNull(cursor)) {
                    newShapes.push(new RLine(cursor, res[1].getStartPoint()));
                }
                newShapes.push(res[1].clone());
                cursor = res[1].getEndPoint();
            }
        }
        if (newShapes.length>0) {
            newShapes.unshift(new RLine(newShapes[newShapes.length-1].getEndPoint(), newShapes[0].getStartPoint()));
        }
        shapes = newShapes;
    }

    if (action.createPolyline===true) {
        var pl = new RPolyline();
        for (i=0; i<shapes.length; ++i) {
            pl.appendShape(shapes[i]);
        }
        pl.autoClose();
        return [pl];
    }
    else {
        return shapes;
    }
};

Shape.prototype.complementOperation = function(op, shapes) {
    Shape.complementOperation(this, this.getDocument(), op, shapes);
};

Shape.complementOperation = function(action, doc, op, shapes) {
    if (action.fill) {
        var hatchData = new RHatchData();
        hatchData.setDocument(doc);
        hatchData.setAngle(0.0);
        hatchData.setScale(1.0);
        hatchData.setSolid(true);
        hatchData.setPatternName("SOLID");
        hatchData.newLoop();
        for (var k=0; k<shapes.length; ++k) {
            hatchData.addBoundary(shapes[k]);
        }
        op.addObject(new RHatchEntity(doc, hatchData));
    }
};
