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

    var shapes = [ shape1, shape2, shape3 ];

    for (var i=0; i<shapes.length; i++) {
        var s = shapes[i];

        if (isPointShape(s)) {
            points.push(s);
            continue;
        }
        if (isLineBasedShape(s)) {
            lines.push(s);
            continue;
        }
        if (isArcShape(s)) {
            circles.push(new RCircle(s.center, s.radius));
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
            return Apollonius.getSolutionsLCC(lines[0], circles[0], circles[1]);
        }
        else if (circles.length===3) {
            return Apollonius.getSolutionsCCC(circles[0], circles[1], circles[2]);
        }
    }

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
Apollonius.getSolutionsCCC = function(c1, c2, c3, intersect) {
    if (!isCircleShape(c1) ||
        !isCircleShape(c2) ||
        !isCircleShape(c3)) {

        return [];
    }

    var ret = [];

    var circle1 = c1;
    var circle2 = c2;
    var circle3 = c3;

    // special case: at least two circles are concentric: no solution:
    if (c1.center.equalsFuzzy(c2.center) ||
        c1.center.equalsFuzzy(c3.center) ||
        c2.center.equalsFuzzy(c3.center)) {

        return [];
    }

    // special case: three circles of equal size:
    if (RMath.fuzzyCompare(c1.radius, c2.radius) && RMath.fuzzyCompare(c1.radius, c3.radius)) {
        // add outer and inner circles to result:
        var sol = RCircle.createFrom3Points(c1.center, c2.center, c3.center);
        if (sol.isValid()) {
            var sol1 = sol.clone();
            var sol2 = sol.clone();
            sol1.radius = sol1.radius + c1.radius;
            sol2.radius = Math.abs(sol2.radius - c1.radius);
            ret.push(sol1);
            ret.push(sol2);
        }
    }

    // circle1 is always the smallest:
    else {
        if (c2.radius <= c1.radius && c2.radius <= c3.radius) {
            circle1 = c2;
            circle2 = c1;
            circle3 = c3;
        }

        if (c3.radius <= c1.radius && c3.radius <= c2.radius) {
            circle1 = c3;
            circle2 = c1;
            circle3 = c2;
        }
    }

//    qDebug("circle1: ", circle1);
//    qDebug("circle2: ", circle2);
//    qDebug("circle3: ", circle3);

    // special case: three circles intersect in one point:
    var commonIP = Apollonius.getCommonIntersectionPoint(circle1, circle2, circle3);
    if (!isNull(commonIP)) {
        var inversionCircle = new RCircle(commonIP, 10);
        var shapesInverse = Apollonius.getInverseShapes([circle1, circle2, circle3], inversionCircle);

        if (isLineBasedShape(shapesInverse[0]) &&
            isLineBasedShape(shapesInverse[1]) &&
            isLineBasedShape(shapesInverse[2])) {

            var circlesTouching = Apollonius.getSolutions(shapesInverse);
            ret = Apollonius.getInverseShapes(circlesTouching, inversionCircle);
        }

        return ret;
    }

    // special case: each circle intersects the other two,
    // at least one intersects through two points:
    var nIps12 = circle1.getIntersectionPoints(circle2).length;
    var nIps13 = circle1.getIntersectionPoints(circle3).length;
    var nIps23 = circle2.getIntersectionPoints(circle3).length;

    if (!intersect && nIps12>0 && nIps13>0 && nIps23>0 &&
        (nIps12===2 || nIps13===2 || nIps23===2)) {

        var ips12 = circle1.getIntersectionPoints(circle2);
        var ips13 = circle1.getIntersectionPoints(circle3);
        var ips23 = circle2.getIntersectionPoints(circle3);

        var inversionCircles = [];
        var r;

        if (ips12.length===2) {
            r = ips12[0].getDistanceTo(ips12[1]);
            inversionCircles.push(new RCircle(ips12[0], r));
            inversionCircles.push(new RCircle(ips12[1], r));
        }
        if (ips13.length===2) {
            r = ips13[0].getDistanceTo(ips13[1]);
            inversionCircles.push(new RCircle(ips13[0], r));
            inversionCircles.push(new RCircle(ips13[1], r));
        }
        if (ips23.length===2) {
            r = ips23[0].getDistanceTo(ips23[1]);
            inversionCircles.push(new RCircle(ips23[0], r));
            inversionCircles.push(new RCircle(ips23[1], r));
        }

        for (var i=0; i<inversionCircles.length; i++) {
            var circle1Inverse = Apollonius.getInverseShape(circle1, inversionCircles[i]);
            var circle2Inverse = Apollonius.getInverseShape(circle2, inversionCircles[i]);
            var circle3Inverse = Apollonius.getInverseShape(circle3, inversionCircles[i]);

            var iSol = Apollonius.getSolutions(circle1Inverse, circle2Inverse, circle3Inverse);
            var sol = Apollonius.getInverseShapes(iSol, inversionCircles[i]);

            ret = ret.concat(sol);
        }

        ret = Apollonius.removeDuplicates(ret);

        return ret;
    }

    var powerCenter = Apollonius.getPowerCenter(circle1, circle2, circle3);
    //Apollonius.constructionShapes.push(new RPoint(powerCenter));

    if (isNull(powerCenter)) {
        return ret;
    }

    var similarityAxes = Apollonius.getSimilarityAxes(circle1, circle2, circle3);

    for (var i=0; i<similarityAxes.length; i++) {
        // array may contain 'null' items to guarantee index for
        // alpha, beta, gamma tests:
        if (isNull(similarityAxes[i])) {
            continue;
        }

        //Apollonius.constructionShapes.push(similarityAxes[i]);

        var p, pp, q, qq, r, rr;

        var pole1 = Apollonius.getPole(circle1, similarityAxes[i]);
        var pole2 = Apollonius.getPole(circle2, similarityAxes[i]);
        var pole3 = Apollonius.getPole(circle3, similarityAxes[i]);

        if (isNull(pole1) || isNull(pole2) || isNull(pole3)) {
            continue;
        }

//        Apollonius.constructionShapes.push(new RPoint(pole1));
//        Apollonius.constructionShapes.push(new RPoint(pole2));
//        Apollonius.constructionShapes.push(new RPoint(pole3));

        var ray1 = new RLine(powerCenter, pole1);
        var ray2 = new RLine(powerCenter, pole2);
        var ray3 = new RLine(powerCenter, pole3);

        var ips1 = ray1.getIntersectionPoints(circle1, false);
        var ips2 = ray2.getIntersectionPoints(circle2, false);
        var ips3 = ray3.getIntersectionPoints(circle3, false);

        var gotPoints = false;
        if (circle1.contains(powerCenter) || circle2.contains(powerCenter) || circle3.contains(powerCenter)) {
            var ipsRight = [];
            var ipsLeft = [];
            var ipss = [ips1, ips2, ips3];
            for (var k=0; k<ipss.length; k++) {
                var ips = ipss[k];
                for (var n=0; n<ips.length; n++) {
                    var ip = ips[n];
                    if (similarityAxes[i].getSideOfPoint(ip)===RS.RightHand) {
                        ipsRight.push(ip);
                    }
                    else {
                        ipsLeft.push(ip);
                    }
                }
            }
            if (ipsRight.length===3 && ipsLeft.length===3) {
                p = ipsRight[0];
                q = ipsRight[1];
                r = ipsRight[2];
                pp = ipsLeft[0];
                qq = ipsLeft[1];
                rr = ipsLeft[2];
                gotPoints = true;
            }
        }

        if (!gotPoints) {
            ips1 = RVector.getSortedByDistance(ips1, powerCenter);
            ips2 = RVector.getSortedByDistance(ips2, powerCenter);
            ips3 = RVector.getSortedByDistance(ips3, powerCenter);

            if (ips1.length!==2 || ips2.length!==2 || ips3.length!==2) {
                continue;
            }

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
        }

        if (!isNull(p) && !isNull(q) && !isNull(r)) {
            ret.push(RCircle.createFrom3Points(p,q,r));
        }

        if (!isNull(pp) && !isNull(qq) && !isNull(rr)) {
            ret.push(RCircle.createFrom3Points(pp,qq,rr));
        }
    }

    ret = ret.concat(Apollonius.getSolutionsCCCAlt(c1, c2, c3));
    ret = Apollonius.removeDuplicates(ret);
    ret = Apollonius.verify(ret, c1, c2, c3);

    return ret;
}

