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
 * \class InfoDistanceEE
 * \ingroup ecma_information
 * \brief Measure distance from entity to entity.
 */
function InfoDistanceEE(guiAction) {
    Information.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.point1 = undefined;

    this.entity2 = undefined;
    this.shape2 = undefined;
    this.point2 = undefined;

    this.setUiOptions("../Information.ui");
}

InfoDistanceEE.prototype = new Information();

InfoDistanceEE.State = {
    SettingShape1 : 0,
    SettingShape2 : 1
};

InfoDistanceEE.prototype.beginEvent = function() {
    Information.prototype.beginEvent.call(this);
    this.setState(InfoDistanceEE.State.SettingShape1);
};

InfoDistanceEE.prototype.setState = function(state) {
    Information.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {

    case InfoDistanceEE.State.SettingShape1:
        di.setClickMode(RAction.PickEntity);
        var trFirstEntity = qsTr("Specify first entity");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case InfoDistanceEE.State.SettingShape2:
        this.point2 = undefined;
        di.setClickMode(RAction.PickEntity);
        var trSecondEntity = qsTr("Specify second entity");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    this.setCrosshairCursor();
    //EAction.showSnapTools();
};

InfoDistanceEE.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    // keep showing preview after 2nd point has been set:
    if (!this.addToDrawing) {
        if (!isNull(this.point1) && !isNull(this.point2)) {
            var op = this.getOperation(preview);
            if (preview) {
                di.previewOperation(op);
            }
            else {
                op.destroy();
            }
        }
    }

    if (isNull(entity)) {
        return;
    }

    var shape = entity.getClosestSimpleShape(pos);

    if (!this.isShapeSupported(shape)) {
        if (!preview) {
            this.warnUnsupportedShape();
        }
        return;
    }

    switch (this.state) {

    case InfoDistanceEE.State.SettingShape1:
        this.entity1 = entity;
        if (!preview) {
            this.shape1 = shape;
            this.setState(InfoDistanceEE.State.SettingShape2);
        }
        break;

    case InfoDistanceEE.State.SettingShape2:
        this.entity2 = entity;
        this.shape2 = shape;

        // points on shape2 which might be closest to shape1:
        var candidates1 = this.getCandidatePoints(this.shape1, this.shape2);
        var candidates2 = this.getCandidatePoints(this.shape2, this.shape1);

        this.point1 = undefined;
        this.point2 = undefined;
        var minDist = undefined;
        for (var i1=0; i1<candidates1.length; i1++) {
            var c1 = candidates1[i1];

            for (var i2=0; i2<candidates2.length; i2++) {
                var c2 = candidates2[i2];

                var dist = c1.getDistanceTo(c2);
                if (isNull(minDist) || dist<minDist) {
                    minDist = dist;
                    this.point1 = c1;
                    this.point2 = c2;
                }
            }
        }

        if (!isNull(this.point1) && !isNull(this.point2)) {
            if (this.addToDrawing) {
                var op = this.getOperation(preview);
                if (preview) {
                    di.previewOperation(op);
                }
                else {
                    di.applyOperation(op);
                    di.setRelativeZero(this.point2);
                }
            }
        }

        if (!preview) {
            var distance = this.point1.getDistanceTo(this.point2);
            EAction.getMainWindow().handleUserInfo(qsTr("Distance:") + " " + this.formatLinearResultCmd(distance));

            if (this.autoTerminate) {
                this.updateLineEdit(distance);
                this.setNoState(false);
                this.terminate();
                return;
            }
            else {
                this.setState(InfoDistanceEE.State.SettingShape1);
            }
        }

        break;
    }

    di.highlightEntity(entity.getId());
};

InfoDistanceEE.prototype.isShapeSupported = function(shape) {
    return isLineBasedShape(shape) ||
           isArcShape(shape) ||
           isCircleShape(shape);
};

InfoDistanceEE.prototype.warnUnsupportedShape = function() {
    EAction.warnNotLineArcCircle();
};

