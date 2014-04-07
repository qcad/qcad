/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

function Break(guiAction) {
    Modify.call(this, guiAction);

    this.entity = undefined;
    this.shape = undefined;
    this.cedo1 = undefined;     // circle/ellipse draw order
    this.cedo2 = undefined;
    this.point1 = undefined;
    this.point2 = undefined;
    this.point3 = undefined;
    this.point4 = undefined;
    this.removeSegment = true;

    this.setUiOptions("Break.ui");
}

Break.prototype = new Modify();

Break.State = {
    SettingShape : 0,
    SettingPoint1 : 1,
    SettingPoint2 : 2,
    SelectCircleEllipsePart : 3
};

Break.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);
    this.setState(Break.State.SettingShape);
};

Break.prototype.escapeEvent = function() {
    switch (this.state) {
    case Break.State.SettingShape:
        EAction.prototype.escapeEvent.call(this);
        return;
    case Break.State.SettingPoint1:
        this.setState(Break.State.SettingShape);
        break;
    case Break.State.SettingPoint2:
        this.setState(Break.State.SettingPoint1);
        break;
    case Break.State.SelectCircleEllipsePart:
        this.setState(Break.State.SettingShape);
        break;
    }
};

Break.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Break.State.SettingShape:
        di.setClickMode(RAction.PickEntity);
        var trFirstPoint = qsTr("Select entity to break");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case Break.State.SettingPoint1:
        this.point2 = undefined;
        di.setClickMode(RAction.PickCoordinate);
        var trSecondPoint = qsTr("Select first break point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(qsTr("Done"));
        break;
    case Break.State.SettingPoint2:
        this.point4 = undefined;
        di.setClickMode(RAction.PickCoordinate);
        var trThirdPoint = qsTr("Select second break point");
        this.setCommandPrompt(trThirdPoint);
        this.setLeftMouseTip(trThirdPoint);
        this.setRightMouseTip(qsTr("Done"));
        break;
    case Break.State.SelectCircleEllipsePart:
        di.setClickMode(RAction.PickEntity);
        var cepos = qsTr("Select the part of the circle/ellipse to remove");
        this.setCommandPrompt(cepos);
        this.setLeftMouseTip(cepos);
        this.setRightMouseTip(qsTr("Done"));
        break;
    }

    this.setCrosshairCursor();
    EAction.showSnapTools();
};

Break.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    this.entity = entity;
    di.highlightEntity(this.entity.getId());

    switch (this.state) {
    case Break.State.SettingShape:
        var cond = isLineEntity(entity) ||
            isArcEntity(entity) ||
            isCircleEntity(entity) ||
            isEllipseEntity(entity) ||
            (RSpline.hasProxy() && isSplineEntity(entity));

        if (!cond) {
            if (!preview) {
                if (RSpline.hasProxy()) {
                    EAction.warnNotLineArcCircleEllipseSpline();
                }
                else {
                    EAction.warnNotLineArcCircleEllipse();
                }
            }
            break;
        }

        if (!EAction.assertEditable(entity, preview)) {
            break;
        }
        if (!preview) {
            this.shape = entity.getClosestShape(pos);
            this.setState(Break.State.SettingPoint1);
        }
        break;
    case Break.State.SelectCircleEllipsePart:
        if (!preview) {
            if (this.entity.getDrawOrder() === this.cedo1 || this.entity.getDrawOrder() === this.cedo2) {
                var op = new RDeleteObjectOperation(this.entity);
                if (!isNull(op)) {
                    di.applyOperation(op);
                }
                this.setState(Break.State.SettingShape);
            }
        }
        break;
    }
};

