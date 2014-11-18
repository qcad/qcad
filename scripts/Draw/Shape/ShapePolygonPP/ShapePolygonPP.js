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

include("../Shape.js");

/**
 * \class ShapePolygonPP
 * \brief Polygon from two corner points and number of edges.
 * \ingroup ecma_draw_line
 */
function ShapePolygonPP(guiAction) {
    Shape.call(this, guiAction);

    this.corner1 = undefined;
    this.corner2 = undefined;

    this.setUiOptions("ShapePolygonPP.ui");
}

ShapePolygonPP.prototype = new Shape();

ShapePolygonPP.State = {
    SettingCorner1 : 0,
    SettingCorner2 : 1
};

ShapePolygonPP.prototype.beginEvent = function() {
    Shape.prototype.beginEvent.call(this);

    this.setState(ShapePolygonPP.State.SettingCorner1);
};

ShapePolygonPP.prototype.setState = function(state) {
    Shape.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ShapePolygonPP.State.SettingCorner1:
        var trCorner1 = qsTr("First corner");
        this.setCommandPrompt(trCorner1);
        this.setLeftMouseTip(trCorner1);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ShapePolygonPP.State.SettingCorner2:
        var trCorner2 = qsTr("Corner point");
        this.setCommandPrompt(trCorner2);
        this.setLeftMouseTip(trCorner2);
        this.setRightMouseTip(qsTr("Done"));
        break;
    }

    EAction.showSnapTools();
};

ShapePolygonPP.prototype.escapeEvent = function() {
    switch (this.state) {
    case ShapePolygonPP.State.SettingCorner1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case ShapePolygonPP.State.SettingCorner2:
        this.setState(ShapePolygonPP.State.SettingCorner1);
        break;
    }
};

ShapePolygonPP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case ShapePolygonPP.State.SettingCorner1:
        this.corner1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.corner1);
            //di.repaintViews();
            this.setState(ShapePolygonPP.State.SettingCorner2);
        }
        break;

    case ShapePolygonPP.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.corner2);
                this.setState(ShapePolygonPP.State.SettingCorner1);
            }
        }
        break;
    }
};

ShapePolygonPP.prototype.getOperation = function(preview) {
    if (isNull(this.corner1) || isNull(this.corner2)) {
        return undefined;
    }

    var c1;
    var c2 = this.corner1;

    var len = this.corner1.getDistanceTo(this.corner2);
    var ang1 = this.corner1.getAngleTo(this.corner2);
    var ang = ang1;

    var op = new RAddObjectsOperation();
    for (var n=1; n<=this.numberOfCorners; ++n) {
        c1 = c2.copy();
        var edge = new RVector();
        edge.setPolar(len, ang);
        c2 = c1.operator_add(edge);

        var line = new RLineEntity(
            this.getDocument(),
            new RLineData(c1, c2)
        );

        op.addObject(line);

        // more accurate than incrementing the angle:
        ang = ang1 + (2*Math.PI)/this.numberOfCorners * n;
    }

    return op;
};

ShapePolygonPP.prototype.slotCornersChanged = function(value) {
    this.numberOfCorners = value;
    this.updatePreview(true);
};

