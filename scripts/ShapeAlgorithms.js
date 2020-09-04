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

/**
 * \class ShapeAlgorithms
 * Various shape based algorithms.
 */
function ShapeAlgorithms() {
}

/**
 * \return Array with only the circle shapes from the given shapes.
 */
ShapeAlgorithms.getCircleShapes = function(shapes) {
    if (isNull(shapes)) {
        return undefined;
    }

    var ret = [];
    for (var i=0; i<shapes.length; i++) {
        if (isCircleShape(shapes[i])) {
            ret.push(shapes[i]);
        }
    }
    return ret;
};

/**
 * \return The shape of the given shapes that is closest to the given position.
 */
ShapeAlgorithms.getClosestShape = function(shapes, position) {
    if (isNull(shapes)) {
        return undefined;
    }

    var ret = undefined;
    var minDist = undefined;
    var circle = undefined;
    for (var i=0; i<shapes.length; i++) {
        var s = shapes[i];
        var dist = s.getDistanceTo(position);
        if (isNumber(dist) && (isNull(minDist) || dist<minDist)) {
            minDist = dist;
            ret = s;
        }
    }
    return ret;
};

ShapeAlgorithms.getTangents = function(circle1, circle2) {
    var offs1, offs2;

    var circleCenter1 = circle1.getCenter();
    var circleRadius1 = circle1.getRadius();
    var circleCenter2 = circle2.getCenter();
    var circleRadius2 = circle2.getRadius();

    // create all four possible tangents:
    var tangents = [];

    var angle1 = circleCenter1.getAngleTo(circleCenter2);
    var dist1 = circleCenter1.getDistanceTo(circleCenter2);

    if (dist1<1.0e-6) {
        return [];
    }

    // outer tangents:
    var dist2 = circleRadius2 - circleRadius1;
    if (dist1>dist2) {
        var angle2 = Math.asin(dist2/dist1);
        var angt1 = angle1 + angle2 + Math.PI/2.0;
        var angt2 = angle1 - angle2 - Math.PI/2.0;
        offs1 = new RVector();
        offs2 = new RVector();

        offs1.setPolar(circleRadius1, angt1);
        offs2.setPolar(circleRadius2, angt1);

        tangents.push(new RLine(circleCenter1.operator_add(offs1),
                                circleCenter2.operator_add(offs2)));

        offs1.setPolar(circleRadius1, angt2);
        offs2.setPolar(circleRadius2, angt2);

        tangents.push(new RLine(circleCenter1.operator_add(offs1),
                                circleCenter2.operator_add(offs2)));
    }
    else {
        tangents.push(undefined);
        tangents.push(undefined);
    }

    // inner tangents:
    var dist3 = circleRadius2 + circleRadius1;
    if (dist1>dist3) {
        var angle3 = Math.asin(dist3/dist1);
        var angt3 = angle1 + angle3 + Math.PI/2.0;
        var angt4 = angle1 - angle3 - Math.PI/2.0;
        offs1 = new RVector();
        offs2 = new RVector();

        offs1.setPolar(circleRadius1, angt3);
        offs2.setPolar(circleRadius2, angt3);

        tangents.push(new RLine(circleCenter1.operator_subtract(offs1),
                                circleCenter2.operator_add(offs2)));

        offs1.setPolar(circleRadius1, angt4);
        offs2.setPolar(circleRadius2, angt4);

        tangents.push(new RLine(circleCenter1.operator_subtract(offs1),
                                circleCenter2.operator_add(offs2)));
    }
    else {
        tangents.push(undefined);
        tangents.push(undefined);
    }

    return tangents;
};

/**
 * \return Line that is orthogonal to line and tangential to circle.
 */
ShapeAlgorithms.getOrthogonalTangents = function(line, circle) {
    var ret = [];

    var auxLine1, auxLine2;
    var ips, ips1, ips2;

    var lineAngle = line.getAngle();

    if (isCircleShape(circle) || isArcShape(circle)) {
        // line parallel to line through center of circle:
        auxLine1 = new RLine(circle.getCenter(), lineAngle, 100.0);

        // intersections of parallel with circle:
        ips1 = circle.getIntersectionPoints(auxLine1, false);
        for (var i=0; i<ips1.length; i++) {
            // candidate:
            auxLine2 = new RLine(ips1[i], lineAngle+Math.PI/2, 100.0);
            ips2 = line.getIntersectionPoints(auxLine2, false);
            if (ips2.length===1) {
                ret.push(new RLine(ips1[i], ips2[0]));
            }
        }
    }
    else if (isEllipseShape(circle)) {
        var center = circle.getCenter();

        // circle around ellipse:
        var auxCircle = new RCircle(center, circle.getMajorRadius());

        var foci = circle.getFoci();
        auxLine1 = new RLine(foci[0], lineAngle, 100.0);
        auxLine2 = new RLine(foci[1], lineAngle, 100.0);

        ips1 = auxLine1.getIntersectionPoints(auxCircle, false);
        ips2 = auxLine2.getIntersectionPoints(auxCircle, false);

        var pointOfContact1 = undefined;
        var pointOfContact2 = undefined;

        if (ips1.length>=1 && ips2.length>=1) {
            if (ips1[0].equalsFuzzy(ips2[0])) {
                pointOfContact1 = ips1[0];
            }
            else {
                auxLine1 = new RLine(ips1[0], ips2[0]);
                ips = circle.getIntersectionPoints(auxLine1, false);
                if (ips.length>=1) {
                    pointOfContact1 = ips[0];
                }
            }
        }

        if (ips1.length>=2 && ips2.length>=2) {
            if (ips1[1].equalsFuzzy(ips2[1])) {
                pointOfContact2 = ips1[1];
            }
            else {
                auxLine2 = new RLine(ips1[1], ips2[1]);
                ips = circle.getIntersectionPoints(auxLine2, false);
                if (ips.length>=1) {
                    pointOfContact2 = ips[0];
                }
            }
        }

        if (!isNull(pointOfContact1)) {
            var pointOnLine1 = line.getClosestPointOnShape(pointOfContact1, false);
            ret.push(new RLine(pointOfContact1, pointOnLine1));
        }
        if (!isNull(pointOfContact2)) {
            var pointOnLine2 = line.getClosestPointOnShape(pointOfContact2, false);
            ret.push(new RLine(pointOfContact2, pointOnLine2));
        }
    }

    return ret;
};

/**
 * \return Parallels to this shape.
 * \param distance Distance of first parallel or concentric arc or circle.
 * \param number Number of offset shapes to generate.
 * \param sidePosition RVector indicating what side of the shape the parallels
 *         should be RS.LeftHand or RS.RightHand or RS.BothSides.
 */
ShapeAlgorithms.getOffsetShapes = function(shape, distance, number, sidePosition) {
    var side = isVector(sidePosition) ? RS.NoSide : sidePosition;
    var pos = isVector(sidePosition) ? sidePosition : RVector.invalid;
    return shape.getOffsetShapes(distance, number, side, pos);
};

ShapeAlgorithms.getOffsetLines = function(shape, distance, number, sidePosition) {
    var side = isVector(sidePosition) ? RS.NoSide : sidePosition;
    var pos = isVector(sidePosition) ? sidePosition : RVector.invalid;
    return RShape.getOffsetLines(shape, distance, number, side, pos);
};

ShapeAlgorithms.getOffsetArcs = function(shape, distance, number, sidePosition) {
    var side = isVector(sidePosition) ? RS.NoSide : sidePosition;
    var pos = isVector(sidePosition) ? sidePosition : RVector.invalid;
    return RShape.getOffsetArcs(shape, distance, number, side, pos);
};

