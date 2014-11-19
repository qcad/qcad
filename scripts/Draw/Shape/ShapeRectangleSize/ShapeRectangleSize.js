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
 * \class ShapeRectangleSize
 * \brief Rectangle from point and size.
 * \ingroup ecma_draw_line
 */
function ShapeRectangleSize(guiAction) {
    Shape.call(this, guiAction);

    this.State = {
        SettingPosition : 0
    };

    this.setUiOptions(["../Shape.ui", "ShapeRectangleSize.ui"]);

    // note: these are not default (default are defined in the .ui file),
    // values are provided here to make this class functional from the start.
    this.pos = undefined;
    this.width = 1;
    this.height = 1;
    
    // [ObjectName], [Shown Text], offset vector
    this.rbReferencePoints = [
        [ "TopLeft", qsTr("Top Left"), new RVector(-1, 1) ],
        [ "Top", qsTr("Top"), new RVector(0, 1) ],
        [ "TopRight", qsTr("Top Right"), new RVector(1, 1) ],
        [ "Left", qsTr("Left"), new RVector(-1, 0) ],
        [ "Middle", qsTr("Middle"), new RVector(0, 0) ],
        [ "Right", qsTr("Right"), new RVector(1, 0) ],
        [ "BottomLeft", qsTr("Bottom Left"), new RVector(-1, -1) ],
        [ "Bottom", qsTr("Bottom"), new RVector(0, -1) ],
        [ "BottomRight", qsTr("Bottom Right"), new RVector(1, -1) ]
    ];
    this.referencePoint = this.rbReferencePoints[0][2]; 
}

ShapeRectangleSize.prototype = new Shape();

ShapeRectangleSize.prototype.showUiOptions = function(resume, restoreFromSettings) {
    debugger;
    Shape.prototype.showUiOptions.call(this, resume, restoreFromSettings);
    
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");

    for (var i=0; i<this.rbReferencePoints.length; i++) {
        refPointCombo.addItem(this.rbReferencePoints[i][1], this.rbReferencePoints[i][2]);
    }
};

ShapeRectangleSize.prototype.beginEvent = function() {
    Shape.prototype.beginEvent.call(this);
    this.setState(this.State.SettingPosition);
};

ShapeRectangleSize.prototype.setState = function(state) {
    Shape.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPosition = qsTr("Position");
    this.setCommandPrompt(trPosition);
    this.setLeftMouseTip(trPosition);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

ShapeRectangleSize.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();
    this.pos = event.getModelPosition();
    var op = this.getOperation(false);
    if (!isNull(op)) {
        di.applyOperation(op);
        di.setRelativeZero(this.pos);
    }
};

ShapeRectangleSize.prototype.coordinateEventPreview = function(event) {
    this.pos = event.getModelPosition();
    var op = this.getOperation(false);
    if (isNull(op)) {
        return;
    }
    this.getDocumentInterface().previewOperation(op);
};

ShapeRectangleSize.prototype.getOperation = function(preview) {
    var i;
    
    if (isNull(this.pos) || isNull(this.width) || isNull(this.height)) {
        return;
    }
    
    var x = this.pos.x;
    var y = this.pos.y;
    var w2 = this.width / 2;
    var h2 = this.height / 2;
    var corners = [
        new RVector(x - w2, y - h2),
        new RVector(x + w2, y - h2),
        new RVector(x + w2, y + h2),
        new RVector(x - w2, y + h2)
    ];
    // apply reference point vector
    for (i = 0; i < corners.length; ++i) {
        corners[i] = new RVector(
            corners[i].x - w2 * this.referencePoint.x,
            corners[i].y - h2 * this.referencePoint.y
        );
    }

    var op = new RAddObjectsOperation();

    var shapes = this.getShapes(corners);
    for (i=0; i<shapes.length; ++i) {
        var e = shapeToEntity(this.getDocument(), shapes[i]);
        if (isNull(e)) {
            continue;
        }
        op.addObject(e);
    }

    return op;
};

ShapeRectangleSize.prototype.slotWidthChanged = function(value) {
    this.width = value;
    this.updatePreview(true);
};

ShapeRectangleSize.prototype.slotHeightChanged = function(value) {
    this.height = value;
    this.updatePreview(true);
};

ShapeRectangleSize.prototype.slotReferencePointChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");

    this.referencePoint = refPointCombo.itemData(refPointCombo.currentIndex);

    this.updatePreview(true);
};

