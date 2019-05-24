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
 * \class ShapePolygonAFPP
 * \brief Polygon from two center points of two sides and number of edges.
 * \ingroup ecma_draw_shape
 */
function ShapePolygonAFPP(guiAction) {
    Shape.call(this, guiAction);
    this.corner1 = undefined;
    this.corner2 = undefined;
    this.cornerToCorner = false;

    this.setUiOptions(["../Shape.ui", "ShapePolygonAFPP.ui"]);
}

ShapePolygonAFPP.prototype = new Shape();

ShapePolygonAFPP.State = {
    SettingCorner1 : 0,
    SettingCorner2 : 1
};

ShapePolygonAFPP.prototype.beginEvent = function() {
    Shape.prototype.beginEvent.call(this);

    this.setState(ShapePolygonAFPP.State.SettingCorner1);
};

ShapePolygonAFPP.prototype.setState = function(state) {
    Shape.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ShapePolygonAFPP.State.SettingCorner1:
        var trCorner1 = qsTr("First side");
        if (this.cornerToCorner) {
            trCorner1 = qsTr("First Corner");
        }
        this.setCommandPrompt(trCorner1);
        this.setLeftMouseTip(trCorner1);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ShapePolygonAFPP.State.SettingCorner2:
        var trCorner2 = qsTr("Second side");
        if (this.cornerToCorner) {
            trCorner2 = qsTr("Second Corner");
        }
        this.setCommandPrompt(trCorner2);
        this.setLeftMouseTip(trCorner2);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    EAction.showSnapTools();
};

ShapePolygonAFPP.prototype.escapeEvent = function() {
    switch (this.state) {
    case ShapePolygonAFPP.State.SettingCorner1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case ShapePolygonAFPP.State.SettingCorner2:
        this.setState(ShapePolygonAFPP.State.SettingCorner1);
        break;
    }
};

ShapePolygonAFPP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case ShapePolygonAFPP.State.SettingCorner1:
        this.corner1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.corner1);
            //di.repaintViews();
            this.setState(ShapePolygonAFPP.State.SettingCorner2);
        }
        break;

    case ShapePolygonAFPP.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.corner2);
                this.setState(ShapePolygonAFPP.State.SettingCorner1);
            }
        }
        break;
    }
};

ShapePolygonAFPP.prototype.getOperation = function(preview) {
    if (isNull(this.corner1) || isNull(this.corner2)) {
        return undefined;
    }

    var corners = [];

    var angle = Math.PI/this.numberOfCorners;
    var dist = (this.corner1.getDistanceTo(this.corner2)) / 2.0;
    var opp = Math.tan(angle)*dist;
    var hyp = Math.sqrt((dist * dist) + (opp * opp));
    var cen = RVector.createPolar(dist, this.corner1.getAngleTo(this.corner2));
    var center = this.corner1.operator_add(cen);
    if (this.cornerToCorner) {
        var corner = this.corner2;
    } else {
        var v = RVector.createPolar(hyp, center.getAngleTo(this.corner1) + angle);
        corner = center.operator_add(v);
    }


    if ((this.numberOfCorners % 2) == 1) {
        // odd no. of corners
        var newdist = (dist / (dist + hyp)) * (dist * 2);
        var newopp = Math.tan(angle) * newdist;
        var newhyp = Math.sqrt((newdist * newdist) + (newopp * newopp));
        var newcen = RVector.createPolar(newdist, this.corner1.getAngleTo(this.corner2));
        var newcenter = this.corner1.operator_add(newcen);
        if (this.cornerToCorner) {
            newcenter = this.corner2.operator_subtract(newcen);
            v = RVector.createPolar(newhyp, newcenter.getAngleTo(this.corner1));
            corner = newcenter.operator_add(v);
        } else {
            v = RVector.createPolar(newhyp, newcenter.getAngleTo(this.corner1) + angle);
            corner = newcenter.operator_add(v);
        }
        center = newcenter;
    }


    for (var n=1; n<=this.numberOfCorners; ++n) {
        var c = corner.copy();
        c.rotate((Math.PI*2.0)/this.numberOfCorners*n, center);
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

ShapePolygonAFPP.prototype.slotCornersChanged = function(value) {
    this.numberOfCorners = value;
    this.updatePreview(true);
};

ShapePolygonAFPP.prototype.slotCornerToCornerChanged = function(checked) {
    this.cornerToCorner = checked;
    //Change prompt
    if (this.state >= 0) {
        this.setState(this.state);
    }
    this.updatePreview(true);
};
