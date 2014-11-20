/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

include("../Modify.js");

/**
 * \class Divide
 * \brief Divide entities into two equally long parts.
 * \ingroup ecma_modify
 */
function Divide(guiAction) {
    Modify.call(this, guiAction);

    this.entity = undefined;
    this.shape = undefined;
    // user click position:
    this.pos = undefined;
    this.pos2 = undefined;
    // actual cutting point:
    this.cutPos = undefined;
    this.cutPos2 = undefined;
}

Divide.prototype = new Modify();

Divide.State = {
    ChoosingEntity : 0,
    SettingPos : 1,
    SettingPos2 : 2
};

Divide.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(Divide.State.ChoosingEntity);
};

Divide.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Divide.State.ChoosingEntity:
        this.entity = undefined;
        this.shape = undefined;
        this.pos = undefined;
        this.cutPos = undefined;
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        if (RSpline.hasProxy()) {
            this.setLeftMouseTip(qsTr("Choose line, arc, circle, ellipse or spline"));
        }
        else {
            this.setLeftMouseTip(qsTr("Choose line, arc, circle or ellipse"));
        }
        this.setRightMouseTip(EAction.trCancel);
        EAction.showModificationTools();
        break;
    case Divide.State.SettingPos:
        this.pos = undefined;
        this.cutPos = undefined;
        this.pos2 = undefined;
        this.cutPos2 = undefined;
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.setLeftMouseTip(qsTr("Specify point"));
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;
    case Divide.State.SettingPos2:
        this.pos2 = undefined;
        this.cutPos2 = undefined;
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.setLeftMouseTip(qsTr("Specify second point"));
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;
    }
};

Divide.prototype.escapeEvent = function() {
    switch (this.state) {
    case Divide.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    case Divide.State.SettingPos:
        this.setState(Divide.State.ChoosingEntity);
        break;
    case Divide.State.SettingPos2:
        this.setState(Divide.State.SettingPos);
        break;
    }
};

Divide.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        this.entity = undefined;
        return;
    }

    switch (this.state) {
    case Divide.State.ChoosingEntity:
        if (isLineBasedEntity(entity) ||
            isArcEntity(entity) ||
            isCircleEntity(entity) ||
            isEllipseEntity(entity) ||
            (RSpline.hasProxy() && isSplineEntity(entity))) {

            this.entity = entity;
            this.shape = entity.getClosestShape(pos);

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(Divide.State.SettingPos);
            }
        }
        else {
            if (!preview) {
                EAction.warnNotLineArcCircleEllipse();
            }
        }
        break;
    }
};

Divide.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var op;

    switch (this.state) {
    case Divide.State.SettingPos:
        this.pos = event.getModelPosition();

        // full circle or ellipse: require two cutting points:
        if (isCircleEntity(this.entity) ||
            (isEllipseEntity(this.entity) && this.entity.isFullEllipse())) {

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(Divide.State.SettingPos2);
            }
        }
        else {
            if (preview) {
                this.updatePreview();
            }
            else {
                op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                }
                this.setState(Divide.State.ChoosingEntity);
            }
        }
        break;

    case Divide.State.SettingPos2:
        this.pos2 = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
            this.setState(Divide.State.ChoosingEntity);
        }
        break;
    }
};

Divide.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || isNull(this.entity) || !isShape(this.shape)) {
        return undefined;
    }

    if (isNull(this.pos2)) {
        if (isCircleShape(this.shape) || (isEllipseShape(this.shape) && this.shape.isFullEllipse())) {
            return undefined;
        }
    }

    var center;
    var angle = undefined;
    var angle2 = undefined;
    var e;

    var op = new RMixedOperation();
    if (isCircleShape(this.shape)) {
        op.deleteObject(this.entity);
        center = this.shape.getCenter();
        var radius = this.shape.getRadius();
        angle = center.getAngleTo(this.pos);
        angle2 = center.getAngleTo(this.pos2);

        this.cutPos = center.operator_add(RVector.createPolar(radius, angle));
        this.cutPos2 = center.operator_add(RVector.createPolar(radius, angle2));

        // introduce tiny gap to make sure full arc is still rendered correctly
        // in other CAD systems:
        var arc = new RArc(
                this.shape.getCenter(),
                this.shape.getRadius(),
                angle,
                angle2,
                false);
        e = new RArcEntity(this.entity.getDocument(), new RArcData(arc));
        e.copyAttributesFrom(this.entity.data());
        op.addObject(e, false);
        var arc2 = new RArc(
                    this.shape.getCenter(),
                    this.shape.getRadius(),
                    angle2,
                    angle,
                    false);
        e = new RArcEntity(this.entity.getDocument(), new RArcData(arc2));
        e.copyAttributesFrom(this.entity.data());
        op.addObject(e, false);
    }
    else if (isEllipseShape(this.shape) && this.shape.isFullEllipse()) {
        op.deleteObject(this.entity);
        center = this.shape.getCenter();
        var ellipseAngle = this.shape.getAngle();

        angle = center.getAngleTo(this.pos) - ellipseAngle;
        angle2 = center.getAngleTo(this.pos2) - ellipseAngle;

        this.cutPos = this.shape.getPointAt(angle);
        this.cutPos2 = this.shape.getPointAt(angle2);

        var ellipse = this.shape.clone();
        ellipse.setStartParam(ellipse.angleToParam(angle));
        ellipse.setEndParam(ellipse.angleToParam(angle2));
        e = new REllipseEntity(this.entity.getDocument(), new REllipseData(ellipse));
        e.copyAttributesFrom(this.entity.data());
        op.addObject(e, false);

        var ellipse2 = this.shape.clone();
        ellipse2.setStartParam(ellipse2.angleToParam(angle2));
        ellipse2.setEndParam(ellipse2.angleToParam(angle));
        e = new REllipseEntity(this.entity.getDocument(), new REllipseData(ellipse2));
        e.copyAttributesFrom(this.entity.data());
        op.addObject(e, false);
    }
    else {
        var shape1 = this.shape.clone();
        var shape2 = this.shape.clone();

        shape1 = trimEndPoint(shape1, this.pos);
        this.cutPos = shape1.getEndPoint();
        shape2 = trimStartPoint(shape2, this.pos);

        // modify chosen entity into first part:
        modifyEntity(op, this.entity.data(), shape1);
        //this.entity.setShape(shape1);
        //op.addObject(this.entity, false);

        // add second part as new entity:
        if (isLineBasedShape(shape2) || isArcShape(shape2) ||
            isEllipseShape(shape2) || isSplineShape(shape2)) {

            e = shapeToEntity(this.entity.getDocument(), shape2);
            if (!isNull(e)) {
                e.copyAttributesFrom(this.entity.data());
                op.addObject(e, false);
            }
        }
    }
    return op;
};

Divide.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

Divide.prototype.getAuxPreview = function() {
    if (!isValidVector(this.cutPos)) {
        return undefined;
    }

    var ret = [];

    var view = EAction.getGraphicsView();
    var overlap = view.mapDistanceFromView(25);

    var line = new RLine(this.cutPos, this.pos);
    var points = line.getPointsWithDistanceToEnd(-overlap);
    line = new RLine(points[0], points[1]);
    ret.push(line);

    return ret;
};