/**
 * \return Points on shape1 which might be closest to shape2.
 */
InfoDistanceEE.prototype.getCandidatePoints = function(shape1, shape2) {
    var ret = [];

//    var s1 = this.shape1;
//    var s2 = this.shape2;

//    // make sure s1 is line and s2 arc for line <-> arc:
//    // make sure s1 is circle and s2 arc for circle <-> arc:
//    if (((isArcShape(s1) || isCircleShape(s1)) && isLineBasedShape(s2)) ||
//        (isArcShape(s1) && isCircleShape(s2))) {
//        var d = s1;
//        s1 = s2;
//        s2 = d;
//    }

    // add start and end point for lines, xlines and arcs:
    // line <-> line
    // line <-> arc
    if (isLineShape(shape1) || isXLineShape(shape1) || isArcShape(shape1)) {
        ret.push(shape1.getStartPoint());
        ret.push(shape1.getEndPoint());
    }

    // add start point for rays:
    // line <-> ray
    if (isRayShape(shape1)) {
        ret.push(shape1.getStartPoint());
    }

    var a, p;

    // arc <-> arc / line / circle
    // circle <-> arc / line / circle
    if (isArcShape(shape1) || isCircleShape(shape1)) {
        p = shape2.getClosestPointOnShape(shape1.getCenter());
        a = shape1.getCenter().getAngleTo(p);
        p = shape1.getPointAtAngle(a);
        if (shape1.isOnShape(p)) {
            ret.push(p);
        }
    }

    var s2Points = [];
    if (isFunction(shape2.getStartPoint)) {
        s2Points.push(shape2.getStartPoint());
    }
    if (isFunction(shape2.getEndPoint)) {
        s2Points.push(shape2.getEndPoint());
    }
    if (isFunction(shape2.getCenter)) {
        s2Points.push(shape2.getCenter());
    }
    for (var i=0; i<s2Points.length; i++) {
        var s2Point = s2Points[i];
        p = shape1.getClosestPointOnShape(s2Point);
        if (shape1.isOnShape(p)) {
            ret.push(p);
        }
    }

    // add intersection points:
    var ips = shape1.getIntersectionPoints(shape2.data());
    ret = ret.concat(ips);

    // line <-> arc / circle
//    if (isLineBasedShape(shape1) && (isArcShape(shape2) || isCircleShape(shape2))) {
//        p = shape1.getClosestPointOnShape(shape2.getCenter());
//        if (shape1.isOnShape(p)) {
//            ret.push(p);
//        }
//    }

    return ret;
};

//InfoDistanceEE.prototype.pickCoordinate = function(event, preview) {
//    var di = this.getDocumentInterface();

//    if (isNull(this.shape)) {
//        return;
//    }

//    this.point2 = event.getModelPosition();

//    if (!isValidVector(this.point2)) {
//        return;
//    }

//    this.point1 = this.shape.getClosestPointOnShape(this.point2, false);

//    if (!isValidVector(this.point1)) {
//        return;
//    }

//    di.highlightEntity(this.entity.getId());

//    var op = this.getOperation(preview);
//    if (preview) {
//        di.previewOperation(op);
//    }
//    else {
//        if (this.addToDrawing) {
//            di.applyOperation(op);
//            di.setRelativeZero(this.point2);
//        }
//        else {
//            op.destroy();
//        }
//    }

//    if (!preview) {
//        this.setState(InfoDistanceEE.State.SettingShape1);
//        var distance = this.point1.getDistanceTo(this.point2);
//        EAction.getMainWindow().handleUserInfo(qsTr("Distance:") + " " + this.formatLinearResultCmd(distance));
//    }
//};

InfoDistanceEE.prototype.getOperation = function(preview) {
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    this.addInfoLine(op, this.point1, this.point2, preview);

//    var candidates1 = this.getCandidatePoints(this.shape1, this.shape2);
//    for (var i=0; i<candidates1.length; i++) {
//        this.addInfoLine(op, candidates1[i], this.point2, preview);
//    }

    return op;
};
