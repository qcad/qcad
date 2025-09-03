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

    this.center = undefined;
    this.reversed = undefined;

    // radius set in options tool bar:
    this.radius = 1.0;
    // radius that is being used (from options tool bar or click):
    this.actualRadius = 1.0;
    // point on radius set by mouse click:
    this.pointR = undefined;

    this.startAngle = undefined;
    this.actualStartAngle = undefined;
    this.startPoint = undefined;

    this.endAngle = undefined;
    this.actualEndAngle = undefined;
    this.endPoint = undefined;

    this.setUiOptions("ArcCPA.ui");
}

ArcCPA.prototype = new Arc();

ArcCPA.State = {
    SettingCenter : 0,
    SettingRadius : 1,
    SettingStartAngle : 2,
    SettingEndAngle : 3
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
        this.pointR = undefined;
        this.center = undefined;
        this.startPoint = undefined;
        this.endPoint = undefined;

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

    case ArcCPA.State.SettingStartAngle:
        var trStartAngle = qsTr("Start angle");
        this.setCommandPrompt(trStartAngle);
        this.setLeftMouseTip(trStartAngle);
        this.setRightMouseTip(EAction.trBack);
        break;

    case ArcCPA.State.SettingEndAngle:
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

    case ArcCPA.State.SettingStartAngle:
        this.setState(ArcCPA.State.SettingRadius);
        break;

    case ArcCPA.State.SettingEndAngle:
        this.setState(ArcCPA.State.SettingStartAngle);
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
        this.pointR = event.getModelPosition();

        this.updateActualRadius();

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(ArcCPA.State.SettingStartAngle);
        }
        break;

    case ArcCPA.State.SettingStartAngle:
        this.startPoint = event.getModelPosition();

        this.updateActualStartAngle();
        //this.startAngle = this.center.getAngleTo(this.startPoint);
        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(ArcCPA.State.SettingEndAngle);
        }
        break;

    case ArcCPA.State.SettingEndAngle:
        this.endPoint = event.getModelPosition();
        this.updateActualEndAngle();
        //this.endAngle = this.center.getAngleTo(this.endPoint);
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
        !isNumber(this.actualRadius) || !isBoolean(this.reversed)) {

        return undefined;
    }

    var reversed = this.reversed;

    if (this.state === ArcCPA.State.SettingRadius) {
        this.actualStartAngle = 0.0;
        this.actualEndAngle = 2*Math.PI;
        reversed = false;
    }
    else if (this.state === ArcCPA.State.SettingStartAngle) {
        if (this.reversed===true) {
            this.actualEndAngle = this.actualStartAngle - Math.PI/3;
        }
        else {
            this.actualEndAngle = this.actualStartAngle + Math.PI/3;
        }
    }

    var arc = new RArcEntity(
        this.getDocument(),
        new RArcData(
            this.center,
            this.actualRadius,
            this.actualStartAngle,
            this.actualEndAngle,
            reversed
        )
    );

    return new RAddObjectOperation(arc, this.getToolTitle());
};

ArcCPA.prototype.getAuxPreview = function() {
    var d;
    var ret = [];

    var v = new RVector();

    if (this.state===ArcCPA.State.SettingStartAngle) {
        d = Math.max(this.center.getDistanceTo(this.startPoint), this.actualRadius);
        v.setPolar(d,this.actualStartAngle);
        ret.push(new RLine(this.center, this.center.operator_add(v)));
    }
    if (this.state===ArcCPA.State.SettingEndAngle) {
        d = Math.max(this.center.getDistanceTo(this.endPoint), this.actualRadius);
        v.setPolar(d,this.actualEndAngle);
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

    this.updatePreview(true);
};

ArcCPA.prototype.updateActualRadius = function() {
    this.actualRadius = undefined;

    if (isVector(this.center) && isVector(this.pointR)) {
        this.actualRadius = this.center.getDistanceTo(this.pointR);
    }
};

ArcCPA.prototype.updateActualStartAngle = function() {
    this.actualStartAngle = undefined;

    if (isVector(this.center) && isVector(this.startPoint)) {
        this.actualStartAngle = this.center.getAngleTo(this.startPoint)
    }
};

ArcCPA.prototype.updateActualEndAngle = function() {
    this.actualEndAngle = undefined;

    if (isVector(this.center) && isVector(this.endPoint)) {
        this.actualEndAngle = this.center.getAngleTo(this.endPoint)
    }
};

ArcCPA.prototype.applyCommand = function(event, preview) {
    var v;
    var di = this.getDocumentInterface();
    var cmd = event.getCommand();

    var pos = RMath.parseCoordinate(cmd, di.getRelativeZero());
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
        this.actualRadius = value;
        this.updateRadiusOption(this.actualRadius);

        if (preview) {
            this.updatePreview(true);
        }
        else {
            this.setState(ArcCPA.State.SettingStartAngle);
        }
        break;

    case ArcCPA.State.SettingStartAngle:
        event.accept();
        this.actualStartAngle = RMath.deg2rad(value);
        this.updateStartAngleOption(this.actualStartAngle);
        v = new RVector();
        v.setPolar(this.actualRadius, this.actualStartAngle);
        this.startPoint = this.center.operator_add(v);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            this.setState(ArcCPA.State.SettingEndAngle);
        }
        break;

    case ArcCPA.State.SettingEndAngle:
        event.accept();
        this.actualEndAngle = RMath.deg2rad(value);
        this.updateEndAngleOption(this.actualEndAngle);
        v = new RVector();
        v.setPolar(this.actualRadius, this.actualEndAngle);
        this.endPoint = this.center.operator_add(v);
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

ArcCPA.prototype.updateRadiusOption = function(value) {
};
ArcCPA.prototype.updateStartAngleOption = function(value) {
};
ArcCPA.prototype.updateEndAngleOption = function(value) {
};
