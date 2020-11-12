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

include("scripts/Modify/Modify.js");
include("scripts/ShapeAlgorithms.js");

function BreakOutManual(guiAction) {
    Modify.call(this, guiAction);

    this.entity = undefined;
    this.shape = undefined;
    this.ceids = [];
    this.point1 = undefined;
    this.point2 = undefined;
    this.point3 = undefined;
    this.point4 = undefined;
    this.removeSegment = true;

    this.setUiOptions("BreakOutManual.ui");
}

BreakOutManual.prototype = new Modify();

BreakOutManual.State = {
    SettingShape : 0,
    SettingPoint1 : 1,
    SettingPoint2 : 2,
    SelectCircleEllipsePart : 3
};

BreakOutManual.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);
    this.setState(BreakOutManual.State.SettingShape);
};

BreakOutManual.prototype.escapeEvent = function() {
    switch (this.state) {
    case BreakOutManual.State.SettingShape:
        EAction.prototype.escapeEvent.call(this);
        return;
    case BreakOutManual.State.SettingPoint1:
        this.setState(BreakOutManual.State.SettingShape);
        break;
    case BreakOutManual.State.SettingPoint2:
        this.setState(BreakOutManual.State.SettingPoint1);
        break;
    case BreakOutManual.State.SelectCircleEllipsePart:
        this.setState(BreakOutManual.State.SettingShape);
        break;
    }
};

BreakOutManual.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);
    var di = this.getDocumentInterface();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case BreakOutManual.State.SettingShape:
        di.setClickMode(RAction.PickEntity);
        var trFirstPoint;
        if (RSpline.hasProxy() && RPolyline.hasProxy()) {
            trFirstPoint = qsTr("Choose line, arc, circle, ellipse, spline or polyline to break up");
        }
        else {
            trFirstPoint = qsTr("Choose line, arc, circle or ellipse to break up");
        }
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trCancel);
        this.ceids = [];
        break;
    case BreakOutManual.State.SettingPoint1:
        this.point2 = undefined;
        di.setClickMode(RAction.PickCoordinate);
        var trSecondPoint = qsTr("First break point");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trDone);
        break;
    case BreakOutManual.State.SettingPoint2:
        this.point4 = undefined;
        di.setClickMode(RAction.PickCoordinate);
        var trThirdPoint = qsTr("Second break point");
        this.setCommandPrompt(trThirdPoint);
        this.setLeftMouseTip(trThirdPoint);
        this.setRightMouseTip(EAction.trDone);
        break;
    case BreakOutManual.State.SelectCircleEllipsePart:
        di.setClickMode(RAction.PickEntity);
        var cepos = qsTr("Click the part of the circle or ellipse to remove");
        this.setCommandPrompt(cepos);
        this.setLeftMouseTip(cepos);
        this.setRightMouseTip(EAction.trDone);
        break;
    }

    this.setCrosshairCursor();
    EAction.showSnapTools();
};

BreakOutManual.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    this.entity = entity;

    switch (this.state) {
    case BreakOutManual.State.SettingShape:
        var cond = isLineBasedEntity(entity) ||
            isArcEntity(entity) ||
            isCircleEntity(entity) ||
            isEllipseEntity(entity) ||
            (RSpline.hasProxy() && isSplineEntity(entity)) ||
            (RPolyline.hasProxy() && isPolylineEntity(entity));

        if (!cond) {
            if (!preview) {
                if (RSpline.hasProxy() && RPolyline.hasProxy()) {
                    EAction.warnNotLineArcCircleEllipseSplinePolyline();
                }
                else {
                    EAction.warnNotLineArcCircleEllipse();
                }
            }
            break;
        }
        else {
            di.highlightEntity(this.entity.getId());
        }

        if (!EAction.assertEditable(entity, preview)) {
            break;
        }
        if (!preview) {
            this.shape = entity.getClosestShape(pos);
            this.setState(BreakOutManual.State.SettingPoint1);
        }
        break;
    case BreakOutManual.State.SelectCircleEllipsePart:
        di.highlightEntity(this.entity.getId());
        if (!preview) {
            if (this.ceids.indexOf(this.entity.getId())!==-1) {
                var op = new RDeleteObjectOperation(this.entity);
                op.setTransactionGroup(doc.getTransactionGroup());
                if (!isNull(op)) {
                    di.applyOperation(op);
                }
            }
            this.setState(BreakOutManual.State.SettingShape);
        }
        break;
    }
};

BreakOutManual.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var line;
    var op;

    if (isNull(this.shape)) {
        return;
    }
    switch (this.state) {
    case BreakOutManual.State.SettingPoint1:
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
            this.setState(BreakOutManual.State.SettingPoint2);
        }
        break;

    case BreakOutManual.State.SettingPoint2:
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
                doc.startTransactionGroup();
                op.setTransactionGroup(doc.getTransactionGroup());
                var t = di.applyOperation(op);

                if ((isCircleEntity(this.entity) || isFullEllipseEntity(this.entity)) && this.removeSegment) {
                    if (this.point2.equalsFuzzy(this.point4)) {
                        this.setState(BreakOutManual.State.SettingShape);
                    } else {
                        // remember IDs of added entities from transaction:
                        // used to make sure user cannot delete another entity:
                        this.ceids = t.getAffectedObjects();
                        this.setState(BreakOutManual.State.SelectCircleEllipsePart);
                    }
                } else {
                    this.setState(BreakOutManual.State.SettingShape);
                }
            }
        }
        break;
	}
};

BreakOutManual.prototype.getOperation = function(preview) {
    //var newSegments = BreakOutManual.autoTrim(this.shape, this.point2, this.point4);
    var newSegments = ShapeAlgorithms.autoSplitManual(this.shape, undefined, undefined, this.point2, this.point4, RVector.getAverage(this.point2, this.point4));

    if (isNull(newSegments)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    var e;

    // replace circle with arc:
    if (isCircleEntity(this.entity) || isFullEllipseEntity(this.entity)) {
        op.deleteObject(this.entity);
        if (!isNull(newSegments[2])) {
            e = shapeToEntity(this.entity.getDocument(), newSegments[2]);
            if (!isNull(e)) {
                e.copyAttributesFrom(this.entity.data());
                op.addObject(e, false);
            }
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
        if (!isNull(e)) {
            e.copyAttributesFrom(this.entity.data());
            op.addObject(e, false);
        }
    }

    if (!isNull(newSegments[1])) {
        e = shapeToEntity(this.entity.getDocument(), newSegments[1])
        if (!isNull(e)) {
            e.copyAttributesFrom(this.entity.data());
            op.addObject(e, false);
        }
    }

    return op;
};

BreakOutManual.prototype.slotRemoveSegmentChanged = function(value) {
    this.removeSegment = value;
};
