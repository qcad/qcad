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
 * \class LineBisector
 * \brief Line as bisector of two other lines.
 * \ingroup ecma_draw_line
 */
function LineBisector(guiAction) {
    Line.call(this, guiAction);

    this.length = undefined;
    this.number = undefined;
    this.line1 = undefined;
    this.pos1 = undefined;
    this.line2 = undefined;
    this.pos2 = undefined;

    this.setUiOptions(["../Line.ui", "LineBisector.ui"]);
}

LineBisector.prototype = new Line();

LineBisector.State = {
    ChoosingLine1 : 0,
    ChoosingLine2 : 1
};

LineBisector.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineBisector.State.ChoosingLine1);
};

LineBisector.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var tr;
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineBisector.State.ChoosingLine1:
        this.line1 = undefined;
        this.pos1 = undefined;
        this.line2 = undefined;
        this.pos2 = undefined;
        tr = qsTr("First line");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        break;

    case LineBisector.State.ChoosingLine2:
        tr = qsTr("Second line");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        break;
    }

    this.setRightMouseTip(EAction.trCancel);
};

LineBisector.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineBisector.State.ChoosingLine1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case LineBisector.State.ChoosingLine2:
        this.setState(LineBisector.State.ChoosingLine1);
        break;
    }
};

LineBisector.prototype.finishEvent = function() {
    EAction.prototype.finishEvent.call(this);
};

LineBisector.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var pos = event.getModelPosition();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);

    if (isNull(entity)) {
        return;
    }

    var shape = entity.getClosestSimpleShape(pos);

    if (!isLineBasedShape(shape)) {
        if (!preview) {
            EAction.warnNotLine();
        }
        return;
    }

    if (preview) {
        di.highlightEntity(entityId);
    }

    switch (this.state) {
    case LineBisector.State.ChoosingLine1:
        this.line1 = shape;
        this.pos1 = pos;
        if (!preview) {
            this.setState(LineBisector.State.ChoosingLine2);
        }
        break;

    case LineBisector.State.ChoosingLine2:
        this.line2 = shape;
        this.pos2 = pos;
        if (preview) {
            //di.previewOperation(op);
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
            else {
                EAction.handleUserWarning(qsTr("Lines don't intersect."));
            }
            this.setState(LineBisector.State.ChoosingLine1);
        }
        break;
    }
};

LineBisector.prototype.getOperation = function(preview) {
    if (isNull(this.pos1) || isNull(this.pos2) ||
        isNull(this.line1) || isNull(this.line2) ||
        !isNumber(this.length) || !isNumber(this.number)) {

        return undefined;
    }

    // get intersection of the two chosen lines:
    var ips = this.line1.getIntersectionPoints(this.line2.data(), false);

    if (ips.length===0) {
        return undefined;
    }

    var doc = this.getDocument();
    var ip = ips[0];

    var angle1 = ip.getAngleTo(this.line1.getClosestPointOnShape(this.pos1));
    var angle2 = ip.getAngleTo(this.line2.getClosestPointOnShape(this.pos2));
    var angleDiff = RMath.getAngleDifference(angle1, angle2);
    if (angleDiff>Math.PI) {
        angleDiff = angleDiff - 2*Math.PI;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    for (var n=1; n<=this.number; ++n) {
        var angle = angle1 + (angleDiff / (this.number+1) * n);

        // create vector from intersection to bisected angle / length:
        var vector = new RVector();
        vector.setPolar(this.length, angle);

        var line = this.createLineEntity(doc, ip, ip.operator_add(vector));

        op.addObject(line);
    }

    return op;
};

LineBisector.prototype.update = function() {
    var di = this.getDocumentInterface();
    di.clearPreview();
    var op = this.getOperation(false);
    if (!isNull(op)) {
        di.previewOperation(op);
    }
    di.repaintViews();
};

LineBisector.prototype.slotLengthChanged = function(value) {
    this.length = value;
    this.update();
};

LineBisector.prototype.slotNumberChanged = function(value) {
    this.number = value;
    this.update();
};

LineBisector.prototype.typeChanged = function() {
    var optionsToolBar = EAction.getOptionsToolBar();

    var ws = ["LengthLabel", "Length"];
    for (var i=0; i<ws.length; i++) {
        var w = optionsToolBar.findChild(ws[i]);
        if (!isNull(w)) {
            w.enabled = !this.isRayOrXLine();
        }
    }
};