Apollonius.getSolutionsCCCAlt = function(c1, c2, c3) {
    var circle1 = c1;
    var circle2 = c2;
    var circle3 = c3;

    var allEqualSizes = RMath.fuzzyCompare(circle1.radius, circle2.radius) &&
            RMath.fuzzyCompare(circle1.radius, circle3.radius);

    if (!allEqualSizes
        //&& !intersect
            ) {
        // make sure that circle1 has the smallest radius:
        if (c2.radius <= c1.radius && c2.radius <= c3.radius) {
            circle1 = c2;
            circle2 = c1;
            circle3 = c3;
        }

        if (c3.radius <= c1.radius && c3.radius <= c2.radius) {
            circle1 = c3;
            circle2 = c1;
            circle3 = c2;
        }
    }

    // build arrays of three shapes each: either PCC or PPC:
    var shapes1 = [];
    var shapes2 = [];
    var shapes3 = [];
    var shapes4 = [];

    shapes1.push(new RPoint(circle1.center));
    shapes2.push(new RPoint(circle1.center));
    shapes3.push(new RPoint(circle1.center));
    shapes4.push(new RPoint(circle1.center));

    var circle21 = circle2.clone();
    var circle22 = circle2.clone();
    circle21.radius -= circle1.radius;
    circle22.radius += circle1.radius;
    //        Apollonius.constructionShapes.push(circle21);
    //        Apollonius.constructionShapes.push(circle22);
    if (RMath.fuzzyCompare(circle21.radius, 0.0)) {
        circle21 = new RPoint(circle21.center);
    }
    shapes1.push(circle21.clone());
    shapes2.push(circle21.clone());
    shapes3.push(circle22.clone());
    shapes4.push(circle22.clone());

    var circle31 = circle3.clone();
    var circle32 = circle3.clone();
    circle31.radius -= circle1.radius;
    circle32.radius += circle1.radius;
    //        Apollonius.constructionShapes.push(circle31);
    //        Apollonius.constructionShapes.push(circle32);
    if (RMath.fuzzyCompare(circle31.radius, 0.0)) {
        circle31 = new RPoint(circle31.center);
    }
    shapes1.push(circle31.clone());
    shapes3.push(circle31.clone());
    shapes2.push(circle32.clone());
    shapes4.push(circle32.clone());

    // intermediate solutions for PCC / PPC cases:
    var iSol1 = Apollonius.getSolutions(shapes1[0],shapes1[1],shapes1[2]);
    var iSol2 = Apollonius.getSolutions(shapes2[0],shapes2[1],shapes2[2]);
    var iSol3 = Apollonius.getSolutions(shapes3[0],shapes3[1],shapes3[2]);
    var iSol4 = Apollonius.getSolutions(shapes4[0],shapes4[1],shapes4[2]);

    //        for (var i=0; i<iSol1.length; i++) {
    //            Apollonius.constructionShapes.push(iSol1[i]);
    //        }
    //        for (var i=0; i<shapes2.length; i++) {
    //            Apollonius.constructionShapes.push(shapes2[i]);
    //        }
    //        for (var i=0; i<shapes3.length; i++) {
    //            Apollonius.constructionShapes.push(shapes3[i]);
    //        }
    //        for (var i=0; i<shapes4.length; i++) {
    //            if (!isNull(shapes4[i])) {
    //                Apollonius.constructionShapes.push(shapes4[i]);
    //            }
    //        }

    var iSols = [ iSol1, iSol2, iSol3, iSol4 ];

    var candidates = [];
    for (var i=0; i<iSols.length; i++) {
        if (isNull(iSols[i])) {
            continue;
        }

        for (var k=0; k<iSols[i].length; k++) {
            var obj = iSols[i][k];
            candidates = candidates.concat(ShapeAlgorithms.getOffsetShapes(obj, circle1.radius, 1, RS.BothSides));
        }
    }

    // innermost and outermost solutions for equal sized circles:
    if (allEqualSizes) {
        var sol = RCircle.createFrom3Points(circle1.center, circle2.center, circle3.center);
        var sol1 = sol.clone();
        var sol2 = sol.clone();
        sol1.radius = sol1.radius + circle1.radius;
        sol2.radius = Math.abs(sol2.radius - circle1.radius);
        candidates.push(sol1);
        candidates.push(sol2);
    }

    // filter out non-results:
    return Apollonius.verify(candidates, circle1, circle2, circle3);
};

