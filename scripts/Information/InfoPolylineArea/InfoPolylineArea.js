/**
 * Copyright (c) 2016 by Robert S. All rights reserved.
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
 * \class InfoPolylineArea
 * \ingroup ecma_information
 * \brief Measure area of polyline.
 */
function InfoPolylineArea(guiAction) {
    Information.call(this, guiAction);
    this.polyline = undefined;
    this.shape = undefined

    this.setUiOptions("../Information.ui");
}

InfoPolylineArea.prototype = new Information();

InfoPolylineArea.State = {
    ChoosingPolyline : 0
};

InfoPolylineArea.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.setState(InfoPolylineArea.State.ChoosingPolyline);
};

InfoPolylineArea.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    di.setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var trSelectPolyline = qsTr("Choose polyline");
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case InfoPolylineArea.State.ChoosingPolyline:
        this.setCommandPrompt(trSelectPolyline);
        this.setLeftMouseTip(trSelectPolyline);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    EAction.showSnapTools();
};

InfoPolylineArea.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);

    if (isNull(entity)) {
        this.polyline = undefined;
        return;
    } else {
        this.polyline = entity;
    }
    this.shape = this.polyline.getData().castToShape();

    if (!preview) {
        this.slotCalculate();
    }
    else {
        this.updatePreview();
    }
};

InfoPolylineArea.prototype.getOperation = function(preview) {
    if (isNull(this.polyline) || isNull(this.shape)) {
        return undefined;
    }

    var di = this.getDocumentInterface();
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var view = di.getLastKnownViewWithFocus();
    view = view.getRGraphicsView();
    var area = this.getArea();
    area = area.toFixed(6);
    var circ = this.getCircumference();
    circ = circ.toFixed(6);

    var label1 = qsTr("Area") + " = " + this.formatAreaResult(area, true);;
    var label2 = qsTr("Circumference") + " = " + circ;
    view.clearTextLabels();
    var c = this.shape.getLastVertex();
    if (c.isValid()) {
        this.addTextLabel(op, view, c, label2, preview);
        var v;
        if (preview) {
            var font = RSettings.getInfoLabelFont();
            font.setPointSizeF(font.pointSizeF()*view.getDevicePixelRatio());
            var fm = new QFontMetrics(font);
            var h = fm.height()+10;
            v = new RVector(0, view.mapDistanceFromView(h));
            c = c.operator_add(v);
        }
        else {
            v = new RVector(0, this.textHeight * 1.4);
            c = c.operator_add(v);
        }

        this.addTextLabel(op, view, c, label1, preview);
    }

    return op;
};

InfoPolylineArea.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.polyline)) {
        ret.push(this.polyline.getId());
    }
    return ret;
};

InfoPolylineArea.prototype.getArea = function() {
    return this.shape.getArea();
};

InfoPolylineArea.prototype.getCircumference = function() {
    return this.shape.getLength();
};

InfoPolylineArea.prototype.getCenter = function() {
    var pts = this.shape.getVertices();
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

InfoPolylineArea.prototype.slotCalculate = function() {
    var di = this.getDocumentInterface();

    if (isNull(this.polyline) || this.polyline.countVertices()===0) {
        this.polyline = undefined;
        return;
    }

    var info = qsTr("Polyline area:") + " " + this.formatAreaResult(this.getArea(), false) +
            ", " + qsTr("circumference:") + " " + this.getCircumference();

    if (this.addToDrawing) {
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
        }
        this.polyline = undefined;
    }

    EAction.getMainWindow().handleUserInfo(info);
};
