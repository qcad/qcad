/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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
 * \class DrawBasedOnRectangle
 * 
 * \brief Base class for drawing tools that draw something based on 
 * a rectangular shape with given width, height and angle. The tool
 * also supports reference points at the corners, top, left, right, 
 * bottom and middle.
 * 
 * \ingroup ecma_misc_draw
 */
function DrawBasedOnRectangle(guiAction) {
    EAction.call(this, guiAction);

    this.pos = undefined;
    this.width = 1;
    this.height = 1;
    this.angle = 0;
    this.corners = [];
    
    // [ObjectName], [Shown Text], offset vector
    this.rbReferencePoints = [
        [ "TopLeft",     qsTr("Top Left"),     new RVector(-1,  1) ],
        [ "Top",         qsTr("Top"),          new RVector( 0,  1) ],
        [ "TopRight",    qsTr("Top Right"),    new RVector( 1,  1) ],
        [ "Left",        qsTr("Left"),         new RVector(-1,  0) ],
        [ "Middle",      qsTr("Middle"),       new RVector( 0,  0) ],
        [ "Right",       qsTr("Right"),        new RVector( 1,  0) ],
        [ "BottomLeft",  qsTr("Bottom Left"),  new RVector(-1, -1) ],
        [ "Bottom",      qsTr("Bottom"),       new RVector( 0, -1) ],
        [ "BottomRight", qsTr("Bottom Right"), new RVector( 1, -1) ]
    ];
    this.referencePoint = this.rbReferencePoints[0][2];
}

DrawBasedOnRectangle.prototype = new EAction();

DrawBasedOnRectangle.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);
    this.setState(0);
};

DrawBasedOnRectangle.prototype.showUiOptions = function(resume, restoreFromSettings) {
    EAction.prototype.showUiOptions.call(this, resume, restoreFromSettings);
    
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");
    var shortcuts = [];

    for (var i=0; i<this.rbReferencePoints.length; i++) {
        var str = "%1".arg(i+1);
        refPointCombo.addItem(
            "[" + str + "] " + this.rbReferencePoints[i][1],
            this.rbReferencePoints[i][2]
        );
        shortcuts[i] = new QShortcut(new QKeySequence(str), refPointCombo, 0, 0, Qt.WindowShortcut);
        shortcuts[i].activated.connect(new KeyReactor(i), "activated");
    }

};

DrawBasedOnRectangle.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPosition = qsTr("Position");
    this.setCommandPrompt(trPosition);
    this.setLeftMouseTip(trPosition);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

DrawBasedOnRectangle.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    this.pos = event.getModelPosition();

    if (preview) {
        this.updatePreview();
    }
    else {
        var op = this.getOperation(preview);
        if (!isNull(op)) {
            di.applyOperation(op);
            di.setRelativeZero(this.pos);
        }
    }
};

DrawBasedOnRectangle.prototype.getOperation = function(preview) {
    var i;
    
    if (isNull(this.pos) || isNull(this.width) || isNull(this.height) || isNull(this.angle)) {
        return;
    }
    
    var x = this.pos.x;
    var y = this.pos.y;
    var w2 = this.width / 2;
    var h2 = this.height / 2;

    // create corners (centered)
    this.corners = [
        new RVector(x - w2, y - h2),
        new RVector(x + w2, y - h2),
        new RVector(x + w2, y + h2),
        new RVector(x - w2, y + h2)
    ];
    // apply reference point vector
    for (i = 0; i < this.corners.length; ++i) {
        this.corners[i] = new RVector(
            this.corners[i].x - w2 * this.referencePoint.x,
            this.corners[i].y - h2 * this.referencePoint.y
        );
    }
    // apply angle:
    if (this.angle!==0.0) {
        for (i = 0; i < this.corners.length; ++i) {
            this.corners[i].rotate(this.angle, this.pos);
        }
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var shapes = this.getShapes(this.corners);
    for (i=0; i<shapes.length; ++i) {
        var e = shapeToEntity(this.getDocument(), shapes[i]);
        if (isNull(e)) {
            continue;
        }
        op.addObject(e);
    }

    return op;
};

DrawBasedOnRectangle.prototype.getShapes = function(corners) {
    return [];
};

DrawBasedOnRectangle.prototype.slotWidthChanged = function(value) {
    this.width = value;
    this.updatePreview(true);
};

DrawBasedOnRectangle.prototype.slotHeightChanged = function(value) {
    this.height = value;
    this.updatePreview(true);
};

DrawBasedOnRectangle.prototype.slotAngleChanged = function(value) {
    this.angle = value;
    this.updatePreview(true);
};

DrawBasedOnRectangle.prototype.slotReferencePointChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");

    this.referencePoint = refPointCombo.itemData(refPointCombo.currentIndex);

    this.updatePreview(true);
};



/**
 * Reacts to an assigned shortcut for the given index of the reference point combo box.
 */
function KeyReactor(i) {
    this.i = i;
}

KeyReactor.prototype.activated = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    var refPointCombo = optionsToolBar.findChild("ReferencePoint");
    refPointCombo.currentIndex = this.i;
};
