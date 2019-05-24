/**
 * Modifications Copyright (c) 2015 by Robert S.
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
 * \class ShapePolygonAFCP
 * \brief Polygon with center, center point of flat edge and number of edges.
 * \ingroup ecma_draw_shape
 */
function ShapePolygonAFCP(guiAction) {
    Shape.call(this, guiAction);

    this.center = undefined;
    this.middleOfSide = undefined;

    this.setUiOptions(["../Shape.ui", "ShapePolygonAFCP.ui"]);
}

ShapePolygonAFCP.prototype = new Shape();

ShapePolygonAFCP.State = {
    SettingCenter : 0,
    SettingCorner : 1
};

ShapePolygonAFCP.prototype.beginEvent = function() {
    Shape.prototype.beginEvent.call(this);

    this.setState(ShapePolygonAFCP.State.SettingCenter);
};

ShapePolygonAFCP.prototype.setState = function(state) {
    Shape.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ShapePolygonAFCP.State.SettingCenter:
        this.center = undefined;
        this.middleOfSide = undefined;
        var trCenter = qsTr("Center");
        this.setCommandPrompt(trCenter);
        this.setLeftMouseTip(trCenter);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ShapePolygonAFCP.State.SettingCorner:
        this.middleOfSide = undefined;
        var trMiddlePoint = qsTr("Middle of Side");
        this.setCommandPrompt(trMiddlePoint);
        this.setLeftMouseTip(trMiddlePoint);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    EAction.showSnapTools();
};

ShapePolygonAFCP.prototype.escapeEvent = function() {
    switch (this.state) {
    case ShapePolygonAFCP.State.SettingCenter:
        EAction.prototype.escapeEvent.call(this);
        break;

    case ShapePolygonAFCP.State.SettingCorner:
        this.setState(ShapePolygonAFCP.State.SettingCenter);
        break;
    }
};

ShapePolygonAFCP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case ShapePolygonAFCP.State.SettingCenter:
        if (!preview) {
            this.center = event.getModelPosition();
            di.setRelativeZero(this.center);
            //di.repaintViews();
            this.setState(ShapePolygonAFCP.State.SettingCorner);
        }
        break;

    case ShapePolygonAFCP.State.SettingCorner:
        this.middleOfSide = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.middleOfSide);
                this.setState(ShapePolygonAFCP.State.SettingCenter);
            }
        }
        break;
    }
};

ShapePolygonAFCP.prototype.getOperation = function(preview) {
    if (isNull(this.center) || isNull(this.middleOfSide)) {
        return undefined;
    }

    var corners = [];

    var angle = Math.PI/this.numberOfCorners;
    var dist = this.center.getDistanceTo(this.middleOfSide);
    var opp = Math.tan(angle)*dist;
    var hyp = Math.sqrt((dist * dist) + (opp * opp));
    var v = RVector.createPolar(hyp, this.center.getAngleTo(this.middleOfSide) + angle);
    var corner = this.center.operator_add(v);

    for (var n=1; n<=this.numberOfCorners; ++n) {
        var c = corner.copy();
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

ShapePolygonAFCP.prototype.getAuxPreview = function() {
    if (isNull(this.center) || isNull(this.middleOfSide)) {
        return undefined;
    }

    return [ new RCircle(this.center, this.center.getDistanceTo(this.middleOfSide)) ];
};

ShapePolygonAFCP.prototype.slotCornersChanged = function(value) {
    this.numberOfCorners = value;
    this.updatePreview(true);
};
