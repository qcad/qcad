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
include("scripts/library.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Apollonius implementation for fining tangent circles to 
 * three shapes (points, lines, circles).
 */
function Apollonius() {
}

Apollonius.constructionShapes = [];

/**
 * \return Solutions for circles (<=8) that are tangetial to the three given shapes.
 */
Apollonius.getSolutions = function(shape1, shape2, shape3) {
    if (isArray(shape1) && isNull(shape2) && isNull(shape3)) {
        if (shape1.length!==3) {
            debugger;
            return [];
        }
        return Apollonius.getSolutions(shape1[0], shape1[1], shape1[2]);
    }

    var points = [];
    var lines = [];
    var circles = [];

    var shapes = [ shape1, shape2, shape3];

    for (var i=0; i<shapes.length; i++) {
        var s = shapes[i];

        if (isPointShape(s)) {
            points.push(s);
            continue;
        }
        if (isLineShape(s)) {
            lines.push(s);
            continue;
        }
        if (isCircleShape(s)) {
            circles.push(s);
            continue;
        }
    }

    if (points.length===3) {
        return Apollonius.getSolutionsPPP(points[0], points[1], points[2]);
    }

    else if (points.length===2) {
        if (circles.length===1) {
            return Apollonius.getSolutionsPPC(points[0], points[1], circles[0]);
        }
        else if (lines.length===1) {
            return Apollonius.getSolutionsPPL(points[0], points[1], lines[0]);
        }
    }

    else if (points.length===1) {
        if (circles.length===2) {
            return Apollonius.getSolutionsPCC(points[0], circles[0], circles[1]);
        }
        else if (lines.length===2) {
            return Apollonius.getSolutionsPLL(points[0], lines[0], lines[1]);
        }
        else if (circles.length===1 && lines.length===1) {
            // TODO:
            return Apollonius.getSolutionsPLC(points[0], lines[0], circles[0]);
        }
    }

    else if (points.length===0) {
        if (lines.length===3) {
            return Apollonius.getSolutionsLLL(lines[0], lines[1], lines[2]);
        }
        else if (lines.length===2 && circles.length===1) {
            return Apollonius.getSolutionsLLC(lines[0], lines[1], circles[0]);
        }
        else if (lines.length===1 && circles.length===2) {
            // TODO:
            return Apollonius.getSolutionsLCC(lines[0], circles[0], circles[1]);
        }
        else if (circles.length===3) {
            return Apollonius.getSolutionsCCC(circles[0], circles[1], circles[2]);
        }
    }

    qDebug("CASE NOT YET HANDLED");
    debugger;
    return [];
};

/**
 * \return Solutions for circles that are tangetial to the three given points.
 */
Apollonius.getSolutionsPPP = function(point1, point2, point3) {
    return RCircle.createFrom3Points(point1.position, point2.position, point3.position);
};

/**
 * \return Solutions for circles that are tangetial to the three given circles.
 */
Apollonius.getSolutionsCCC = function(c1, c2, c3) {
    var ret = [];
    var circle1 = c1;
    var circle2 = c2;
    var circle3 = c3;

    var commonIP = Apollonius.getCommonIntersectionPoint(circle1, circle2, circle3);
    if (!isNull(commonIP)) {
        var inversionCircle = new RCircle(commonIP, 10);
        var invertedArray = Apollonius.getInverseShapes([circle1, circle2, circle3], inversionCircle);

        if (isLineShape(invertedArray[0]) &&
            isLineShape(invertedArray[1]) &&
            isLineShape(invertedArray[2])) {

            var circlesTouching = Apollonius.getSolutions(invertedArray);
            return Apollonius.getInverseShapes(circlesTouching, inversionCircle);
        }
        else {
            return [];
        }
    }
    else {
        var powerCenter = Apollonius.getPowerCenter(c1, c2, c3);
        qDebug("powerCenter: ", powerCenter);
        var similarityAxes = Apollonius.getSimilarityAxes(c1, c2, c3);
        qDebug("similarityAxes: ", similarityAxes);

        for (var i=0; i<similarityAxes.length; i++) {
            var p, pp, q, qq, r, rr;

            var pole1 = Apollonius.getPole(c1, similarityAxes[i]);
            var pole2 = Apollonius.getPole(c2, similarityAxes[i]);
            var pole3 = Apollonius.getPole(c3, similarityAxes[i]);

            qDebug("poles: ", [pole1, pole2, pole3]);

            var ray1 = new RLine(powerCenter, pole1);
            var ray2 = new RLine(powerCenter, pole2);
            var ray3 = new RLine(powerCenter, pole3);

            qDebug("rays: ", [ray1, ray2, ray3]);

            var ips1 = ray1.getIntersectionPoints(c1, false);
            ips1 = RVector.getSortedByDistance(ips1, powerCenter);
            var ips2 = ray2.getIntersectionPoints(c2, false);
            ips2 = RVector.getSortedByDistance(ips2, powerCenter);
            var ips3 = ray3.getIntersectionPoints(c3, false);
            ips3 = RVector.getSortedByDistance(ips3, powerCenter);

            if (ips1.length===2 && ips2.length===2 && ips3.length===2) {
                // alpha: +
                if (i==0 || i==3) {
                    p = ips1[0];
                    pp = ips1[1];
                }
                // alpha: -
                else {
                    p = ips1[1];
                    pp = ips1[0];
                }

                // beta: +
                if (i==0 || i==2) {
                    q = ips2[0];
                    qq = ips2[1];
                }
                // beta: -
                else {
                    q = ips2[1];
                    qq = ips2[0];
                }

                // gamma: +
                if (i==0 || i==1) {
                    r = ips3[0];
                    rr = ips3[1];
                }
                // gamma: -
                else {
                    r = ips3[1];
                    rr = ips3[0];
                }

                ret.push(RCircle.createFrom3Points(p,q,r));
                ret.push(RCircle.createFrom3Points(pp,qq,rr));
            }
        }
    }

    return ret;
};

/**
 * \return Pole point of the polar line with respect to circle.
 */
Apollonius.getPole = function(circle, polarLine) {
    var r = circle.getRadius();
    var center = circle.getCenter();

    var p = polarLine.getClosestPointOnShape(center, false);
    var op = center.getDistanceTo(p);
    if (Math.abs(op)<RS.PointTolerance) {
        return undefined;
    }

    var opInverse = (r * r) / op;

    var v = p.operator_subtract(center);
    v.setMagnitude2d(opInverse);
    return center.operator_add(v);
};

/**
 * \return Similarity axes of the tree given circles.
 */
Apollonius.getSimilarityAxes = function(c1, c2, c3) {
    var ret = [];
    var tangents12 = ShapeAlgorithms.getTangents(c1, c2);
    var tangents13 = ShapeAlgorithms.getTangents(c1, c3);
    var tangents23 = ShapeAlgorithms.getTangents(c2, c3);

    var ips12o = [];
    var ips13o = [];
    var ips23o = [];
    var ips12i = [];
    var ips13i = [];
    var ips23i = [];

    // intersection of outer tangents circles 1,2:
    if (tangents12.length>1) {
        ips12o = tangents12[0].getIntersectionPoints(tangents12[1], false);
    }
    // intersection of outer tangents circles 1,3:
    if (tangents13.length>1) {
        ips13o = tangents13[0].getIntersectionPoints(tangents13[1], false);
    }
    // intersection of outer tangents circles 2,3:
    if (tangents23.length>1) {
        ips23o = tangents23[0].getIntersectionPoints(tangents23[1], false);
    }
    // intersection of inner tangents circles 1,2:
    if (tangents12.length>3) {
        ips12i = tangents12[2].getIntersectionPoints(tangents12[3], false);
    }
    // intersection of inner tangents circles 1,3:
    if (tangents13.length>3) {
        ips13i = tangents13[2].getIntersectionPoints(tangents13[3], false);
    }
    // intersection of inner tangents circles 2,3:
    if (tangents23.length>3) {
        ips23i = tangents23[2].getIntersectionPoints(tangents23[3], false);
    }

    // alpha: - for inner / + for outer tangents of circles 2 and 3
    // beta: - for inner / + for outer tangents of circles 1 and 3
    // gamma: - for inner / + for outer tangents of circles 1 and 2

    var l;

    // outer, outer, outer:
    // alpha: +, beta: +, gamma: +
    l = Apollonius.getLine(ips12o, ips13o, ips23o);
    if (!isNull(l)) {
        ret.push(l);
    }

    // outer, inner, inner:
    // alpha: -, beta: -, gamma: +
    l = Apollonius.getLine(ips12o, ips13i, ips23i);
    if (!isNull(l)) {
        ret.push(l);
    }

    // inner, outer, inner:
    // alpha: -, beta: +, gamma: -
    l = Apollonius.getLine(ips12i, ips13o, ips23i);
    if (!isNull(l)) {
        ret.push(l);
    }

    // inner, inner, outer:
    // alpha: +, beta: -, gamma: -
    l = Apollonius.getLine(ips12i, ips13i, ips23o);
    if (!isNull(l)) {
        ret.push(l);
    }

    return ret;
};

/**
 * \return Line that connectes first points contained in each array.
 * Helper function. No check is performmed if the three points are indeed on
 * one line.
 */
Apollonius.getLine = function(arr1, arr2, arr3) {
    var ps = [];
    if (arr1.length>0) {
        ps.push(arr1[0]);
    }
    if (arr2.length>0) {
        ps.push(arr2[0]);
    }
    if (arr3.length>0) {
        ps.push(arr3[0]);
    }
    if (ps.length>=2) {
        return new RLine(ps[0], ps[1]);
    }
    return undefined;
};

/**
 * \return Power center of the three given circles.
 */
Apollonius.getPowerCenter = function(c1, c2, c3) {
    var radicalAxis1 = Apollonius.getRadicalAxis(c1, c2);
    //Apollonius.constructionShapes.push(radicalAxis1);
    var radicalAxis2 = Apollonius.getRadicalAxis(c1, c3);
    //Apollonius.constructionShapes.push(radicalAxis2);
    var ips = radicalAxis1.getIntersectionPoints(radicalAxis2, false);
    if (ips.length===0) {
        return undefined;
    }
    return ips[0];
};

/**
 * \return Radical axis of circles c1 and c2 with given length.
 */
Apollonius.getRadicalAxis = function(c1, c2, length) {
    if (isNull(length)) {
        length = 100.0;
    }

    var c2c = new RLine(c1.center, c2.center);
    var dir = c2c.getAngle() + Math.PI/2;
    var center;

    var ips = c1.getIntersectionPoints(c2, false);
    if (ips.length===2) {
        center = RVector.getAverage(ips[0], ips[1]);
    }
    else {
        //Apollonius.constructionShapes.push(c2c);
        var v = RVector.createPolar(c1.radius, c2c.getAngle() + Math.PI/2);
        var p1 = c1.center.operator_add(v);
        v = RVector.createPolar(c2.radius, c2c.getAngle() + Math.PI/2);
        var p3 = c2.center.operator_add(v);
        var p2 = c2c.getMiddlePoint();
        var helperCircle = RCircle.createFrom3Points(p1, p2, p3);
        //Apollonius.constructionShapes.push(helperCircle);
        var ra1 = Apollonius.getRadicalAxis(c1, helperCircle);
        //Apollonius.constructionShapes.push(ra1);
        var ra2 = Apollonius.getRadicalAxis(c2, helperCircle);
        //Apollonius.constructionShapes.push(ra2);
        var rips = ra1.getIntersectionPoints(ra2, false);
        if (rips.length===0) {
            debugger;
        }
        center = c2c.getClosestPointOnShape(rips[0], false);
    }

    var dirV = RVector.createPolar(length*0.5, dir);
    return new RLine(center.operator_subtract(dirV), center.operator_add(dirV));
};


/**
 * \return Solutions for circles (<=4) that are tangetial to the three given lines.
 */
Apollonius.getSolutionsLLL = function(line1, line2, line3) {
    /*
    situations:
    0: all lines are parallel (no solutions)
    3: lines 2 and 3 are parallel
    5: lines 1 and 3 are parallel
    6: lines 1 and 2 are parallel
    7: none of the lines are parallel (4 solutions)
    */

    var situation = 0;
    var angleBisectors1, angleBisectors2, angleBisectors3;
    if (line1.intersectsWith(line2, false)) {
        situation+=1;
    }
    if (line1.intersectsWith(line3, false)) {
        situation+=2;
    }
    if (line2.intersectsWith(line3, false)) {
        situation+=4;
    }

    if (situation === 3 || situation === 5 || situation === 7) {
        angleBisectors1 = Apollonius.getAngleBisectors(line1, line2);
    }
    if (situation == 3 || situation == 6 || situation == 7) {
        angleBisectors2 = Apollonius.getAngleBisectors(line1, line3);
    }
    if (situation == 5 || situation == 6) {
        angleBisectors3 = Apollonius.getAngleBisectors(line2, line3);
    }

    var centerPoints = [];

    if (situation == 3 || situation == 7) {
        centerPoints = centerPoints.concat(angleBisectors1[0].getIntersectionPoints(angleBisectors2[0], false));
        centerPoints = centerPoints.concat(angleBisectors1[0].getIntersectionPoints(angleBisectors2[1], false));
        centerPoints = centerPoints.concat(angleBisectors1[1].getIntersectionPoints(angleBisectors2[0], false));
        centerPoints = centerPoints.concat(angleBisectors1[1].getIntersectionPoints(angleBisectors2[1], false));
    }
    else if (situation == 5) {
        centerPoints = centerPoints.concat(angleBisectors1[0].getIntersectionPoints(angleBisectors3[0], false));
        centerPoints = centerPoints.concat(angleBisectors1[0].getIntersectionPoints(angleBisectors3[1], false));
        centerPoints = centerPoints.concat(angleBisectors1[1].getIntersectionPoints(angleBisectors3[0], false));
        centerPoints = centerPoints.concat(angleBisectors1[1].getIntersectionPoints(angleBisectors3[1], false));
    }
    else if (situation == 6) {
        centerPoints = centerPoints.concat(angleBisectors2[0].getIntersectionPoints(angleBisectors3[0], false));
        centerPoints = centerPoints.concat(angleBisectors2[0].getIntersectionPoints(angleBisectors3[1], false));
        centerPoints = centerPoints.concat(angleBisectors2[1].getIntersectionPoints(angleBisectors3[0], false));
        centerPoints = centerPoints.concat(angleBisectors2[1].getIntersectionPoints(angleBisectors3[1], false));
    }

    var circlesTouching = [];
    var radius;
    var c;
    for (var i=0; i<centerPoints.length; i++) {
        var cp = centerPoints[i];
        radius = line1.getDistanceTo(cp, false);
        c = new RCircle(cp, radius);
        circlesTouching.push(c);
    }
    return circlesTouching;
};


/**
 * \return Solutions for circles that are tangetial to the two given circles
 * and the given point.
 */
Apollonius.getSolutionsPCC = function(point, circle1, circle2) {
    if (!circle1.isOnShape(point.position, false) &&
        !circle2.isOnShape(point.position, false)) {

        var inversionCircle = new RCircle(point.position, 10);
        //Apollonius.constructionShapes.push(inversionCircle);

        var circles = [];
        circles.push(circle1.clone());
        circles.push(circle2.clone());

        var circlesInverse = Apollonius.getInverseShapes(circles, inversionCircle);
        qDebug("circlesInverse", circlesInverse);
        //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(circlesInverse);

        var tangents = Apollonius.getCommonTangents(circlesInverse[0], circlesInverse[1]);
        qDebug("tangents", tangents);

        return Apollonius.getInverseShapes(tangents, inversionCircle);
    }
    else {
        // TODO: error handling
        qDebug("Point is on either circle");
        debugger;
        return undefined;
    }
};

/**
 * \return Solutions for circles that are tangetial to the two given points
 * and the given circle.
 */
Apollonius.getSolutionsPPC = function(point1, point2, circle) {
    // both points are on the circle line:
    if (circle.isOnShape(point1.position) && circle.isOnShape(point2.position)) {
        return [ circle ];
    }

    var inversionCircle = new RCircle(point1.position, 10);
    var ret = [];

    var circleInverse = Apollonius.getInverseShape(circle, inversionCircle);
    var point2Inverse = Apollonius.getInverseShape(point2, inversionCircle);

    var tangents = Apollonius.getTangentsThroughPoint(circleInverse, point2Inverse.position);

    return Apollonius.getInverseShapes(tangents, inversionCircle);
};

/**
 * \return Solutions for circles that are tangetial to the two given points
 * and the given line.
 */
Apollonius.getSolutionsPPL = function(point1, point2, line) {
    if (line.isOnShape(point1.position)) {
        var p = point1.clone();
        point1 = point2.clone();
        point2 = p.clone();

        if (line.isOnShape(point1)) {
            return [];
        }
    }

    var inversionCircle = new RCircle(point1.position, 10);

    var lineInverse = Apollonius.getInverseShape(line, inversionCircle);
    var point2Inverse = Apollonius.getInverseShape(point2, inversionCircle);
    var tangents = Apollonius.getTangentsThroughPoint(lineInverse, point2Inverse.position);

    return Apollonius.getInverseShapes(tangents, inversionCircle);
};

/**
 * \return Solutions for circles that are tangetial to the two given lines
 * and the given point.
 */
Apollonius.getSolutionsLLP = function(line1, line2, point) {
    var inversionCircle = new RCircle(point.position, 10);

    var line1Inverse = Apollonius.getInverseShape(line1, inversionCircle);
    var line2Inverse = Apollonius.getInverseShape(line2, inversionCircle);

    var tangents = Apollonius.getCommonTangents(line1Inverse, line2Inverse);
    return Apollonius.getInverseShapes(tangents, inversionCircle);
};

/**
 * \return Solutions for circles that are tangetial to the two given lines
 * and the given circle.
 */
Apollonius.getSolutionsLLC = function(line1, line2, circle) {
    var parallels1 = ShapeAlgorithms.getOffsetShapes(line1, circle.radius, 1, RS.BothSides);
    var parallels2 = ShapeAlgorithms.getOffsetShapes(line2, circle.radius, 1, RS.BothSides);

    var arr1 = [];
    var arr2 = [];
    var arr3 = [];
    var arr4 = [];

    arr1.push(new RPoint(circle.center));
    arr2.push(new RPoint(circle.center));
    arr3.push(new RPoint(circle.center));
    arr4.push(new RPoint(circle.center));

    arr1.push(parallels1[0]);
    arr2.push(parallels1[0]);
    arr3.push(parallels1[1]);
    arr4.push(parallels1[1]);

    arr1.push(parallels2[0]);
    arr2.push(parallels2[1]);
    arr3.push(parallels2[0]);
    arr4.push(parallels2[1]);

    var cArr1 = Apollonius.getSolutions(arr1[0], arr1[1], arr1[2]);
    var cArr2 = Apollonius.getSolutions(arr2[0], arr2[1], arr2[2]);
    var cArr3 = Apollonius.getSolutions(arr3[0], arr3[1], arr3[2]);
    var cArr4 = Apollonius.getSolutions(arr4[0], arr4[1], arr4[2]);

    var cArrs = [ cArr1, cArr2, cArr3, cArr4 ];
    var rArr = [];
    var tmpCircle, obj1, obj2;
    for (var i=0; i<cArrs.length; i++) {
        var cArr = cArrs[i];

        for (var k=0; k<cArr.length; k++) {
            var obj = cArr[k];
            if (!isCircleShape(obj)) {
                continue;
            }
            tmpCircle = obj.clone();
            obj1 = obj.clone();
            obj2 = obj.clone();
            obj1.radius += circle.radius;
            obj2.radius -= circle.radius;

            if (RMath.fuzzyCompare(obj1.center.getDistanceTo(circle.center), obj1.radius+circle.radius) &&
                RMath.fuzzyCompare(line1.getDistanceTo(obj1.center, false), obj1.radius) &&
                RMath.fuzzyCompare(line2.getDistanceTo(obj1.center, false), obj1.radius)) {

                rArr.push(obj1);
            }

            if (RMath.fuzzyCompare(obj2.center.getDistanceTo(circle.center), obj2.radius+circle.radius) &&
                RMath.fuzzyCompare(line1.getDistanceTo(obj2.center, false), obj2.radius) &&
                RMath.fuzzyCompare(line2.getDistanceTo(obj2.center, false), obj2.radius)) {

                rArr.push(obj2);
            }
        }
    }

    return rArr;
};


/**
 * \return Solutions for circles that are tangetial to the given point
 * and the given lines.
 */
Apollonius.getSolutionsPLL = function(point, line1, line2) {
    var inversionCircle = new RCircle(point.position, 10);

    if (line1.isOnShape(point.position) && line2.isOnShape(point.position)) {
        return [];
    }

    if (line2.isOnShape(point.position)) {
        return Apollonius.getSolutionsPLL(point, line2, line1);
    }

    if (line1.isOnShape(point.position)) {
        var bisectors = Apollonius.getAngleBisectors(line1, line2);
        qDebug("bisectors: ", bisectors);
        if (bisectors.length===0) {
            var distV = line1.getVectorTo(line2.startPoint, false);
            distV = distV.operator_multiply(0.5);
            bisectors = [ new RLine(line1.startPoint.operator_add(distV), line1.endPoint.operator_add(distV)) ];
        }

        var ortho = new RLine(point.position, point.position.operator_add(RVector.createPolar(1.0, line1.getAngle()+Math.PI/2)));

        var ret = [];
        for (var i=0; i<bisectors.length; i++) {
            var ips = bisectors[i].getIntersectionPoints(ortho, false);
            if (ips.length<1) {
                continue;
            }
            ret.push(new RCircle(ips[0], ips[0].getDistanceTo(point.position)));
        }

        return ret;
    }

    var line1Inverse = Apollonius.getInverseShape(line1, inversionCircle);
    Apollonius.constructionShapes.push(line1Inverse);
    var line2Inverse = Apollonius.getInverseShape(line2, inversionCircle);
    Apollonius.constructionShapes.push(line2Inverse);

    if (!isCircleShape(line1Inverse) || !isCircleShape(line2Inverse)) {
        return [];
    }

    var tangents = Apollonius.getCommonTangents(line1Inverse, line2Inverse);
    Apollonius.constructionShapes = Apollonius.constructionShapes.concat(tangents);
    var tangentsInversed = Apollonius.getInverseShapes(tangents, inversionCircle);
    //Apollonius.constructionShapes.push(tangentsInversed);

    var ret = [];
    for (var i=0; i<tangentsInversed.length; i++) {
        if (isCircleShape(tangentsInversed[i])) {
            ret.push(tangentsInversed[i]);
        }
    }

    return ret;
};

/*
Apollonius.getCommonTangents = function() {

};
*/

Apollonius.getInverseShapes = function(shapes, inversionCircle) {
    var iObj;
    var length = shapes.length;
    var invertedArray = [];
    var k=0;
    for (var i=0; i<length; i++) {
        if (isNull(shapes[i])) {
            continue;
        }
        iObj = Apollonius.getInverseShape(shapes[i], inversionCircle);
        if (!isNull(iObj)) {
            invertedArray[k++] = iObj;
        }
    }
    return invertedArray;
}

Apollonius.getInverseShape = function(shape, inversionCircle) {
    if (isPointShape(shape)) {
        var r = inversionCircle.radius;
        var center = inversionCircle.center;
        var d = shape.position.getDistanceTo(center);

        if (Math.abs(d)<RS.PointTolerance) {
            //debugger;
            return shape;
        }

        // d' = r^2 / d
        var dInverse = Math.pow(r, 2) / d;

        var x = center.x + (shape.position.x - center.x) * dInverse / d;
        var y = center.y + (shape.position.y - center.y) * dInverse / d;

        return new RPoint(new RVector(x, y));
    }

    if (isLineShape(shape)) {
        var center = inversionCircle.center;

        if (shape.isOnShape(center, false)) {
            return shape;
        }
        else {
            var s = Apollonius.getVerticalToPoint(shape, center);
            var p = shape.getIntersectionPoints(s, false)[0];
            var pInverse = Apollonius.getInverseShape(new RPoint(p), inversionCircle);

            if (!pInverse.position.isValid()) {
                debugger;
            }

            return RCircle.createFrom2Points(center, pInverse.position);
        }
    }

    if (isCircleShape(shape)) {
        var circle = shape;
        var ips;
        if (circle.center.equalsFuzzy(inversionCircle.center)) {
            // create Point on circle and invert it with the circle
            var radiusHelperPoint = new RPoint(new RVector(circle.center.x + circle.radius, circle.center.y));
            var radius = circle.center.x - Apollonius.getInverseShape(radiusHelperPoint, inversionCircle).position.x;

            if (radius<0) {
                debugger;
            }

            return new RCircle(circle.center, radius);
        }
        else if (circle.isOnShape(inversionCircle.center)) {
            var s = new RLine(inversionCircle.center, circle.center);
            ips = s.getIntersectionPoints(circle, false);
            if (ips.length<1) {
                debugger;
                return undefined;
            }

            var p = ips[0];

            if (p.equalsFuzzy(inversionCircle.center)) {
                if (ips.length<2) {
                    debugger;
                    return undefined;
                }
                p = ips[1];
            }

            var pInverse = Apollonius.getInverseShape(new RPoint(p), inversionCircle);

            if (!pInverse.position.isValid()) {
                debugger;
            }

            return new RLine(pInverse.position, s.getAngle() + Math.PI/2, 1.0);
        }
        else {
            var l = new RLine(inversionCircle.center, circle.center);

            ips = l.getIntersectionPoints(circle, false);
            if (ips.length<2) {
                debugger;
                return undefined;
            }
            var p1 = ips[0];
            var p2 = ips[1];
            var p1Inverse = Apollonius.getInverseShape(new RPoint(p1), inversionCircle);
            var p2Inverse = Apollonius.getInverseShape(new RPoint(p2), inversionCircle);

            if (!p1Inverse.position.isValid()) {
                debugger;
            }
            if (!p2Inverse.position.isValid()) {
                debugger;
            }

            return RCircle.createFrom2Points(p1Inverse.position, p2Inverse.position);
        }
    }

    debugger;
};

/**
 * \return Tangents from circle1 to circle 2
 */
Apollonius.getCommonTangents = function(circle1, circle2) {
    if (circle1.center.equalsFuzzy(circle2.center)) {
        qDebug("Apollonius.getCommonTangents: circles are concentric");
        return [];
    }

    if (circle1.radius < RS.PointTolerance) {
        return Apollonius.getTangentsThroughPoint(circle2, circle1.center);
    }
    if (circle2.radius < RS.PointTolerance) {
        var tangentsInWrongOrder = Apollonius.getTangentsThroughPoint(circle1, circle2.center);
        var tangents = [];
        tangents[0] = tangentsInWrongOrder[1];
        tangents[1] = tangentsInWrongOrder[0];
        return tangents;
    }

    var circle1IsSmaller = circle1.radius < circle2.radius;

    var c1, c2;
    if (circle1IsSmaller) {
        c1 = circle1;
        c2 = circle2;
    }
    else {
        c1 = circle2;
        c2 = circle1;
    }

    var c2s = c2.clone();
    c2s.radius -= c1.radius;

    var c2l = c2.clone();
    c2l.radius += c1.radius;

    var sArr = Apollonius.getTangentsThroughPoint(c2s, c1.center);
    var lArr = Apollonius.getTangentsThroughPoint(c2l, c1.center);

    var ret = [];

    if (sArr.length === 2) {
        ret[0] = Apollonius.getParallelLinesWithDistance(sArr[0], c1.radius)[0];
        ret[3] = Apollonius.getParallelLinesWithDistance(sArr[1], c1.radius)[1];
    }

    if (lArr.length > 1) {
        ret[1] = Apollonius.getParallelLinesWithDistance(lArr[1], c1.radius)[0];
        ret[2] = Apollonius.getParallelLinesWithDistance(lArr[0], c1.radius)[1];
    }

    qDebug("tangents: ", ret);

    return ret;
};

Apollonius.getTangentsThroughPoint = function(circle, p) {
    // used when creating tangential circles to two parallel lines and point:
    if (Math.abs(circle.radius)<RS.PointTolerance) {
        var lines = [];
        lines[0] = lines[1] = new RLine(p, circle.center);
        return lines;
    }

    // point is inside the circle:
    else if (circle.contains(p)) {
        return [];
    }

    // point on the circle line (produces error):
    else if (circle.isOnShape(p)) {
//        var s = new RLine(p, circle.center);
//        var lines = [];
//        lines[0] = lines[1] = new RLine(p, s.getAngle() + Math.PI/2, 1.0);
//        return lines;
        return [];
    }

    // point outside circle:
    else {
        var circle2 = RCircle.createFrom2Points(p, circle.center);
        var touchingPoints = circle2.getIntersectionPoints(circle, false);
        var lines = [];
        lines[0] = new RLine(p, touchingPoints[1]);
        lines[1] = new RLine(p, touchingPoints[0]);
        return lines;
    }
};

Apollonius.getParallelLinesWithDistance = function(line, distance) {
    var point1 = (new RLine(line.startPoint, line.getAngle() + Math.PI/2, distance)).endPoint;
    var point2 = (new RLine(line.startPoint, line.getAngle() - Math.PI/2, distance)).endPoint;
    var line1 = new RLine(point1, line.getAngle(), 1.0);
    var line2 = new RLine(point2, line.getAngle(), 1.0);
    var arr = [];
    arr[0] = line1;
    arr[1] = line2;
    return arr;
};


/**
 * \return Common intersection point of all three circles or undefined.
 */
Apollonius.getCommonIntersectionPoint = function(c1, c2, c3) {
    var ips1 = c1.getIntersectionPoints(c2, false);
    var ips2 = c1.getIntersectionPoints(c3, false);

    if (ips1.length!==2 || ips2.length!==2) {
        return undefined;
    }

    var p1_1 = ips1[0];
    var p1_2 = ips1[1];
    var p2_1 = ips2[0];
    var p2_2 = ips2[1];

    if (p1_1.equalsFuzzy(p2_1) || p1_1.equalsFuzzy(p2_2)) {
        return p1_1;
    }
    else {
        return p1_2;
    }
};

/**
 * \return Angle bisectors of the two given lines or empty array if
 * lines are parallel.
 */
Apollonius.getAngleBisectors = function(line1, line2) {
    var angle1 = (line1.getAngle() + line2.getAngle()) / 2;
    var angle2 = angle1 + Math.PI/2;
    var points = line1.getIntersectionPoints(line2, false);
    if (points.length===0) {
        qDebug("lines are parallel");
        return [];
    }

    var point = points[0];
    return [
        new RLine(point, angle1, 1.0),
        new RLine(point, angle2, 1.0)
    ];
};

Apollonius.getVerticalToPoint = function(line, p) {
    var p1 = line.getClosestPointOnShape(p, false);
    return new RLine(p, p1);

    /*
    var v = RVector.createPolar(10, line.getAngle() + Math.PI/2);
    v = v.operator_add(p);
    return new RLine(p, v);
    */
};