Apollonius.removeDuplicates = function(shapes) {
    var ret = [];

    for (var i=0; i<shapes.length; i++) {
        var add = true;
        for (var k=0; k<ret.length; k++) {
            if (Apollonius.compareShapes(shapes[i], ret[k])) {
                add = false;
            }
        }

        if (add) {
            ret.push(shapes[i]);
        }
    }

    return ret;
};

Apollonius.compareShapes = function(shape1, shape2) {
    if (isLineBasedShape(shape1)) {
        if (!isLineBasedShape(shape2)) {
            return false;
        }

        return shape1.startPoint.equalsFuzzy(shape2.startPoint) &&
               shape1.endPoint.equalsFuzzy(shape2.endPoint);
    }
    if (isCircleShape(shape1)) {
        if (!isCircleShape(shape2)) {
            return false;
        }

        return shape1.center.equalsFuzzy(shape2.center) &&
               RMath.fuzzyCompare(shape1.radius, shape2.radius);
    }

    debugger;
    return false;
};

Apollonius.verify = function(candidates, shape1, shape2, shape3) {
    var ret = [];
    var shapes = [shape1, shape2, shape3];

    for (var i=0; i<candidates.length; i++) {
        var candidate = candidates[i];

        var pass = true;
        for (var k=0; k<shapes.length; k++) {
            var shape = shapes[k];

            if (!Apollonius.shapesTouch(shape, candidate)) {
                pass = false;
            }
        }

        if (pass) {
            ret.push(candidate);
        }
    }
    return ret;
}