/**
 * \return Array of spline shapes representing the parallel curves to the given ellipse shape.
 */
ShapeAlgorithms.getOffsetEllipses = function(shape, distance, number, sidePosition) {
    var side = isVector(sidePosition) ? RS.NoSide : sidePosition;
    var pos = isVector(sidePosition) ? sidePosition : RVector.invalid;
    return RShape.getOffsetEllipses(shape, distance, number, side, pos);
};

/**
 * \return Intersection points between shape and other shapes.
 */
ShapeAlgorithms.getIntersectionPoints = function(shape, otherShapes, onShape, onOtherShapes) {
    var intersections = [];
    var i, k;

    // treat start and end points as intersection points for open shapes:
    if (onShape &&
        !isCircleShape(shape) &&
        !isFullEllipseShape(shape) &&
        !isXLineShape(shape) &&
        (!isPolylineShape(shape) || !shape.isGeometricallyClosed()) &&
        (!isSplineShape(shape) || !shape.isClosed())) {

        var sp = shape.getStartPoint();
        sp.isStart = true;
        intersections.push(sp);

        if (!isRayShape(shape)) {
            var ep = shape.getEndPoint()
            ep.isEnd = true;
            intersections.push(ep);
        }
    }

    // find all intersection points:
    for (i=0; i<otherShapes.length; i++) {
        var otherShape = otherShapes[i];
        if (isFunction(otherShape.data)) {
            otherShape = otherShape.data();
        }

        var sol = shape.getIntersectionPoints(otherShape, onShape, false, true);
        for (k=0; k<sol.length; k++) {
            if (!onOtherShapes || otherShape.isOnShape(sol[k])) {
                intersections.push(sol[k]);
            }
        }
    }

    var selfIntersectionPoints = shape.getSelfIntersectionPoints();

    // add self intersection points to list:
    if (selfIntersectionPoints.length!==0) {
        intersections = intersections.concat(selfIntersectionPoints);
    }

    return intersections;
};

/**
 * \return Array of shapes to extend or trim to.
 *
 * \param doc RDocument
 * \param entityId ID of entity to exclude (typically clicked entity).
 * \param shape Shape of (clicked) entity.
 * \param extend True if entity is being extended.
 */
ShapeAlgorithms.getIntersectingShapes = function(doc, entityId, shape, extend) {
    if (isNull(extend)) {
        extend = false;
    }

    if (isNull(shape)) {
        return [];
    }

    // find other shapes that potentially intersect with the chosen entity:
    var ret = [];
    // allow for error: especialy for ellipse segments bordering to tangential lines this is needed:
    var otherEntityIds;

    if (extend===true) {
        // TODO: if we are extending, the 'rest' has to be queried instead
        //otherEntityIds = document.queryIntersectedEntitiesXY(document.getBoundingBox().growXY(1.0e-2), true);
        otherEntityIds = doc.queryAllVisibleEntities();
    }
    else {
        if (isXLineShape(shape) || isRayShape(shape)) {
            otherEntityIds = doc.queryAllEntities();
        }
        else {
            otherEntityIds = doc.queryIntersectedEntitiesXY(shape.getBoundingBox().growXY(1.0e-2));
        }
    }

    for (var i=0; i<otherEntityIds.length; i++) {
        var otherEntity = doc.queryEntityDirect(otherEntityIds[i]);

        // ignore intersection points of same entity
        // self intersection points are handled elsewhere
        var same = otherEntityIds[i]===entityId;
        if (same && !isBlockReferenceEntity(otherEntity)) {
            continue;
        }

        // TODO: if shape is arc, circle, ellipse or ellipse arc:
        // entities with full bounding box outside full circle or full ellipse
        // bounding box could be ignored.

        var s = otherEntity.getShapes();
        if (s.length!==0) {
            if (!same) {
                ret = ret.concat(s);
            }
            else {
                // ignore same shape for block reference entities:
                for (var k=0; k<s.length; k++) {
                     if (!shape.equals(s[k].data())) {
                         ret.push(s[k]);
                     }
                }
            }
        }
    }

    return ret;
};

/**
 * Breaks the closest segment in shape to position between two intersections
 * with otherShapes or
 * extends a shape to the next two (imaginary) intersections with otherShapes.
 *
 * \param extend True: extending instead of breaking out.
 *
 * \return Array of three new shapes which each might be undefined if its
 * length would otherwise be 0.
 * The first shape is the rest at the start of the shape.
 * The second shape is the rest at the end of the shape.
 * The third shape is the segment self in its new shape.
 */
ShapeAlgorithms.autoSplit = function(shape, otherShapes, position, extend) {
    if (isNull(extend)) {
        extend = false;
    }

    // get intersection points:
    var ips = ShapeAlgorithms.getIntersectionPoints(shape, otherShapes, !extend, extend);
    if (ips.length===0) {
        // no intersections with other shapes or self,
        // return whole shape as segment:
        return [undefined, undefined, shape.clone()];
    }

    // convert circle to arc:
    if (isCircleShape(shape)) {
        var ap = shape.getCenter().getAngleTo(position);
        var arc = new RArc(shape.getCenter(), shape.getRadius(), ap, ap, false);

        var maxD = undefined;
        var p = undefined;
        for (var i=0; i<ips.length; i++) {
            var ip = ips[i];
            var d  = arc.getDistanceFromStart(ip);
            if (isNull(maxD) || d>maxD) {
                maxD = d;
                p = ip;
            }
        }

        // no intersections:
        if (isNull(p)) {
            return [undefined, undefined, shape.clone()];
        }

        // angle at intersection point closest to end of arc is where we split the circle:
        ap = shape.getCenter().getAngleTo(p);
        shape = new RArc(shape.getCenter(), shape.getRadius(), ap, ap, false);
    }

    // find intersection points closest to position:
    // array of two distances and two point vectors:
    var cutDistances = ShapeAlgorithms.getClosestIntersectionPointDistances(shape, ips, position);

    // distance along shape to clicked position:
    //var dPosition = ;

    // make sure direction of shape does not change in the process:
    //intersectionPointDistances.sort();

    var cutDist1 = undefined;
    var cutDist2 = undefined;
    var cutPos1 = undefined;
    var cutPos2 = undefined;

    if (!isNull(cutDistances) && cutDistances.length>1) {
        cutDist1 = cutDistances[0][0];
        cutDist2 = cutDistances[0][1];
        cutPos1 = cutDistances[1][0];
        cutPos2 = cutDistances[1][1];
    }

    // if we only have one cutting point (XLine, Ray), make it the first parameter:
    if (isNull(cutDist1)) {
        cutDist1 = cutDist2;
        cutPos1 = cutPos2;
        cutDist2 = undefined;
        cutPos2 = undefined;
    }

    return ShapeAlgorithms.autoSplitManual(shape, cutDist1, cutDist2, cutPos1, cutPos2, position, extend);
};

/**
 * Cut shape at given distances / positions.
 *
 * \return Array of three new shapes which each might be undefined if its
 * length would otherwise be 0.
 * The first shape is the rest at the start of the shape.
 * The second shape is the rest at the end of the shape.
 * The third shape is the segment self in its new shape.
 */
