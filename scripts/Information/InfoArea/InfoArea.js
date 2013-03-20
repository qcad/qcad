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

include("../Information.js");

function InfoArea(guiAction) {
    Information.call(this, guiAction);
    //this.setUiOptions("InfoArea.ui");
    this.polyline = undefined;
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
        this.setRightMouseTip(qsTr("Done"));
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
        //this.setState(InfoArea.State.SettingPoint);
        this.updatePreview();
        if (preview) {
            this.polyline.removeLastVertex();
        }
        break;
    }
};

InfoArea.prototype.updatePreview = function() {
    var di = this.getDocumentInterface();
    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();

    // polygon
    this.addShape(this.polyline);

    // label
    var area = this.getArea();
    var label = sprintf("%0.3f", area);
    view.clearTextLabels();

    // center calculation is off sometimes:
    //var c = this.getCenter();

    var c = this.polyline.getLastVertex();
    var dx = view.mapDistanceFromView(10);
    var dy = view.mapDistanceFromView(30);
    view.addTextLabel(new RTextLabel(new RVector(c.x+dx, c.y+dy), label));
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

    EAction.getMainWindow().handleUserInfo(
            qsTr("Polygon area:") + " " + this.getArea() +
            ", " + qsTr("circumference:") + " " + this.getCircumference());
    this.setState(InfoArea.State.Done);
    di.clearPreview();
    this.updatePreview();
    di.regenerateViews();
    di.repaintViews();
};

//InfoArea.prototype.slotClose = function() {
//    this.terminate();
//};

