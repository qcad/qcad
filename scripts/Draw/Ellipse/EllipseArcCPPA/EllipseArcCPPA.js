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

include("scripts/Draw/Ellipse/Ellipse.js");

/**
 * \class EllipseArcCPPA
 * \brief Ellipse arc from center point, major point, minor point and angles.
 * \ingroup ecma_draw_ellipse
 */
function EllipseArcCPPA(guiAction, fullEllipse) {
    Ellipse.call(this, guiAction);

    this.reversed = undefined;
    this.fullEllipse = false;
    if (!isNull(fullEllipse)) {
        this.fullEllipse = fullEllipse;
    }

    this.setUiOptions("EllipseArcCPPA.ui");
}

EllipseArcCPPA.prototype = new Ellipse();

EllipseArcCPPA.State = {
    SettingCenter : 0,
    SettingMajorPoint : 1,
    SettingAngle : 2,
    SettingRatio : 3,
    SettingParam1 : 4,
    SettingParam2 : 5
};

EllipseArcCPPA.prototype.beginEvent = function() {
    Ellipse.prototype.beginEvent.call(this);

    this.setState(EllipseArcCPPA.State.SettingCenter);
};

EllipseArcCPPA.prototype.setState = function(state) {
    Ellipse.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case EllipseArcCPPA.State.SettingCenter:
        this.center = undefined;
        this.majorPoint = undefined;
        this.angle = undefined;
        this.ratio = undefined;
        this.param1 = undefined;
        this.point1 = undefined;
        this.param2 = undefined;
        this.point2 = undefined;

        var trCenter = qsTr("Center");
        this.setCommandPrompt(trCenter);
        this.setLeftMouseTip(trCenter);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case EllipseArcCPPA.State.SettingMajorPoint:
        this.setCommandPrompt(qsTr("Major point of ellipse or major radius"));
        this.setLeftMouseTip(qsTr("Major point of ellipse"));
        this.setRightMouseTip(EAction.trBack);
        break;

    case EllipseArcCPPA.State.SettingRatio:
        this.setCommandPrompt(qsTr("Minor point of ellipse or minor radius"));
        this.setLeftMouseTip(qsTr("Minor point of ellipse"));
        this.setRightMouseTip(EAction.trBack);
        break;

    case EllipseArcCPPA.State.SettingAngle:
        var trRotationAngle = qsTr("Rotation angle");
        this.setCommandPrompt(trRotationAngle);
        this.setLeftMouseTip(trRotationAngle);
        this.setRightMouseTip(EAction.trBack);
        break;

    case EllipseArcCPPA.State.SettingParam1:
        var trStartParam = qsTr("Start parameter");
        this.setCommandPrompt(trStartParam);
        this.setLeftMouseTip(trStartParam);
        this.setRightMouseTip(EAction.trBack);
        break;

    case EllipseArcCPPA.State.SettingParam2:
        var trEndParam = qsTr("End parameter");
        this.setCommandPrompt(trEndParam);
        this.setLeftMouseTip(trEndParam);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

EllipseArcCPPA.prototype.escapeEvent = function() {
    switch (this.state) {
    case EllipseArcCPPA.State.SettingCenter:
        EAction.prototype.escapeEvent.call(this);
        break;

    case EllipseArcCPPA.State.SettingMajorPoint:
        this.setState(EllipseArcCPPA.State.SettingCenter);
        break;

    case EllipseArcCPPA.State.SettingAngle:
        this.setState(EllipseArcCPPA.State.SettingCenter);
        break;

    case EllipseArcCPPA.State.SettingRatio:
        this.setState(EllipseArcCPPA.State.SettingMajorPoint);
        break;

    case EllipseArcCPPA.State.SettingParam1:
        this.setState(EllipseArcCPPA.State.SettingRatio);
        break;

    case EllipseArcCPPA.State.SettingParam2:
        this.setState(EllipseArcCPPA.State.SettingParam1);
        break;

    }
};

EllipseArcCPPA.prototype.pickCoordinate = function(event, preview) {
    var op;
    
    var di = this.getDocumentInterface();

    switch (this.state) {
    case EllipseArcCPPA.State.SettingCenter:
        if (!preview) {
            this.center = event.getModelPosition();
            //this.ellipse.setCenter(this.center);
            di.setRelativeZero(this.center);
            this.setState(EllipseArcCPPA.State.SettingMajorPoint);
        }
        break;

    case EllipseArcCPPA.State.SettingMajorPoint:
        this.majorPoint = event.getModelPosition().operator_subtract(this.center);
        //this.ellipse.setMajorPoint(this.majorPoint);
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.center.operator_add(this.majorPoint));
            this.setState(EllipseArcCPPA.State.SettingRatio);
        }
        break;

    case EllipseArcCPPA.State.SettingAngle:
        this.angle = this.center.getAngleTo(event.getModelPosition());
        //this.ellipse.setAngle(this.angle);
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(event.getModelPosition());
            if (this.fullEllipse) {
                this.param1 = 0.0;
                this.param2 = 2*Math.PI;
                this.reversed = false;
                op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                    this.setState(EllipseArcCPPA.State.SettingCenter);
                }
            }
            else {
                this.setState(EllipseArcCPPA.State.SettingParam1);
            }
        }
        break;

    case EllipseArcCPPA.State.SettingRatio:
        var line = new RLine(this.center, this.center.operator_add(this.majorPoint));
        var distance = line.getDistanceTo(event.getModelPosition(), false);
        this.ratio = distance / this.majorPoint.getMagnitude();
        //this.ellipse.setRatio(this.ratio);
        if (preview) {
            this.updatePreview();
        }
        else {
            if (this.fullEllipse) {
                this.param1 = 0.0;
                this.param2 = 2*Math.PI;
                this.reversed = false;
                op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                    this.setState(EllipseArcCPPA.State.SettingCenter);
                }
            }
            else {
                this.setState(EllipseArcCPPA.State.SettingParam1);
            }
        }
        break;

    case EllipseArcCPPA.State.SettingParam1:
        this.point1 = event.getModelPosition();
        this.param1 = this.getEllipse().getParamTo(this.point1);

        if (this.reversed==true) {
            this.param2 = this.param1 - Math.PI/3;
        }
        else {
            this.param2 = this.param1 + Math.PI/3;
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(EllipseArcCPPA.State.SettingParam2);
        }
        break;

    case EllipseArcCPPA.State.SettingParam2:
        this.point2 = event.getModelPosition();
        this.param2 = this.getEllipse().getParamTo(this.point2);
        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(EllipseArcCPPA.State.SettingCenter);
            }
        }
        break;
    }
};

