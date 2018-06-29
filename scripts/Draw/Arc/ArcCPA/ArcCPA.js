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
 * \class ArcCPA
 * \brief Arc from center, point and angles.
 * \ingroup ecma_draw_arc
 */
function ArcCPA(guiAction) {
    Arc.call(this, guiAction);

    this.reversed = undefined;

    this.setUiOptions("ArcCPA.ui");
}

ArcCPA.prototype = new Arc();

ArcCPA.State = {
    SettingCenter : 0,
    SettingRadius : 1,
    SettingAngle1 : 2,
    SettingAngle2 : 3
};

ArcCPA.prototype.beginEvent = function() {
    Arc.prototype.beginEvent.call(this);

    this.setState(ArcCPA.State.SettingCenter);
};

ArcCPA.prototype.setState = function(state) {
    Arc.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ArcCPA.State.SettingCenter:
        this.center = undefined;
        this.radius = undefined;
        this.angle1 = undefined;
        this.point1 = undefined;
        this.angle2 = undefined;
        this.point2 = undefined;

        var trCenter = qsTr("Center");
        this.setCommandPrompt(trCenter);
        this.setLeftMouseTip(trCenter);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ArcCPA.State.SettingRadius:
        this.setCommandPrompt(qsTr("Point on arc or radius"));
        this.setLeftMouseTip(qsTr("Point on arc"));
        this.setRightMouseTip(EAction.trBack);
        break;

    case ArcCPA.State.SettingAngle1:
        var trStartAngle = qsTr("Start angle");
        this.setCommandPrompt(trStartAngle);
        this.setLeftMouseTip(trStartAngle);
        this.setRightMouseTip(EAction.trBack);
        break;

    case ArcCPA.State.SettingAngle2:
        var trEndAngle = qsTr("End angle");
        this.setCommandPrompt(trEndAngle);
        this.setLeftMouseTip(trEndAngle);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

ArcCPA.prototype.escapeEvent = function() {
    switch (this.state) {
    case ArcCPA.State.SettingCenter:
        EAction.prototype.escapeEvent.call(this);
        break;

    case ArcCPA.State.SettingRadius:
        this.setState(ArcCPA.State.SettingCenter);
        break;

    case ArcCPA.State.SettingAngle1:
        this.setState(ArcCPA.State.SettingRadius);
        break;

    case ArcCPA.State.SettingAngle2:
        this.setState(ArcCPA.State.SettingAngle1);
        break;

    }
};

ArcCPA.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case ArcCPA.State.SettingCenter:
        if (!preview) {
            this.center = event.getModelPosition();
            di.setRelativeZero(this.center);
            this.setState(ArcCPA.State.SettingRadius);
        }
        break;

    case ArcCPA.State.SettingRadius:
        this.radius = this.center.getDistanceTo(event.getModelPosition());
        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(ArcCPA.State.SettingAngle1);
        }
        break;

    case ArcCPA.State.SettingAngle1:
        this.point1 = event.getModelPosition();
        this.angle1 = this.center.getAngleTo(this.point1);
        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(ArcCPA.State.SettingAngle2);
        }
        break;

    case ArcCPA.State.SettingAngle2:
        this.point2 = event.getModelPosition();
        this.angle2 = this.center.getAngleTo(this.point2);
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(ArcCPA.State.SettingCenter);
            }
        }
        break;
    }
};

ArcCPA.prototype.getOperation = function(preview) {
    if (isNull(this.center) ||
        !isNumber(this.radius) || !isBoolean(this.reversed)) {

        return undefined;
    }

    var reversed = this.reversed;

    if (this.state == ArcCPA.State.SettingRadius) {
        this.angle1 = 0.0;
        this.angle2 = 2*Math.PI;
        reversed = false;
    }
    else if (this.state == ArcCPA.State.SettingAngle1) {
        if (this.reversed==true) {
            this.angle2 = this.angle1 - Math.PI/3;
        }
        else {
            this.angle2 = this.angle1 + Math.PI/3;
        }
    }

    var arc = new RArcEntity(
        this.getDocument(),
        new RArcData(
            this.center,
            this.radius,
            this.angle1,
            this.angle2,
            reversed
        )
    );

    return new RAddObjectOperation(arc, this.getToolTitle());
};

ArcCPA.prototype.getAuxPreview = function() {
    var d;
    var ret = [];

    var v = new RVector();

    if (this.state==ArcCPA.State.SettingAngle1) {
        d = Math.max(this.center.getDistanceTo(this.point1), this.radius);
        v.setPolar(d,this.angle1);
        ret.push(new RLine(this.center, this.center.operator_add(v)));
    }
    if (this.state==ArcCPA.State.SettingAngle2) {
        d = Math.max(this.center.getDistanceTo(this.point2), this.radius);
        v.setPolar(d,this.angle2);
        ret.push(new RLine(this.center, this.center.operator_add(v)));
    }

    return ret;
};

ArcCPA.prototype.slotDirectionChanged = function(button) {
    if (!isQObject(button) || button.checked!=true) {
        return;
    }

    if (button.objectName==="Clockwise") {
        this.reversed = true;
    }
    else {
        this.reversed = false;
    }
};

ArcCPA.prototype.applyCommand = function(event, preview) {
    var v;
    var di = this.getDocumentInterface();
    var cmd = event.getCommand();

    var pos = RMath.parseCoordinate(cmd);
    if (pos.isValid()) {
        return;
    }

    var value = RMath.eval(cmd);
    if (isNaN(value)) {
        return;
    }

    switch (this.state) {
    case ArcCPA.State.SettingRadius:
        event.accept();
        this.radius = value;
        if (preview) {
            this.updatePreview(true);
        }
        else {
            this.setState(ArcCPA.State.SettingAngle1);
        }
        break;

    case ArcCPA.State.SettingAngle1:
        event.accept();
        this.angle1 = RMath.deg2rad(value);
        v = new RVector();
        v.setPolar(this.radius, this.angle1);
        this.point1 = this.center.operator_add(v);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            this.setState(ArcCPA.State.SettingAngle2);
        }
        break;

    case ArcCPA.State.SettingAngle2:
        event.accept();
        this.angle2 = RMath.deg2rad(value);
        v = new RVector();
        v.setPolar(this.radius, this.angle1);
        this.point2 = this.center.operator_add(v);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            var op = this.getOperation(false);
            di.applyOperation(op);
            this.setState(ArcCPA.State.SettingCenter);
        }
        break;
    }
};