ShapeAlgorithms.autoSplitManual = function(shape, cutDist1, cutDist2, cutPos1, cutPos2, position, extend) {
    if (isNull(extend)) {
        extend = false;
    }

//    if (!isCircleShape(shape) && !isFullEllipseShape(shape) &&
//        !isXLineShape(shape) && !isRayShape(shape)) {

//        if (isNull(cutDist1) || isNull(cutDist2)) {
//            // abort if shape requires two intersection points:
//            return undefined;
//        }
//    }

//    if (isNull(cutDist2)) {
//        cutDist2 = cutDist1;
//    }

    var dummy;
    var distSegment;

//    var cutPos1 = shape.getPointWithDistanceToStart(cutDist1);
//    var cutPos2 = undefined;
//    if (!isNull(cutDist2)) {
//        cutPos2 = shape.getPointWithDistanceToStart(cutDist2);
//    }

    if (isNull(cutDist1) && !isNull(cutPos1)) {
        cutDist1 = shape.getDistanceFromStart(cutPos1);
    }
    if (isNull(cutDist2) && !isNull(cutPos2)) {
        cutDist2 = shape.getDistanceFromStart(cutPos2);
    }

    if (isNull(cutDist2)) {
        // ray, nothing to cut:
        if (RMath.fuzzyCompare(cutDist1, 0.0) && shape.getStartPoint().equalsFuzzy(cutPos1)) {
            return [undefined, undefined, shape.clone()];
        }
    }
    else {
        if (RMath.fuzzyCompare(cutDist1, 0.0) && shape.getStartPoint().equalsFuzzy(cutPos1) &&
            RMath.fuzzyCompare(cutDist2, shape.getLength()) && shape.getEndPoint().equalsFuzzy(cutPos2)) {

            return [undefined, undefined, shape.clone()];
        }
    }

    var rest1 = undefined;
    var rest2 = undefined;
    var segment = undefined;

    // lines:
    if (isLineShape(shape)) {
        rest1 = shape.clone();
        rest2 = shape.clone();

        if (cutDist1 < cutDist2) {
            rest1.trimEndPoint(cutDist1);
            rest2.trimStartPoint(cutDist2);
        }
        else {
            rest1.trimEndPoint(cutDist2);
            rest2.trimStartPoint(cutDist1);
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

    // xlines:
    else if (isXLineShape(shape)) {
        var line = shape.getLineShape();
        cutPos1 = line.getPointWithDistanceToStart(cutDist1);
        if (isNull(cutDist2)) {
            cutPos2 = undefined;
        }
        else {
            cutPos2 = line.getPointWithDistanceToStart(cutDist2);
        }

        rest1 = undefined;
        rest2 = undefined;

        if (!isNull(cutDist1) && !isNull(cutDist2) && cutDist1 > cutDist2) {
            dummy = cutDist1;
            cutDist1 = cutDist2;
            cutDist2 = dummy;
        }

//        if (!isNull(cutDist1) && !isNull(cutDist2)) {
//            cutDist1 = cutDist2;
//            cutDist2 = undefined;
//        }

        // <--------x---------------x--------->
        // rest2   cp2   segment   cp1   rest1
        if (!isNull(cutDist1) && !isNull(cutDist2)) {
            rest1 = new RRay(cutPos1, RVector.createPolar(1.0, shape.getDirection2()));
            segment = new RLine(cutPos1, cutPos2);
            rest2 = new RRay(cutPos2, RVector.createPolar(1.0, shape.getDirection1()));
        }

        // <-o--------------x----------------->
        //  pos  segment   cp1   rest1
        // <----------------x-------------o--->
        //        rest1    cp1  segment  pos
        else if (!isNull(cutDist1)) {
            rest1 = new RRay(cutPos1, RVector.createPolar(1.0, shape.getDirection2()));
            segment = new RRay(cutPos1, RVector.createPolar(1.0, shape.getDirection1()));

            distSegment = segment.getDistanceTo(position);
            if (isNaN(distSegment)) {
                dummy = rest1;
                rest1 = segment;
                segment = dummy;
            }
            rest2 = undefined;
        }
    }

    // rays:
    else if (isRayShape(shape)) {
        rest1 = undefined;
        rest2 = undefined;

        if (!isNull(cutDist1) && !isNull(cutDist2) && Math.sign(cutDist1) !== Math.sign(cutDist2)) {
            dummy = cutDist1;
            cutDist1 = cutDist2;
            cutDist2 = dummy;
        }

//        if (!cutDist1.isValid() && cutDist2.isValid()) {
//            cutDist1 = cutDist2;
//            cutDist2 = undefined;
//        }


        // <--------x-------o-------x---------
        // rest2   cp2   segment   cp1   rest1
        if (isValidVector(cutPos1) && isValidVector(cutPos2)) {
            rest1 = new RLine(shape.getBasePoint(), cutPos1);
            segment = new RLine(cutPos1, cutPos2);
            rest2 = new RRay(cutPos2, RVector.createPolar(1.0, shape.getDirection1()));
        }

        // <-------o--------x-----------------
        //      segment    cp1     rest1
        // <----------------x--------o--------
        //       rest1     cp1    segment
        else if (isValidVector(cutPos1)) {
            rest1 = new RLine(shape.getBasePoint(), cutPos1);
            segment = new RRay(cutPos1, RVector.createPolar(1.0, shape.getDirection1()));
            rest2 = undefined;

            distSegment = segment.getDistanceTo(position);
            if (isNaN(distSegment)) {
                dummy = rest1;
                rest1 = segment;
                segment = dummy;
            }
        }
    }

    // arcs:
    else if (isArcShape(shape)) {
        rest1 = shape.clone();
        rest2 = shape.clone();

        rest1.trimEndPoint(cutDist1);
        rest2.trimStartPoint(cutDist2);

        segment = shape.clone();
        //var l1 = segment.getLength();
        segment.setStartAngle(segment.getCenter().getAngleTo(cutPos1));
        //segment.trimStartPoint(cutDist1);
        //var l2 = segment.getLength();
        //segment.trimEndPoint(cutDist2 - (l1-l2));
        segment.setEndAngle(segment.getCenter().getAngleTo(cutPos2));

        if (!extend) {
            var angleLength1 = rest1.getAngleLength(true);
            var angleLength2 = rest2.getAngleLength(true);
            if (angleLength1+angleLength2 > shape.getAngleLength()) {
                rest1.trimEndPoint(cutDist2);
                rest2.trimStartPoint(cutDist1);

                segment.trimStartPoint(cutDist2);
                segment.trimEndPoint(cutDist1);

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
    }

    // circles:
    else if (isCircleShape(shape)) {
        if (isNull(cutDist1) || isNull(cutDist2)) {
            rest1 = undefined;
            rest2 = undefined;
        }
        else {
            var angle1 = shape.getCenter().getAngleTo(cutPos1);
            var angle2 = shape.getCenter().getAngleTo(cutPos2);

            rest1 = new RArc(
                        shape.getCenter(),
                        shape.getRadius(),
                        angle1, angle2,
                        false);
            rest2 = undefined;

            segment = new RArc(
                        shape.getCenter(),
                        shape.getRadius(),
                        angle2, angle1,
                        false);

            if (!isNull(position)) {
                var cursorAngle = shape.getCenter().getAngleTo(position);

                if (RMath.isAngleBetween(cursorAngle, angle1, angle2, false)) {
                    rest1.setStartAngle(angle2);
                    rest1.setEndAngle(angle1);
                    segment.setStartAngle(angle1);
                    segment.setEndAngle(angle2);
                }
            }

            var angleLength1 = rest1.getAngleLength(true);
            if (angleLength1<RS.AngleTolerance) {
                rest1 = undefined;
            }
        }
    }

    // ellipse arcs:
    else if (isEllipseArcShape(shape)) {
        rest1 = shape.clone();
        rest2 = shape.clone();

        rest1.trimEndPoint(cutPos1, cutPos1);
        rest2.trimStartPoint(cutPos2, cutPos2);

        segment = shape.clone();
        segment.trimStartPoint(cutPos1, cutPos1);
        segment.trimEndPoint(cutPos2, cutPos2);

        var angleLength1 = rest1.getAngleLength(true);
        var angleLength2 = rest2.getAngleLength(true);

        if (angleLength1+angleLength2 > shape.getAngleLength()) {
            rest1.trimEndPoint(cutPos2, cutPos2);
            rest2.trimStartPoint(cutPos1, cutPos1);
            segment.trimStartPoint(cutPos2, cutPos2);
            segment.trimEndPoint(cutPos1, cutPos1);

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

    // full ellipses:
    else if (isFullEllipseShape(shape)) {
        if (!isValidVector(cutPos1) || !isValidVector(cutPos2)) {
            rest1 = undefined;
            rest2 = undefined;
        }
        else {
            var angle1 = shape.getParamTo(cutPos1);
            var angle2 = shape.getParamTo(cutPos2);

            rest1 = new REllipse(
                        shape.getCenter(),
                        shape.getMajorPoint(),
                        shape.getRatio(),
                        angle1, angle2,
                        false);
            rest2 = undefined;

            segment = new REllipse(
                        shape.getCenter(),
                        shape.getMajorPoint(),
                        shape.getRatio(),
                        angle2, angle1,
                        false);

            if (!isNull(position)) {
                var cursorAngle = shape.getParamTo(position);

                if (RMath.isAngleBetween(cursorAngle, angle1, angle2, false)) {
                    rest1.setStartParam(angle2);
                    rest1.setEndParam(angle1);
                    segment.setStartParam(angle1);
                    segment.setEndParam(angle2);
                }
            }

            var angleLength1 = rest1.getAngleLength();

            if (angleLength1<RS.AngleTolerance) {
                rest1 = undefined;
            }
        }
    }

    // polyline:
    else if (isPolylineShape(shape)) {
        var closed = shape.isGeometricallyClosed();
        if (closed) {
            shape.relocateStartPoint(cutDist1);
            shape.convertToOpen();
            cutDist2 -= cutDist1;
            if (cutDist2<0.0) {
                cutDist2 = shape.getLength() + cutDist2;
            }

            cutDist1 = 0.0;
        }
        rest1 = shape.clone();
        rest2 = shape.clone();
        segment = shape.clone();

        if (closed) {
            rest1.trimEndPoint(cutDist2);
            segment = undefined;
            rest2.trimStartPoint(cutDist2);
        }
        else {
//            var l1 = shape.getLengthTo(cutDist1);
//            if (l1<RS.PointTolerance && cutDist1.isEnd===true) {
//                l1 = shape.getLength();
//            }
//            var l2 = shape.getLengthTo(cutDist2);
//            if (l2<RS.PointTolerance && cutDist2.isEnd===true) {
//                l2 = shape.getLength();
//            }

            // TODO: use real click point (position)
//            if (l1 > l2) {
//                rest1.trimEndPoint(cutDist2, cutDist2);
//                segment.trimStartPoint(cutDist2, cutDist2);
//                segment.trimEndPoint(cutDist1, cutDist1);
//                rest2.trimStartPoint(cutDist1, cutDist1);
//            }
//            else {
                rest1.trimEndPoint(cutDist1);

                var l1 = segment.getLength();
                segment.trimStartPoint(cutDist1);
                var l2 = segment.getLength();
                segment.trimEndPoint(cutDist2 - (l1-l2));

                rest2.trimStartPoint(cutDist2);
//            }
        }

        if (!isNull(segment)) {
            if (segment.getLength()<RS.PointTolerance || (closed && RMath.fuzzyCompare(segment.getLength(), shape.getLength()))) {
                segment = undefined;
            }
        }

        if (!isNull(rest1)) {
            if (rest1.getLength()<RS.PointTolerance || (closed && RMath.fuzzyCompare(rest1.getLength(), shape.getLength()))) {
                rest1 = undefined;
            }
        }

        if (!isNull(rest2)) {
            if (rest2.getLength()<RS.PointTolerance || (closed && RMath.fuzzyCompare(rest2.getLength(), shape.getLength()))) {
                rest2 = undefined;
            }
        }

        if (isNull(segment) && !isNull(rest1) && !isNull(rest2)) {
            var distRest1 = rest1.getDistanceTo(position);
            var distRest2 = rest2.getDistanceTo(position);
            if (distRest1<distRest2 || isNaN(distRest2)) {
                segment = rest1;
                rest1 = undefined;
            }
            else {
                segment = rest2;
                rest2 = undefined;
            }
        }
    }

    // spline:
    else if (isSplineShape(shape)) {
        rest1 = shape.clone();
        rest2 = shape.clone();
        segment = shape.clone();

        var tAtCutPos1 = shape.getTAtDistance(cutDist1);
        var tAtCutPos2 = shape.getTAtDistance(cutDist2);
        var tMax = shape.getTMax();

        if (shape.getStartPoint().equalsFuzzy(shape.getEndPoint())) {
            if (RMath.fuzzyCompare(tAtCutPos1, shape.getTMax())) {
                tAtCutPos1 = shape.getTMin();
            }
        }

        if (tAtCutPos1 < tAtCutPos2) {
            if (RMath.fuzzyCompare(tAtCutPos1, 0.0)) {
                rest1 = undefined;
            }
            else {
                rest1.trimEndPoint(cutDist1);
                // positions are more precise but
                // distances take into account possible self intersections:
                rest1.setEndPoint(cutPos1);
            }

            var l1 = segment.getLength();
            segment.trimStartPoint(cutDist1);
            segment.setStartPoint(cutPos1);
            var l2 = segment.getLength();
            segment.trimEndPoint(cutDist2 - (l1-l2));
            segment.setEndPoint(cutPos2);

            if (RMath.fuzzyCompare(tAtCutPos2, tMax)) {
                rest2 = undefined;
            }
            else {
                rest2.trimStartPoint(cutDist2);
                rest2.setStartPoint(cutPos2);
            }
        }
        else {
            if (RMath.fuzzyCompare(tAtCutPos1, 0.0)) {
                rest1 = undefined;
            }
            else {
                rest1.trimEndPoint(cutDist2);
                rest1.setEndPoint(cutPos2);
            }

            var l1 = segment.getLength();
            segment.trimStartPoint(cutDist2);
            segment.setStartPoint(cutPos2);
            var l2 = segment.getLength();
            segment.trimEndPoint(cutDist1 - (l1-l2));
            segment.setEndPoint(cutPos1);

            if (RMath.fuzzyCompare(tAtCutPos2, tMax)) {
                rest2 = undefined;
            }
            else {
                rest2.trimStartPoint(cutDist1);
                rest2.setStartPoint(cutPos1);
            }
        }

        if (!isNull(segment)) {
            if (!segment.isValid() || segment.getLength()<RS.PointTolerance) {
                segment = undefined;
            }
        }

        if (!isNull(rest1)) {
            if (!rest1.isValid() || rest1.getLength()<RS.PointTolerance) {
                rest1 = undefined;
            }
        }

        if (!isNull(rest2)) {
            if (!rest2.isValid() || rest2.getLength()<RS.PointTolerance) {
                rest2 = undefined;
            }
        }
    }

    var ret = [];

    // add new rest entities:
    ret.push(rest1);
    ret.push(rest2);
    ret.push(segment);

    return ret;
};

/**
 * \return The two distances along the given shape identifying the
 * intersections points closest to the given position along with the cut positions:
 * [ [cutDist1, cutDist2], [cutPos1, cutPos2] ]
 *
 * \param onShape True: only return intersections on the shape
 * (for trimming, breaking, default).
 * False: Also consider intersection points outside of shape (for extending).
 * \param onOtherShapes True only return intersections on one of the other
 * shapes (for extending).
 */
ShapeAlgorithms.getClosestIntersectionPointDistances = function(shape, intersections, position) {
//    if (isNull(onShape)) {
//        onShape = true;
//    }
//    if (isNull(onOtherShapes)) {
//        onOtherShapes = false;
//    }

//    var i, k;

//    // treat start and end points as intersection points for open shapes:
//    if (onShape &&
//        !isCircleShape(shape) &&
//        !isFullEllipseShape(shape) &&
//        !isXLineShape(shape) &&
//        (!isPolylineShape(shape) || !shape.isGeometricallyClosed()) &&
//        (!isSplineShape(shape) || !shape.isClosed())) {

//        var sp = shape.getStartPoint();
//        sp.isStart = true;
//        intersections.push(sp);

//        if (!isRayShape(shape)) {
//            var ep = shape.getEndPoint()
//            ep.isEnd = true;
//            intersections.push(ep);
//        }
//    }

//    // find all intersection points:
//    for (i=0; i<otherShapes.length; i++) {
//        var otherShape = otherShapes[i];
//        if (isFunction(otherShape.data)) {
//            otherShape = otherShape.data();
//        }

//        var sol = shape.getIntersectionPoints(otherShape, onShape, false, true);
//        for (k=0; k<sol.length; k++) {
//            if (!onOtherShapes || otherShape.isOnShape(sol[k])) {
//                intersections.push(sol[k]);
//            }
//        }
//    }

//    // add self intersection points to list:
//    if (!isNull(selfIntersectionPoints) && selfIntersectionPoints.length!==0) {
//        intersections = intersections.concat(selfIntersectionPoints);
//    }

    var ip, dist;

    // closed circular shapes:
    var circular = false;
    if (isCircleShape(shape)) {
        var a = shape.getCenter().getAngleTo(position);
        shape = new RArc(shape.getCenter(), shape.getRadius(), a, a, false);
        circular = true;
    }

    if (isPolylineShape(shape) && shape.isGeometricallyClosed()) {
        circular = true;
    }
    if (isArcShape(shape)) {
        circular = true;
    }

//    if (isSplineShape(shape) && shape.isGeometricallyClosed()) {
//        circular = true;
//    }

    var pDist = shape.getDistanceFromStart(position);

    var orthoLine;
    var reversedShape = false;
    if (isEllipseShape(shape)) {
        orthoLine = new RLine(shape.getCenter(), position);
        if (isEllipseShape(shape)) {
            if (shape.isReversed()) {
                shape.reverse();
                reversedShape = true;
            }
        }
    }

    // find intersection points directly before and after clicked position:
    var cutDist1 = undefined;
    var cutDist2 = undefined;
    var cutPos1 = undefined;
    var cutPos2 = undefined;

    // for circular shapes, also find intersections closest to and furthest from start point:
    var cutDistMax = undefined;
    var cutDistMin = undefined;
    var cutPosMax = undefined;
    var cutPosMin = undefined;

    for (var i=0; i<intersections.length; i++) {
        ip = intersections[i];

        if (isEllipseShape(shape)) {
            dist = RMath.getAngleDifference(orthoLine.getAngle(), shape.getCenter().getAngleTo(ip));
            if (isNull(cutDist1) || dist<cutDist1) {
                cutPos1 = ip;
                cutDist1 = dist;
            }
            if (isNull(cutDist2) || dist>cutDist2) {
                cutPos2 = ip;
                cutDist2 = dist;
            }
        }
        else {
            var dists = shape.getDistancesFromStart(ip);
            for (var k=0; k<dists.length; k++) {
                dist = dists[k];

                // largest distance to start
                // but smaller than click point:
                if (dist<pDist) {
                    if (isNull(cutDist1) || dist>cutDist1) {
                        cutDist1 = dist;
                        cutPos1 = ip;
                    }
                }

                if (circular) {
                    if (isNull(cutDistMax) || dist>cutDistMax) {
                        cutDistMax = dist;
                        cutPosMax = ip;
                    }
                }

                // smallest distance to start
                // but larger than click point
                if (dist>pDist) {
                    if (isNull(cutDist2) || dist<cutDist2) {
                        cutDist2 = dist;
                        cutPos2 = ip;
                    }
                }

                if (circular) {
                    if (isNull(cutDistMin) || (dist<cutDistMin && (dist>pDist || isPolylineShape(shape)))) {
                        cutDistMin = dist;
                        cutPosMin = ip;
                    }
                }
            }
        }
    }

    if (circular) {
        if (isNull(cutDist1)) {
            cutDist1 = cutDistMax;
            cutPos1 = cutPosMax;
        }
        if (isNull(cutDist2)) {
            cutDist2 = cutDistMin;
            cutPos2 = cutPosMin;
        }
    }

    if (isEllipseShape(shape) && shape.isReversed()) {
        var dummy = cutPos1;
        cutPos1 = cutPos2;
        cutPos2 = dummy;

        dummy = cutDist1;
        cutDist1 = cutDist2;
        cutDist2 = dummy;
    }

    // open shape: cut to start or end point:
    if (!isCircleShape(shape) &&
        !isFullEllipseShape(shape) &&
        !isXLineShape(shape) &&
        !isRayShape(shape) &&
        (!isPolylineShape(shape) || !shape.isGeometricallyClosed()) &&
        (!isSplineShape(shape) || !shape.isClosed())) {

        if (!isValidVector(cutPos1)) {
            cutDist1 = 0.0;
            cutPos1 = shape.getStartPoint();
        }
        if (!isValidVector(cutPos2)) {
            cutDist2 = shape.getLength();
            cutPos2 = shape.getEndPoint();
        }
    }

    if (reversedShape) {
        shape.reverse();
    }

    return [ [cutDist1, cutDist2], [cutPos1, cutPos2] ];

    /*
    var orthoLine = undefined;
    var reversedShape = false;

    // auxiliary line othogonal to entity and through cursor:
    var p = shape.getClosestPointOnShape(position, true);
    if (isLineBasedShape(shape)) {
        var orthoAngle = shape.getDirection1()+Math.PI/2.0;
        var r = RVector.createPolar(1.0, orthoAngle);
        orthoLine = new RLine(position, position.operator_add(r));
    }
    else if (isArcShape(shape) || isCircleShape(shape) || isEllipseShape(shape)) {
        orthoLine = new RLine(shape.getCenter(), position);
        if (isArcShape(shape) || isEllipseShape(shape)) {
            if (shape.isReversed()) {
                shape.reverse();
                reversedShape = true;
            }
        }
    }

    if (isNull(orthoLine) && !isSplineShape(shape) && !isPolylineShape(shape)) {
        return undefined;
    }

    var intersections = [];

    // treat start and end points as intersection points:
    if (onShape &&
        !isCircleShape(shape) &&
        !isFullEllipseShape(shape) &&
        !isXLineShape(shape) &&
        (!isPolylineShape(shape) || !shape.isGeometricallyClosed())) {

        var sp = shape.getStartPoint();
        sp.isStart = true;
        intersections.push(sp);

        if (!isRayShape(shape)) {
            var ep = shape.getEndPoint()
            ep.isEnd = true;
            intersections.push(ep);
        }
    }

    // find all intersection points:
    for (var i=0; i<otherShapes.length; i++) {
        var otherShape = otherShapes[i];
        if (isFunction(otherShape.data)) {
            otherShape = otherShape.data();
        }

        var sol = shape.getIntersectionPoints(otherShape, onShape, false, true);
        for (var k=0; k<sol.length; k++) {
            if (!onOtherShapes || otherShape.isOnShape(sol[k])) {
                intersections.push(sol[k]);
            }
        }
    }

    // add self intersection points to list:
    if (!isNull(selfIntersectionPoints)) {
        intersections = intersections.concat(selfIntersectionPoints);
    }

    var cutPos1 = RVector.invalid;
    var distRight = undefined;
    var cutPos2 = RVector.invalid;
    var distLeft = undefined;

    // for closed polylines:
    var cutPos3 = RVector.invalid;
    var distRightMax = undefined;
    var cutPos4 = RVector.invalid;
    var distLeftMax = undefined;

    // at least 2 intersection points are required to proceed:
    if (intersections.length<2 && onShape && !isXLineShape(shape)) {
        if (reversedShape) {
            shape.reverse();
        }
        return undefined;
    }

    // find cutting point left and right of click point:
    var tPos = undefined;
    for (i=0; i<intersections.length; i++) {
        var inters = intersections[i];

        if (!inters.isValid()) {
            continue;
        }

        var s;
        var dist;
        if (isLineBasedShape(shape)) {
            s = orthoLine.getSideOfPoint(inters);
            dist = inters.getDistanceTo(position);

            if (s===RS.RightHand) {
                if (isNull(distRight) || dist<distRight) {
                    cutPos1 = inters;
                    distRight = dist;
                }
            }
            else if (s===RS.LeftHand) {
                if (isNull(distLeft) || dist<distLeft) {
                    cutPos2 = inters;
                    distLeft = dist;
                }
            }
        }
        else if (isArcShape(shape) || isCircleShape(shape) || isEllipseShape(shape)) {
            dist = RMath.getAngleDifference(orthoLine.getAngle(), shape.getCenter().getAngleTo(inters));
            if (isNull(distRight) || dist>distRight) {
                cutPos1 = inters;
                distRight = dist;
            }
            if (isNull(distLeft) || dist<distLeft) {
                cutPos2 = inters;
                distLeft = dist;
            }
        }
        else if (isSplineShape(shape)) {
            if (isNull(tPos)) {
                tPos = shape.getTAtPoint(position);
            }
            var tInters = shape.getTAtPoint(inters);

            dist = tPos - tInters;

            if (dist>0.0) {
                if (isNull(distRight) || dist<distRight) {
                    cutPos2 = inters;
                    distRight = dist;
                }
            }
            else if (dist<0.0) {
                dist = Math.abs(dist);
                if (isNull(distLeft) || dist<distLeft) {
                    cutPos1 = inters;
                    distLeft = dist;
                }
            }
        }
        else if (isPolylineShape(shape)) {
            if (isNull(tPos)) {
                tPos = shape.getLengthTo(position);
            }

            // shortest distance to intersection:
            var tInters1 = shape.getLengthTo(inters, true, true);
            if (inters.isEnd===true && tInters1<RS.PointTolerance) {
                tInters1 = shape.getLength();
            }

            // longest distance to intersection:
            var tInters2 = shape.getLengthTo(inters, true, false);
            if (inters.isEnd===true && tInters2<RS.PointTolerance) {
                tInters2 = shape.getLength();
            }

            var dists = [tPos - tInters1, tPos - tInters2];

            for (var n=0; n<dists.length; n++) {
                var dist = dists[n];
                if (dist>0.0) {
                    if (isNull(distRight) || dist<distRight) {
                        cutPos2 = inters;
                        distRight = dist;
                    }
                    if (isNull(distRightMax) || dist>distRightMax) {
                        cutPos3 = inters;
                        distRightMax = dist;
                    }
                }
                else if (dist<0.0) {
                    dist = Math.abs(dist);
                    if (isNull(distLeft) || dist<distLeft) {
                        cutPos1 = inters;
                        distLeft = dist;
                    }
                    if (isNull(distLeftMax) || dist>distLeftMax) {
                        cutPos4 = inters;
                        distLeftMax = dist;
                    }
                }
            }
        }
    }

    if (!isCircleShape(shape) &&
        !isFullEllipseShape(shape) &&
        !isXLineShape(shape) &&
        !isRayShape(shape) &&
        (!isPolylineShape(shape) || shape.isGeometricallyClosed())) {

        if (!isValidVector(cutPos1)) {
            cutPos1 = shape.getEndPoint();
        }
        if (!isValidVector(cutPos2)) {
            cutPos2 = shape.getStartPoint();
        }
    }

    if (isPolylineShape(shape)) {
        if (isNull(distLeft)) {
            cutPos1 = cutPos3;
            cutPos2 = cutPos2;
        }
        if (isNull(distRight)) {
            cutPos1 = cutPos1;
            cutPos2 = cutPos4;
        }
    }

    if (reversedShape) {
        shape.reverse();
    }

    return [cutPos1, cutPos2];
    */
};

/**
 * \return RCircle through all three given points (RVector) or RLine if only
 * two points are given.
 */
ShapeAlgorithms.createCircleFrom3Points = function(point1, point2, point3) {
    ShapeAlgorithms.error = undefined;
    if (isNull(point1) || isNull(point2)) {
        return undefined;
    }

    if (isNull(point3)) {
        return new RLine(point1, point2);
    }

    if (point1.equalsFuzzy(point2) || point2.equalsFuzzy(point3) || point3.equalsFuzzy(point1)) {
        ShapeAlgorithms.error = qsTr("At least two points are identical.");
        return undefined;
    }

    var ret = RCircle.createFrom3Points(point1, point2, point3);

    if (isNull(ret)) {
        ShapeAlgorithms.error = qsTr("No circle possible.");
        return undefined;
    }

    return ret;
};

/**
 * \return RArc through all three given points (RVector) or RLine if only
 * two points are given.
 */
ShapeAlgorithms.createArcFrom3Points = function(point1, point2, point3) {
    ShapeAlgorithms.error = undefined;
    if (isNull(point1) || isNull(point2)) {
        return undefined;
    }

    if (isNull(point3)) {
        return new RLine(point1, point2);
    }

    if (point1.equalsFuzzy(point2) || point2.equalsFuzzy(point3) || point3.equalsFuzzy(point1)) {
        ShapeAlgorithms.error = qsTr("At least two points are identical.");
        return undefined;
    }

    var ret = RArc.createFrom3Points(point1, point2, point3);

    if (!ret.isValid()) {
        ShapeAlgorithms.error = qsTr("No arc possible.");
        return undefined;
    }

    return ret;
};

/**
 * Approximates the given ellipse with arc segments and returns a polyline with
 * arc segments.
 *
 * \param segments Number of arc segments to generate.
 * \return RPolyline object or undefined
 */
ShapeAlgorithms.approximateEllipse = function(ellipse, segments) {
    ShapeAlgorithms.error = undefined;

    if (segments<=0) {
        ShapeAlgorithms.error =
            qsTr("Invalid number of segments: %1.").arg(segments);
        return undefined;
    }

    if (ellipse.getMajorRadius()<RS.PointTolerance ||
        ellipse.getMinorRadius()<RS.PointTolerance) {
        ShapeAlgorithms.error = qsTr("Invalid ellipse major / minor: %1 / %2.")
            .arg(ellipse.getMajorRadius()).arg(ellipse.getMinorRadius());
        return undefined;
    }

    return ellipse.approximateWithArcs(segments);
};

ShapeAlgorithms.getCompleteQuadrilateralSegments = function(line1, line2, line3, line4) {
    var ret = [];

    // maps vertices to number of intersection points at that vertex:
    var vertices = new Map(function(v1, v2) { return v1.equalsFuzzy(v2); });

    var lines = ShapeAlgorithms.removeSharedPointer([ line1, line2, line3, line4 ]);
    var i, k;

    for (i=0; i<lines.length; i++) {
        var angle = lines[i].getAngle();
        var ips = [];
        for (k=0; k<lines.length; k++) {
            if (i===k) {
                continue;
            }

            ips = ips.concat(lines[i].getIntersectionPoints(lines[k], false));
        }

        if (ips===0) {
            return [];
        }

        var edge;
        if (RMath.fuzzyCompare(angle, Math.PI/2, 0.1) || RMath.fuzzyCompare(angle, Math.PI/2*3, 0.1)) {
            // line is (almost) vertical:
            edge = RVector.getMinimumY(ips);
        }
        else {
            // line is not vertical:
            edge = RVector.getMinimumX(ips);
        }

        ips = RVector.getSortedByDistance(ips, edge);
        for (k=0; k<ips.length-1; k++) {
            ret.push(new RLine(ips[k], ips[k+1]));
        }
    }

    for (i=0; i<ret.length; i++) {
        var sp = ret[i].getStartPoint();
        var ep = ret[i].getEndPoint();
        vertices.put(sp, vertices.get(sp, 0) + 1);
        vertices.put(ep, vertices.get(ep, 0) + 1);
    }

    ret["vertices"] = vertices;

    return ret;
};

ShapeAlgorithms.getQuadrilateral = function(line1, line2, line3, line4) {
    var segments = ShapeAlgorithms.getCompleteQuadrilateralSegments(line1, line2, line3, line4);
    var vertices = segments.vertices;
    var i, k;

    // produce vs array:
    // vs[order] = list of vertices
    // where order is the number of intersections at those vertices
    var vs = [];
    for (var order=4; order>0; order--) {
        vs[order] = [];
        var startIndex = 0;
        var keys = vertices.getKeys();
        var values = vertices.getValues();
        do {
            i = values.indexOf(order, startIndex);
            startIndex = i+1;
            if (i!==-1) {
                vs[order].push(keys[i]);
            }
        } while (i!==-1);
    }

    var vert = [];

    // quadrilateral:
    if (vs[4].length===1 && vs[3].length===2 && vs[2].length===3) {
        vert = [vs[3][0], vs[4][0], vs[3][1]];
        var l1 = new RLine(vs[3][0], vs[4][0]);
        var l2 = new RLine(vs[4][0], vs[3][1]);
//        ret.push(new RLine(vs[3][0], vs[4][0]));
//        ret.push(new RLine(vs[4][0], vs[3][1]));
        for (i=0; i<vs[2].length; i++) {
            if (l1.isOnShape(vs[2][i], false) || l2.isOnShape(vs[2][i], false)) {
                continue;
            }
            vert.push(vs[2][i]);
//            ret.push(new RLine(vs[3][1], vs[2][i]));
//            ret.push(new RLine(vs[2][i], vs[3][0]));
            break;
        }
//        return ret;
    }

    // trapezoid:
    else if (vs[4].length===0 && vs[3].length===2 && vs[2].length===3) {
        vert = [vs[3][0], vs[3][1]];
//        ret.push(new RLine(vs[3][0], vs[3][1]));
        for (i=0; i<vs[2].length; i++) {
            for (k=0; k<vs[2].length; k++) {
                if (i===k) {
                    continue;
                }

                var l = new RLine(vs[2][k], vs[2][i]);
                if (!l.isOnShape(vs[3][0], true) && !l.isOnShape(vs[3][1], true)) {
                    vert.push(vs[2][i]);
                    vert.push(vs[2][k]);
//                    ret.push(new RLine(vs[3][1], vs[2][k]));
//                    ret.push(l);
//                    ret.push(new RLine(vs[2][i], vs[3][0]));
                    break;
                }
            }
            if (vert.length===4) {
                break;
            }
        }
    }

    // parallelogram:
    if (vs[4].length===0 && vs[3].length===0 && vs[2].length===4) {
        vert = vs[2];
    }

    if (vert.length!==4) {
        return undefined;
    }

    var ret = [];
    var cursor = vert[0];

    for (k=0; k<4; k++) {
        for (i=0; i<segments.length; i++) {
            var segment = segments[i];

            if (segment.getEndPoint().equalsFuzzy(cursor)) {
                segment.reverse();
            }

            if (segment.getStartPoint().equalsFuzzy(cursor)) {
                for (var c=0; c<4; c++) {
                    if (segment.getEndPoint().equalsFuzzy(vert[c])) {
                        ret.push(segment.getStartPoint());
                        cursor = segment.getEndPoint();
                        segments.splice(i, 1);
                        break;
                    }
                }
            }

            if (ret.length===k+1) {
                break;
            }
        }
    }

    if (ret.length!==4) {
        return undefined;
    }

    return ret;
};

/**
 * Produces an ellipse inscribed in the quadrilateral defined by the
 * four given unordered / untrimmed edges (RLine shapes).
 */
ShapeAlgorithms.createEllipseInscribedFromLines = function(line1, line2, line3, line4) {
    var quad = ShapeAlgorithms.getQuadrilateral(line1, line2, line3, line4);
    if (isNull(quad)) {
        return undefined;
    }
    return REllipse.createInscribed(quad[0], quad[1], quad[2], quad[3]);
};


/**
 * Produces an ellipse inscribed in the quadrilateral defined by the
 * four given ordered vertices (RVector).
 */
ShapeAlgorithms.createEllipseInscribedFromVertices = function(v1, v2, v3, v4) {
    return REllipse.createInscribed(v1, v2, v3, v4);
};

/**
 * Tries to convert the given spline into one line or arc.
 * \return RArc, RLine or the original RSpline.
 */
ShapeAlgorithms.splineToLineOrArc = function(spline, tolerance, linesOnly) {
    if (isNull(linesOnly)) {
        linesOnly = false;
    }

    var startPoint = spline.getStartPoint();
    var endPoint = spline.getEndPoint();
    var middlePoint = spline.getMiddlePoint();
    var i, point;

    if (!linesOnly) {
        var arc = RArc.createFrom3Points(startPoint, middlePoint, endPoint);
        if (arc.isValid()) {
            var splineIsArc = true;
            for (i=0.0; i<1.0; i+=0.1) {
                point = spline.getPointAt(i);
                if (!arc.isOnShape(point, true, tolerance)) {
                    splineIsArc = false;
                    break;
                }
            }

//            if (splineIsArc && arc.getRadius()>1000.0) {
//                return new RLine(startPoint, endPoint);
//            }

            if (splineIsArc) {
                return arc;
            }
        }
    }

    var line = new RLine(startPoint, endPoint);
    var splineIsLine = true;
    for (i=0.0; i<1.0; i+=0.1) {
        point = spline.getPointAt(i);
        if (!line.isOnShape(point, true, tolerance)) {
            splineIsLine = false;
            break;
        }
    }
    if (splineIsLine) {
        return line;
    }

    return spline;
};

/**
 * Converts the given circle into an arc with the given start angle or 0.
 */
ShapeAlgorithms.circleToArc = function(circle, startAngle) {
    return circle.toArc(startAngle);
};

/**
 * Converts the given line or arc into a polyline with numSegments segments.
 */
ShapeAlgorithms.lineOrArcToPolyline = function(shape, numSegments) {
    var ret = new RPolyline();
    var l = shape.getLength();

    var cursor;
    for (var i=0; i<=numSegments; i++) {
        if (i===0) {
            cursor = shape.getStartPoint();
        }
        else if (i===numSegments) {
            cursor = shape.getEndPoint();
        }
        else {
            cursor = shape.getPointsWithDistanceToEnd(l/numSegments*i, RS.FromStart)[0];
        }

        ret.appendVertex(cursor);
    }
    return ret;
};

ShapeAlgorithms.removeSharedPointer = function(shape) {
    if (isArray(shape)) {
        var ret = [];
        for (var i=0; i<shape.length; i++) {
            ret.push(ShapeAlgorithms.removeSharedPointer(shape[i]));
        }
        return ret;
    }

    if (isFunction(shape.data)) {
        return shape.data().clone();
    }
    else {
        return shape;
    }
};

/**
 * \return Array of shapes of type point, line, arc, circle, ellipse.
 */
ShapeAlgorithms.explodeToTrimmable = function(shape) {
    if (isSplineShape(shape) && !RSpline.hasProxy()) {
        return ShapeAlgorithms.removeSharedPointer(shape.getExploded());
    }
    if (isPolylineShape(shape)) {
        return ShapeAlgorithms.removeSharedPointer(shape.getExploded());
    }
    if (isTriangleShape(shape)) {
        return ShapeAlgorithms.removeSharedPointer(shape.getExploded());
    }
    return [ shape ];
};

/**
 * \return Array of shapes which represent the given shape
 * split up at the given points.
 *
 * \param points Array of RVector, assumed to be on shape.
 */
ShapeAlgorithms.splitAt = function(shape, points) {
    return shape.splitAt(points);
};

/**
 * \return An arc, circle or ellipse, whichever can be used to represent
 * the given ellipse best.
 */
ShapeAlgorithms.ellipseToArcCircleEllipse = function(ellipse) {
    return RShape.ellipseToArcCircleEllipse(ellipse);
};

/**
 * Transforms the given arc, circle or ellipse into an ellipse
 * using the given function which projects an RVector to another RVector.
 *
 * \returns An REllipse or in special cases an RArc or RCircle.
 *
 * OBSOLETE use RShape::transformArc instead
 */
ShapeAlgorithms.transformArc = function(arc, fun) {
    var r1, r2;

    if (isEllipseShape(arc)) {
        r1 = arc.getMajorPoint();
        r2 = arc.getMinorPoint();
    }
    else {
        r1 = new RVector(arc.getRadius(), 0);
        r2 = new RVector(0, arc.getRadius());
    }

    // get vertices at extremities:
    var v1 = arc.getCenter().operator_add(r1).operator_add(r2);
    var v2 = arc.getCenter().operator_add(r1).operator_subtract(r2);
    var v3 = arc.getCenter().operator_subtract(r1).operator_subtract(r2);
    var v4 = arc.getCenter().operator_subtract(r1).operator_add(r2);

    // project those vertices:
    fun(v1);
    fun(v2);
    fun(v3);
    fun(v4);

    //var ret = [];
    // inscribe ellipse into vertices:
    var ellipse = ShapeAlgorithms.createEllipseInscribedFromVertices(v1, v2, v3, v4);
    //ret.push(ellipse.copy());

    if (isArcShape(arc) || isEllipseShape(arc)) {
        var sp = arc.getStartPoint();
        var ep = arc.getEndPoint();
        var mp = arc.getMiddlePoint();

        fun(sp);
        fun(ep);
        fun(mp);

        ellipse.setStartParam(ellipse.getParamTo(sp));
        ellipse.setEndParam(ellipse.getParamTo(ep));

        var d1 = ellipse.getMiddlePoint().getDistanceTo(mp);
        ellipse.setReversed(true);
        var d2 = ellipse.getMiddlePoint().getDistanceTo(mp);

        if (d1<d2) {
            ellipse.setReversed(false);
        }
    }

    //ret.push(ShapeAlgorithms.ellipseToArcCircleEllipse(ellipse));
    //ret = ret.concat([new RLine(v1, v2), new RLine(v2, v3), new RLine(v3, v4), new RLine(v4, v1)]);

    return ShapeAlgorithms.ellipseToArcCircleEllipse(ellipse);
};

/**
 * \return List of points (RVector) which all lay on the given shape with
 * the given maximum distance.
 */
ShapeAlgorithms.getPointsOnShape = function(shape, distance, from) {
    if (isNull(from)) {
        from = RS.FromStart;
    }

    var ret = [];
    if (isLineShape(shape) || isArcShape(shape)) {
        var n = Math.floor(shape.getLength() / distance);
        for (var i=1; i<=n; i++) {
            var p = shape.getPointsWithDistanceToEnd(distance*i, from);
            if (p.length===1) {
                ret.push(p[0]);
            }
        }
    }
    return ret;
};

ShapeAlgorithms.appendShapeToPolylineAuto = function(pl, shape) {
    if (!isFunction(shape.getEndPoint) || !isFunction(shape.reverse)) {
        return;
    }

    if (pl.countVertices()>0 && pl.getEndPoint().equalsFuzzy(shape.getEndPoint())) {
        shape.reverse();
    }
    pl.appendShape(shape);
};

/**
 * Round or bevel between given polylines.
 *
 * \param trimmedShape1 Polyline segment or polyline 1, trimmed to cornerShape.
 * \param ending1 RS::Ending which end was trimmed.
 * \param segmentIndex1 Index of polyline segment that was trimmed.
 * \param trimmedShape2 Polyline segment or polyline 2, trimmed to cornerShape.
 * \param ending2 RS::Ending which end was trimmed.
 * \param segmentIndex2 Index of polyline segment that was trimmed.
 * \param cornerShape Shape to add at corner (arc, line, ...).
 */
ShapeAlgorithms.modifyPolylineCorner = function(polyline1, trimmedShape1, ending1, segmentIndex1,
                                                polyline2, trimmedShape2, ending2, segmentIndex2, cornerShape) {

    return polyline1.modifyPolylineCorner(trimmedShape1, ending1, segmentIndex1,
                                          trimmedShape2, ending2, segmentIndex2, cornerShape);
};


/**
 * Finds the next segment in CCW direction from the cursor position.
 *
 * \param cursor Current position
 * \param dir Direction backwards to last traced segment
 */
//ShapeAlgorithms.getShapeSegment = function(cursor, dir) {

//};

ShapeAlgorithms.divideShape = function(shape, pos1, pos2) {
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
        shape.convertToOpen();
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

        if (isRayShape(shape1)) {
            // ray points in opposite direction:
            cutPos1 = shape1.getStartPoint();
        }
        else {
            cutPos1 = shape1.getEndPoint();
        }

        shape2 = trimStartPoint(shape2, pos1, pos1);

        return [ [ shape1, shape2 ], [ cutPos1, cutPos2 ] ];
    }
};
