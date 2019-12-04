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

function BreakOut(guiAction) {
    Modify.call(this, guiAction);

    this.entity = undefined;
    this.pos = undefined;
    this.removeSegment = true;
    this.extend = false;

    this.setUiOptions("BreakOut.ui");
}

BreakOut.prototype = new Modify();

BreakOut.State = {
    ChoosingEntity : 0
};

BreakOut.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(BreakOut.State.ChoosingEntity);
};

BreakOut.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case BreakOut.State.ChoosingEntity:
        this.entity = undefined;
        this.shape = undefined;
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        var tr;
        if (RSpline.hasProxy() && RPolyline.hasProxy()) {
            tr = qsTr("Choose line, arc, circle, ellipse, spline or polyline segment");
        }
        else {
            tr = qsTr("Choose line, arc, circle or ellipse segment");
        }
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }

};

BreakOut.prototype.escapeEvent = function() {
    switch (this.state) {
    case BreakOut.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

BreakOut.prototype.pickEntity = function(event, preview) {
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
    case BreakOut.State.ChoosingEntity:
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

        if (!EAction.assertEditable(entity, preview)) {
            break;
        }

        this.entity = entity;
        this.pos = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
        }
        break;
    }
};

BreakOut.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || isNull(this.entity)) {
        return undefined;
    }

    if (preview) {
        // no preview of operation:
        return;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    BreakOut.breakOut(op, this.entity, this.pos, this.extend, this.removeSegment);

    return op;
};

BreakOut.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

BreakOut.prototype.getAuxPreview = function() {
//    if (!isValidVector(this.cutPos)) {
//        return undefined;
//    }

//    var ret = [];

//    var view = EAction.getGraphicsView();
//    var overlap = view.mapDistanceFromView(25);

//    var line = new RLine(this.cutPos, this.pos);
//    var points = line.getPointsWithDistanceToEnd(-overlap);
//    line = new RLine(points[0], points[1]);
//    ret.push(line);

//    return ret;
};

BreakOut.prototype.slotRemoveSegmentChanged = function(value) {
    this.removeSegment = value;
};

/**
 * Breaks out the segment closest to pos from the given entity.
 *
 * \param op RAddObjectsOperation
 * \param entity REntity
 * \param pos RVector
 * \param extend True to extend to closesd intersections instead.
 * \param removeSegment True to remove (delete) broken out segment.
 *
 * \return True on success or false otherwise.
 */
BreakOut.breakOut = function(op, entity, pos, extend, removeSegment) {
    var doc = entity.getDocument();
    var shape = entity.getClosestShape(pos);

    var otherShapes = ShapeAlgorithms.getIntersectingShapes(doc, entity.getId(), shape, extend);
    var newSegments = ShapeAlgorithms.autoSplit(shape, otherShapes, pos, extend);

    if (isNull(newSegments)) {
        return false;
    }

    var e;

    if (isNull(newSegments[0]) && isNull(newSegments[1])) {
        if (!extend && removeSegment) {
            // delete entity completely:
            op.deleteObject(entity);
        }
    }
    else {
        // replace circle with arc:
        if (isCircleEntity(entity)) {
            op.deleteObject(entity);
            if (!isNull(newSegments[2])) {
                if (extend || !removeSegment) {
                    e = shapeToEntity(doc, newSegments[2]);
                    if (!isNull(e)) {
                        e.copyAttributesFrom(entity.data());
                        op.addObject(e, false);
                    }
                }
            }
        }

        // change existing entity into segment if we keep the segment,
        // otherwise delete existing entity
        else {
            if (removeSegment && !extend) {
                // delete entity completely:
                op.deleteObject(entity);
            }
            else {
                //modifyEntity(op, entity.data(), newSegments[2]);
                if (!isNull(newSegments[2])) {
                    modifyEntity(op, entity.clone(), newSegments[2]);
                }
            }
        }
    }

    if (!extend) {
        if (!BreakOut.drop(newSegments[0])) {
            e = shapeToEntity(entity.getDocument(), newSegments[0]);
            if (!isNull(e)) {
                e.copyAttributesFrom(entity.data());
                op.addObject(e, false);
            }
        }

        if (!BreakOut.drop(newSegments[1])) {
            e = shapeToEntity(entity.getDocument(), newSegments[1]);
            if (!isNull(e)) {
                e.copyAttributesFrom(entity.data());
                op.addObject(e, false);
            }
        }
    }

    return true;
};

BreakOut.drop = function(shape) {
    if (isNull(shape)) {
        return true;
    }

    if (isLineShape(shape) || isArcShape(shape)) {
        if (shape.getLength()<=RS.PointTolerance) {
            // drop zero length segments:
            return true;
        }
    }

    return false;
};
