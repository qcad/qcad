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

include("../Circle.js");

/**
 * \class Circle2PR
 * \brief Circle from start point, end point and radius.
 * \ingroup ecma_draw_circle
 */
function Circle2PR(guiAction) {
    Circle.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;
    this.radius = undefined;

    // for aux construction:
    this.center = undefined;

    this.setUiOptions("Circle2PR.ui");
}

Circle2PR.prototype = new Circle();

Circle2PR.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1
    //ChoosingSolution : 2
};

Circle2PR.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(Circle2PR.State.SettingPoint1);
};

Circle2PR.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Circle2PR.State.SettingPoint1:
        this.point1 = undefined;
        this.point2 = undefined;
        var trFirstPoint = qsTr("First point");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Circle2PR.State.SettingPoint2:
        var trSecondPoint = qsTr("Second point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trBack);
        break;

    /*case Circle2PR.State.ChoosingSolution:
        var trSolution = qsTr("Solution");
        this.setCommandPrompt(trSolution);
        this.setLeftMouseTip(trSolution);
        this.setRightMouseTip(EAction.trBack);
        break;*/
    }

    EAction.showSnapTools();
};

Circle2PR.prototype.escapeEvent = function() {
    switch (this.state) {
    case Circle2PR.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Circle2PR.State.SettingPoint2:
        this.setState(Circle2PR.State.SettingPoint1);
        break;

    //case Circle2PR.State.ChoosingSolution:
    //    this.setState(Circle2PR.State.SettingPoint2);
    //    break;
    }
};

Circle2PR.prototype.pickCoordinate = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Circle2PR.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.point1);
            this.setState(Circle2PR.State.SettingPoint2);
        }
        break;

    case Circle2PR.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.point2);
                this.setState(Circle2PR.State.SettingPoint1);
            }
        }
        break;

//    case Circle2PR.State.ChoosingSolution:
//        this.point2 = event.getModelPosition();
//        if (preview) {
//            this.updatePreview();
//        }
//        else {
//            var op = this.getOperation(false);
//            if (!isNull(op)) {
//                di.applyOperation(op);
//                di.setRelativeZero(this.point2);
//                this.setState(Circle2PR.State.SettingPoint1);
//            }
//        }
//        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Circle2PR.prototype.getOperation = function(preview) {
    var shape = this.getCircle2PR(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();

    var entity = new RCircleEntity(doc, new RCircleData(shape));

    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

Circle2PR.prototype.getCircle2PR = function(preview) {
    if (isNull(this.point1) || isNull(this.point2) || !isNumber(this.radius)) {
        return undefined;
    }

    if (this.radius <= 0.0 || this.radius > 1.0e6) {
        if (!preview) {
            this.error = qsTr("Invalid radius");
        }
        return undefined;
    }

    if (this.point1.equalsFuzzy(this.point2)) {
        if (!preview) {
            this.error = qsTr("The two points are identical");
        }
        return undefined;
    }

    var circle1 = new RCircle(this.point1, this.radius);
    var circle2 = new RCircle(this.point2, this.radius);

    var ips = circle1.getIntersectionPoints(circle2, false);

    if (ips.length===2) {
        var ipRight, ipLeft;
        var line = new RLine(this.point1, this.point2);
        if (line.getSideOfPoint(ips[0])==RS.RightHand) {
            ipRight = ips[0];
            ipLeft = ips[1];
        }
        else {
            ipLeft = ips[0];
            ipRight = ips[1];
        }

        // XOR:
        if ((this.reversed==true) != (this.alternativeSolution==true)) {
            this.center = ipRight;
        }
        else {
            this.center = ipLeft;
        }
    }
    else {
        // center in the middle:
        var v = new RVector();
        v.setPolar(this.radius, this.point1.getAngleTo(this.point2));
        this.center = this.point1.operator_add(v);
        //this.point2 = this.point1.operator_add(v.operator_multiply(2.0));
    }

    return new RCircle(this.center, this.radius);
};

Circle2PR.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
    this.updatePreview(true);
};

Circle2PR.prototype.slotDirectionChanged = function(button) {
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

Circle2PR.prototype.slotSolutionChanged = function(button) {
    if (!isQObject(button) || button.checked!=true) {
        return;
    }

    if (button.objectName==="Solution2") {
        this.alternativeSolution = true;
    }
    else {
        this.alternativeSolution = false;
    }

    this.updatePreview(true);
};

Circle2PR.prototype.getAuxPreview = function() {
    if (isNull(this.center) || isNull(this.point1) || isNull(this.point2)) {
        return undefined;
    }

    var ret = [];

    if (this.state===Circle2PR.State.SettingPoint2) {
        ret.push(new RLine(this.point1, this.point2));
    }

    return ret;
};