Break.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var line;
    var op;

    if (isNull(this.shape)) {
        return;
    }
    switch (this.state) {
    case Break.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        if (!isValidVector(this.point1)) {
            return;
        }
        this.point2 = this.shape.getClosestPointOnShape(this.point1, true);
        if (!isValidVector(this.point2)) {
            if (this.point1.getDistanceTo(this.entity.getStartPoint()) <= this.point1.getDistanceTo(this.entity.getEndPoint())) {
                this.point2 = this.entity.getStartPoint();
            } else {
                this.point2 = this.entity.getEndPoint();
            }
            //return;
        }
        di.highlightEntity(this.entity.getId());

        if (preview) {
            line = new RLine(this.point1, this.point2);
            di.addAuxShapeToPreview(line);
        } else  {
            this.setState(Break.State.SettingPoint2);
        }
        break;
    case Break.State.SettingPoint2:
        this.point3 = event.getModelPosition();
        if (!isValidVector(this.point3)) {
            return;
        }
        this.point4 = this.shape.getClosestPointOnShape(this.point3, true);
        if (!isValidVector(this.point4)) {
            if (this.point3.getDistanceTo(this.entity.getStartPoint()) <= this.point3.getDistanceTo(this.entity.getEndPoint())) {
                this.point4 = this.entity.getStartPoint();
            } else {
                this.point4 = this.entity.getEndPoint();
            }
            //return;
        }
        di.highlightEntity(this.entity.getId());

        if (preview) {
            line = new RLine(this.point3, this.point4);
            di.addAuxShapeToPreview(line);
        } else  {
            op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }

            if ((isCircleEntity(this.entity) || isFullEllipseEntity(this.entity)) && this.removeSegment) {
                if (this.point2.equalsFuzzy(this.point4)) {
                    this.setState(Break.State.SettingShape);
                } else {
                    this.cedo1 = this.getDocument().getStorage().getMaxDrawOrder() - 1;
                    this.cedo2 = this.getDocument().getStorage().getMaxDrawOrder() - 2;
                    this.setState(Break.State.SelectCircleEllipsePart);
                }
            } else {
                this.setState(Break.State.SettingShape);
            }
        }
        break;
	}
};

Break.prototype.getOperation = function(preview) {
    var newSegments = Break.autoTrim(this.shape, this.point2, this.point4);

    if (isNull(newSegments)) {
        return undefined;
    }

    var op = new RMixedOperation();
    var e;

    // replace circle with arc:
    if (isCircleEntity(this.entity) || isFullEllipseEntity(this.entity)) {
        op.deleteObject(this.entity);
        if (!isNull(newSegments[2])) {
            e = shapeToEntity(this.entity.getDocument(), newSegments[2]);
            e.copyAttributesFrom(this.entity.data());
            op.addObject(e, false);
        }
    }

    // change existing entity into segment if we keep the segment,
    // otherwise delete existing entity
    else {
        if (this.removeSegment) {
            // delete entity completely:
            op.deleteObject(this.entity);
        }
        else {
            this.entity.setShape(newSegments[2]);
            op.addObject(this.entity, false);
        }
    }

    if (!isNull(newSegments[0])) {
        e = shapeToEntity(this.entity.getDocument(), newSegments[0]);
        e.copyAttributesFrom(this.entity.data());
        op.addObject(e, false);
    }

    if (!isNull(newSegments[1])) {
        e = shapeToEntity(this.entity.getDocument(), newSegments[1])
        e.copyAttributesFrom(this.entity.data());
        op.addObject(e, false);
    }

    return op;
};

Break.prototype.slotRemoveSegmentChanged = function(value) {
    this.removeSegment = value;
};


/**
 * Breaks the closest segment in shape between two break points
 *
 * \return Array of three new shapes which each might be undefined if its
 * length would otherwise be 0.
 * The first shape is the rest at the start of the shape.
 * The second shape is the rest at the end of the shape.
 * The third shape is the segment self in its new shape.
 */