Apollonius.shapesTouch = function(shape1, shape2) {
    if (isNull(shape1) || isNull(shape2)) {
        return false;
    }

    if (isPointShape(shape1)) {
        if (isPointShape(shape2)) {
            return false;
        }
        else {
            return RMath.fuzzyCompare(shape2.getDistanceTo(shape1.position, false), 0.0);
        }
    }
    else if (isLineBasedShape(shape1)) {
        if (isPointShape(shape2)) {
            return Apollonius.shapesTouch(shape2, shape1);
        }
        else if (isLineBasedShape(shape2)) {
            return false;
        }
        else if (isCircleShape(shape2)) {
            return RMath.fuzzyCompare(shape1.getDistanceTo(shape2.center, false), shape2.radius);
        }
    }
    else if (isCircleShape(shape1)) {
        if (isPointShape(shape2)) {
            return Apollonius.shapesTouch(shape2, shape1);
        }
        else if (isLineBasedShape(shape2)) {
            return Apollonius.shapesTouch(shape2, shape1);
        }
        else if (isCircleShape(shape2)) {
            var d = shape1.center.getDistanceTo(shape2.center);
            return RMath.fuzzyCompare(d, shape1.radius + shape2.radius) ||
                   RMath.fuzzyCompare(d, Math.abs(shape1.radius - shape2.radius));
        }
    }

    debugger;
    return false;
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

    //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(tangents12);
    //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(tangents13);
    //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(tangents23);

    var ips12o = [];
    var ips13o = [];
    var ips23o = [];
    var ips12i = [];
    var ips13i = [];
    var ips23i = [];

    // intersection of outer tangents circles 1,2:
    if (!isNull(tangents12[0]) && !isNull(tangents12[1])) {
        ips12o = tangents12[0].getIntersectionPoints(tangents12[1], false);
    }
    // intersection of outer tangents circles 1,3:
    if (!isNull(tangents13[0]) && !isNull(tangents13[1])) {
        ips13o = tangents13[0].getIntersectionPoints(tangents13[1], false);
    }
    // intersection of outer tangents circles 2,3:
    if (!isNull(tangents23[0]) && !isNull(tangents23[1])) {
        ips23o = tangents23[0].getIntersectionPoints(tangents23[1], false);
    }

    // intersection of inner tangents circles 1,2:
    if (!isNull(tangents12[2]) && !isNull(tangents12[3])) {
        ips12i = tangents12[2].getIntersectionPoints(tangents12[3], false);
    }
    else if (ips12o.length===0) {
        // two intersecting circles with same radius:
        ips12i = [RVector.getAverage(c1.center, c2.center)];
    }
    // intersection of inner tangents circles 1,3:
    if (!isNull(tangents13[2]) && !isNull(tangents13[3])) {
        ips13i = tangents13[2].getIntersectionPoints(tangents13[3], false);
    }
    else if (ips13o.length===0) {
        // two intersecting circles with same radius:
        ips13i = [RVector.getAverage(c1.center, c3.center)];
    }
    // intersection of inner tangents circles 2,3:
    if (!isNull(tangents23[2]) && !isNull(tangents23[3])) {
        ips23i = tangents23[2].getIntersectionPoints(tangents23[3], false);
    }
    else if (ips23o.length===0) {
        // two intersecting circles with same radius:
        ips23i = [RVector.getAverage(c2.center, c3.center)];
    }

    // alpha: - for inner / + for outer tangents of circles 2 and 3
    // beta: - for inner / + for outer tangents of circles 1 and 3
    // gamma: - for inner / + for outer tangents of circles 1 and 2

    var l;

    // outer, outer, outer:
    // alpha: +, beta: +, gamma: +
    l = Apollonius.getLine(ips12o, ips13o, ips23o);
    ret.push(l);

    // outer, inner, inner:
    // alpha: -, beta: -, gamma: +
    l = Apollonius.getLine(ips12o, ips13i, ips23i);
    ret.push(l);

    // inner, outer, inner:
    // alpha: -, beta: +, gamma: -
    l = Apollonius.getLine(ips12i, ips13o, ips23i);
    ret.push(l);

    // inner, inner, outer:
    // alpha: +, beta: -, gamma: -
    l = Apollonius.getLine(ips12i, ips13i, ips23o);
    ret.push(l);

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
    if (!isLineBasedShape(line1) ||
        !isLineBasedShape(line2) ||
        !isLineBasedShape(line3)) {

        return [];
    }

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

    var ret = [];
    var radius;
    var c;
    for (var i=0; i<centerPoints.length; i++) {
        var cp = centerPoints[i];
        radius = line1.getDistanceTo(cp, false);
        c = new RCircle(cp, radius);
        ret.push(c);
    }
    return ret;
};


