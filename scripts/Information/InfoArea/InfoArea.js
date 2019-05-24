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

include("scripts/Information/Information.js");

/**
 * \class InfoArea
 * \ingroup ecma_information
 * \brief Measure area.
 */
function InfoArea(guiAction) {
    Information.call(this, guiAction);
    this.polyline = undefined;

    this.setUiOptions("../Information.ui");
}

InfoArea.prototype = new Information();

InfoArea.State = {
    SettingPoint : 0,
    Done : 1
};

InfoArea.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.reset();
};

InfoArea.prototype.escapeEvent = function() {
    switch (this.state) {
    case InfoArea.State.SettingPoint:
        this.slotCalculate();
        break;
    case InfoArea.State.Done:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

InfoArea.prototype.reset = function() {
    this.polyline = new RPolyline();
    this.polyline.setClosed(true);
    this.setState(InfoArea.State.SettingPoint);
};

InfoArea.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    di.setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var trSelectPoint = qsTr("Set next polygon corner");
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case InfoArea.State.SettingPoint:
        this.setCommandPrompt(trSelectPoint);
        this.setLeftMouseTip(trSelectPoint);
        this.setRightMouseTip(EAction.trDone);
        break;
    case InfoArea.State.Done:
        this.setCommandPrompt(trSelectPoint);
        this.setLeftMouseTip(trSelectPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

    EAction.showSnapTools();
};

InfoArea.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var pos = event.getModelPosition();

    switch (this.state) {
    case InfoArea.State.Done:
        if (!preview) {
            this.reset();
        }
        this.updatePreview();
        if (preview) {
            break;
        }
    case InfoArea.State.SettingPoint:
        this.point1 = pos;
        this.polyline.appendVertex(pos);
        if (!preview) {
            di.setRelativeZero(pos);
        }
        if (preview) {
            this.updatePreview();
            this.polyline.removeLastVertex();
        }
        break;
    }
};

InfoArea.prototype.getOperation = function(preview) {
    if (isNull(this.polyline)) {
        return undefined;
    }

    var di = this.getDocumentInterface();
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    this.addShape(op, this.polyline, preview);

    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();
    var areaText = this.getAreaText();
    view.clearTextLabels();
    var c = this.polyline.getLastVertex();
    if (c.isValid()) {
        this.addTextLabel(op, view, c, areaText, preview);
    }

    return op;
};

InfoArea.prototype.getAreaText = function(rounded) {
    return this.formatAreaResult(this.getArea(), rounded);
};

InfoArea.prototype.getArea = function() {
    var pts = this.polyline.getVertices();
    var area = 0;
    var nPts = pts.length;
    var j = nPts - 1;
    var p1;
    var p2;

    for (var i = 0; i < nPts; j = i++) {
        p1 = pts[i];
        p2 = pts[j];
        area += p1.x * p2.y;
        area -= p1.y * p2.x;
    }
    area /= 2;
    return Math.abs(area);
};

InfoArea.prototype.getCircumference = function() {
    var pts = this.polyline.getVertices();
    var circ = 0;
    var nPts = pts.length;
    var j = nPts - 1;
    var p1;
    var p2;

    for (var i = 0; i < nPts; j = i++) {
        p1 = pts[i];
        p2 = pts[j];
        circ += p1.getDistanceTo(p2);
    }
    return circ;
};

InfoArea.prototype.getCenter = function() {
    var pts = this.polyline.getVertices();
    var nPts = pts.length;
    var x = 0;
    var y = 0;
    var f;
    var j = nPts - 1;
    var p1;
    var p2;

    for (var i = 0; i < nPts; j = i++) {
        p1 = pts[i];
        p2 = pts[j];
        f = p1.x * p2.y - p2.x * p1.y;
        x += (p1.x + p2.x) * f;
        y += (p1.y + p2.y) * f;
    }

    f = this.getArea() * 6;

    return new RVector(x / f, y / f);
};

InfoArea.prototype.slotCalculate = function() {
    var di = this.getDocumentInterface();
    var doc = di.getDocument();

    if (isNull(this.polyline) || this.polyline.countVertices()===0) {
        this.polyline = undefined;
        this.setState(InfoArea.State.Done);
//        di.clearPreview();
//        di.regenerateViews();
//        di.repaintViews();
        return;
    }

    var areaText = this.getAreaText();

    var info = qsTr("Polygon area:") + " " + areaText +
            ", " + qsTr("circumference:") + " " + this.getCircumference();

    if (this.addToDrawing) {
        //var di = this.getDocumentInterface();
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
        }
        this.polyline = undefined;
    }

    this.setState(InfoArea.State.Done);
    di.clearPreview();
    this.updatePreview();
    di.regenerateViews();
    di.repaintViews();

    EAction.getMainWindow().handleUserInfo(info);
};
