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

include("Draw.js");

/**
 * \class DrawBasedOnRectanglePP
 * 
 * \brief Base class for drawing tools that draw something based on 
 * a rectangular shape with given width, height and angle. The tool
 * also supports reference points at the corners, top, left, right, 
 * bottom and middle.
 * 
 * \ingroup ecma_draw
 */
function DrawBasedOnRectanglePP(guiAction) {
    EAction.call(this, guiAction);

    this.corner1 = undefined;
    this.corner2 = undefined;
    this.rotation = 0.0;
    this.previewRectangle = false;
}

DrawBasedOnRectanglePP.prototype = new EAction();
DrawBasedOnRectanglePP.includeBasePath = includeBasePath;

DrawBasedOnRectanglePP.State = {
    SettingCorner1 : 0,
    SettingCorner2 : 1
};

DrawBasedOnRectanglePP.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(DrawBasedOnRectanglePP.State.SettingCorner1);
};

DrawBasedOnRectanglePP.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    var di = this.getDocumentInterface();
    if (isNull(di)) {
        return;
    }

    di.setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case DrawBasedOnRectanglePP.State.SettingCorner1:
        var trFirstCorner = qsTr("First corner");
        this.setCommandPrompt(trFirstCorner);
        this.setLeftMouseTip(trFirstCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case DrawBasedOnRectanglePP.State.SettingCorner2:
        var trSecondCorner = qsTr("Second corner");
        this.setCommandPrompt(trSecondCorner);
        this.setLeftMouseTip(trSecondCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

DrawBasedOnRectanglePP.prototype.escapeEvent = function() {
    switch (this.state) {
    case DrawBasedOnRectanglePP.State.SettingCorner1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DrawBasedOnRectanglePP.State.SettingCorner2:
        this.setState(DrawBasedOnRectanglePP.State.SettingCorner1);
        break;
    }
};

DrawBasedOnRectanglePP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case DrawBasedOnRectanglePP.State.SettingCorner1:
        this.corner1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.corner1);
            this.setState(DrawBasedOnRectanglePP.State.SettingCorner2);
        }
        break;

    case DrawBasedOnRectanglePP.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.corner2);
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(DrawBasedOnRectanglePP.State.SettingCorner1);
            }
        }
        break;
    }
};

DrawBasedOnRectanglePP.prototype.getCorners = function() {
    if (isNull(this.corner1) || isNull(this.corner2)) {
        return [];
    }

    if (RMath.fuzzyCompare(this.rotation, 0.0)) {
        return [
            new RVector(this.corner1.x, this.corner1.y),
            new RVector(this.corner2.x, this.corner1.y),
            new RVector(this.corner2.x, this.corner2.y),
            new RVector(this.corner1.x, this.corner2.y)
        ];
    }
    else {
        var l1 = new RLine(this.corner1, this.rotation, 1.0);
        var l2 = new RLine(this.corner2, this.rotation + Math.PI/2, 1.0);
        var ips = RShape.getIntersectionPointsLL(l1, l2, false);
        if (ips.length!==1) {
            return [];
        }
        var c3 = ips[0];
        var v = this.corner1.operator_subtract(c3);
        var c4 = this.corner2.operator_add(v);
        return [ this.corner1, c3, this.corner2, c4 ];
    }
};

DrawBasedOnRectanglePP.prototype.getCenter = function() {
    return RVector.getAverage(this.corner1, this.corner2);
};

DrawBasedOnRectanglePP.prototype.getWidth = function() {
    if (RMath.fuzzyCompare(this.rotation, 0.0)) {
        return Math.abs(this.corner1.x-this.corner2.x);
    }
    else {
        var c = this.getCorners();
        return c[0].getDistanceTo(c[1]);
    }
};

DrawBasedOnRectanglePP.prototype.getHeight = function() {
    if (RMath.fuzzyCompare(this.rotation, 0.0)) {
        return Math.abs(this.corner1.y-this.corner2.y);
    }
    else {
        var c = this.getCorners();
        return c[1].getDistanceTo(c[2]);
    }
};

DrawBasedOnRectanglePP.prototype.getAuxPreview = function() {
    if (this.previewRectangle!==true) {
        return undefined;
    }

    var shapes = [];
    var corners = this.getCorners();
    for (var i=0; i<corners.length; ++i) {
        shapes.push(new RLine(corners[i], corners[(i+1)%corners.length]));
    }
    return shapes;
};
