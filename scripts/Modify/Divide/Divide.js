/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
        this.pos = undefined;
        this.cutPos = undefined;
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        if (RSpline.hasProxy() && RPolyline.hasProxy()) {
            this.setLeftMouseTip(qsTr("Choose line, arc, circle, ellipse, spline or polyline"));
        }
        else {
            this.setLeftMouseTip(qsTr("Choose line, arc, circle or ellipse"));
        }
        this.setRightMouseTip(EAction.trCancel);
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
    var entityId = this.getEntityId(event, preview);
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
            (RSpline.hasProxy() && isSplineEntity(entity)) ||
            (RPolyline.hasProxy() && isPolylineEntity(entity))) {

            this.entity = entity;

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(Divide.State.SettingPos);
            }
        }
        else {
            if (!preview) {
                if (RSpline.hasProxy() && RPolyline.hasProxy()) {
                    EAction.warnNotLineArcCircleEllipseSplinePolyline();
                }
                else {
                    EAction.warnNotLineArcCircleEllipse();
                }
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
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var cutPositions = Divide.divide(op, this.pos, this.pos2, this.entity);
    if (cutPositions.length===0) {
        op.destroy();
        return undefined;
    }
    this.cutPos = cutPositions[0];
    this.cutPos2 = cutPositions[1];

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

/**
 * Divides the given entity at the given one or two positions
 * as part of the given operation.
 *
 * \return Array of actual cut points.
 */
Divide.divide = function(op, pos1, pos2, entity) {
    if (isNull(pos1) || isNull(entity)) {
        return [];
    }

    entity = entity.clone();
    //var shape = entity.getClosestSimpleShape(pos);
    var shape = entity.castToShape();

    var res = Divide.divideShape(pos1, pos2, shape);
    if (isNull(res)) {
        return [];
    }

    var shape1 = res[0][0];
    var shape2 = res[0][1];

    op.deleteObject(entity);

    var e;
    if (!isNull(shape1)) {
        e = shapeToEntity(entity.getDocument(), shape1);
        e.copyAttributesFrom(entity);
        op.addObject(e, false);
    }

    if (!isNull(shape2)) {
        e = shapeToEntity(entity.getDocument(), shape2);
        e.copyAttributesFrom(entity);
        op.addObject(e, false);
    }

    return res[1];

//    else if (isPolylineShape(shape) && shape.isClosed()) {
//        shape.relocateStartPoint(pos1);
//        modifyEntity(op, entity, shape);
//        cutPos1 = pos1;
//        if (!isNull(pos2)) {
//            Divide.divide(op, pos2, undefined, entity);
//        }
//    }
//    else {
//        var shape1 = shape.clone();
//        var shape2 = shape.clone();

//        shape1 = trimEndPoint(shape1, pos1, pos1);

//        cutPos1 = shape1.getEndPoint();

//        shape2 = trimStartPoint(shape2, pos1, pos1);

//        // modify chosen entity into first part:
//        modifyEntity(op, entity, shape1);

//        // add second part as new entity:
//        if (isLineBasedShape(shape2) || isArcShape(shape2) ||
//            isEllipseShape(shape2) || isSplineShape(shape2) || isPolylineShape(shape2)) {

//            e = shapeToEntity(entity.getDocument(), shape2);
//            if (!isNull(e)) {
//                e.copyAttributesFrom(entity);
//                op.addObject(e, false);
//            }
//        }
//    }
//    return [cutPos1, cutPos2];
};


Divide.divideShape = function(pos1, pos2, shape) {
    if (isNull(pos1) || isNull(shape)) {
        return undefined;
    }

    // circles and ellipses require two cut points:
    if (isNull(pos2)) {
        if (isCircleShape(shape) || (isEllipseShape(shape) && shape.isFullEllipse())) {
            return undefined;
        }
    }

    var center;
    var angle = undefined;
    var angle2 = undefined;
    var e;
    var cutPos1 = undefined;
    var cutPos2 = undefined;

    if (isCircleShape(shape)) {
        center = shape.getCenter();
        var radius = shape.getRadius();
        angle = center.getAngleTo(pos1);
        angle2 = center.getAngleTo(pos2);

        cutPos1 = center.operator_add(RVector.createPolar(radius, angle));
        cutPos2 = center.operator_add(RVector.createPolar(radius, angle2));

        // introduce tiny gap to make sure full arc is still rendered correctly
        // in other CAD systems:
        var arc1 = new RArc(
            shape.getCenter(),
            shape.getRadius(),
            angle,
            angle2,
            false);
        var arc2 = new RArc(
            shape.getCenter(),
            shape.getRadius(),
            angle2,
            angle,
            false);

        return [ [ arc1, arc2 ], [ cutPos1, cutPos2 ] ];
    }
    else if (isEllipseShape(shape) && shape.isFullEllipse()) {
        center = shape.getCenter();
        var ellipseAngle = shape.getAngle();

        angle = center.getAngleTo(pos1) - ellipseAngle;
        angle2 = center.getAngleTo(pos2) - ellipseAngle;

        cutPos1 = shape.getPointAt(angle);
        cutPos2 = shape.getPointAt(angle2);

        var ellipse1 = shape.clone();
        ellipse1.setStartParam(ellipse1.angleToParam(angle));
        ellipse1.setEndParam(ellipse1.angleToParam(angle2));

        var ellipse2 = shape.clone();
        ellipse2.setStartParam(ellipse2.angleToParam(angle2));
        ellipse2.setEndParam(ellipse2.angleToParam(angle));

        return [ [ ellipse1, ellipse2 ], [ cutPos1, cutPos2 ] ];
    }
    else if (isPolylineShape(shape) && shape.isClosed()) {
        shape.relocateStartPoint(pos1);
        cutPos1 = pos1;
        if (!isNull(pos2)) {
            return Divide.divideShape(pos2, undefined, shape);
        }
        return [ [ shape, undefined ], [ pos1, undefined ] ];
    }
    else {
        var shape1 = shape.clone();
        var shape2 = shape.clone();

        shape1 = trimEndPoint(shape1, pos1, pos1);

        cutPos1 = shape1.getEndPoint();

        shape2 = trimStartPoint(shape2, pos1, pos1);

        return [ [ shape1, shape2 ], [ cutPos1, cutPos2 ] ];
    }
};
