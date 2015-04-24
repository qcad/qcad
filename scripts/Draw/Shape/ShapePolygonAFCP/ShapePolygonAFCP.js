/**
 * Modifications Copyright (c) 2015 by Robert S.
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

include("../Shape.js");

/**
 * \class ShapePolygonAFCP
 * \brief Polygon with center, center point of flat edge and number of edges.
 * \ingroup ecma_draw_shape
 */
function ShapePolygonAFCP(guiAction) {
    Shape.call(this, guiAction);

    this.center = undefined;
    this.corner = undefined;
    this.inside = false;

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
        this.corner = undefined;
        var trCenter = qsTr("Center");
        this.setCommandPrompt(trCenter);
        this.setLeftMouseTip(trCenter);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ShapePolygonAFCP.State.SettingCorner:
        this.corner = undefined;
        var trCornerPoint = qsTr("Side");
        if (this.inside) {
            trCornerPoint = qsTr("Corner");
        }
        this.setCommandPrompt(trCornerPoint);
        this.setLeftMouseTip(trCornerPoint);
        this.setRightMouseTip(qsTr("Done"));
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
        this.corner = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.corner);
                this.setState(ShapePolygonAFCP.State.SettingCenter);
            }
        }
        break;
    }
};

ShapePolygonAFCP.prototype.getOperation = function(preview) {
    if (isNull(this.center) || isNull(this.corner)) {
        return undefined;
    }

    var corners = [];

    var angle = Math.PI/this.numberOfCorners;
    var dist = this.center.getDistanceTo(this.corner);
    var opp = Math.tan(angle)*dist;
    var hyp = Math.sqrt((dist * dist) + (opp * opp));
    if (this.inside) {
        var corner = this.corner;
    } else {
        var v = RVector.createPolar(hyp, this.center.getAngleTo(this.corner) + angle);
        corner = this.center.operator_add(v);
    }

//    if ((this.numberOfCorners % 2) == 1) {
//        // odd no. of corners
//        var newdist = (dist / (dist + hyp)) * (dist * 2);
//        var newopp = Math.tan(angle) * newdist;
//        var newhyp = Math.sqrt((newdist * newdist) + (newopp * newopp));
//        if (this.inside) {
//            v = RVector.createPolar(newhyp, this.center.getAngleTo(this.corner));
//            corner = this.center.operator_add(v);
//        } else {
//            v = RVector.createPolar(newhyp, this.center.getAngleTo(this.corner) + angle);
//            corner = this.center.operator_add(v);
//        }
//    }

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

    return op;
};

ShapePolygonAFCP.prototype.slotCornersChanged = function(value) {
    this.numberOfCorners = value;
    this.updatePreview(true);
};

ShapePolygonAFCP.prototype.slotInsideChanged = function(checked) {
    this.inside = checked;
    //Change prompt
    if (this.state >= 0) {
        this.setState(this.state);
    }
    this.updatePreview(true);
};
