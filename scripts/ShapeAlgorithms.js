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

/**
 * \class ShapeAlgorithms
 * Various shape based algorithms.
 */
function ShapeAlgorithms() {
}

/**
 * \return Parallels to this shape.
 * \param distance Distance of first parallel or concentric arc or circle.
 * \param number Number of offset shapes to generate.
 * \param sidePosition RVector indicating what side of the shape the parallels
 *         should be or RS.LeftHand or RS.RightHand or RS.BothSides.
 */
ShapeAlgorithms.getOffsetShapes = function(shape, distance, number, sidePosition) {
    ShapeAlgorithms.error = undefined;
    var ret = new Array();
    var i, n;

    if (isLineShape(shape)) {
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

    //qDebug("intersection points: ", res);

    var cutPos1 = undefined;
    var cutPos2 = undefined;

    if (!isNull(res) && res.length>1) {
        cutPos1 = res[0];
        cutPos2 = res[1];
    }

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

        //if (!remove) {
            segment = shape.clone();
            segment.setStartPoint(cutPos1);
            segment.setEndPoint(cutPos2);
//            if (!segment.getStartPoint().isValid()) {
//                debugger;
//            }
//            if (!segment.getEndPoint().isValid()) {
//                debugger;
//            }
        //}

        if (rest1.getLength()<RS.PointTolerance) {
            rest1 = undefined;
        }

        if (rest2.getLength()<RS.PointTolerance) {
            rest2 = undefined;
        }
    }

    // arcs:
    else if (isArcShape(shape) || isEllipseArcShape(shape)) {
        rest1 = shape.clone();
        rest2 = shape.clone();

        rest1.trimEndPoint(cutPos1);
        rest2.trimStartPoint(cutPos2);

        //if (!remove) {
            segment = shape.clone();
            segment.trimStartPoint(cutPos1);
            segment.trimEndPoint(cutPos2);
        //}

        var angleLength1 = rest1.getAngleLength(true);
        var angleLength2 = rest2.getAngleLength(true);

        if (angleLength1+angleLength2 > shape.getAngleLength()) {
            rest1.trimEndPoint(cutPos2);
            rest2.trimStartPoint(cutPos1);

            //if (!remove) {
                segment.trimStartPoint(cutPos2);
                segment.trimEndPoint(cutPos1);
            //}

            angleLength1 = rest1.getAngleLength(true);
            angleLength2 = rest2.getAngleLength(true);
        }

        if (angleLength1<RS.AngleTolerance) {
            rest1 = undefined;
        }

        if (angleLength2<RS.AngleTolerance) {
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

            //if (!remove) {
                segment = new RArc(
                            shape.getCenter(),
                            shape.getRadius(),
                            angle2, angle1,
                            false);
            //}

            var cursorAngle = shape.getCenter().getAngleTo(position);

            if (RMath.isAngleBetween(cursorAngle, angle1, angle2, false)) {
                rest1.setStartAngle(angle2);
                rest1.setEndAngle(angle1);
                //if (!remove) {
                    segment.setStartAngle(angle1);
                    segment.setEndAngle(angle2);
                //}
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

            //if (!remove) {
                segment = new REllipse(
                            shape.getCenter(),
                            shape.getMajorPoint(),
                            shape.getRatio(),
                            angle2, angle1,
                            false);
            //}

            var cursorAngle = shape.getParamTo(position);

            if (RMath.isAngleBetween(cursorAngle, angle1, angle2, false)) {
                rest1.setStartParam(angle2);
                rest1.setEndParam(angle1);
                //if (!remove) {
                    segment.setStartParam(angle1);
                    segment.setEndParam(angle2);
                //}
            }

            var angleLength1 = rest1.getAngleLength();

            if (angleLength1<RS.AngleTolerance) {
                rest1 = undefined;
            }
        }
    }

    var ret = new Array();

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
    if (isLineShape(shape)) {
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

    if (isNull(orthoLine)) {
        return undefined;
    }

    // find all intersection points:
    var intersections = new Array();
    if (onShape && !isCircleShape(shape) && !isFullEllipseShape(shape)) {
        intersections.push(shape.getStartPoint());
        intersections.push(shape.getEndPoint());
    }

    for (var i=0; i<otherShapes.length; i++) {
        //qDebug("otherShapes[" + i + "]: ", otherShapes[i]);
        var sol = shape.getIntersectionPoints(otherShapes[i].data(), onShape);
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
        if (isLineShape(shape)) {
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
            //dist = RMath.getAngleDifference(orthoLine.getAngle(), shape.getCenter().getAngleTo(inters));
            dist = RMath.getRelativeAngle(shape.getCenter().getAngleTo(inters), orthoLine.getAngle());
            if (dist<0) {
                s = RS.LeftHand;
            }
            else {
                s = RS.RightHand;
            }
            dist = Math.abs(dist);

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

            /*
            if (isNull(distRight) || dist<distRight) {
                cutPos1 = inters;
                distRight = dist;
            }
            if (isNull(distLeft) || dist>distLeft) {
                cutPos2 = inters;
                distLeft = dist;
            }
            */
        }
    }

    if (!isCircleShape(shape) && !isFullEllipseShape(shape)) {
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

/**
 * Tries to convert the given spline into one line or arc.
 * \return RArc, RLine or the original RSpline.
 */
ShapeAlgorithms.splineToLineOrArc = function(spline, tolerance) {
    var startPoint = spline.getStartPoint();
    var endPoint = spline.getEndPoint();
    var middlePoint = spline.getMiddlePoint();
    var i, point;

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
 * Converts the given circle into an arc with start angle 0 and end angle 2*PI.
 */
ShapeAlgorithms.circleToArc = function(circle) {
    return new RArc(circle.getCenter(), circle.getRadius(), 0.0, 2*Math.PI, false);
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
