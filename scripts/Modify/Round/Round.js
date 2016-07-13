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

include("../ModifyCorner.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Round
 * \brief Adds a rounding to two entities and optionally trims both entities.
 * \ingroup ecma_modify
 */
function Round(guiAction) {
    ModifyCorner.call(this, guiAction);

    this.radius = 1.0;

    this.setUiOptions("Round.ui");
}

Round.prototype = new ModifyCorner();

Round.includeBasePath = includeBasePath;

Round.prototype.getOperation = function(preview) {
    if (!isEntity(this.entity1) || !isEntity(this.entity2)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    var success = Round.round(
            op,
            this.entity1.clone(), this.clickPos1,
            this.entity2.clone(), this.clickPos2,
            this.trim,
            this.radius,
            this.posSolution,
            preview);

    if (!success && !preview) {
        EAction.handleUserWarning(qsTr("The two entities cannot be rounded."));
    }

    return op;
};

/**
 * Rounds or extends the given entity2 to the intersection point of the
 * entity2 and the limitingShape.
 *
 * \param op Operation to use to add new objects and modify objects.
 * \param entity1 First entity which will be rounded.
 * \param clickPos1 Coordinate that was clicked when the user selected entity1.
 * \param entity2 Second entity which will be rounded.
 * \param clickPos2 Coordinate that was clicked when the user selected entity2.
 * \param trim true: Trim both entities to rounding arc.
 * \param radius Radius of rounding.
 * \param solutionPos Position that determines which solution to apply (optional, defaults to clickPos1)
 * \param preview Operation is used for preview.
 */
Round.round = function(op, entity1, clickPos1, entity2, clickPos2, trim, radius, solutionPos, preview) {
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

    var newShapes = Round.roundShapes(shape1, clickPos1, shape2, clickPos2, trim, samePolyline, radius, solutionPos);

    if (newShapes.length===0) {
        return false;
    }

    // add new trimmed entities:
    if (trim && !modifyEntity(op, entity1, newShapes[0])) {
        if (!preview) {
            EAction.handleUserWarning(qsTr("First entity cannot be trimmed."));
        }
    }

    if (newShapes.length<3) {
        // rounding was within same polyline:
        return true;
    }

    if (trim && !modifyEntity(op, entity2, newShapes[2])) {
        if (!preview) {
            EAction.handleUserWarning(qsTr("Second entity cannot be trimmed."));
        }
    }

    // add rounding:
    op.addObject(new RArcEntity(entity1.getDocument(), new RArcData(newShapes[1])));

    return true;
};

/**
 * Rounds the given shape1 againt shape2.
 *
 * \param shape1 First shape which will be rounded.
 * \param clickPos1 Coordinate that was clicked when the user selected shape1.
 * \param shape2 Second shape which will be rounded.
 * \param clickPos2 Coordinate that was clicked when the user selected shape2.
 * \param trim true: Trim both shape to rounding arc.
 * \param radius Radius of rounding.
 * \param solutionPos Position that determines which solution to apply (optional, defaults to clickPos1)
 *
 * \return Array of three shapes: shape1 (trimmed), rounding, shape2 (trimmed)
 * or emtpy array.
 */
Round.roundShapes = function(shape1, clickPos1, shape2, clickPos2, trim, samePolyline, radius, solutionPos) {
    if (!isShape(shape1) || !isValidVector(clickPos1) ||
        !isShape(shape2) || !isValidVector(clickPos2) ||
        !isBoolean(trim)) {
        return [];
    }

    if (isNull(solutionPos)) {
        solutionPos = clickPos2;
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

    // create two temporary parallels:
    var par1 = ShapeAlgorithms.getOffsetShapes(simpleShape1, radius, 1, solutionPos);
    var par2 = ShapeAlgorithms.getOffsetShapes(simpleShape2, radius, 1, solutionPos);

    if (par1.length!==1 || par2.length!==1) {
        return [];
    }

    par1 = par1[0];
    par2 = par2[0];

    var sol2 = simpleShape1.getIntersectionPoints(simpleShape2, false);

    var ipParallel = par1.getIntersectionPoints(par2.data(), false);
    if (ipParallel.length===0) {
        return [];
    }

    // there might be two intersections: choose the closest:
    var ip = solutionPos.getClosest(ipParallel);
    var p1 = simpleShape1.getClosestPointOnShape(ip, false);
    var p2 = simpleShape2.getClosestPointOnShape(ip, false);
    var ang1 = ip.getAngleTo(p1);
    var ang2 = ip.getAngleTo(p2);
    var reversed = (RMath.getAngleDifference(ang1, ang2) > Math.PI);

    var arc = new RArc(ip, radius, ang1, ang2, reversed);

    var bp1 = arc.getStartPoint();
    var bp2 = arc.getEndPoint();

    var trimmed1, trimmed2;
    if (samePolyline) {
        trimmed1 = simpleShape1.clone();
        trimmed2 = simpleShape2.clone();
    }
    else {
        trimmed1 = shape1.clone();
        trimmed2 = shape2.clone();
    }

    var ending1, ending2;

    if (trim || samePolyline) {
        // trim entities to intersection
        var is2 = clickPos2.getClosest(sol2);
        ending1 = trimmed1.getTrimEnd(is2, clickPos1);
        switch (ending1) {
        case RS.EndingStart:
            trimmed1 = trimStartPoint(trimmed1, p1, clickPos1);
            break;
        case RS.EndingEnd:
            trimmed1 = trimEndPoint(trimmed1, p1, clickPos1);
            break;
        default:
            break;
        }

        is2 = clickPos1.getClosest(sol2);
        ending2 = trimmed2.getTrimEnd(is2, clickPos2);
        switch (ending2) {
        case RS.EndingStart:
            trimmed2 = trimStartPoint(trimmed2, p2, clickPos2);
            break;
        case RS.EndingEnd:
            trimmed2 = trimEndPoint(trimmed2, p2, clickPos2);
            break;
        default:
            break;
        }
    }

    if (samePolyline) {
        var pl = ShapeAlgorithms.modifyPolylineCorner(shape1, trimmed1, ending1, i1, shape2, trimmed2, ending2, i2, arc);
        return [ pl ];
    }

    return [ trimmed1, arc, trimmed2 ];
};

Round.prototype.getAuxPreview = function() {
    var ret = [];

    if (!isNull(this.par1)) {
        ret.push(this.par1);
    }
    if (!isNull(this.par2)) {
        ret.push(this.par2);
    }

    return ret;
}

Round.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
};