/**
 * \return Solutions for circles that are tangetial to the two given circles
 * and the given point.
 */
Apollonius.getSolutionsPCC = function(point, circle1, circle2) {
    if (!isPointShape(point) ||
        !isCircleShape(circle1) ||
        !isCircleShape(circle2)) {

        return [];
    }

    if (!circle1.isOnShape(point.position, false) &&
        !circle2.isOnShape(point.position, false)) {

        var inversionCircle = new RCircle(point.position, 10);
        //Apollonius.constructionShapes.push(inversionCircle);

        var circles = [];
        circles.push(circle1.clone());
        circles.push(circle2.clone());

        var circlesInverse = Apollonius.getInverseShapes(circles, inversionCircle);
        //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(circlesInverse);

        var tangents = Apollonius.getCommonTangents(circlesInverse[0], circlesInverse[1]);

        return Apollonius.getInverseShapes(tangents, inversionCircle);
    }
    else {
        return [];
    }
};

/**
 * \return Solutions for circles that are tangetial to the two given points
 * and the given circle.
 */
Apollonius.getSolutionsPPC = function(point1, point2, circle) {
    if (!isPointShape(point1) ||
        !isPointShape(point2) ||
        !isCircleShape(circle)) {

        return [];
    }

    // both points are on the circle line:
    if (circle.isOnShape(point1.position) && circle.isOnShape(point2.position)) {
        return [ circle ];
    }

    var inversionCircle = new RCircle(point1.position, 10);

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
    if (!isPointShape(point1) ||
        !isPointShape(point2) ||
        !isLineBasedShape(line)) {

        return [];
    }

    if (line.isOnShape(point1.position)) {
        var p = point1.clone();
        point1 = point2.clone();
        point2 = p.clone();

        if (line.isOnShape(point1.position)) {
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
    if (!isLineBasedShape(line1) ||
        !isLineBasedShape(line2) ||
        !isPointShape(point)) {

        return [];
    }

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
    if (!isLineBasedShape(line1) ||
        !isLineBasedShape(line2) ||
        !isCircleShape(circle)) {

        return [];
    }

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
    var ret = [];
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

                ret.push(obj1);
            }

            if (RMath.fuzzyCompare(obj2.center.getDistanceTo(circle.center), obj2.radius+circle.radius) &&
                RMath.fuzzyCompare(line1.getDistanceTo(obj2.center, false), obj2.radius) &&
                RMath.fuzzyCompare(line2.getDistanceTo(obj2.center, false), obj2.radius)) {

                ret.push(obj2);
            }
        }
    }

    return ret;
};

