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
        if (isNull(minDist) || dist<minDist) {
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
 *         should be or RS.LeftHand or RS.RightHand or RS.BothSides.
 */
ShapeAlgorithms.getOffsetShapes = function(shape, distance, number, sidePosition) {
    ShapeAlgorithms.error = undefined;
    var ret = [];
    var i, n;

    if (isLineBasedShape(shape)) {
        var sides = [];
        if (isVector(sidePosition)) {
            sides.push(shape.getSideOfPoint(sidePosition));
        }
        else {
            if (sidePosition===RS.BothSides) {
                sides.push(RS.LeftHand);
                sides.push(RS.RightHand);
            }
            else {
                sides.push(sidePosition);
            }
        }

        for (i=0; i<sides.length; i++) {
            var side = sides[i];

            var ang;
            if (side===RS.LeftHand) {
                ang = shape.getAngle() + Math.PI/2.0;
            }
            else {
                ang = shape.getAngle() - Math.PI/2.0;
            }

            var distanceV = new RVector();

            for (n=1; n<=number; ++n) {
                distanceV.setPolar(distance * n, ang);
                var parallel = shape.clone();
                parallel.move(distanceV);
                ret.push(parallel);
            }
        }
    }
    else if (isArcShape(shape) || isCircleShape(shape)) {
        var center = shape.getCenter();
        var insides = [];
        if (isVector(sidePosition)) {
            insides.push(center.getDistanceTo(sidePosition) < shape.getRadius());
        }
        else {
            if (sidePosition===RS.BothSides) {
                insides.push(true);
                insides.push(false);
            }
            else {
                if (isCircleShape(shape) || !shape.isReversed()) {
                    if (sidePosition===RS.LeftHand) {
                        insides.push(true);
                    }
                    else {
                        insides.push(false);
                    }
                }
            }
        }

        //var inside = (center.getDistanceTo(sidePosition) < shape.getRadius());

        for (i=0; i<insides.length; i++) {
            var inside = insides[i];
            var d = distance;

            if (inside) {
                d *= -1;
            }

            for (n=1; n<=number; ++n) {
                var concentric = shape.clone();
                concentric.setRadius(shape.getRadius() + d*n);
                if (concentric.getRadius()<0.0) {
                    if (isCircleShape(shape)) {
                        ShapeAlgorithms.error =
                                qsTr("Radius dropped below 0.0 " +
                                     "after %1 concentric circle(s).").arg(n-1);
                    }
                    else {
                        ShapeAlgorithms.error =
                                qsTr("Radius dropped below 0.0 " +
                                     "after %1 concentric arc(s).").arg(n-1);
                    }

                    break;
                }
                ret.push(concentric);
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
ShapeAlgorithms.autoTrim = function(shape, otherShapes, position, extend) {
    if (isNull(extend)) {
        extend = false;
    }

    var res = ShapeAlgorithms.getClosestIntersectionPoints(shape, otherShapes, position, !extend, extend);

    var cutPos1 = undefined;
    var cutPos2 = undefined;

    if (!isNull(res) && res.length>1) {
        cutPos1 = res[0];
        cutPos2 = res[1];
    }

    return ShapeAlgorithms.autoTrimManual(shape, cutPos1, cutPos2, position);
};

ShapeAlgorithms.autoTrimManual = function(shape, cutPos1, cutPos2, position) {
    if (!isCircleShape(shape) && !isFullEllipseShape(shape) &&
        !isXLineShape(shape) && !isRayShape(shape)) {

        if (!isValidVector(cutPos1) || !isValidVector(cutPos2)) {
            // most shapes requires two intersection points:
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

    // xlines:
    else if (isXLineShape(shape)) {
        rest1 = undefined;
        rest2 = undefined;

        if (isValidVector(cutPos2)) {
            rest1 = new RRay(cutPos2, RVector.createPolar(1.0, shape.getDirection2()));
        }
        if (isValidVector(cutPos1)) {
            rest2 = new RRay(cutPos1, RVector.createPolar(1.0, shape.getDirection1()));
        }

        if (isValidVector(cutPos1) && isValidVector(cutPos2)) {
            segment = new RLine();
            segment.setStartPoint(cutPos1);
            segment.setEndPoint(cutPos2);
        }
    }

    // rays:
    else if (isRayShape(shape)) {
        rest1 = undefined;
        rest2 = undefined;

        if (cutPos1.isValid() && !RMath.isSameDirection(cutPos2.getAngleTo(cutPos1), shape.getDirection1(), 0.01)) {
            var dummy = cutPos1;
            cutPos1 = cutPos2;
            cutPos2 = dummy;
        }

        if (isValidVector(cutPos2)) {
            rest1 = new RLine(shape.getBasePoint(), cutPos2);
        }
        if (isValidVector(cutPos1)) {
            rest2 = new RRay(cutPos1, RVector.createPolar(1.0, shape.getDirection1()));
        }

        if (isValidVector(cutPos1) && isValidVector(cutPos2)) {
            segment = new RLine();
            segment.setStartPoint(cutPos1);
            segment.setEndPoint(cutPos2);
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

/**
 * \return The two intersection points of given shape with given
 * otherShapes which are closest to the given position or undefined.
 *
 * \param onShape True: only return intersections on the shape
 * (for trimming, breaking, default).
 * \param onOtherShapes True only return intersections on one of the other
 * shapes (for extending).
 * False: Also consider intersection points outside of shape (for extending).
 */
ShapeAlgorithms.getClosestIntersectionPoints = function(shape, otherShapes, position, onShape, onOtherShapes) {
    if (isNull(onShape)) {
        onShape = true;
    }
    if (isNull(onOtherShapes)) {
        onOtherShapes = false;
    }

    var orthoLine = undefined;

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
            }
        }
    }

    if (isNull(orthoLine) && !isSplineShape(shape)) {
        return undefined;
    }

    var intersections = [];

    // treat start and end points as intersection points:
    if (onShape && !isCircleShape(shape) && !isFullEllipseShape(shape) && !isXLineShape(shape)) {
        intersections.push(shape.getStartPoint());

        if (!isRayShape(shape)) {
            intersections.push(shape.getEndPoint());
        }
    }

    // find all intersection points:
    for (var i=0; i<otherShapes.length; i++) {
        //qDebug("otherShapes[" + i + "]: ", otherShapes[i]);
        var sol = shape.getIntersectionPoints(otherShapes[i].data(), onShape, false, true);
        //qDebug("sol: ", sol);
        for (var k=0; k<sol.length; k++) {
            if (!onOtherShapes || otherShapes[i].isOnShape(sol[k])) {
                intersections.push(sol[k]);
            }
        }
    }

    //qDebug("intersections: ", intersections);

    var cutPos1 = RVector.invalid;
    var distRight = undefined;
    var cutPos2 = RVector.invalid;
    var distLeft = undefined;

    // at least 2 intersection points are required to proceed:
    if (intersections.length<2 && onShape) {
        return undefined;
    }

    // find cutting point left and right of click point:
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
            var tPos = shape.getTAtPoint(position);
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
    }

    if (!isCircleShape(shape) && !isFullEllipseShape(shape) && !isXLineShape(shape) && !isRayShape(shape)) {
        if (!isValidVector(cutPos1)) {
            cutPos1 = shape.getEndPoint();
        }
        if (!isValidVector(cutPos2)) {
            cutPos2 = shape.getStartPoint();
        }
    }

    return [cutPos1, cutPos2];
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

    if (isNull(ret)) {
        ShapeAlgorithms.error = qsTr("No arc possible.");
        return undefined;
    }

    return ret;
};

/**
 * Approximates the given ellipse with arc segments and returns a polyline with
 * arc segments.
 *
 * Derivative work of Wm5ApprEllipseByArcs2.cpp, Geometric Tools, LLC
 * Copyright (c) 1998-2012
 * License: http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
 *
 * \param segments Number of arc segments to generate.
 * \return RPolyline object or undefined
 */
ShapeAlgorithms.approximateEllipse = function(ellipse, segments) {
    ShapeAlgorithms.error = undefined;
    segments = Math.round(segments/4);

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

    // special case: circular ellipse
    if (ellipse.isCircular()) {
        var polyline = new RPolyline();

        var arc = undefined;
        if (ellipse.isFullEllipse()) {
            arc = new RArc(ellipse.getCenter(),
                           ellipse.getMajorRadius(),
                           0,
                           Math.PI,
                           ellipse.isReversed());
            polyline.appendShape(arc);
            arc.setStartAngle(Math.PI);
            arc.setEndAngle(Math.PI*2);
            polyline.appendShape(arc);
        }
        else {
            arc = new RArc(ellipse.getCenter(),
                           ellipse.getMajorRadius(),
                           ellipse.getStartAngle() + ellipse.getAngle(),
                           ellipse.getEndAngle() + ellipse.getAngle(),
                           ellipse.isReversed());
            polyline.appendShape(arc);
        }

//        polyline.appendVertex(arc.getStartPoint(), arc.getBulge());
//        polyline.appendVertex(arc.getEndPoint());

        return polyline;
    }

    var rev = false;
    if (ellipse.isReversed()) {
        ellipse.reverse();
        rev = true;
    }

    var majorRadius = ellipse.getMajorRadius();
    var minorRadius = ellipse.getMinorRadius();

    var rakPoint = new Array(segments+1);
    var rakCenter = new Array(segments);
    var rafRadius = new Array(segments);

    // intermediate ellipse quantities
    var majorRadiusSquare = majorRadius*majorRadius;
    var minorRadiusSquare = minorRadius*minorRadius;
    var minorTimesMajor = majorRadius*minorRadius;
    var invMinorMinusMajor;

    if (Math.abs(minorRadiusSquare-majorRadiusSquare)<RS.PointTolerance) {
        invMinorMinusMajor = 1.0;
    }
    else {
        invMinorMinusMajor = 1.0/(minorRadiusSquare-majorRadiusSquare);
    }

    // segment points on ellipse in first quadrant. points generated ccw
    rakPoint[0] = new RVector(majorRadius,0.0);
    rakPoint[segments] = new RVector(0.0,minorRadius);

    // curvature at end points, store curvature for computing arcs
    var k0 = majorRadius/minorRadiusSquare;
    var k1 = minorRadius/majorRadiusSquare;

    // select ellipse points based on curvature properties
    var invSegments = 1.0/segments;
    var i;
    for (i=1; i<segments; i++) {
        // curvature at new point is weighted average of curvature at ends
        var w1 = i*invSegments;
        var w0 = 1.0 - w1;
        var k = w0*k0 + w1*k1;
        // compute point having this curvature
        var tmp = Math.pow(minorTimesMajor/k, 2.0/3.0);
        var x = majorRadius*Math.sqrt(Math.abs((tmp-majorRadiusSquare)*invMinorMinusMajor));
        var y = minorRadius*Math.sqrt(Math.abs((tmp-minorRadiusSquare)*invMinorMinusMajor));
        rakPoint[i] = new RVector(x, y);
    }

    // compute arc at (a,0)
    var circle = ShapeAlgorithms.createCircleFrom3Points(
                new RVector(rakPoint[1].x,-rakPoint[1].y),
                rakPoint[0], rakPoint[1]);
    rakCenter[0] = circle.getCenter();
    rafRadius[0] = circle.getRadius();

    // compute arc at (0,b)
    var last = segments-1;
    circle = ShapeAlgorithms.createCircleFrom3Points(
                new RVector(-rakPoint[last].x,rakPoint[last].y),
                rakPoint[segments], rakPoint[last]);
    rakCenter[last] = circle.getCenter();
    rafRadius[last] = circle.getRadius();

    // compute arcs at intermediate points between (a,0) and (0,b)
    var iM, iP;
    for (iM = 0, i = 1, iP = 2; i < last; iM++, i++, iP++) {
        circle = ShapeAlgorithms.createCircleFrom3Points(rakPoint[iM], rakPoint[i], rakPoint[iP]);
        rakCenter[i] = circle.getCenter();
        rafRadius[i] = circle.getRadius();
    }

    // create polyline from the arc data:
    var polyline = new RPolyline();

    var arc = undefined;

    var limitAngle1 = RMath.getNormalizedAngle(ellipse.getCenter().getAngleTo(ellipse.getStartPoint()) - ellipse.getAngle());
    var limitAngle2 = RMath.getNormalizedAngle(ellipse.getCenter().getAngleTo(ellipse.getEndPoint()) - ellipse.getAngle());

    var normalizedStartPoint = ellipse.getStartPoint();
    normalizedStartPoint.move(ellipse.getCenter().getNegated());
    normalizedStartPoint.rotate(-ellipse.getAngle());

    var normalizedEndPoint = ellipse.getEndPoint();
    normalizedEndPoint.move(ellipse.getCenter().getNegated());
    normalizedEndPoint.rotate(-ellipse.getAngle());

    // find out start and end quadrant:
    var startQuadrant = 1;
    var endQuadrant = 4;
    if (!ellipse.isFullEllipse()) {
        if (ellipse.getStartAngle() < Math.PI/2.0 - RS.AngleTolerance) {
            startQuadrant = 1;
        } else if (ellipse.getStartAngle() < Math.PI - RS.AngleTolerance) {
            startQuadrant = 2;
        } else if (ellipse.getStartAngle() < Math.PI/2.0*3.0 - RS.AngleTolerance) {
            startQuadrant = 3;
        } else {
            startQuadrant = 4;
        }

        if (ellipse.getEndAngle() < Math.PI/2.0 + RS.AngleTolerance) {
            endQuadrant = 1;
        } else if (ellipse.getEndAngle() < Math.PI + RS.AngleTolerance) {
            endQuadrant = 2;
        } else if (ellipse.getEndAngle() < Math.PI/2.0*3.0 + RS.AngleTolerance) {
            endQuadrant = 3;
        } else {
            endQuadrant = 4;
        }
    }

    var quadrant = startQuadrant;
    var done = false;
    var adding = false;
    var counter = 0;
    do {
        counter++;

        var startIndex;
        var endIndex;
        var step;
        if (quadrant===1 || quadrant===3) {
            startIndex = 0;
            endIndex = segments;
            step = 1;
        }
        else {
            startIndex = segments-1;
            endIndex = -1;
            step = -1;
        }

        for (i=startIndex; i!=endIndex && !done; i+=step) {
            if (quadrant===1) {
                arc = new RArc(rakCenter[i], rafRadius[i], 0.0, 2*Math.PI, false);
                arc.trimStartPoint(rakPoint[i]);
                arc.trimEndPoint(rakPoint[i+1]);
            }
            else if (quadrant===2) {
                arc = new RArc(new RVector(-rakCenter[i].x, rakCenter[i].y),
                        rafRadius[i], 0.0, 2*Math.PI, false);
                arc.trimStartPoint(new RVector(-rakPoint[i+1].x, rakPoint[i+1].y));
                arc.trimEndPoint(new RVector(-rakPoint[i].x, rakPoint[i].y));
            }
            else if (quadrant===3) {
                arc = new RArc(rakCenter[i].getNegated(), rafRadius[i],
                        0.0, 2*Math.PI, false);
                arc.trimStartPoint(rakPoint[i].getNegated());
                arc.trimEndPoint(rakPoint[i+1].getNegated());
            }
            else if (quadrant===4) {
                arc = new RArc(new RVector(rakCenter[i].x, -rakCenter[i].y),
                        rafRadius[i], 0.0, 2*Math.PI, false);
                arc.trimStartPoint(new RVector(rakPoint[i+1].x, -rakPoint[i+1].y));
                arc.trimEndPoint(new RVector(rakPoint[i].x, -rakPoint[i].y));
            }

            if (isNull(arc)) {
                continue;
            }

            if (!ellipse.isFullEllipse()) {
                if (arc.getStartPoint().getDistanceTo(arc.getEndPoint())>RS.PointTolerance) {
                    // does the segment start on ellipse arc?
                    var startInside = RMath.isAngleBetween(arc.getStartPoint().getAngle(),
                        limitAngle1, limitAngle2, ellipse.isReversed());
                    // does the segment end on ellipse arc?
                    var endInside = RMath.isAngleBetween(arc.getEndPoint().getAngle(),
                        limitAngle1, limitAngle2+RS.AngleTolerance, ellipse.isReversed());

                    if (adding && startInside && endInside &&
                        RMath.isAngleBetween(limitAngle2,
                            arc.getStartPoint().getAngle(), arc.getEndPoint().getAngle(), false)) {

                        endInside = false;
                    }

                    if (!adding && startInside && endInside &&
                        RMath.isAngleBetween(limitAngle1,
                            arc.getStartPoint().getAngle(), arc.getEndPoint().getAngle(), false)) {

                        startInside = false;
                    }

                    // arc covers part of the ellipse arc:
                    if (startInside && endInside) {
                        // segment starts exactly at start of ellipse arc:
                        if (Math.abs(arc.getStartPoint().getAngle()-limitAngle1)<RS.AngleTolerance) {
                            adding = true;
                        }
                        // segment ends exactly at end of ellipse arc:
                        if (Math.abs(arc.getEndPoint().getAngle()-limitAngle2)<RS.AngleTolerance) {
                            done = true;
                        }
                        if (adding) {
                            polyline.appendVertex(arc.getStartPoint(), arc.getBulge());
                        }
                    }

                    // arc covers first part of the ellipse arc:
                    else if (endInside) {
                        arc.trimStartPoint(normalizedStartPoint);
                        polyline.appendVertex(arc.getStartPoint(), arc.getBulge());
                        adding = true;
                    }

                    // arc covers last part of the ellipse arc:
                    else if (startInside) {
                        if (adding) {
                            arc.trimEndPoint(normalizedEndPoint);
                            polyline.appendVertex(arc.getStartPoint(), arc.getBulge());
                            done = true;
                        }
                    }

                    // arc covers whole ellipse arc at once:
                    else {
                        var relStartAngle = RMath.getRelativeAngle(arc.getStartPoint().getAngle(), limitAngle1);
                        var relEndAngle = RMath.getRelativeAngle(arc.getEndPoint().getAngle(), limitAngle1);
                        if (relStartAngle<0 && relEndAngle>0) {
                            arc.trimStartPoint(normalizedStartPoint);
                            arc.trimEndPoint(normalizedEndPoint);
                            polyline.appendVertex(arc.getStartPoint(), arc.getBulge());
                            done = true;
                        }
                    }
                }
            }
            else {
                polyline.appendVertex(arc.getStartPoint(), arc.getBulge());
            }

            arc = undefined;
        }

        quadrant++;
        if (quadrant>4) {
            if (ellipse.isFullEllipse()) {
                done = true;
            }
            quadrant=1;
        }
    } while(!done && counter<10);

    // close polyline
    if (!normalizedEndPoint.equalsFuzzy(polyline.getEndPoint())) {
        if (ellipse.isFullEllipse()) {
            polyline.setClosed(true);
        }
        else {
            polyline.appendVertex(normalizedEndPoint);
        }
    }

    // transform polyline to real position of ellipse:
    polyline.rotate(ellipse.getAngle());
    polyline.move(ellipse.getCenter());

    if (rev) {
        polyline.reverse();
    }

    return polyline;
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

//    qDebug("vs[4]: ", vs[4]);
//    qDebug("vs[3]: ", vs[3]);
//    qDebug("vs[2]: ", vs[2]);
//    qDebug("vs[1]: ", vs[1]);

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
    return ShapeAlgorithms.createEllipseInscribedFromVertices(quad[0], quad[1], quad[2], quad[3]);
};


/**
 * Produces an ellipse inscribed in the quadrilateral defined by the
 * four given ordered vertices (RVector).
 *
 * Based on:
 * http://chrisjones.id.au/Ellipses/ellipse.html
 * http://mathworld.wolfram.com/Ellipse.html
 */
ShapeAlgorithms.createEllipseInscribedFromVertices = function(v1, v2, v3, v4) {
    var scale = undefined;

    var i;
    var quad = [v1, v2, v3, v4];

    // numbers in this algorithm can get extremely large, so we scale down here
    // a bit if appropriate:
    var extr = new RBox(RVector.getMinimum(quad), RVector.getMaximum(quad));
    if (extr.getWidth()>100.0 || extr.getHeight()>100.0) {
        scale = 100.0/Math.max(extr.getWidth(), extr.getHeight());
        v1.scale(scale);
        v2.scale(scale);
        v3.scale(scale);
        v4.scale(scale);
    }

    var edges = [];
    for (i=0; i<4; i++) {
        edges[i] = new RLine(quad[i], quad[(i+1)%4]);
    }

    var x0 = quad[0].x;
    var y0 = quad[0].y;
    var x1 = quad[1].x;
    var y1 = quad[1].y;
    var x2 = quad[2].x;
    var y2 = quad[2].y;
    var x3 = quad[3].x;
    var y3 = quad[3].y;

    var ma =  x1 * x2 * y3 - x0 * x2 * y3 - x1 * y2 * x3 + x0 * y2 * x3 - x0 * y1 * x3 + y0 * x1 * x3 + x0 * y1 * x2 - y0 * x1 * x2;
    var mb =  x0 * x2 * y3 - x0 * x1 * y3 - x1 * y2 * x3 + y1 * x2 * x3 - y0 * x2 * x3 + y0 * x1 * x3 + x0 * x1 * y2 - x0 * y1 * x2;
    var mc =  x1 * x2 * y3 - x0 * x1 * y3 - x0 * y2 * x3 - y1 * x2 * x3 + y0 * x2 * x3 + x0 * y1 * x3 + x0 * x1 * y2 - y0 * x1 * x2;
    var md =  y1 * x2 * y3 - y0 * x2 * y3 - x0 * y1 * y3 + y0 * x1 * y3 - y1 * y2 * x3 + y0 * y2 * x3 + x0 * y1 * y2 - y0 * x1 * y2;
    var me = -x1 * y2 * y3 + x0 * y2 * y3 + y1 * x2 * y3 - x0 * y1 * y3 - y0 * y2 * x3 + y0 * y1 * x3 + y0 * x1 * y2 - y0 * y1 * x2;
    var mf =  x1 * y2 * y3 - x0 * y2 * y3 + y0 * x2 * y3 - y0 * x1 * y3 - y1 * y2 * x3 + y0 * y1 * x3 + x0 * y1 * y2 - y0 * y1 * x2;
    var mg =  x1 * y3 - x0 * y3 - y1 * x3 + y0 * x3 - x1 * y2 + x0 * y2 + y1 * x2 - y0 * x2;
    var mh =  x2 * y3 - x1 * y3 - y2 * x3 + y1 * x3 + x0 * y2 - y0 * x2 - x0 * y1 + y0 * x1;
    var mi =  x2 * y3 - x0 * y3 - y2 * x3 + y0 * x3 + x1 * y2 - y1 * x2 + x0 * y1 - y0 * x1;

    var T = RMatrix.create3x3(
        ma, mb, mc,
        md, me, mf,
        mg, mh, mi
    );

    var TI = T.getInverse();

    var mj = TI.get(0, 0);
    var mk = TI.get(0, 1);
    var ml = TI.get(0, 2);
    var mm = TI.get(1, 0);
    var mn = TI.get(1, 1);
    var mo = TI.get(1, 2);
    var mp = TI.get(2, 0);
    var mq = TI.get(2, 1);
    var mr = TI.get(2, 2);

    var a = mj*mj + mm*mm - mp*mp;
    var b = mj*mk + mm*mn - mp*mq;
    var c = mk*mk + mn*mn - mq*mq;
    var d = mj*ml + mm*mo - mp*mr;
    var f = mk*ml + mn*mo - mq*mr;
    var g = ml*ml + mo*mo - mr*mr;

    var term = (b*b - a*c);

    var cx, cy, axis1, axis2;

    // circle:
    if (Math.abs(term)<1e-50) {
        cx = (v1.x + v3.x)/2;
        cy = (v1.y + v3.y)/2;
        axis1 = v1.getDistanceTo(v2)/2;
        axis2 = axis1;
    }
    else {
        cx = (c*d - b*f) / term;
        cy = (a*f - b*d) / term;

        var term1 = (2 * (a*f*f + c*d*d + g*b*b - 2*b*d*f - a*c*g));
        var term2 = Math.sqrt((a-c)*(a-c) + 4*b*b);
        var term3 = (a + c);

        axis1 = Math.sqrt(term1 / (term * (term2-term3)));
        axis2 = Math.sqrt(term1 / (term * (-term2-term3)));
    }

    var center = new RVector(cx, cy);

    var angle;

    if (b===0.0) {
        angle = 0;
    }
    else {
        var arccot = function(v) {
            return Math.PI/2 - Math.atan(v);
        };

        angle = 0.5 * arccot((a-c)/(2*b));
    }

    if (a>c) {
        angle += Math.PI/2;
    }

    var majorPoint = RVector.createPolar(axis1, angle);

    var ellipse = new REllipse(center, majorPoint, axis2/axis1, 0.0, 2*Math.PI, false);

    // workaround if the algorithm above does not produce the correct angle
    // (90 degrees off):
    for (i=0; i<4; i++) {
        var ips = ellipse.getIntersectionPoints(edges[i], false);
        if (ips.length===2) {
            if (!ips[0].equalsFuzzy(ips[1], 0.001)) {
                ellipse.rotate(Math.PI/2, ellipse.getCenter());
                break;
            }
        }
    }

    if (!isNull(scale)) {
        ellipse.scale(new RVector(1.0/scale,1.0/scale));
    }

    return ellipse;
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

            if (splineIsArc && arc.getRadius()>1000.0) {
                return new RLine(startPoint, endPoint);
            }

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
    if (isNull(startAngle)) {
        startAngle = 0.0;
    }

    return new RArc(circle.getCenter(), circle.getRadius(), startAngle, startAngle + 2*Math.PI, false);
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
    var ret = [];
    var i;
    var center;
    var radius;
    var startPoint;
    var endPoint;

    if ((isArcShape(shape) || isEllipseShape(shape)) && shape.isReversed()) {
        shape.reverse();
    }

    if (points.length===0) {
        return [ shape ];
    }

    if (isLineShape(shape)) {
        startPoint = shape.getStartPoint();
        endPoint = shape.getEndPoint();

        points = RVector.getSortedByDistance(points, startPoint);

        if (!startPoint.equalsFuzzy(points[0])) {
            points.unshift(startPoint);
        }
        if (!endPoint.equalsFuzzy(points[points.length-1])) {
            points.push(endPoint);
        }
        for (i=0; i<points.length-1; i++) {
            if (points[i].equalsFuzzy(points[i+1])) {
                continue;
            }

            ret.push(new RLine(points[i], points[i+1]));
        }
        return ret;
    }

    if (isXLineShape(shape)) {
        points = RVector.getSortedByDistance(points, shape.getBasePoint().operator_subtract(shape.getDirectionVector().operator_multiply(1e9)));

        ret.push(new RRay(points[0], shape.getDirectionVector().getNegated()));

        for (i=0; i<points.length-1; i++) {
            if (points[i].equalsFuzzy(points[i+1])) {
                continue;
            }

            ret.push(new RLine(points[i], points[i+1]));
        }

        ret.push(new RRay(points[points.length-1], shape.getDirectionVector()));

        return ret;
    }

    if (isRayShape(shape)) {
        startPoint = shape.getBasePoint();
        points = RVector.getSortedByDistance(points, startPoint);

        if (!startPoint.equalsFuzzy(points[0])) {
            points.unshift(startPoint);
        }

        for (i=0; i<points.length-1; i++) {
            if (points[i].equalsFuzzy(points[i+1])) {
                continue;
            }

            ret.push(new RLine(points[i], points[i+1]));
        }

        ret.push(new RRay(points[points.length-1], shape.getDirectionVector()));

        return ret;
    }

    if (isSplineShape(shape) && RSpline.hasProxy()) {
        startPoint = shape.getStartPoint();
        endPoint = shape.getEndPoint();

        var sortable = [];
        for (i=0; i<points.length; i++) {
            var t = shape.getTAtPoint(points[i]);
            sortable.push([points[i], t]);
        }
        sortable.sort(function(a,b) { return a[1]-b[1]; });

        var sortedPoints = [];
        for (i=0; i<sortable.length; i++) {
            sortedPoints.push(sortable[i][0]);
        }

        return shape.getSegments(sortedPoints);
    }

    if (isCircleShape(shape)) {
        center = shape.getCenter();
        var refAngle = center.getAngleTo(points[0]);
        radius = shape.getRadius();
        startPoint = endPoint = center.operator_add(RVector.createPolar(shape.getRadius(), refAngle));

        points = RVector.getSortedByAngle(points, shape.getCenter(), refAngle);

        if (!startPoint.equalsFuzzy(points[0])) {
            points.unshift(startPoint);
        }
        if (!endPoint.equalsFuzzy(points[points.length-1])) {
            points.push(endPoint);
        }
        for (i=0; i<points.length-1; i++) {
            if (points[i].equalsFuzzy(points[i+1])) {
                continue;
            }

            ret.push(new RArc(center, radius, center.getAngleTo(points[i]), center.getAngleTo(points[i+1]), false));
        }
        return ret;
    }

    if (isArcShape(shape)) {
        center = shape.getCenter();
        radius = shape.getRadius();
        startPoint = shape.getStartPoint();
        endPoint = shape.getEndPoint();

        points = RVector.getSortedByAngle(points, center, shape.getStartAngle());

        if (!startPoint.equalsFuzzy(points[0])) {
            points.unshift(startPoint);
        }
        if (!endPoint.equalsFuzzy(points[points.length-1])) {
            points.push(endPoint);
        }
        for (i=0; i<points.length-1; i++) {
            if (points[i].equalsFuzzy(points[i+1])) {
                continue;
            }

            var e = shape.clone();
            e.setStartAngle(center.getAngleTo(points[i]));
            e.setEndAngle(center.getAngleTo(points[i+1]));
            ret.push(e);
        }
        return ret;
    }

    if (isEllipseShape(shape)) {
        center = shape.getCenter();
        startPoint = shape.getStartPoint();
        endPoint = shape.getEndPoint();

        points = RVector.getSortedByAngle(points, center, center.getAngleTo(startPoint));

        if (!startPoint.equalsFuzzy(points[0])) {
            points.unshift(startPoint);
        }
        if (!endPoint.equalsFuzzy(points[points.length-1])) {
            points.push(endPoint);
        }
        for (i=0; i<points.length-1; i++) {
            if (points[i].equalsFuzzy(points[i+1])) {
                continue;
            }

            var e = shape.clone();
            e.setStartParam(e.getParamTo(points[i]));
            e.setEndParam(e.getParamTo(points[i+1]));
            ret.push(e);
        }
        return ret;
    }

    return ret;
};


/**
 * \return An arc, circle or ellipse, whichever can be used to represent
 * the given ellipse best.
 */
ShapeAlgorithms.ellipseToArcCircleEllipse = function(ellipse) {
    if (ellipse.isCircular()) {
        if (ellipse.isFullEllipse()) {
            return new RCircle(ellipse.getCenter(), ellipse.getMajorRadius());
        }
        else {
            var c = ellipse.getCenter();
            var ret = new RArc(c, ellipse.getMajorRadius(),
                //ellipse.getStartAngle(), ellipse.getEndAngle(),
                0.0, 2*Math.PI,
                ellipse.isReversed());
            ret.setStartAngle(c.getAngleTo(ellipse.getStartPoint()));
            ret.setEndAngle(c.getAngleTo(ellipse.getEndPoint()));
            return ret;
        }
    }
    else {
        return ellipse;
    }
};

/**
 * Transforms the given arc, circle or ellipse into an ellipse
 * using the given function which projects an RVector to another RVector.
 *
 * \returns An REllipse or in special cases an RArc or RCircle.
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

    var v1 = arc.getCenter().operator_add(r1).operator_add(r2);
    var v2 = arc.getCenter().operator_add(r1).operator_subtract(r2);
    var v3 = arc.getCenter().operator_subtract(r1).operator_subtract(r2);
    var v4 = arc.getCenter().operator_subtract(r1).operator_add(r2);

    fun(v1);
    fun(v2);
    fun(v3);
    fun(v4);

    //var ret = [];
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
