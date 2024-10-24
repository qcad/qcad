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
 * \return Solutions for circles (<=8) that are tangential to the three given shapes.
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
 * \return Solutions for circles that are tangential to the three given points.
 */
Apollonius.getSolutionsPPP = function(point1, point2, point3) {
    return RCircle.createFrom3Points(point1.position, point2.position, point3.position);
};

/**
 * \return Solutions for circles that are tangential to the three given circles.
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
    // # Enhanced by CVH #
    // Verify if circle 1 is concentric with circle 2:
    if (c1.center.equalsFuzzy(c2.center)) {
        if (c1.center.equalsFuzzy(c3.center)) {
            // Failed: 3 concentric circles
            return [];    // No or infinite solutions
        }
        var rDiff = c1.getRadius() - c2.getRadius();
        var locus = c1.clone();
        circle1 = c3.clone();
    }
    // Verify if circle 1 is concentric with circle 3:
    else if (c1.center.equalsFuzzy(c3.center)) {
        if (c1.center.equalsFuzzy(c2.center)) {
            // Failed: 3 concentric circles
            return [];    // No or infinite solutions
        }
        var rDiff = c1.getRadius() - c3.getRadius();
        var locus = c1.clone();
        circle1 = c2.clone();
    }
    // Verify if circle 2 is concentric with circle 3:
    else if (c2.center.equalsFuzzy(c3.center)) {
        if (c2.center.equalsFuzzy(c1.center)) {
            // Failed: 3 concentric circles
            return [];    // No or infinite solutions
        }
        var rDiff = c2.getRadius() - c3.getRadius();
        var locus = c2.clone();
        circle1 = c1.clone();
    }

    // Handle two concentric circles:
    if (!isNull(locus)) {
        if (!isNumber(rDiff)) {
            return [];    // No solutions
        }
        if (RMath.fuzzyCompare(rDiff, 0.0)) {
            return [];    // Infinite solutions
        }

        // Get intersections of two concentric with the other circle and the locus:
        locus.setRadius(locus.getRadius() - rDiff / 2);
        circle1.setRadius(circle1.getRadius() + Math.abs(rDiff / 2));
        var ips = locus.getIntersectionPoints(circle1);
        circle1.setRadius(circle1.getRadius() - Math.abs(rDiff));
        // Avoid inversion through the center with negative radii:
        if (circle1.getRadius() > 0) {
          ips = ips.concat(locus.getIntersectionPoints(circle1));
        }


        // If any, create tangent circles at intersections;
        if (ips.length === 0) {
            return [];    // No solutions
        }
        for (var i=0; i<ips.length; i++) {
            ret.push(new RCircle(ips[i], Math.abs(rDiff / 2)));
        }

        ret = Apollonius.removeDuplicates(ret);    // Most likely none
        return ret;
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
    circle21.radius = Math.abs(circle21.radius - circle1.radius);
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
    circle31.radius = Math.abs(circle31.radius - circle1.radius);
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
            var offsetShapes = ShapeAlgorithms.getOffsetShapes(obj, circle1.radius, 1, RS.BothSides);
            for (var n=0; n<offsetShapes.length; n++) {
                candidates.push(getPtr(offsetShapes[n]));
            }
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
    v.setMagnitude2D(opInverse);
    return center.operator_add(v);
};

/**
 * \return Similarity axes of the tree given circles.
 */
//Apollonius.getSimilarityAxes = function(c1, c2, c3) {
//    var ret = [];
//    var tangents12 = ShapeAlgorithms.getTangents(c1, c2);
//    var tangents13 = ShapeAlgorithms.getTangents(c1, c3);
//    var tangents23 = ShapeAlgorithms.getTangents(c2, c3);

//    //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(tangents12);
//    //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(tangents13);
//    //Apollonius.constructionShapes = Apollonius.constructionShapes.concat(tangents23);

//    var ips12o = [];
//    var ips13o = [];
//    var ips23o = [];
//    var ips12i = [];
//    var ips13i = [];
//    var ips23i = [];

//    // intersection of outer tangents circles 1,2:
//    if (!isNull(tangents12[0]) && !isNull(tangents12[1])) {
//        ips12o = tangents12[0].getIntersectionPoints(tangents12[1], false);
//    }
//    // intersection of outer tangents circles 1,3:
//    if (!isNull(tangents13[0]) && !isNull(tangents13[1])) {
//        ips13o = tangents13[0].getIntersectionPoints(tangents13[1], false);
//    }
//    // intersection of outer tangents circles 2,3:
//    if (!isNull(tangents23[0]) && !isNull(tangents23[1])) {
//        ips23o = tangents23[0].getIntersectionPoints(tangents23[1], false);
//    }

//    // intersection of inner tangents circles 1,2:
//    if (!isNull(tangents12[2]) && !isNull(tangents12[3])) {
//        ips12i = tangents12[2].getIntersectionPoints(tangents12[3], false);
//    }
//    else if (ips12o.length===0) {
//        // two intersecting circles with same radius:
//        ips12i = [RVector.getAverage(c1.center, c2.center)];
//    }
//    // intersection of inner tangents circles 1,3:
//    if (!isNull(tangents13[2]) && !isNull(tangents13[3])) {
//        ips13i = tangents13[2].getIntersectionPoints(tangents13[3], false);
//    }
//    else if (ips13o.length===0) {
//        // two intersecting circles with same radius:
//        ips13i = [RVector.getAverage(c1.center, c3.center)];
//    }
//    // intersection of inner tangents circles 2,3:
//    if (!isNull(tangents23[2]) && !isNull(tangents23[3])) {
//        ips23i = tangents23[2].getIntersectionPoints(tangents23[3], false);
//    }
//    else if (ips23o.length===0) {
//        // two intersecting circles with same radius:
//        ips23i = [RVector.getAverage(c2.center, c3.center)];
//    }

//    // alpha: - for inner / + for outer tangents of circles 2 and 3
//    // beta: - for inner / + for outer tangents of circles 1 and 3
//    // gamma: - for inner / + for outer tangents of circles 1 and 2

//    var l;

//    // outer, outer, outer:
//    // alpha: +, beta: +, gamma: +
//    l = Apollonius.getLine(ips12o, ips13o, ips23o);
//    ret.push(l);

//    // outer, inner, inner:
//    // alpha: -, beta: -, gamma: +
//    l = Apollonius.getLine(ips12o, ips13i, ips23i);
//    ret.push(l);

//    // inner, outer, inner:
//    // alpha: -, beta: +, gamma: -
//    l = Apollonius.getLine(ips12i, ips13o, ips23i);
//    ret.push(l);