/**
 * \return Solutions for circles that are tangetial to the given line and the
 * two given circles.
 */
Apollonius.getSolutionsLCC = function(line, circle1, circle2) {
    if (!isLineBasedShape(line) ||
        !isCircleShape(circle1) ||
        !isCircleShape(circle2)) {

        return [];
    }

    if (circle1.radius > circle2.radius) {
        var tmp = circle1;
        circle1 = circle2;
        circle2 = tmp;
    }

    var arr1 = [];
    var arr2 = [];
    var arr3 = [];
    var arr4 = [];

    arr1.push(new RPoint(circle1.center));
    arr2.push(new RPoint(circle1.center));
    arr3.push(new RPoint(circle1.center));
    arr4.push(new RPoint(circle1.center));

    var circle21 = circle2.clone();
    circle21.radius += circle1.radius;
    arr1.push(circle21);
    arr3.push(circle21);

    if (RMath.fuzzyCompare(circle1.radius, circle2.radius)) {
        arr2.push(new RPoint(circle2.center));
        arr3.push(new RPoint(circle2.center));
    }
    else {
        var circle22 = circle2.clone();
        circle22.radius -= circle1.radius;
        arr2.push(circle22);
        arr4.push(circle22);
    }

    var parallels = ShapeAlgorithms.getOffsetShapes(line, circle1.radius, 1, RS.BothSides);
    arr1.push(parallels[0]);
    arr2.push(parallels[0]);
    arr3.push(parallels[1]);
    arr4.push(parallels[1]);

    var cArr1 = Apollonius.getSolutions(arr1[0], arr1[1], arr1[2]);
    var cArr2 = Apollonius.getSolutions(arr2[0], arr2[1], arr2[2]);
    var cArr3 = Apollonius.getSolutions(arr3[0], arr3[1], arr3[2]);
    var cArr4 = Apollonius.getSolutions(arr4[0], arr4[1], arr4[2]);

    var cArrs = [ cArr1, cArr2, cArr3, cArr4 ];
    var ret = [];
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
            obj1.radius += circle1.radius;
            obj2.radius -= circle1.radius;

            if (RMath.fuzzyCompare(obj1.center.getDistanceTo(circle1.center), obj1.radius+circle1.radius) &&
                RMath.fuzzyCompare(obj1.center.getDistanceTo(circle2.center), obj1.radius+circle2.radius) &&
                RMath.fuzzyCompare(line.getDistanceTo(obj1.center, false), obj1.radius)) {

                ret.push(obj1);
            }

            if (RMath.fuzzyCompare(obj2.center.getDistanceTo(circle1.center), obj2.radius+circle1.radius) &&
                RMath.fuzzyCompare(obj2.center.getDistanceTo(circle2.center), obj2.radius+circle2.radius) &&
                RMath.fuzzyCompare(line.getDistanceTo(obj2.center, false), obj2.radius)) {

                ret.push(obj2);
            }
        }
    }

    return ret;
};

