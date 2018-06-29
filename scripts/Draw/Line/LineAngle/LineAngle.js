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

include("scripts/Draw/Line/Line.js");

/**
 * \class LineAngle
 * \brief Line from point and angle.
 * \ingroup ecma_draw_line
 */
function LineAngle(guiAction) {
    Line.call(this, guiAction);

    this.pos = undefined;
    this.angle = undefined;
    this.length = undefined;
    this.referencePoint = undefined;
    this.fixedAngle = false;

    if (!isNull(guiAction)) {
        this.setUiOptions(["../Line.ui", "LineAngle.ui"]);
    }
}

LineAngle.State = {
    SettingPosition : 0
};

LineAngle.ReferencePoint = {
    Start  : 0,
    Middle : 1,
    End    : 2
};

LineAngle.prototype = new Line();

LineAngle.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);
    this.setState(LineAngle.State.SettingPosition);
};

LineAngle.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    this.setCommandPrompt(qsTr("Position"));
    this.setLeftMouseTip(qsTr("Specify position"));
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();

    this.typeChanged();
};

LineAngle.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();
    this.pos = event.getModelPosition();
    di.setRelativeZero(this.pos);
    var op = this.getOperation(false);
    if (!isNull(op)) {
        di.applyOperation(op);
    }
};

LineAngle.prototype.coordinateEventPreview = function(event) {
    this.pos = event.getModelPosition();
    var op = this.getOperation(false);
    if (!isNull(op)) {
        this.getDocumentInterface().previewOperation(op);
    }
};

LineAngle.prototype.getOperation = function(preview) {
    if (isNull(this.pos) ||
        isNull(this.angle)) {
        return undefined;
    }

    var p1;
    var p2;

    // for rays / xlines, always use start point as reference
    // with length = 1.0:
    var referencePoint;
    var length;
    if (this.isRayOrXLine()) {
        referencePoint = LineAngle.ReferencePoint.Start;
        length = 1.0;
    }
    else {
        if (isNull(this.length) ||
            isNull(this.referencePoint)) {

            return undefined;
        }
        referencePoint = this.referencePoint;
        length = this.length;
    }

    switch (referencePoint) {
    case LineAngle.ReferencePoint.Start:
        p1 = this.pos;
        p2 = this.pos.operator_add(
            RVector.createPolar(+length, this.angle)
        );
        break;
    case LineAngle.ReferencePoint.Middle:
        p1 = this.pos.operator_add(
            RVector.createPolar(-length/2, this.angle)
        );
        p2 = this.pos.operator_add(
            RVector.createPolar(+length/2, this.angle)
        );
        break;
    case LineAngle.ReferencePoint.End:
        p1 = this.pos.operator_add(
            RVector.createPolar(-length, this.angle)
        );
        p2 = this.pos;
        break;
    default:
        return undefined;
    }

    var line = this.createLineEntity(this.getDocument(), p1, p2);
    if (isXLineEntity(line) && this.fixedAngle) {
        line.setFixedAngle(true);
    }
    return new RAddObjectOperation(line, this.getToolTitle());
};

LineAngle.prototype.slotAngleChanged = function(value) {
    this.angle = value;
    this.updatePreview(true);
};

LineAngle.prototype.slotLengthChanged = function(value) {
    this.length = value;
    this.updatePreview(true);
};

LineAngle.prototype.slotReferencePointChanged = function(value) {
    this.referencePoint = value;
    this.updatePreview(true);
};

LineAngle.prototype.typeChanged = function() {
    var optionsToolBar = EAction.getOptionsToolBar();

    var ws = ["LengthLabel", "Length", "ReferencePointLabel", "ReferencePoint"];
    for (var i=0; i<ws.length; i++) {
        var w = optionsToolBar.findChild(ws[i]);
        if (!isNull(w)) {
            w.enabled = !this.isRayOrXLine();
        }
    }
};
