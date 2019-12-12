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

include("../Shape.js");

/**
 * \class ShapePolygonCP
 * \brief Polygon with center, corner point and number of edges.
 * \ingroup ecma_draw_shape
 */
function ShapePolygonCP(guiAction) {
    Shape.call(this, guiAction);

    this.numberOfCorners = undefined;
    this.center = undefined;
    this.corner = undefined;

    this.setUiOptions(["../Shape.ui", "ShapePolygonCP.ui"]);
}

ShapePolygonCP.prototype = new Shape();

ShapePolygonCP.State = {
    SettingCenter : 0,
    SettingCorner : 1
};

ShapePolygonCP.prototype.beginEvent = function() {
    Shape.prototype.beginEvent.call(this);

    this.setState(ShapePolygonCP.State.SettingCenter);
};

ShapePolygonCP.prototype.setState = function(state) {
    Shape.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ShapePolygonCP.State.SettingCenter:
        var trCenter = qsTr("Center");
        this.setCommandPrompt(trCenter);
        this.setLeftMouseTip(trCenter);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ShapePolygonCP.State.SettingCorner:
        var trCornerPoint = qsTr("Corner point");
        this.setCommandPrompt(trCornerPoint);
        this.setLeftMouseTip(trCornerPoint);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    EAction.showSnapTools();
};

ShapePolygonCP.prototype.escapeEvent = function() {
    switch (this.state) {
    case ShapePolygonCP.State.SettingCenter:
        EAction.prototype.escapeEvent.call(this);
        break;

    case ShapePolygonCP.State.SettingCorner:
        this.setState(ShapePolygonCP.State.SettingCenter);
        break;
    }
};

ShapePolygonCP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case ShapePolygonCP.State.SettingCenter:
        if (!preview) {
            this.center = event.getModelPosition();
            di.setRelativeZero(this.center);
            //di.repaintViews();
            this.setState(ShapePolygonCP.State.SettingCorner);
        }
        break;

    case ShapePolygonCP.State.SettingCorner:
        this.corner = event.getModelPosition();
        if (preview) {
            this.updatePreview();
            //di.previewOperation();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.corner);
                this.setState(ShapePolygonCP.State.SettingCenter);
            }
        }
        break;
    }
};

ShapePolygonCP.prototype.getOperation = function(preview) {
    if (isNull(this.center) || isNull(this.corner)) {
        return undefined;
    }

    var corners = [];

    for (var n=1; n<=this.numberOfCorners; ++n) {
        var c = this.corner.copy();
        c.rotate((Math.PI*2.0)/this.numberOfCorners*n, this.center);
        corners.push(c);
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var shapes = this.getShapes(corners);
    for (var i=0; i<shapes.length; ++i) {
        var e = shapeToEntity(this.getDocument(), shapes[i]);
        if (isNull(e)) {
            continue;
        }
        op.addObject(e);
    }

    this.complementOperation(op, shapes);

    return op;
};

ShapePolygonCP.prototype.slotCornersChanged = function(value) {
    this.numberOfCorners = value;
    this.updatePreview(true);
};