//    // inner, inner, outer:
//    // alpha: +, beta: -, gamma: -
//    l = Apollonius.getLine(ips12i, ips13i, ips23o);
//    ret.push(l);

//    return ret;
//};

/**
 * Returns the similarity axes (0-4) of a triplet of circle shapes.
 * \author Original by Andrew Mustun, fully revised by CVH © 2024.
 *
 * \param c1        First RCircle shape.
 * \param c2        Second RCircle shape.
 * \param c3        Third RCircle shape.
 *
 * \return An array with RLine shapes, at least empty.
 */
Apollonius.getSimilarityAxes = function(c1, c2, c3) {
    var ret = [];         // Collection array for results
    var hCenters12, hCenters13, hCenters23;     // External and internal homothetic centers per combination
    var hExtC, hIntC;     // External and internal homothetic centers
    var d12, d13, d23;    // Intermediate distances
    var p1, p2;           // Positions to consider
    var d1, d2;           // Intermediate distances with current external homothetic center

    // Reject incorrect shape types:
    if (!isCircleShape(c1) ||
        !isCircleShape(c2) ||
        !isCircleShape(c3)) {

        return ret;    // Empty, failed on incorrect data
    }

    // Get the homothetic centers for each pair of circles:
    // Both invalid when a shape is not a circle
    hCenters12 = Apollonius.getHomotheticCenters(c1, c2);
    hCenters13 = Apollonius.getHomotheticCenters(c1, c3);
    hCenters23 = Apollonius.getHomotheticCenters(c2, c3);

    // External and internal homothetic centers, in 2D by default:
    hExtC = [hCenters12[0], hCenters13[0], hCenters23[0]];
    hIntC = [hCenters12[1], hCenters13[1], hCenters23[1]];

    // Remove invalid external homothetic centers:
    hExtC.clean(RVector.invalid);

    // One solution is a line connecting all valid external homothetic centers
    // With at least 2 valid external homothetic centers:
    if (hExtC.length === 2) {
        ret.push(new RLine(hExtC[0], hExtC[1]));
    }
    // With all 3 valid external homothetic centers:
    else if (hExtC.length > 2) {
        // Get all 3 intermediate distances:
        d12 = hExtC[0].getDistanceTo2D(hExtC[1]);
        d13 = hExtC[0].getDistanceTo2D(hExtC[2]);
        d23 = hExtC[1].getDistanceTo2D(hExtC[2]);

        // Comparing with NaN is always false
        // Avoid false assumptions:
        if (!isNumber(d12) || !isNumber(d13) || !isNumber(d23)) {
            return ret;    // Failed, at least one distance is invalid
        }

        // Diversify on the longest segment, 1 out 3:
        if (d13 > d12) {
            if (RMath.fuzzyCompare(d23, d13)) {
                ret.push(new RLine(RVector.getAverage(hExtC[0], hExtC[1]), hExtC[2]));
            }
            else if (d23 > d13) {
                ret.push(new RLine(hExtC[1], hExtC[2]));
            }
            else {
                ret.push(new RLine(hExtC[0], hExtC[2]));
            }
        }
        else {
            if (RMath.fuzzyCompare(d23, d12)) {
                ret.push(new RLine(RVector.getAverage(hExtC[2], hExtC[0]), hExtC[1]));
            }
            else if (d23 > d12) {
                ret.push(new RLine(hExtC[1], hExtC[2]));
            }
            else {
                ret.push(new RLine(hExtC[0], hExtC[1]));
            }
        }
    }

    // Each valid external homothetic centers is crossed a second time
    // This line emerges from one of the other internal homothetic centers
    // Process each valid external homothetic center:
    for (var i=0; i<hExtC.length; i++) {
        // Get intermediate distances with internal homothetic centers, excluding it's own :
        p1 = hIntC[(i+1)%3];
        p2 = hIntC[(i+2)%3];
        d1 = hExtC[i].getDistanceTo2D(p1);
        d2 = hExtC[i].getDistanceTo2D(p2);

        // Comparing with NaN is always false
        // Avoid false assumptions:
        if (!isNumber(d1) || !isNumber(d2)) {
            continue;    // Failed, at least one distance is invalid
        }

        // Diversify on the longest segment:
        if (RMath.fuzzyCompare(d1, d2)) {
            ret.push(new RLine(hExtC[i], RVector.getAverage(p1, p2)));
        }
        else if (d1 > d2) {
            ret.push(new RLine(hExtC[i], p1));
        }
        else {
            ret.push(new RLine(hExtC[i], p2));
        }
    }

    // Return the collected results (0-4):
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
//Apollonius.getRadicalAxis = function(c1, c2, length) {
//    if (isNull(length)) {
//        length = 100.0;
//    }

//    var c2c = new RLine(c1.center, c2.center);
//    var dir = c2c.getAngle() + Math.PI/2;
//    var center;

//    var ips = c1.getIntersectionPoints(c2, false);
//    if (ips.length===2) {
//        center = RVector.getAverage(ips[0], ips[1]);
//    }
//    else {
//        //Apollonius.constructionShapes.push(c2c);
//        var v = RVector.createPolar(c1.radius, c2c.getAngle() + Math.PI/2);
//        var p1 = c1.center.operator_add(v);
//        v = RVector.createPolar(c2.radius, c2c.getAngle() + Math.PI/2);
//        var p3 = c2.center.operator_add(v);
//        var p2 = c2c.getMiddlePoint();
//        var helperCircle = RCircle.createFrom3Points(p1, p2, p3);
//        //Apollonius.constructionShapes.push(helperCircle);
//        var ra1 = Apollonius.getRadicalAxis(c1, helperCircle);
//        //Apollonius.constructionShapes.push(ra1);
//        var ra2 = Apollonius.getRadicalAxis(c2, helperCircle);
//        //Apollonius.constructionShapes.push(ra2);
//        var rips = ra1.getIntersectionPoints(ra2, false);
//        if (rips.length===0) {
//            debugger;
//        }
//        center = c2c.getClosestPointOnShape(rips[0], false);
//    }

//    var dirV = RVector.createPolar(length*0.5, dir);
//    return new RLine(center.operator_subtract(dirV), center.operator_add(dirV));
//};

/**
 * \author Original by Andrew Mustun, hardened &amp; simplified by CVH © 2024.
 * \return Radical axis of circles c1 and c2 with given length or undefined.
 */
Apollonius.getRadicalAxis = function(c1, c2, length) {
    var v;         // An RVector
    var d, dir;    // Length of v and direction
    var d1;        // Distance to center of first circle
    var offset;    // Offset vectors for a line with the given length

    if (!isCircleShape(c1) ||
        !isCircleShape(c2)) {
        return undefined;    // Failed, incorrect data
    }

    if (!c1.center.isValid() || !c2.center.isValid() || !isNumber(c1.radius) || !isNumber(c2.radius)){
        return undefined;    // Failed, invalid data
    }

    if (isNull(length)) {
        length = 100.0;
    }

    // Define a vector from center to center in 2D, its orientation and length, reject concentric:
    v = c2.center.operator_subtract(c1.center);
    v.setZ(0.0);
    d = v.getMagnitude2D();
    if (d < RS.PointTolerance) {
        return undefined;    // Failed, concentric circles
    }
    dir = v.getAngle();

    // Define distance to center of first circle:
    d1 = (d + c1.radius / d * c1.radius - c2.radius / d * c2.radius) / 2;

    // Define position on central axis:
    v.setMagnitude2D(d1);
    v.operator_add_assign(c1.center);

    // Define an offset vector, construct and return the radical axis:
    offset = RVector.createPolar(length / 2, dir + Math.PI/2);
    return new RLine(v.operator_subtract(offset), v.operator_add(offset));
};


/**
 * \return Solutions for circles (<=4) that are tangential to the three given lines.
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
 * \author Andrew Mustun, CVH © 2024
 * \return Solutions for circles (<=4) that are tangential to the two given circles
 * and the given point.
 */
Apollonius.getSolutionsPCC = function(point, circle1, circle2) {
    if (!isPointShape(point) ||
        !isCircleShape(circle1) ||
        !isCircleShape(circle2)) {

        return [];    // Empty, no solutions
    }

    // Relative sized inversion circle (FS#2590):
    var rInv = circle1.getRadius();
    if (circle2.radius > circle1.radius) {
        rInv = circle2.getRadius();
    }
    var inversionCircle = new RCircle(point.getPosition(), rInv);

    // Construct inversion shapes:
    var c1Inverse = Apollonius.getInverseShape(circle1, inversionCircle);
    var c2Inverse = Apollonius.getInverseShape(circle2, inversionCircle);

    // Get all tangent shapes for given inversion shapes:
    // Exploits an enhanced algorithm by CVH
    var tangents = Apollonius.getAllTangents(c1Inverse, c2Inverse);

    // Return the re-inversion of all tangents (0-4 solutions):
    return Apollonius.getInverseShapes(tangents, inversionCircle);
};

/**
 * Especially intended to constructs all tangent shapes of inversed shapes for re-inversion.
 * Supports RCirle and RLine shapes and additionally RPoint shapes as zero sized circles.
 * Returned array is empty with invalid data or no solutions.
 * All but the first tangent of 4 are undefined when non-existent.
 * The first two are typically external tangents, the latter two are internal tangents.
 * There is no guarantee on the order of external/internal tangents and none on the direction.
 * There is no guarantee on the length when not ending on a circle circumference.
 * \author CVH © 2024
 *
 * \param shape1                 First RShape, limited to a circle, a line or a point.
 * \param shape1                 Second RShape, limited to a circle, a line or a point.
 *
 * \return An array with the 4 tangents from shape 1 to shape 2, at least empty or at least 1 defined.
 */
Apollonius.getAllTangents = function(shape1, shape2) {
    var tangents = [];         // Collection of tangent lines to return
    var c1, c2, cTemp;         // Normalized 2D circle shape clones, dummy to order c1-c2 on size
    var c1Radius, c2Radius;    // Radii of circle shapes
    var c1Center, c2Center;    // Centers of circle shapes
    var dC1C2, rDiff, rSum;    // Distance between center points, difference of radii, sum of radii
    var tangent;               // Tangent being constructed
    var a1, a2, at;            // Angles
    var offset1, offset2;      // Offset points
    var line;                  // Line shape
    var ips;                   // Intersection points
    var item1, item2;          // Ifso, RPoints converted to RCircles or the original shape

    // Most common usage: Handle 2 circle shapes first:
    if (isCircleShape(shape1) && isCircleShape(shape2)) {
        // Validate first circle shape:
        if (isValidVector(shape1.center)) {
            if (!isNumber(shape1.radius)) {
                return tangents;    // Empty, invalid radius
            }
            else if (Math.abs(shape1.radius) < RS.PointTolerance) {
                // Handle as zero sized 2D circle:
                c1 = shape1.clone();
                c1.to2D();
                c1.setRadius(0.0);
            }
            else {
                // Handle as normalized 2D circle:
                c1 = shape1.clone();
                c1.to2D();
                c1.setRadius(Math.abs(shape1.getRadius()));
            }
        }
        else {
            return tangents;    // Empty, invalid center
        }

        // Validate second circle shape:
        if (isValidVector(shape2.center)) {
            if (!isNumber(shape2.radius)) {
                return tangents;    // Empty, invalid radius
            }
            else if (Math.abs(shape2.radius) < RS.PointTolerance) {
                // Handle as zero sized 2D circle:
                c2 = shape2.clone();
                c2.to2D();
                c2.setRadius(0.0);
            }
            else {
                // Handle as normalized 2D circle:
                c2 = shape2.clone();
                c2.to2D();
                c2.setRadius(Math.abs(shape2.getRadius()));
            }
        }
        else {
            return tangents;    // Empty, invalid center
        }

        // Ensure that c1 is the smaller circle:
        // Does not swap equal sized circles
        if (c1.radius > c2.radius) {
            cTemp = c1;
            c1 = c2;
            c2 = cTemp;
        }

        // With 2 valid circle shapes;
        c1Radius = c1.getRadius();
        c1Center = c1.getCenter();
        c2Radius = c2.getRadius();
        c2Center = c2.getCenter();
        // Not expecting NaN with 2 valid circle shapes:
        dC1C2 = c1Center.getDistanceTo2D(c2Center);

        // Reject (almost) concentric circles:
        if (dC1C2 < 1e-6) {
            return tangents;    // Empty, no solutions
        }

        // (Almost) internally touching circles:
        if (RMath.fuzzyCompare(dC1C2 + c1Radius, c2Radius)) {    // RS.PointTolerance
            tangent = new RLine(c2Center, c1Center);
            // With 2 radii larger than zero:
            if (c1Radius > 0.0) {
                tangent.setLength((dC1C2 + c1Radius) * 2, true);    // fromStart
            }
            // Handle point on circle here instead of externally touching:
            // Ensuring that the single valid tangent is the first
            else {
                tangent.setLength(c2Radius * 2, true);    // fromStart
            }
            tangent.rotate(Math.PI/2, tangent.getMiddlePoint());

            // First and final solution:
            tangents.push(tangent);
            tangents.push(undefined);
            tangents.push(undefined);
            tangents.push(undefined);

            return tangents;    // One single solution
        }

        // Exclude other nested circles:
        if (dC1C2 + c1Radius < c2Radius) {
            return tangents;    // Empty, no solutions
        }

        // Include external tangents:
        rDiff = c2Radius - c1Radius;
        if (dC1C2 > rDiff) {
            a1 = c1Center.getAngleTo(c2Center);
            a2 = Math.asin(rDiff/dC1C2);
            offset1 = new RVector();
            offset2 = new RVector();

            // First solution:
            at = a1 + a2 + Math.PI/2.0;
            offset1.setPolar(c1Radius, at);
            offset2.setPolar(c2Radius, at);
            tangents.push(new RLine(c1Center.operator_add(offset1),
                                    c2Center.operator_add(offset2)));

            // Second solution, exclude for R1=R2=zero:
            if (c2Radius < RS.PointTolerance) {
                tangents.push(undefined);
            }
            else {
                at = a1 - a2 - Math.PI/2.0;
                offset1.setPolar(c1Radius, at);
                offset2.setPolar(c2Radius, at);
                tangents.push(new RLine(c1Center.operator_add(offset1),
                                    c2Center.operator_add(offset2)));
            }
        }
        // No external tangents:
        else {
            tangents.push(undefined);
            tangents.push(undefined);
        }

        // (Almost) externally touching circles:
        rSum = c2Radius + c1Radius;
        if (RMath.fuzzyCompare(dC1C2, rSum)) {    // RS.PointTolerance
            tangent = new RLine(c2Center, c1Center);
            tangent.setLength(c2Radius * 2, true);    // fromStart
            tangent.rotate(Math.PI/2, tangent.getMiddlePoint());

            // Third and final solution:
            tangents.push(tangent);
            tangents.push(undefined);

            return tangents;    // 3 solutions
        }

        // Include internal tangents but only for radii larger than zero:
        if (dC1C2 > rSum && c1Radius > 0.0) {
            a1 = c1Center.getAngleTo(c2Center);
            a2 = Math.asin(rSum/dC1C2);
            offset1 = new RVector();
            offset2 = new RVector();

            // Third solution:
            at = a1 + a2 + Math.PI/2.0;
            offset1.setPolar(c1Radius, at);
            offset2.setPolar(c2Radius, at);
            tangents.push(new RLine(c1Center.operator_subtract(offset1),
                                    c2Center.operator_add(offset2)));

            // Fourth solution:
            at = a1 - a2 - Math.PI/2.0;
            offset1.setPolar(c1Radius, at);
            offset2.setPolar(c2Radius, at);
            tangents.push(new RLine(c1Center.operator_subtract(offset1),
                                    c2Center.operator_add(offset2)));
        }
        // No internal tangents:
        else {
            tangents.push(undefined);
            tangents.push(undefined);
        }

        return tangents;    // 4 solutions
    } // End 2 circles

    // With 2 line shapes (Circles with infinite radii):
    else if (isLineBasedShape(shape1) && isLineBasedShape(shape2)) {
        if (shape1.isValid() && shape2.isValid()) {
            // Handle as 2D RLine shapes:
            // This would convert RXLine and RRay shapes
            c1 = new RLine(shape1.getStartPoint(), shape1.getEndPoint());
            c1.to2D();
            c2 = new RLine(shape2.getStartPoint(), shape2.getEndPoint());
            c2.to2D();

            // The angle of a near zero-length line is zero by default (RVector::getAngle())
            // Exclude solutions for a line with almost no length:
            if (c1.getLength() <= 1.0e-6 || c2.getLength() <= 1.0e-6) {
                return tangents;    // Empty, not processable line(s)
            }

            // Diversify on crossing or not:
            // RLine.isParallel(...) may fail (FS#2495)
            ips = shape1.getIntersectionPoints(shape2, false);    // unlimited
            if (ips.isEmpty()) {
                dC1C2 = c1.getDistanceTo(c2.getStartPoint(), false);    // unlimited
                // May return NaN, comparing with NaN is always false
                if (!isNumber(dC1C2) || dC1C2 > RS.PointTolerance) {
                    return tangents;    // Empty, incorrect data or parallel at a distance
                }
                else {
                    // Include one representation of itself when collinear:
                    ips = c1.getEndPoints();
                    ips = ips.concat(c2.getEndPoints());
                    ips = RVector.getSortedLeftRightTopBottom(ips);
                    tangents.push(new RLine(ips[0], ips[3]));
                    tangents.push(undefined);
                }
            }
            // With an intersection point:
            else {
                a1 = (c1.getAngle() + c2.getAngle()) / 2;
                a2 = a1 + Math.PI/2;
                length = (c1.getLength() + c2.getLength()) / 2;
                tangents.push(new RLine(ips[0], a1, length));
                tangents.push(new RLine(ips[0], a2, length));
            }

            // Limited to 2 solutions:
            tangents.push(undefined);
            tangents.push(undefined);
        }

        return tangents;    // No or 1-2 solution(s)
    } // End line-line

    // With a circle and a line shape:
    if (isCircleShape(shape1) && isLineBasedShape(shape2)) {
        if (isValidVector(shape1.center) &&
            isNumber(shape1.radius) &&
            shape2.isValid()) {

            // Handle second shape as 2D RLine:
            // This would convert RXLine and RRay shapes
            line = new RLine(shape2.getStartPoint(), shape2.getEndPoint());
            line.to2D();

            // The angle of a near zero-length line is zero by default (RVector::getAngle())
            // Exclude solutions for a line with almost no length:
            if (line.getLength() <= 1.0e-6) {
                return tangents;    // Empty, not processable line
            }

            // Handle first shape as normalized 2D circle:
            c2 = shape1.clone();
            c2.to2D();
            c2.setRadius(Math.abs(shape1.getRadius()));
        }
    } // End circle-line

    // With a line and a circle shape:
    else if (isLineBasedShape(shape1) && isCircleShape(shape2)) {
        if (isValidVector(shape2.center) &&
            isNumber(shape2.radius) &&
            shape1.isValid()) {

            // Handle first shape as 2D RLine:
            // This would convert RXLine and RRay shapes
            line = new RLine(shape1.getStartPoint(), shape1.getEndPoint());
            line.to2D();

            // The angle of a near zero-length line is zero by default (RVector::getAngle())
            // Exclude solutions for a line with almost no length:
            if (line.getLength() <= 1.0e-6) {
                return tangents;    // Empty, not processable line
            }

            // Handle second shape as normalized 2D circle:
            c2 = shape2.clone();
            c2.to2D();
            c2.setRadius(Math.abs(shape2.getRadius()));
        }
    } // End line-circle

    // Least common usage: Support RPoint shapes as zero sized RCircle shapes:
    // Circle shapes are not guaranteed to be valid circles
    // Shapes are further validated and handled by a recursive call
    else if (isPointShape(shape1) || isPointShape(shape2)) {
        // Ifso, convert first point into an RCircle:
        if (isPointShape(shape1)) {
            item1 = new RCircle(shape1.getPosition(), 0.0)
        }
        else {
            item1 = shape1;
        }

        // Ifso, convert second point into an RCircle:
        if (isPointShape(shape2)) {
            item2 = new RCircle(shape2.getPosition(), 0.0)
        }
        else {
            item2 = shape2;
        }

        // Handle the occurrence of points as circles:
        return Apollonius.getAllTangents(item1, item2);
    }

    // With any unsupported shape:
    else {
        return tangents;    // Empty, incorrect data
    }

    // With validated line and circle shapes:
    // Solutions are tangent to the circle and in special tangent to the line at infinity
    c2Radius = c2.getRadius();
    c2Center = c2.getCenter();
    a1 = line.getAngle();
    // Arbitrary tangent length
    c1Radius = Math.max(c2Radius, line.getLength() / 2);

    // Define a perpendicular diameter:
    ips = line.getClosestPointOnShape(c2Center, false);    // unlimited
    if (ips.equalsFuzzy(c2Center)) {    // RS.PointTolerance
        ips = c2.getIntersectionPoints(line, false);    // unlimited
        line = new RLine(c2Center, ips[0]);
        line.rotate(Math.PI/2, c2Center);
    }
    else {
        line = new RLine(c2Center, ips);
    }
    line.setLength(c2Radius, true);    // fromStart
    line.reverse();
    line.setLength(c2Radius * 2, true);    // fromStart

    // Include first parallels tangent at circle:
    tangents.push(new RLine(line.getStartPoint(), a1, c1Radius));
    // Include a second solution for R2>zero:
    if (c2Radius > 0.0) {
        a2 = a1 + Math.PI;
        tangents.push(new RLine(line.getEndPoint(), a2, c1Radius));
    }
    else {
        tangents.push(undefined);
    }

    // Limited to 2 solutions:
    tangents.push(undefined);
    tangents.push(undefined);

    return tangents;    // 1-2 solutions
};

/**
 * \return Solutions for circles that are tangential to the two given points
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

    var pOnCircle = undefined;
    var pOther = undefined;
    if (circle.isOnShape(point1.position)) {
        pOnCircle = point1.position;
        pOther = point2.position;
    }
    if (circle.isOnShape(point2.position)) {
        pOnCircle = point2.position;
        pOther = point1.position;
    }
    // one point is on circle:
    if (!isNull(pOnCircle) && !isNull(pOther)) {
        //Apollonius.constructionShapes = [];

        // line from circle center to point on circle:
        var l = new RLine(circle.getCenter(), pOnCircle);
        //Apollonius.constructionShapes.push(l);
        // middle orthogonal between points:
        var m = RVector.getAverage(pOnCircle, pOther);
        var lOrtho = new RLine(m, pOther.getAngleTo(pOnCircle) + Math.PI/2, 1.0);
        //Apollonius.constructionShapes.push(lOrtho);

        var ips = l.getIntersectionPoints(lOrtho, false);
        if (ips.length!==1) {
            return [];
        }
        return [ new RCircle(ips[0], ips[0].getDistanceTo(pOnCircle)) ];
    }


    var inversionCircle = new RCircle(point1.position, 10);

    var circleInverse = Apollonius.getInverseShape(circle, inversionCircle);
    var point2Inverse = Apollonius.getInverseShape(point2, inversionCircle);

    var tangents = Apollonius.getTangentsThroughPoint(circleInverse, point2Inverse.position);

    return Apollonius.getInverseShapes(tangents, inversionCircle);
};

/**
 * \return Solutions for circles that are tangential to the two given points
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
 * \return Solutions for circles that are tangential to the two given lines
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
            obj2.radius = Math.abs(obj2.radius - circle.radius);

            var d1 = obj1.center.getDistanceTo(circle.center);
            if ((RMath.fuzzyCompare(d1, obj1.radius+circle.radius) ||
                 RMath.fuzzyCompare(d1, Math.abs(obj1.radius-circle.radius))) &&
                RMath.fuzzyCompare(line1.getDistanceTo(obj1.center, false), obj1.radius) &&
                RMath.fuzzyCompare(line2.getDistanceTo(obj1.center, false), obj1.radius)) {

                ret.push(obj1);
            }

            var d2 = obj2.center.getDistanceTo(circle.center);
            if ((RMath.fuzzyCompare(d2, obj2.radius+circle.radius) ||
                 RMath.fuzzyCompare(d2, Math.abs(obj2.radius-circle.radius))) &&
                RMath.fuzzyCompare(line1.getDistanceTo(obj2.center, false), obj2.radius) &&
                RMath.fuzzyCompare(line2.getDistanceTo(obj2.center, false), obj2.radius)) {

                ret.push(obj2);
            }
        }
    }

    return ret;
};

/**
 * \return Solutions for circles that are tangential to the given line and the
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

    // find solutions for tangent to:
    // center point of smaller circle,
    // concentric circles for larger circle with distance = radius of smaller circle
    // parallels to line with distance = radius of smaller circle
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
        circle22.radius = Math.abs(circle22.radius - circle1.radius);
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

//    qDebug("cArr1:\n" + cArr1 + "\n\n");
//    qDebug("cArr2:\n" + cArr2 + "\n\n");
//    qDebug("cArr3:\n" + cArr3 + "\n\n");
//    qDebug("cArr4:\n" + cArr4 + "\n\n");

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
            obj2.radius = Math.abs(obj2.radius - circle1.radius);

            var obj1c1 = obj1.center.getDistanceTo(circle1.center);
            var obj1c2 = obj1.center.getDistanceTo(circle2.center);
            if ((RMath.fuzzyCompare(obj1c1, circle1.radius+obj1.radius) ||
                 RMath.fuzzyCompare(obj1c1, Math.abs(circle1.radius-obj1.radius))) &&
                (RMath.fuzzyCompare(obj1c2, circle2.radius+obj1.radius) ||
                 RMath.fuzzyCompare(obj1c2, Math.abs(circle2.radius-obj1.radius))) &&
                RMath.fuzzyCompare(line.getDistanceTo(obj1.center, false), obj1.radius)) {

                ret.push(obj1);
            }

            var obj2c1 = obj2.center.getDistanceTo(circle1.center);
            var obj2c2 = obj2.center.getDistanceTo(circle2.center);
            if ((RMath.fuzzyCompare(obj2c1, circle1.radius+obj2.radius) ||
                 RMath.fuzzyCompare(obj2c1, Math.abs(circle1.radius-obj2.radius))) &&
                (RMath.fuzzyCompare(obj2c2, circle2.radius+obj2.radius) ||
                 RMath.fuzzyCompare(obj2c2, Math.abs(circle2.radius-obj2.radius))) &&
                RMath.fuzzyCompare(line.getDistanceTo(obj2.center, false), obj2.radius)) {

                ret.push(obj2);
            }
        }
    }

    return ret;
};

/**
 * \return Solutions for circles that are tangential to the given point, line
 * and circle.
 */
Apollonius.getSolutionsPLC = function(point, line, circle) {
    if (!isPointShape(point) ||
        !isLineBasedShape(line) ||
        !isCircleShape(circle)) {

        return [];
    }

    var lData = line;
    if (isFunction(line.data)) {
        lData = line.data();
    }

//    if (point.position.equalsFuzzy(new RVector(190,90))) {
//        debugger;
//    }




//    var inversionCircle = new RCircle(point.position, 10);

//    if (line.isOnShape(point.position) || circle.isOnShape(point.position)) {
//        // TODO: there is still a solution here:
//        return [];
//    }

//    var shapes = [];
//    shapes.push(circle);
//    shapes.push(line);

//    var shapesInverse = Apollonius.getInverseShapes(shapes, inversionCircle);
//    var tangents = Apollonius.getCommonTangents(shapesInverse[0], shapesInverse[1]);

//    return Apollonius.getInverseShapes(tangents, inversionCircle);




    var a = point.getPosition();
    var c = circle.getCenter();
    var f = line.getClosestPointOnShape(c, false);
    var ortho = new RLine(c, f);

    var cf = f.operator_subtract(c);
    var ce = cf.copy();
    ce.setMagnitude2D(circle.getRadius());
    // intersections of orthogonal through c to line with circle:
    var d1 = c.operator_add(ce);
    var e1 = c.operator_subtract(ce);
    var ds = [d1, e1];
    var es = [e1, d1];

    var centerCandidates = [];
    var ips;
    var p;

    for (var i=0; i<2; i++) {
        var d = ds[i];
        var e = es[i];

        // special case:
        // a is on orthogonal cf:
        if (ortho.getDistanceTo(a, false)<RS.PointTolerance) {
            var da_ = new RLine(d, f);
            da_.rotate(Math.PI/4, d);
            var par = line.clone();
            par.moveTo(a);

            ips = da_.getIntersectionPoints(par, false);
            if (ips.length!==1) {
                continue;
            }
            var a_ = ips[0];

            ips = da_.getIntersectionPoints(lData, false);
            if (ips.length!==1) {
                continue;
            }

            var f_ = ips[0];

            var a_e = new RLine(a_, e);
            var f_p = a_e.clone();
            f_p.moveTo(f_);

            ips = f_p.getIntersectionPoints(ortho, false);
            if (ips.length!==1) {
                continue;
            }

            p = ips[0];

            var apm = RVector.getAverage(a, p);
            var m = line.getDistanceTo(apm, false);
            var circ = new RCircle(a, m);
            var par2 = line.clone();
            par2.moveTo(apm);

            ips = par2.getIntersectionPoints(circ, false);
            centerCandidates = centerCandidates.concat(ips);
        }

        // special case:
        // point is on line:
        else if (line.isOnShape(a, false)) {
            // similarity axis:
            var ea = new RLine(e, a);
            ips = circle.getIntersectionPoints(ea, false);
            if (ips.length!==2) {
                continue;
            }
            var i1 = ips[0];
            if (i1.equalsFuzzy(e)) {
                i1 = ips[1];
            }
            var ci1 = new RLine(c, i1);

            // ortho through a:
            var orthoA = new RLine(a, line.getAngle() + Math.PI/2, 1.0)

            ips = orthoA.getIntersectionPoints(ci1, false);
            if (ips.length!==1) {
                continue;
            }

            centerCandidates.push(ips[0]);
        }

        else {
            var da = new RLine(d, a);
            ips = da.getIntersectionPoints(lData, false);
            if (ips.length!==1) {
                continue;
            }
            var m = ips[0];
            var efa = RCircle.createFrom3Points(e, f, a);
            var ps = da.getIntersectionPoints(efa, false);
            if (ps.length<1) {
                continue;
            }
            p = ps[0];
            if (p.equalsFuzzy(a) && ps.length>1) {
                p = ps[1];
            }

            var ap = new RLine(a, p);
            var apOrtho = ap.copy();
            apOrtho.rotate(Math.PI/2, ap.getMiddlePoint());

            var tangents = Apollonius.getTangentsThroughPoint(efa, m);
            for (var k=0; k<tangents.length; k++) {
                var tangent = tangents[k];
                if (isNull(tangent)) {
                    continue;
                }

                var mt = tangent.getLength();
                var mu = line.endPoint.operator_subtract(line.startPoint);
                mu.setMagnitude2D(mt);
                var u = m.operator_add(mu);
                var v = m.operator_subtract(mu);
                var orthU = line.clone();
                orthU.rotate(Math.PI/2, u);
                var orthV = line.clone();
                orthV.rotate(Math.PI/2, v);

                var pps = apOrtho.getIntersectionPoints(orthU, false);
                centerCandidates = centerCandidates.concat(pps);
                pps = apOrtho.getIntersectionPoints(orthV, false);
                centerCandidates = centerCandidates.concat(pps);
            }
        }
    }

    var res = [];
    for (var n=0; n<centerCandidates.length; n++) {
        var centerCandidate = centerCandidates[n];
        res.push(new RCircle(centerCandidate, centerCandidate.getDistanceTo(a)));
    }
    return res;
};

/**
 * \return Solutions for circles that are tangential to the given point
 * and the given lines.
 */
Apollonius.getSolutionsPLL = function(point, line1, line2) {
    if (!isPointShape(point) ||
        !isLineBasedShape(line1) ||
        !isLineBasedShape(line2)) {
        return [];
    }

    var line2Data;
    if (isFunction(line2.data)) {
        line2Data = line2.data();
    }
    else {
        line2Data = line2;
    }

    // intersection between two lines line1, line2:
    var ipsLL = line1.getIntersectionPoints(line2Data, false);

    var ips;
    var i, k, c;
    var circles, circle;
    var centers = [];

    var bisectorLines = Apollonius.getAngleBisectors(line1, line2);
    var bisectorLine;

    var onLine1 = line1.isOnShape(point.position, false);
    var onLine2 = line2.isOnShape(point.position, false);

    var onBisector = false;
    for (k=0; k<bisectorLines.length; k++) {
        if (bisectorLines[k].isOnShape(point.position, false)) {
            onBisector = true;
            break;
        }
    }

    // lines are parallel:
    if (ipsLL.length===0) {
        // middle line:
        var s = line1.getStartPoint();
        var p = line2.getClosestPointOnShape(s, false);
        var center = RVector.getAverage(s, p);
        var middleLine = line1.clone();
        middleLine.move(center.operator_subtract(middleLine.getStartPoint()));
        // circle with radius c-s around point:
        circle = new RCircle(point.position, center.getDistanceTo(s));
        // intersections between circle and middle line are candidates:
        centers = circle.getIntersectionPoints(middleLine, false);
    }

    // point is on line1 or line2:
    else if (onLine1 || onLine2) {
        var line = onLine1 ? line1 : line2;
        var orthoLine = new RLine(point.position, line.getAngle() + Math.PI/2, 1.0);
        for (k=0; k<bisectorLines.length; k++) {
            bisectorLine = bisectorLines[k];
            ips = bisectorLine.getIntersectionPoints(orthoLine, false);
            if (ips.length!==1) {
                continue;
            }
            centers.push(ips[0]);
        }
    }

    else {
        var centerCandidates = [];

        // point on bisector:
        if (onBisector) {
            if (ipsLL.length!==1) {
                return [];
            }
            // distance from point to line1 (radius of circle around point, tangential to lines):
            var rp = line1.getDistanceTo(point.position, false);
            // distance from intersection line1/line2 to point:
            var dp = ipsLL[0].getDistanceTo(point.position);
            // distances from intersection line1/line2 to intersection of bisector line with circle around point, touching line1, line2:
            var dc1 = dp + rp;
            var dc2 = dp - rp;
            // factors to scale circle to reach results:
            var f1 = dp / dc1;
            var f2 = dp / dc2;
            // radius of solution
            var r1 = rp * f1;
            var r2 = rp * f2;

            for (k=0; k<bisectorLines.length; k++) {
                bisectorLine = bisectorLines[k];
                var a = bisectorLine.getAngle();
                centerCandidates.push(ipsLL[0].operator_add(RVector.createPolar(dp + r2, a)));
                centerCandidates.push(ipsLL[0].operator_add(RVector.createPolar(dp - r1, a)));
                centerCandidates.push(ipsLL[0].operator_add(RVector.createPolar(dp + r2, a + Math.PI)));
                centerCandidates.push(ipsLL[0].operator_add(RVector.createPolar(dp - r1, a + Math.PI)));
            }
        }

        // circle C tangential to two lines with center E, radius 10:
        else {
            circles = Apollonius.getCircles2TR(line1, line2, 10.0);
            if (isNull(circles) || circles.length===0) {
                return [];
            }

            for (i=0; i<circles.length; i++) {
                circle = circles[i];
                var e = circle.getCenter();

                // line L from intersection between the two lines to the point:
                // center of solution is on this line
                var line;
                if (ipsLL.length===0) {
                    // lines parallel:
                    line = line1.clone();
                    line.move(point.position.operator_subtract(line1.getStartPoint()));
                }
                else {
                    line = new RLine(ipsLL[0], point.position);
                }

                // intersections between line L and circle C -> G, H:
                var ipsLC = line.getIntersectionPoints(circle, false);
                if (ipsLC.length!==2) {
                    continue;
                }

                var g = ipsLC[0];
                var h = ipsLC[1];

                // two lines L1, L2 with same angle as EG, EH through point:
                var l1 = new RLine(e, g);
                var l2 = new RLine(e, h);
                l1.move(point.position.operator_subtract(l1.getStartPoint()));
                l2.move(point.position.operator_subtract(l2.getStartPoint()));

                // intersection of angle bisector and lines L1, L2 are centers of candidates:
                for (k=0; k<bisectorLines.length; k++) {
                    bisectorLine = bisectorLines[k];
                    centerCandidates = centerCandidates.concat(l1.getIntersectionPoints(bisectorLine, false));
                    centerCandidates = centerCandidates.concat(l2.getIntersectionPoints(bisectorLine, false));
                }
            }
        }

        for (c=0; c<centerCandidates.length; c++) {
            var centerCandidate = centerCandidates[c];
            var dLine1 = line1.getDistanceTo(centerCandidate, false);
            var dLine2 = line1.getDistanceTo(centerCandidate, false);
            var dPoint = point.getDistanceTo(centerCandidate, false);
            if (RMath.fuzzyCompare(dLine1, dPoint) && RMath.fuzzyCompare(dLine2, dPoint)) {
                centers.push(centerCandidate);
            }
        }
        centers = RVector.getUnique(centers);
    }

    var ret = [];
    for (c=0; c<centers.length; c++) {
        var r = centers[c].getDistanceTo(point.position);
        if (RMath.fuzzyCompare(r, 0.0)) {
            continue;
        }
        ret.push(new RCircle(centers[c], r));
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
    c21.radius = Math.abs(c21.radius - c1.radius);

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

    // point on the circle line (produces error):
    else if (circle.isOnShape(p)) {
        var s = new RLine(p, circle.center);
        var lines = [];
        lines[0] = new RLine(p, s.getAngle() + Math.PI/2, 1.0);
        lines[1] = undefined;
        return lines;
//        return [];
    }

    // point is inside the circle:
    else if (circle.contains(p)) {
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

    var line2Data;
    if (isFunction(line2.data)) {
        line2Data = line2.data();
    }
    else {
        line2Data = line2;
    }

    var points = line1.getIntersectionPoints(line2Data, false);
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

/**
 * \return Array of circles tangential to shape1 and shape2 with given radius.
 *
 * \param pos Only return circle closest to given pos or undefined to return all circles
 * \param candidates Empty array. Filled with all candidates or undefined if caller is not
 *   interested in all solution.
 * \param preview True for preview mode
 */
Apollonius.getCircles2TR = function(shape1, shape2, radius, pos, candidates, preview) {
    Apollonius.error = "";
    if (isNull(shape1) || isNull(shape2) || !isNumber(radius)) {
        return undefined;
    }

    if (isNull(preview)) {
        preview = false;
    }

    if (radius <= 0.0 || radius > 1.0e6) {
        if (!preview) {
            Apollonius.error = qsTr("Invalid radius");
        }
        return undefined;
    }

    var i,k,ips,s;

    if (isNull(candidates)) {
        candidates = [];
    }

    if (candidates.length===0) {
        var offset1 = ShapeAlgorithms.getOffsetShapes(shape1, radius, 1, RS.BothSides);
        var offset2 = ShapeAlgorithms.getOffsetShapes(shape2, radius, 1, RS.BothSides);

        if (isCircleShape(shape1) || isArcShape(shape1)) {
            if (radius>shape1.getRadius()) {
                s = shape1.clone();
                s.setRadius(radius - shape1.getRadius());
                offset1.push(s);
            }
        }
        if (isCircleShape(shape2) || isArcShape(shape2)) {
            if (radius>shape2.getRadius()) {
                s = shape2.clone();
                s.setRadius(radius - shape2.getRadius());
                offset2.push(s);
            }
        }

        var centerPoints = [];
        for (i=0; i<offset1.length; i++) {
            for (k=0; k<offset2.length; k++) {
                s = offset2[k];
                if (isFunction(s.data)) {
                    s = s.data();
                }
                ips = offset1[i].getIntersectionPoints(s, false);
                centerPoints = centerPoints.concat(ips);
            }
        }

        //var circle = undefined;
        for (i=0; i<centerPoints.length; i++) {
            var c = new RCircle(centerPoints[i], radius);
            candidates.push(c);
        }
    }

    if (candidates.length===0) {
        if (!preview) {
            Apollonius.error = qsTr("No solution");
        }
        return undefined;
    }

    // no position yet: return all candidates for preview:
    if (isNull(pos)) {
        return candidates;
    }

    return [ ShapeAlgorithms.getClosestShape(candidates, pos) ];
};

/**
 * Returns the homothetic centers of a pair of circle shapes.
 * \author CVH © 2024.
 *
 * \param c1        First RCircle shape.
 * \param c2        Second RCircle shape.
 *
 * \return An array with the external homothetic center and the internal homothetic center.
 *         Each can be invalid, at least an array with 2 invalid positions.
 */
Apollonius.getHomotheticCenters = function(c1, c2) {
    var ret = [undefined, undefined];    // Tri-state, nothing to start with, both an RVector when finished
    var center1, center2;    // Circle centers in 2D
    var radius1, radius2;    // Circle radii in absolute
    var sameR, sameC;        // Equality flags
    var zeroR1, zeroR2       // Zero radii flags
    var pos;                 // An RVector
    var axis, a;             // Central axis and angle
    var v1, v2;              // Offset vectors, orthogonal to axis
    var line;                // Line connecting the offsets of centers
    var ips;                 // Intersections (0-1) of axis and line

    // Reject incorrect shape types:
    if (!isCircleShape(c1) ||
        !isCircleShape(c2)) {

        return [RVector.invalid, RVector.invalid];    // Failed, incorrect data
    }

    /* # Remark by CVH #
    With some exceptions any pair of circles has 2 well defined homothetic centers

    Exceptions based on: https://en.wikipedia.org/wiki/Homothetic_center#Special_cases
    r1 == 0 && r2 != 0 -> ext = cc1 = int
    r1 != 0 && r2 == 0 -> ext = cc2 = int
    r1 == 0 && r2 == 0 -> ext = Null = int
    r1 == r2 && cc1 != cc2 -> ext = @Inf; int = halfway or Null when r1 == r2 == 0
    r1 == r2 && cc1 == cc2 -> ext = Null; int = cc1=cc2 or Null when r1 == r2 == 0
    r1 != r2 && cc1 != cc2 -> ext = Math; int = Math or both cc1 when r1 == 0 or both cc2 when r2 == 0
    r1 != r2 && cc1 == cc2 -> ext = cc1=cc2 = int or both cc1 when r1 == 0 or both cc2 when r2 == 0

    v1 & v2 are best seen as offsets upwards and/or downwards (Wiki figure 9)
    Both upwards for the external and only one downwards for the internal homothetic center
    Of interest can be that v1 is always considered to be upwards regarding the center of c1
    Rotating the vertical plane around the central axis we can do the math in XY using standard QCAD resources
    */

    // All in 2D, normalized, reject when invalid:
    center1 = c1.center.get2D();
    center2 = c2.center.get2D();
    radius1 = Math.abs(c1.radius);
    radius2 = Math.abs(c2.radius);
    if (!center1.isValid() || !center2.isValid() || !isNumber(radius1) || !isNumber(radius1)) {
        return [RVector.invalid, RVector.invalid];    // Failed, invalid data
    }

    // Define flags:
    sameC = center1.equalsFuzzy2D(center2);    // RS.PointTolerance
    sameR = RMath.fuzzyCompare(radius1, radius2);    // RS.PointTolerance
    zeroR1 = radius1 < RS.PointTolerance;
    zeroR2 = radius2 < RS.PointTolerance;

    // Force a zero radius if nearly zero:
    if (zeroR1) {
        radius1 = 0.0;
    }
    if (zeroR2) {
        radius2 = 0.0;
    }

    // Handle limit situations (Math won't solve most of these):
    if (sameR) {
        ret[0] = RVector.invalid;    // Infinite or None when cc1 == cc2
        if (zeroR1 && zeroR2) {
            ret[1] = RVector.invalid;    // None
        }
        else {
            ret[1] = RVector.getAverage(center1, center2);    // cc1 or cc2 or halfway
        }
    }
    else {
        if (zeroR1) {
            ret[0] = center1;    // Both cc1
            ret[1] = center1;
        }
        else if (zeroR2) {
            ret[0] = center2;    // Both cc2
            ret[1] = center2;
        }
        else if (sameC) {
            pos = RVector.getAverage(center1, center2);   // cc1 or cc2
            ret[0] = pos;
            ret[1] = pos;
        }
    }

    // Shared Math for when one is still undefined at this point:
    if (isNull(ret[0]) || isNull(ret[1])) {
        axis = new RLine(center1, center2);
        a = axis.getAngle() + Math.PI/2;
        v1 = new RVector();
        v1.setPolar(radius1, a);
        v2 = new RVector();
    }

    // When still undefined get the external homothetic center by an intersection:
    if (isNull(ret[0])) {
        v2.setPolar(radius2, a);
        line = new RLine(v1.operator_add(center1), v2.operator_add(center2));
        ips = axis.getIntersectionPoints(line, false);    // Unlimited
        if (ips.length === 1 && ips[0].isValid()) {
            ret[0] = ips[0];
        }
        else {
            ret[0] = RVector.invalid;
        }
    }

    // When still undefined get the internal homothetic center by an intersection:
    if (isNull(ret[1])) {
        v2.setPolar(radius2, a + Math.PI);
        line = new RLine(v1.operator_add(center1), v2.operator_add(center2));
        ips = axis.getIntersectionPoints(line, false);    // Unlimited
        if (ips.length === 1 && ips[0].isValid()) {
            ret[1] = ips[0];
        }
        else {
            ret[1] = RVector.invalid;
        }
    }

    // Return both homothetic centers:
    return ret;
};
