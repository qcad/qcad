/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
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

    return [
        new RVector(this.corner1.x, this.corner1.y),
        new RVector(this.corner2.x, this.corner1.y),
        new RVector(this.corner2.x, this.corner2.y),
        new RVector(this.corner1.x, this.corner2.y)
    ];
};

DrawBasedOnRectanglePP.prototype.getCenter = function() {
    return RVector.getAverage(this.corner1, this.corner2);
};

DrawBasedOnRectanglePP.prototype.getWidth = function() {
    return Math.abs(this.corner1.x-this.corner2.x);
};

DrawBasedOnRectanglePP.prototype.getHeight = function() {
    return Math.abs(this.corner1.y-this.corner2.y);
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