/**
 * \return Solutions for circles that are tangetial to the given point, line
 * and circle.
 */
Apollonius.getSolutionsPLC = function(point, line, circle) {
    if (!isPointShape(point) ||
        !isLineBasedShape(line) ||
        !isCircleShape(circle)) {

        return [];
    }

    var inversionCircle = new RCircle(point.position, 10);

    if (line.isOnShape(point.position) || circle.isOnShape(point.position)) {
        // TODO: there is still a colution here:
        return [];
    }

    var shapes = [];
    shapes.push(circle);
    shapes.push(line);

    var shapesInverse = Apollonius.getInverseShapes(shapes, inversionCircle);
    var tangents = Apollonius.getCommonTangents(shapesInverse[0], shapesInverse[1]);

    return Apollonius.getInverseShapes(tangents, inversionCircle);
};

/**
 * \return Solutions for circles that are tangetial to the given point
 * and the given lines.
 */
Apollonius.getSolutionsPLL = function(point, line1, line2) {
    if (!isPointShape(point) ||
        !isLineBasedShape(line1) ||
        !isLineBasedShape(line2)) {

        return [];
    }

    var inversionCircle = new RCircle(point.position, 10);

    if (line1.isOnShape(point.position) && line2.isOnShape(point.position)) {
        return [];
    }

    if (line2.isOnShape(point.position)) {
        return Apollonius.getSolutionsPLL(point, line2, line1);
    }

    if (line1.isOnShape(point.position)) {
        var bisectors = Apollonius.getAngleBisectors(line1, line2);
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
    //Apollonius.constructionShapes.push(line1Inverse);
    var line2Inverse = Apollonius.getInverseShape(line2, inversionCircle);
    //Apollonius.constructionShapes.push(line2Inverse);

    if (!isCircleShape(line1Inverse) || !isCircleShape(line2Inverse)) {
        return [];
    }

    var tangents = Apollonius.getCommonTangents(line1Inverse, line2Inverse);
    //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(tangents);
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

/**
 * \return Given shapes inversed by given inversion circle.
 */
Apollonius.getInverseShapes = function(shapes, inversionCircle) {
    var shapesInverse = [];
    for (var i=0; i<shapes.length; i++) {
        if (isNull(shapes[i])) {
            continue;
        }
        var shapeInverse = Apollonius.getInverseShape(shapes[i], inversionCircle);
        if (!isNull(shapeInverse)) {
            shapesInverse.push(shapeInverse);
        }
    }
    return shapesInverse;
}

/**
 * \return Given shape inversed by given inversion circle.
 */
Apollonius.getInverseShape = function(shape, inversionCircle) {
    if (isPointShape(shape)) {
        var r = inversionCircle.radius;
        var center = inversionCircle.center;
        var d = shape.position.getDistanceTo(center);

        if (Math.abs(d)<RS.PointTolerance) {
            return shape;
        }

        // d' = r^2 / d
        var dInverse = Math.pow(r, 2) / d;

        var x = center.x + (shape.position.x - center.x) * dInverse / d;
        var y = center.y + (shape.position.y - center.y) * dInverse / d;

        return new RPoint(new RVector(x, y));
    }

    if (isLineBasedShape(shape)) {
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
                //debugger;
                radius = Math.abs(radius);
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
    // one shape might be a line:
    if (!isCircleShape(circle1) || !isCircleShape(circle2)) {
        return [];
    }

    // concentric:
    if (circle1.center.equalsFuzzy(circle2.center)) {
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

    var c21 = c2.clone();
    c21.radius -= c1.radius;

    var c22 = c2.clone();
    c22.radius += c1.radius;

    var tangents1 = Apollonius.getTangentsThroughPoint(c21, c1.center);
    var tangents2 = Apollonius.getTangentsThroughPoint(c22, c1.center);

    var ret = [];

    if (tangents1.length === 2) {
        ret[0] = Apollonius.getParallelLinesWithDistance(tangents1[0], c1.radius)[0];
        ret[3] = Apollonius.getParallelLinesWithDistance(tangents1[1], c1.radius)[1];
    }

    if (tangents2.length > 1) {
        ret[1] = Apollonius.getParallelLinesWithDistance(tangents2[1], c1.radius)[0];
        ret[2] = Apollonius.getParallelLinesWithDistance(tangents2[0], c1.radius)[1];
    }

    //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(ret);

    return ret;
};

Apollonius.getTangentsThroughPoint = function(circle, p) {
    if (!isCircleShape(circle)) {
        return [];
    }

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
        if (!isNull(touchingPoints[1])) {
            lines[0] = new RLine(p, touchingPoints[1]);
        }
        else {
            lines[0] = undefined;
        }

        if (!isNull(touchingPoints[0])) {
            lines[1] = new RLine(p, touchingPoints[0]);
        }
        else {
            lines[1] = undefined;
        }

        return lines;
    }
};

Apollonius.getParallelLinesWithDistance = function(line, distance) {
    if (isNull(line)) {
        return [];
    }

    if (!isLineBasedShape(line)) {
        return [];
    }

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
    if (!isCircleShape(c1) ||
        !isCircleShape(c2) ||
        !isCircleShape(c3)) {

        return undefined;
    }

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
    else if (p1_2.equalsFuzzy(p2_1) || p1_2.equalsFuzzy(p2_2)) {
        return p1_2;
    }
    else {
        return undefined;
    }
};

/**
 * \return Angle bisectors of the two given lines or empty array if
 * lines are parallel.
 */
Apollonius.getAngleBisectors = function(line1, line2) {
    if (!isLineBasedShape(line1) ||
        !isLineBasedShape(line2)) {

        return [];
    }

    var angle1 = (line1.getAngle() + line2.getAngle()) / 2;
    var angle2 = angle1 + Math.PI/2;
    var points = line1.getIntersectionPoints(line2, false);
    if (points.length===0) {
        // lines are parallel:
        return [];
    }

    var point = points[0];
    return [
        new RLine(point, angle1, 1.0),
        new RLine(point, angle2, 1.0)
    ];
};

Apollonius.getVerticalToPoint = function(line, p) {
    if (!isLineBasedShape(line)) {
        return undefined;
    }

    var p1 = line.getClosestPointOnShape(p, false);
    return new RLine(p, p1);
};