Break.autoTrim = function(shape, brkpt1, brkpt2) {
    var cutPos1 = brkpt1;
    var cutPos2 = brkpt2;

    if (!isCircleShape(shape) && !isFullEllipseShape(shape)) {
        if (!isValidVector(cutPos1) || !isValidVector(cutPos2)) {
            // full circle or ellipse requires two intersection points:
            return undefined;
        }
    }

    var rest1 = undefined;
    var rest2 = undefined;
    var segment = undefined;

    // lines:
    if (isLineShape(shape)) {
        rest1 = shape.clone();
        rest2 = shape.clone();

        if (shape.getStartPoint().getDistanceTo(cutPos1) <
            shape.getStartPoint().getDistanceTo(cutPos2)) {
            rest1.trimEndPoint(cutPos1);
            rest2.trimStartPoint(cutPos2);
        }
        else {
            rest1.trimEndPoint(cutPos2);
            rest2.trimStartPoint(cutPos1);
        }

        segment = shape.clone();
        segment.setStartPoint(cutPos1);
        segment.setEndPoint(cutPos2);

        if (rest1.getLength()<RS.PointTolerance) {
            rest1 = undefined;
        }

        if (rest2.getLength()<RS.PointTolerance) {
            rest2 = undefined;
        }
    }

    // arcs / ellipse arcs:
    else if (isArcShape(shape) || isEllipseArcShape(shape)) {
        rest1 = shape.clone();
        rest2 = shape.clone();

        rest1.trimEndPoint(cutPos1);
        rest2.trimStartPoint(cutPos2);

        segment = shape.clone();
        segment.trimStartPoint(cutPos1);
        segment.trimEndPoint(cutPos2);

        var angleLength1 = rest1.getAngleLength(true);
        var angleLength2 = rest2.getAngleLength(true);

        if (angleLength1+angleLength2 > shape.getAngleLength()) {
            rest1.trimEndPoint(cutPos2);
            rest2.trimStartPoint(cutPos1);

            segment.trimStartPoint(cutPos2);
            segment.trimEndPoint(cutPos1);

            angleLength1 = rest1.getAngleLength(true);
            angleLength2 = rest2.getAngleLength(true);
        }

        if (angleLength1<1.0e-5) {
            rest1 = undefined;
        }

        if (angleLength2<1.0e-5) {
            rest2 = undefined;
        }
    }

    // circles:
    else if (isCircleShape(shape)) {
        if (!isValidVector(cutPos1) || !isValidVector(cutPos2)) {
            rest1 = undefined;
            rest2 = undefined;
        }
        else {
            var angle1 = shape.getCenter().getAngleTo(cutPos1);
            var angle2 = shape.getCenter().getAngleTo(cutPos2);

            if (angle1 === angle2) {
                rest1 = undefined;
            } else {
                rest1 = new RArc(
                        shape.getCenter(),
                        shape.getRadius(),
                        angle1, angle2,
                        false);
            }
            rest2 = undefined;

            segment = new RArc(
                        shape.getCenter(),
                        shape.getRadius(),
                        angle2, angle1,
                        false);

            if (!isNull(rest1)) {
                angleLength1 = rest1.getAngleLength();

                if (angleLength1<RS.AngleTolerance) {
                    rest1 = undefined;
                }
            }
        }
    }
    // full ellipses:
    else if (isFullEllipseShape(shape)) {
        if (!isValidVector(cutPos1) || !isValidVector(cutPos2)) {
            rest1 = undefined;
            rest2 = undefined;
        }
        else {
            angle1 = shape.getParamTo(cutPos1);
            angle2 = shape.getParamTo(cutPos2);

            if (angle1 === angle2) {
                rest1 = undefined;
            } else {
            rest1 = new REllipse(
                        shape.getCenter(),
                        shape.getMajorPoint(),
                        shape.getRatio(),
                        angle1, angle2,
                        false);
            }
            rest2 = undefined;

            segment = new REllipse(
                        shape.getCenter(),
                        shape.getMajorPoint(),
                        shape.getRatio(),
                        angle2, angle1,
                        false);

            if (!isNull(rest1)) {
                angleLength1 = rest1.getAngleLength();

                if (angleLength1<RS.AngleTolerance) {
                    rest1 = undefined;
                }
            }
        }
    }
    // spline:
    else if (isSplineShape(shape)) {
        rest1 = shape.clone();
        rest2 = shape.clone();
        segment = shape.clone();

        var tAtCutPos1 = shape.getTAtPoint(cutPos1);
        var tAtCutPos2 = shape.getTAtPoint(cutPos2);

        if (shape.getStartPoint().equalsFuzzy(shape.getEndPoint())) {
            if (RMath.fuzzyCompare(tAtCutPos1, shape.getTMax())) {
                tAtCutPos1 = shape.getTMin();
            }
        }

        if (tAtCutPos1 < tAtCutPos2) {
            rest1.trimEndPoint(cutPos1);
            segment.trimStartPoint(cutPos1);
            segment.trimEndPoint(cutPos2);
            rest2.trimStartPoint(cutPos2);
        }
        else {
            rest1.trimEndPoint(cutPos2);
            segment.trimStartPoint(cutPos2);
            segment.trimEndPoint(cutPos1);
            rest2.trimStartPoint(cutPos1);
        }

        if (!segment.isValid() || segment.getLength()<RS.PointTolerance) {
            segment = undefined;
        }

        if (!rest1.isValid() || rest1.getLength()<RS.PointTolerance) {
            rest1 = undefined;
        }

        if (!rest2.isValid() || rest2.getLength()<RS.PointTolerance) {
            rest2 = undefined;
        }
    }

    var ret = [];

    // add new rest entities:
    ret.push(rest1);
    ret.push(rest2);
    ret.push(segment);

    return ret;
};