EllipseArcCPPA.prototype.getOperation = function(preview) {
//    if (isNull(this.center) || isNull(this.majorPoint)) {
//        return undefined;
//    }

//    var reversed = this.reversed;
//    if (!isBoolean(reversed) || this.state<=EllipseArcCPPA.State.SettingRatio) {
//        reversed = false;
//    }

//    var ratio = this.ratio;
//    if (!isNumber(ratio)) {
//        ratio = 0.5;
//    }

//    var param1 = this.param1;
//    if (!isNumber(param1)) {
//        param1 = 0.0;
//    }

//    var param2 = this.param2;
//    if (!isNumber(param2)) {
//        param2 = 2*Math.PI;
//    }

    var shape = Ellipse.postProcess(this.getEllipse());
    var entity = shapeToEntity(this.getDocument(), shape);

    return new RAddObjectOperation(entity, this.getToolTitle());
};

EllipseArcCPPA.prototype.getAuxPreview = function() {
    var d, v, a;
    
    var ret = [];

    var ellipse = this.getEllipse();

    if (this.state==EllipseArcCPPA.State.SettingMajorPoint ||
        this.state==EllipseArcCPPA.State.SettingAngle ||
        this.state==EllipseArcCPPA.State.SettingRatio) {

        ret.push(new RLine(this.center.operator_subtract(ellipse.getMajorPoint()),
                           this.center.operator_add(ellipse.getMajorPoint())));

        var mjp = this.center.operator_add(ellipse.getMajorPoint());
        var mjp2 = this.center.operator_subtract(ellipse.getMajorPoint());
        var mnp = this.center.operator_add(ellipse.getMinorPoint());
        var mnp2 = this.center.operator_subtract(ellipse.getMinorPoint());
        var c1 = mjp.operator_add(ellipse.getMinorPoint());
        var c2 = mjp2.operator_add(ellipse.getMinorPoint());
        var c3 = mjp2.operator_subtract(ellipse.getMinorPoint());
        var c4 = mjp.operator_subtract(ellipse.getMinorPoint());

        ret.push(new RLine(mjp, mjp2));
        ret.push(new RLine(mnp, mnp2));
        ret.push(new RLine(c1, c2));
        ret.push(new RLine(c2, c3));
        ret.push(new RLine(c3, c4));
        ret.push(new RLine(c4, c1));
    }

    if (this.state==EllipseArcCPPA.State.SettingParam1 ||
        this.state==EllipseArcCPPA.State.SettingParam2) {

        d = Math.max(this.center.getDistanceTo(this.point1),
                         ellipse.getRadiusAt(this.param1));
        a = this.center.getAngleTo(this.point1);
        v = RVector.createPolar(d,a);
        ret.push(new RLine(this.center, this.center.operator_add(v)));
    }

    if (this.state==EllipseArcCPPA.State.SettingParam2) {
        d = Math.max(this.center.getDistanceTo(this.point2),
                         ellipse.getRadiusAt(this.param2));
        a = this.center.getAngleTo(this.point2);
        v = RVector.createPolar(d,a);
        ret.push(new RLine(this.center, this.center.operator_add(v)));
    }

    return ret;
};

