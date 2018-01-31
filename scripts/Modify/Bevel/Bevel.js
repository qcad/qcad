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

include("../ModifyCorner.js");
include("scripts/ShapeAlgorithms.js");

function Bevel(guiAction) {
    ModifyCorner.call(this, guiAction);

    this.distance1 = 1.0;
    this.distance2 = 1.0;

    this.setUiOptions("Bevel.ui");
}

Bevel.prototype = new ModifyCorner();

Bevel.prototype.beginEvent = function() {
    ModifyCorner.prototype.beginEvent.call(this);
};

Bevel.prototype.getOperation = function(preview) {
    if (!isEntity(this.entity1) || !isEntity(this.entity2)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var success = Bevel.bevel(
            op,
            this.entity1.clone(), this.clickPos1,
            this.entity2.clone(), this.clickPos2,
            this.trim,
            this.distance1, this.distance2,
            preview);

    if (!success && !preview) {
        EAction.handleUserWarning(qsTr("The two entities cannot be bevelled."));
    }

    return op;
};

/**
 * Bevels or extends the given entity2 to the intersection point of the
 * entity2 and the limitingShape.
 *
 * \param entity1 First entity which will be bevelled.
 * \param clickPos1 Coordinate that was clicked when the user selected entity1.
 * \param entity2 Second entity which will be bevelled.
 * \param clickPos2 Coordinate that was clicked when the user selected entity2.
 * \param trim true: Trim both entities to bevel line.
 * \param distance1 Distance of bevel line from end point of entity1.
 * \param distance2 Distance of bevel line from end point of entity2.
 * \param preview Operation is used for preview.
 */
Bevel.bevel = function(op, entity1, clickPos1, entity2, clickPos2, trim, distance1, distance2, preview) {
    if (!isEntity(entity1) || !isValidVector(clickPos1) ||
        !isEntity(entity2) || !isValidVector(clickPos2) ||
        !isBoolean(trim)) {

        return false;
    }

    var samePolyline = (entity1.getId()===entity2.getId() && isPolylineEntity(entity1));

    var shape1P = entity1.getClosestShape(clickPos1);
    var shape2P = entity2.getClosestShape(clickPos2);
    var shape1 = shape1P.data();
    var shape2 = shape2P.data();

    var newShapes = Bevel.bevelShapes(shape1, clickPos1, shape2, clickPos2, trim, samePolyline, distance1, distance2);

    if (newShapes.length===0) {
        return false;
    }

    // add new trimmed entities or polyline:
    if (trim && !modifyEntity(op, entity1, newShapes[0])) {
        if (!preview) {
            EAction.handleUserWarning(qsTr("First entity cannot be trimmed."));
        }
    }

    if (newShapes.length<3) {
        // beveling was within same polyline:
        return true;
    }

    if (trim && !modifyEntity(op, entity2, newShapes[2])) {
        if (!preview) {
            EAction.handleUserWarning(qsTr("Second entity cannot be trimmed."));
        }
    }

    op.addObject(new RLineEntity(entity1.getDocument(), new RLineData(newShapes[1])));

    return true;
};

Bevel.bevelShapes = function(shape1, clickPos1, shape2, clickPos2, trim, samePolyline, distance1, distance2) {
    if (!isShape(shape1) || !isShape(shape2)) {
        return [];
    }

    // convert circles to arcs:
    if (isCircleShape(shape1)) {
        shape1 = ShapeAlgorithms.circleToArc(shape1);
    }
    if (isCircleShape(shape2)) {
        shape2 = ShapeAlgorithms.circleToArc(shape2);
    }

    var simpleShape1 = shape1;
    var simpleShape2 = shape2;
    var i1, i2;

    if (isPolylineShape(shape1)) {
        i1 = shape1.getClosestSegment(clickPos1);
        if (i1===-1) {
            return [];
        }
        simpleShape1 = shape1.getSegmentAt(i1).data();
    }

    if (isPolylineShape(shape2)) {
        i2 = shape2.getClosestSegment(clickPos2);
        if (i2===-1) {
            return [];
        }
        simpleShape2 = shape2.getSegmentAt(i2).data();
    }

    // get intersection point(s) between two shapes:
    var sol = simpleShape1.getIntersectionPoints(simpleShape2, false);

    if (sol.length===0) {
        return [];
    }

    //var trimmed1 = shape1.clone();
    //var trimmed2 = shape2.clone();
    var trimmed1, trimmed2;
    if (samePolyline) {
        trimmed1 = simpleShape1.clone();
        trimmed2 = simpleShape2.clone();
    }
    else {
        trimmed1 = shape1.clone();
        trimmed2 = shape2.clone();
    }

    // trim shapes to intersection:
    var start1 = RS.FromAny;
    var is = clickPos1.getClosest(sol);
    var ending1 = RS.EndingNone;
    if (isFunction(trimmed1.getTrimEnd)) {
        ending1 = trimmed1.getTrimEnd(is, clickPos1);
        switch (ending1) {
        case RS.EndingStart:
            trimmed1 = trimStartPoint(trimmed1, is, clickPos1);
            start1 = RS.FromStart;
            break;
        case RS.EndingEnd:
            trimmed1 = trimEndPoint(trimmed1, is, clickPos1);
            if (isRayShape(trimmed1)) {
                start1 = RS.FromStart;
                ending1 = RS.EndingStart;
            }
            else {
                start1 = RS.FromEnd;
            }
            break;
        default:
            break;
        }
    }

    var start2 = RS.FromAny;
    is = clickPos2.getClosest(sol);
    var ending2 = RS.EndingNone;
    if (isFunction(trimmed2.getTrimEnd)) {
        ending2 = trimmed2.getTrimEnd(is, clickPos2);
        switch (ending2) {
        case RS.EndingStart:
            trimmed2 = trimStartPoint(trimmed2, is, clickPos2);
            start2 = RS.FromStart;
            break;
        case RS.EndingEnd:
            trimmed2 = trimEndPoint(trimmed2, is, clickPos2);
            if (isRayShape(trimmed2)) {
                start2 = RS.FromStart;
                ending2 = RS.EndingStart;
            }
            else {
                start2 = RS.FromEnd;
            }

            break;
        default:
            break;
        }
    }

    // find definitive bevel points:
    var t1 = trimmed1;
    if (isCircleShape(trimmed1)) {
        t1 = ShapeAlgorithms.circleToArc(trimmed1, t1.getCenter().getAngleTo(is));
        start1 = RS.FromAny;
    }
    var t2 = trimmed2;
    if (isCircleShape(trimmed2)) {
        t2 = ShapeAlgorithms.circleToArc(trimmed2, t2.getCenter().getAngleTo(is));
        start2 = RS.FromAny;
    }

    var bp1 = t1.getPointsWithDistanceToEnd(distance1, start1);
    if (bp1.length===0) {
        return [];
    }
    bp1 = clickPos2.getClosest(bp1);

    var bp2 = t2.getPointsWithDistanceToEnd(distance2, start2);
    if (bp2.length===0) {
        return [];
    }
    bp2 = clickPos2.getClosest(bp2);

    // final trim:
    if (trim || samePolyline) {
        switch (ending1) {
        case RS.EndingStart:
            trimmed1.trimStartPoint(bp1);
            break;
        case RS.EndingEnd:
            trimmed1.trimEndPoint(bp1);
            break;
        default:
            break;
        }

        switch (ending2) {
        case RS.EndingStart:
            trimmed2.trimStartPoint(bp2);
            break;
        case RS.EndingEnd:
            trimmed2.trimEndPoint(bp2);
            break;
        default:
            break;
        }
    }

    var bevel = new RLine(bp1, bp2);

    if (samePolyline) {
        var pl = shape1.modifyPolylineCorner(trimmed1, ending1, i1, trimmed2, ending2, i2, bevel);
        return [ pl ];
    }

    return [ trimmed1, bevel, trimmed2 ];
};

Bevel.prototype.slotLength1Changed = function(value) {
    this.distance1 = value;
}

Bevel.prototype.slotLength2Changed = function(value) {
    this.distance2 = value;
}

