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

include("scripts/Draw/Arc/Arc.js");

/**
 * \class Arc2PA
 * \brief Arc from two points and angle.
 * \ingroup ecma_draw_arc
 */
function Arc2PA(guiAction) {
    Arc.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;
    this.angle = undefined;
    this.reversed = undefined;

    // for aux construction:
    this.center = undefined;

    this.setUiOptions("Arc2PA.ui");
}

Arc2PA.prototype = new Arc();

Arc2PA.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1
};

Arc2PA.prototype.beginEvent = function() {
    Arc.prototype.beginEvent.call(this);

    this.setState(Arc2PA.State.SettingPoint1);
};

Arc2PA.prototype.setState = function(state) {
    Arc.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Arc2PA.State.SettingPoint1:
        this.point1 = undefined;
        this.point2 = undefined;
        var trStartPoint = qsTr("Start point");
        this.setCommandPrompt(trStartPoint);
        this.setLeftMouseTip(trStartPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Arc2PA.State.SettingPoint2:
        var trEndPoint = qsTr("End point");
        this.setCommandPrompt(trEndPoint);
        this.setLeftMouseTip(trEndPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Arc2PA.prototype.escapeEvent = function() {
    switch (this.state) {
    case Arc2PA.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Arc2PA.State.SettingPoint2:
        this.setState(Arc2PA.State.SettingPoint1);
        break;
    }
};

Arc2PA.prototype.pickCoordinate = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Arc2PA.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.point1);
            this.setState(Arc2PA.State.SettingPoint2);
        }
        break;

    case Arc2PA.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.point2);
                this.setState(Arc2PA.State.SettingPoint1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Arc2PA.prototype.getOperation = function(preview) {
    var shape = this.getArc2PA(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();

    var entity = new RArcEntity(doc, new RArcData(shape));

    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

Arc2PA.prototype.verifyAngle = function() {
    return !(this.angle >= Math.PI*2-RS.AngleTolerance || this.angle <= -Math.PI*2+RS.AngleTolerance)
};

Arc2PA.prototype.getArc2PA = function(preview) {
    if (isNull(this.point1) || isNull(this.point2) || isNull(this.angle)) {
        return undefined;
    }

    if (!this.verifyAngle()) {
        if (!preview) {
            this.error = qsTr("Invalid angle");
        }
        return undefined;
    }

    if (this.point1.equalsFuzzy(this.point2)) {
        if (!preview) {
            this.error = qsTr("The two points are identical");
        }
        return undefined;
    }

    var angle = this.point1.getAngleTo(this.point2);
    var angle90 = angle + Math.PI/2;
    var a1, a2;
    if (this.reversed===true) {
        a1 = angle90 + this.angle/2;
        a2 = angle90 - this.angle/2;
    }
    else {
        a1 = angle90 - this.angle/2;
        a2 = angle90 + this.angle/2;
    }

    var v1 = new RVector();
    v1.setPolar(1.0, a1);
    var v2 = new RVector();
    v2.setPolar(1.0, a2);

    var line1 = new RLine(this.point1, this.point1.operator_add(v1));
    var line2 = new RLine(this.point2, this.point2.operator_add(v2));

    var ips = line1.getIntersectionPoints(line2, false);

    if (ips.length===1) {
        this.center = ips[0];
    }
    else {
        this.center = RVector.getAverage(this.point1, this.point2);
    }

    var radius = this.center.getDistanceTo(this.point1);
    var angle1 = this.center.getAngleTo(this.point1);
    var angle2 = this.center.getAngleTo(this.point2);

    var ret = new RArc(this.center, radius, angle1, angle2, this.reversed);

    return ret;
};

Arc2PA.prototype.slotAngleChanged = function(value) {
    this.angle = value;
    this.updatePreview(true);
};

Arc2PA.prototype.slotDirectionChanged = function(button) {
    if (!isQObject(button) || button.checked!=true) {
        return;
    }

    if (button.objectName==="Clockwise") {
        this.reversed = true;
    }
    else {
        this.reversed = false;
    }

    this.updatePreview(true);
};

Arc2PA.prototype.getAuxPreview = function() {
    if (isNull(this.center) || isNull(this.point1) || isNull(this.point2)) {
        return undefined;
    }

    if (!this.verifyAngle()) {
        return undefined;
    }

    var ret = [];

    if (this.state==Arc2PA.State.SettingPoint2) {
        ret.push(new RLine(this.center, this.point1));
        ret.push(new RLine(this.center, this.point2));
    }

    return ret;
};