EllipseArcCPPA.prototype.slotDirectionChanged = function(button) {
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

EllipseArcCPPA.prototype.applyCommand = function(event, preview) {
    var op;
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
    case EllipseArcCPPA.State.SettingMajorPoint:
        event.accept();
        if (value<=0) {
            if (!preview) {
                EAction.handleUserWarning(qsTr("Invalid major radius."));
            }
            break;
        }
        this.majorPoint = new RVector(value, 0.0);
        //this.ellipse.setMajorPoint(this.majorPoint);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            EAction.handleUserMessage(qsTr("Major radius:") + " " + value);
            this.setState(EllipseArcCPPA.State.SettingAngle);
        }
        break;

    case EllipseArcCPPA.State.SettingAngle:
        event.accept();
        this.majorPoint =
             RVector.createPolar(
                 this.majorPoint.getMagnitude(), RMath.deg2rad(value)
             );
        //this.ellipse.setMajorPoint(this.majorPoint);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            EAction.handleUserMessage(qsTr("Angle:") + " " + value);
            this.setState(EllipseArcCPPA.State.SettingRatio);
        }
        break;

    case EllipseArcCPPA.State.SettingRatio:
        event.accept();
        this.ratio = value / this.majorPoint.getMagnitude();
        //this.ellipse.setRatio(this.ratio);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            EAction.handleUserMessage(qsTr("Minor radius:") + " " + value);
            if (this.fullEllipse) {
                this.param1 = 0.0;
                this.param2 = 2*Math.PI;
                this.reversed = false;
                op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                    this.setState(EllipseArcCPPA.State.SettingCenter);
                }
            }
            else {
                this.setState(EllipseArcCPPA.State.SettingParam1);
            }
        }
        break;

    case EllipseArcCPPA.State.SettingParam1:
        event.accept();
        this.param1 = RMath.deg2rad(value);
        this.point1 = this.getEllipse().getPointAt(this.param1);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            EAction.handleUserMessage(qsTr("Start angle:") + " " + value);
            this.setState(EllipseArcCPPA.State.SettingParam2);
        }
        break;

    case EllipseArcCPPA.State.SettingParam2:
        event.accept();
        this.param2 = RMath.deg2rad(value);
        this.point2 = this.getEllipse().getPointAt(this.param2);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                EAction.handleUserMessage(qsTr("End angle:") + " " + value);
                this.setState(EllipseArcCPPA.State.SettingCenter);
            }
        }
        break;
    }
};

EllipseArcCPPA.prototype.getEllipse = function() {
    if (isNull(this.center) || isNull(this.majorPoint)) {
        return undefined;
    }

    var reversed = this.reversed;
    if (!isBoolean(reversed) || this.state<=EllipseArcCPPA.State.SettingRatio) {
        reversed = false;
    }

    var ratio = this.ratio;
    if (!isNumber(ratio)) {
        ratio = 0.5;
    }

    var param1 = this.param1;
    if (!isNumber(param1)) {
        param1 = 0.0;
    }

    var param2 = this.param2;
    if (!isNumber(param2)) {
        param2 = 2*Math.PI;
    }

    var e = new REllipse(
                this.center,
                this.majorPoint,
                ratio,
                param1,
                param2,
                reversed);

    e.setStartParam(param1);
    e.setEndParam(param2);

    return e;
};

