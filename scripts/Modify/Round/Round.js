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
            this.entity1.clone(), this.pos1,
            this.entity2.clone(), this.pos2,
            this.trim,
            this.radius,
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
 * \param entity1 First entity which will be bevelled.
 * \param pos1 Coordinate that was clicked when the user selected entity1.
 * \param entity2 Second entity which will be bevelled.
 * \param pos2 Coordinate that was clicked when the user selected entity2.
 * \param trim true: Trim both entities to bevel line.
 * \param radius Radius of rounding.
 * \param preview Operation is used for preview.
 */
Round.round = function(op, entity1, pos1, entity2, pos2, trim, radius, preview) {
    if (!isEntity(entity1) || !isValidVector(pos1) ||
            !isEntity(entity2) || !isValidVector(pos2) ||
            !isBoolean(trim)) {
        return false;
    }

    var shape1P = entity1.getClosestShape(pos1);
    var shape2P = entity2.getClosestShape(pos2);
    var shape1 = shape1P.data();
    var shape2 = shape2P.data();

    if (!isShape(shape1) || !isShape(shape2)) {
        return false;
    }

    // convert circles to arcs:
    if (isCircleShape(shape1)) {
        shape1 = ShapeAlgorithms.circleToArc(shape1);
    }
    if (isCircleShape(shape2)) {
        shape2 = ShapeAlgorithms.circleToArc(shape2);
    }

    if (isPolylineEntity(entity1) && !isPolylineEntity(entity2)) {
        return false;
    }

    if (!isPolylineEntity(entity1) && isPolylineEntity(entity2)) {
        return false;
    }

    if (isPolylineEntity(entity1) && isPolylineEntity(entity2)) {
        if (entity1.getId()!==entity2.getId()) {
            return false;
        }
    }

    // find out whether we're rounding within a polyline:
    var polyline = undefined;
    var segments = undefined;
    var shapeIndex1 = undefined;
    var shapeIndex2 = undefined;
    if (entity1.getId()===entity2.getId() && isPolylineEntity(entity1)) {
        polyline = entity1.getData().castToShape();
        //qDebug("polyline: ", polyline);
        segments = polyline.getExploded();
        var minDistance1 = undefined;
        var minDistance2 = undefined;
        var segment;
        var distance;
        for (var i=0; i<segments.length; ++i) {
            segment = segments[i];

            distance = segment.getDistanceTo(pos1);
            if (isNull(minDistance1) || distance<minDistance1) {
                minDistance1 = distance;
                shapeIndex1 = i;
                shape1 = segment.clone();
            }

            distance = segment.getDistanceTo(pos2);
            if (isNull(minDistance2) || distance<minDistance2) {
                minDistance2 = distance;
                shapeIndex2 = i;
                shape2 = segment.clone();
            }
        }

        if (shapeIndex1===shapeIndex2) {
            return false;
        }

        if (shapeIndex2<shapeIndex1) {
            var tmp = shapeIndex1;
            shapeIndex1 = shapeIndex2;
            shapeIndex2 = tmp;

            tmp = shape1;
            shape1 = shape2;
            shape2 = tmp;
        }
    }

    // create two temporary parallels:
    var par1 = ShapeAlgorithms.getOffsetShapes(shape1, radius, 1, pos2);
    var par2 = ShapeAlgorithms.getOffsetShapes(shape2, radius, 1, pos2);

    if (par1.length!==1 || par2.length!==1) {
        return false;
    }

    par1 = par1[0];
    par2 = par2[0];

    this.par1 = par1.clone();
    this.par2 = par2.clone();

    var sol2 = shape1.getIntersectionPoints(shape2, false);
    var sol =  par1.getIntersectionPoints(par2, false);

    if (sol.length===0) {
        return false;
    }

    // there might be two intersections: choose the closest:
    var is = pos2.getClosest(sol);
    var p1 = shape1.getClosestPointOnShape(is, false);
    var p2 = shape2.getClosestPointOnShape(is, false);
    var ang1 = is.getAngleTo(p1);
    var ang2 = is.getAngleTo(p2);
    var reversed = (RMath.getAngleDifference(ang1, ang2) > Math.PI);

    var arc = new RArc(is, radius, ang1, ang2, reversed);

    var bp1 = arc.getStartPoint();
    var bp2 = arc.getEndPoint();

    var trimmed1 = shape1.clone();
    var trimmed2 = shape2.clone();

    var ending1 = RS.EndingStart;
    var ending2 = RS.EndingStart;


    if (trim || !isNull(polyline)) {
        // trim entities to intersection
        var is2 = pos2.getClosest(sol2);
        ending1 = trimmed1.getTrimEnd(pos1, is2);
        switch (ending1) {
        case RS.EndingStart:
            //trimmed1.trimStartPoint(p1);
            trimmed1 = trimStartPoint(trimmed1, p1);
            break;
        case RS.EndingEnd:
            //trimmed1.trimEndPoint(p1);
            trimmed1 = trimEndPoint(trimmed1, p1);
            break;
        default:
            break;
        }

        is2 = pos1.getClosest(sol2);
        ending2 = trimmed2.getTrimEnd(pos2, is2);
        switch (ending2) {
        case RS.EndingStart:
            //trimmed2.trimStartPoint(p2);
            trimmed2 = trimStartPoint(trimmed2, p2);
            break;
        case RS.EndingEnd:
            //trimmed2.trimEndPoint(p2);
            trimmed2 = trimEndPoint(trimmed2, p2);
            break;
        default:
            break;
        }

        // trim polyline segment and add bevel segment:
        if (!isNull(polyline)) {
            var trimmedPolyline = polyline.clone();
            trimmedPolyline.clear();
            for (i=0; i<segments.length; ++i) {
                segment = segments[i];

                // add first trimmed segment and bevel segment:
                if (i==shapeIndex1) {
                    if (trimmed1.getStartPoint().equalsFuzzy(bp1)) {
                        trimmed1.reverse();
                        trimmed1.setStartPoint(shape1.getStartPoint());
                    }
                    trimmedPolyline.appendShape(trimmed1);

                    trimmedPolyline.appendShape(arc);

                    if (trimmed2.getEndPoint().equalsFuzzy(bp2)) {
                        trimmed2.reverse();
                        trimmed2.setEndPoint(shape2.getEndPoint());
                    }
                    trimmedPolyline.appendShape(trimmed2);
                    i = shapeIndex2;
                }

                // add unaffected segment:
                else {
                    trimmedPolyline.appendShape(segment.data());
                }
            }

            entity1.setShape(trimmedPolyline);
            op.addObject(entity1, false);
        }

        // add new trimmed entities:
        else {
            if (isFunction(entity1.setShape)) {
                modifyEntity(op, entity1, trimmed1);
                //entity1.setShape(trimmed1);
                //op.addObject(entity1, false);
            }
            else {
                if (!preview) {
                    EAction.handleUserWarning(qsTr("First entity cannot be trimmed."));
                }
            }

            if (isFunction(entity2.setShape)) {
                modifyEntity(op, entity2, trimmed2);
                //entity2.setShape(trimmed2);
                //op.addObject(entity2, false);
            }
            else {
                if (!preview) {
                    EAction.handleUserWarning(qsTr("Second entity cannot be trimmed."));
                }
            }
        }
    }

    // add rounding:
    if (isNull(polyline)) {
        op.addObject(new RArcEntity(entity1.getDocument(), new RArcData(arc)));
    }

    return true;
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

