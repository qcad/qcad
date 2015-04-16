/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
        if (this.extend) {
            this.setLeftMouseTip(qsTr("Choose line, arc, circle or ellipse to auto trim"));
        }
        else {
            if (RSpline.hasProxy()) {
                this.setLeftMouseTip(qsTr("Choose line, arc, circle, ellipse or spline segment"));
            }
            else {
                this.setLeftMouseTip(qsTr("Choose line, arc, circle or ellipse segment"));
            }
        }
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
    var entityId = event.getEntityId();
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

    var shape = this.entity.getClosestShape(this.pos);

    if (isNull(shape)) {
        return undefined;
    }

    // find other shapes that potentially intersect with the chosen entity:
    var document = this.getDocument();
    var otherShapes = [];
    // allow for error: especialy for ellipse segments bordering to tangential lines this is needed:
    var otherEntityIds;

    if (this.extend) {
        // TODO: if we are extending, the 'rest' has to be queried instead
        otherEntityIds = document.queryIntersectedEntitiesXY(document.getBoundingBox().growXY(1.0e-2), true);
    }
    else {
        if (isXLineShape(shape) || isRayShape(shape)) {
            otherEntityIds = document.queryAllEntities();
        }
        else {
            otherEntityIds = document.queryIntersectedEntitiesXY(shape.getBoundingBox().growXY(1.0e-2));
        }
    }

    for (var i=0; i<otherEntityIds.length; i++) {
        if (otherEntityIds[i]===this.entity.getId()) {
            continue;
        }

        var otherEntity = document.queryEntity(otherEntityIds[i]);

        // TODO: if shape is arc, circle, ellipse or ellipse arc:
        // entities with full bounding box outside full circle or full ellipse
        // bounding box could be ignored.

        var s = otherEntity.getShapes();
        if (s.length!==0) {
            otherShapes = otherShapes.concat(s);
        }
    }

    var newSegments = ShapeAlgorithms.autoTrim(shape, otherShapes, this.pos, this.extend);

    if (isNull(newSegments)) {
        return undefined;
    }

    var op = new RMixedOperation();
    op.setText(this.getToolTitle());
    var e;

    if (isNull(newSegments[0]) && isNull(newSegments[1])) {
        if (!this.extend && this.removeSegment) {
            // delete entity completely:
            op.deleteObject(this.entity);
        }
    }
    else {
        // replace circle with arc:
        if (isCircleEntity(this.entity)) {
            op.deleteObject(this.entity);
            if (!isNull(newSegments[2])) {
                if (this.extend || !this.removeSegment) {
                    e = shapeToEntity(this.entity.getDocument(), newSegments[2]);
                    if (!isNull(e)) {
                        e.copyAttributesFrom(this.entity.data());
                        op.addObject(e, false);
                    }
                }
            }
        }

        // change existing entity into segment if we keep the segment,
        // otherwise delete existing entity
        else {
            if (this.removeSegment && !this.extend) {
                // delete entity completely:
                op.deleteObject(this.entity);
            }
            else {
                //modifyEntity(op, this.entity.data(), newSegments[2]);
                modifyEntity(op, this.entity.clone(), newSegments[2]);
            }
        }
    }

    if (!this.extend) {
        if (!isNull(newSegments[0])) {
            e = shapeToEntity(this.entity.getDocument(), newSegments[0]);
            if (!isNull(e)) {
                e.copyAttributesFrom(this.entity.data());
                op.addObject(e, false);
            }
        }

        if (!isNull(newSegments[1])/* && !this.removeSegment*/) {
            e = shapeToEntity(this.entity.getDocument(), newSegments[1])
            if (!isNull(e)) {
                e.copyAttributesFrom(this.entity.data());
                op.addObject(e, false);
            }
        }
    }

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


