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
#include <cmath>
#include <typeinfo>

#include "RArc.h"
#include "RCircle.h"
#include "RDebug.h"
#include "REllipse.h"
#include "RLine.h"
#include "RMath.h"
#include "RPolyline.h"
#include "RRay.h"
#include "RShape.h"
#include "RSpline.h"
#include "RXLine.h"

double RShape::twopi = M_PI*2;
double RShape::epsTolerance = 1.0e-04;

/**
 * \return Shortest distance from this shape to the given point.
 *      Based on \ref getVectorTo.
 */
double RShape::getDistanceTo(const RVector& point, bool limited, double strictRange) const {
    RVector v = getVectorTo(point, limited, strictRange);
    if (v.isValid()) {
        return v.getMagnitude();
    }
    return RNANDOUBLE;
}

/**
 * \return true if the given point is on this shape.
 */
bool RShape::isOnShape(const RVector& point, bool limited, double tolerance) const {
//    potential performance gain or loss:
//    if (limited) {
//        // point is well outside bounding box of shape:
//        RBox bbox = getBoundingBox();
//        bbox.grow(tolerance);
//        if (!bbox.contains(point)) {
//            return false;
//        }
//    }

    double d = getDistanceTo(point, limited);
    if (RMath::isNaN(d)) {
        return false;
    }
    // much more tolerance here (e.g. for ellipses):
    return d < tolerance;
}

/**
 * \return List of those points in pointList which are on this shape.
 */
QList<RVector> RShape::filterOnShape(const QList<RVector>& pointList, bool limited, double tolerance) const {
    QList<RVector> ret;
    for (int i=0; i<pointList.length(); i++) {
        if (isOnShape(pointList[i], limited, tolerance)) {
            ret.append(pointList[i]);
        }
    }
    return ret;
}

/**
 * \return Shortest vector from any end point of this shape
 *      to the given point.
 */
RVector RShape::getVectorFromEndpointTo(const RVector& point) const {
    QList<RVector> endPoints = getEndPoints();
    RVector closest = point.getClosest(endPoints);
    return point - closest;
}

/**
 * \return Point on this shape that is closest to p. Based on getVectorTo.
 */
RVector RShape::getClosestPointOnShape(const RVector& p, bool limited, double strictRange) const {
    RVector dv = getVectorTo(p, limited, strictRange);
    if (!dv.isValid()) {
        return RVector::invalid;
    }
    return p - dv;
}

/**
 * \return Point at given percentile.
 */
RVector RShape::getPointAtPercent(double p) const {
    double length = getLength();
    double distance = p * length;
    QList<RVector> candidates = getPointsWithDistanceToEnd(distance, RS::FromStart);
    if (candidates.length()!=1) {
        return RVector::invalid;
    }
    return candidates.at(0);
}

/**
 * \return True if this shape intersects with the given shape.
 */
bool RShape::intersectsWith(const RShape& other, bool limited) const {
    return !getIntersectionPoints(other, limited).isEmpty();
}

/**
 * \return The intersection point(s) between this shape and the given
 *      other shape.
 */
QList<RVector> RShape::getIntersectionPoints(const RShape& other,
        bool limited, bool same, bool force) const {
    return getIntersectionPoints(*this, other, limited, same, force);
}


QList<RVector> RShape::getIntersectionPoints(const RShape& shape1,
        const RShape& shape2, bool limited, bool same, bool force) {

    QList<RVector> empty;

    bool gotInfiniteShape = false;
    if (typeid(shape1) == typeid(RXLine) ||
        typeid(shape2) == typeid(RXLine) ||
        typeid(shape1) == typeid(RRay) ||
        typeid(shape2) == typeid(RRay)) {

        gotInfiniteShape = true;
    }

    if (limited && !gotInfiniteShape) {
        // 20120425: allow for a bit of error, e.g. for vertical line that
        // is tangent to ellipse / circle:
        RBox bb1 = shape1.getBoundingBox().growXY(1e-2);
        RBox bb2 = shape2.getBoundingBox().growXY(1e-2);
        if (!bb1.intersects(bb2)) {
            return empty;
        }
    }

    // spline / spline intersections disabled for now (too slow)
    // for some operations where performance is not crucial, spline/spline
    // intersection calculation can be forced:
    if (!force) {
        const RSpline* spline1 = dynamic_cast<const RSpline*> (&shape1);
        if (spline1 != NULL) {
            const RSpline* spline2 = dynamic_cast<const RSpline*> (&shape2);
            if (spline2 != NULL) {
                return empty;
            }
        }
    }

    {
        const RLine* line1 = dynamic_cast<const RLine*> (&shape1);
        if (line1 != NULL) {
            if (same) {
                return empty;
            }
            const RLine* line2 = dynamic_cast<const RLine*> (&shape2);
            if (line2 != NULL) {
                return getIntersectionPointsLL(*line1, *line2, limited);
            }
            const RArc* arc2 = dynamic_cast<const RArc*> (&shape2);
            if (arc2 != NULL) {
                return getIntersectionPointsLA(*line1, *arc2, limited);
            }
            const RCircle* circle2 = dynamic_cast<const RCircle*> (&shape2);
            if (circle2 != NULL) {
                return getIntersectionPointsLC(*line1, *circle2, limited);
            }
            const REllipse* ellipse2 = dynamic_cast<const REllipse*> (&shape2);
            if (ellipse2 != NULL) {
                return getIntersectionPointsLE(*line1, *ellipse2, limited);
            }
            const RTriangle* triangle2 = dynamic_cast<const RTriangle*> (&shape2);
            if (triangle2 != NULL) {
                return getIntersectionPointsLT(*line1, *triangle2, limited);
            }
            const RSpline* spline2 = dynamic_cast<const RSpline*> (&shape2);
            if (spline2 != NULL) {
                return getIntersectionPointsLS(*line1, *spline2, limited);
            }
            const RRay* ray2 = dynamic_cast<const RRay*> (&shape2);
            if (ray2 != NULL) {
                QList<RVector> ret = getIntersectionPointsLL(*line1, ray2->getLineShape(), limited, false);
                if (limited) ret = ray2->filterOnShape(ret, true);
                return ret;
            }
            const RXLine* xline2 = dynamic_cast<const RXLine*> (&shape2);
            if (xline2 != NULL) {
                return getIntersectionPointsLL(*line1, xline2->getLineShape(), limited, false);
            }

            // spline, polyline, ...:
            const RExplodable* explodable2 = dynamic_cast<const RExplodable*> (&shape2);
            if (explodable2 != NULL) {
                return getIntersectionPointsLX(*line1, *explodable2, limited);
            }
        }
    }

    {
        const RRay* ray1 = dynamic_cast<const RRay*>(&shape1);
        if (ray1 != NULL) {
            if (same) {
                return empty;
            }
            RXLine xline1(ray1->getLineShape());
            QList<RVector> ret = getIntersectionPoints(xline1, shape2, limited, same, force);
            if (limited) ret = ray1->filterOnShape(ret, true);
            return ret;
        }
    }

    {
        const RXLine* xline1 = dynamic_cast<const RXLine*>(&shape1);
        if (xline1 != NULL) {
            if (same) {
                return empty;
            }
            RLine line1 = xline1->getLineShape();

            const RLine* line2 = dynamic_cast<const RLine*> (&shape2);
            if (line2 != NULL) {
                return getIntersectionPointsLL(line1, *line2, false, limited);
            }
            const RArc* arc2 = dynamic_cast<const RArc*> (&shape2);
            if (arc2 != NULL) {
                return getIntersectionPointsLA(line1, *arc2, false, limited);
            }
            const RCircle* circle2 = dynamic_cast<const RCircle*> (&shape2);
            if (circle2 != NULL) {
                return getIntersectionPointsLC(line1, *circle2, false);
            }
            const REllipse* ellipse2 = dynamic_cast<const REllipse*> (&shape2);
            if (ellipse2 != NULL) {
                return getIntersectionPointsLE(line1, *ellipse2, false, limited);
            }
            const RTriangle* triangle2 = dynamic_cast<const RTriangle*> (&shape2);
            if (triangle2 != NULL) {
                return getIntersectionPointsLT(line1, *triangle2, false, limited);
            }
            const RSpline* spline2 = dynamic_cast<const RSpline*> (&shape2);
            if (spline2 != NULL) {
                return getIntersectionPointsLS(line1, *spline2, false);
            }
            const RRay* ray2 = dynamic_cast<const RRay*> (&shape2);
            if (ray2 != NULL) {
                QList<RVector> ret = getIntersectionPointsLL(line1, ray2->getLineShape(), false);
                if (limited) ret = ray2->filterOnShape(ret, true);
                return ret;
            }
            const RXLine* xline2 = dynamic_cast<const RXLine*> (&shape2);
            if (xline2 != NULL) {
                return getIntersectionPointsLL(line1, xline2->getLineShape(), false);
            }

            // spline, polyline, ...:
            const RExplodable* explodable2 = dynamic_cast<const RExplodable*> (&shape2);
            if (explodable2 != NULL) {
                return getIntersectionPointsLX(line1, *explodable2, false);
            }
        }
    }

    {
        const RArc* arc1 = dynamic_cast<const RArc*> (&shape1);
        if (arc1 != NULL) {
            if (same) {
                return empty;
            }
            const RLine* line2 = dynamic_cast<const RLine*> (&shape2);
            if (line2 != NULL) {
                return getIntersectionPointsLA(*line2, *arc1, limited);
            }
            const RArc* arc2 = dynamic_cast<const RArc*> (&shape2);
            if (arc2 != NULL) {
                return getIntersectionPointsAA(*arc1, *arc2, limited);
            }
            const RCircle* circle2 = dynamic_cast<const RCircle*> (&shape2);
            if (circle2 != NULL) {
                return getIntersectionPointsAC(*arc1, *circle2, limited);
            }
            const REllipse* ellipse2 = dynamic_cast<const REllipse*> (&shape2);
            if (ellipse2 != NULL) {
                return getIntersectionPointsAE(*arc1, *ellipse2, limited);
            }
            const RTriangle* triangle2 = dynamic_cast<const RTriangle*> (&shape2);
            if (triangle2 != NULL) {
                return getIntersectionPointsAT(*arc1, *triangle2, limited);
            }
            const RSpline* spline2 = dynamic_cast<const RSpline*> (&shape2);
            if (spline2 != NULL) {
                return getIntersectionPointsAS(*arc1, *spline2, limited);
            }
            const RRay* ray2 = dynamic_cast<const RRay*> (&shape2);
            if (ray2 != NULL) {
                QList<RVector> ret = getIntersectionPointsLA(ray2->getLineShape(), *arc1, false, limited);
                if (limited) ret = ray2->filterOnShape(ret, true);
                return ret;
            }
            const RXLine* xline2 = dynamic_cast<const RXLine*> (&shape2);
            if (xline2 != NULL) {
                return getIntersectionPointsLA(xline2->getLineShape(), *arc1, false, limited);
            }

            // polyline, ...:
            const RExplodable* explodable2 = dynamic_cast<const RExplodable*> (&shape2);
            if (explodable2 != NULL) {
                return getIntersectionPointsAX(*arc1, *explodable2, limited);
            }
        }
    }

    {
        const RCircle* circle1 = dynamic_cast<const RCircle*> (&shape1);
        if (circle1 != NULL) {
            if (same) {
                return empty;
            }
            const RLine* line2 = dynamic_cast<const RLine*> (&shape2);
            if (line2 != NULL) {
                return getIntersectionPointsLC(*line2, *circle1, limited);
            }
            const RArc* arc2 = dynamic_cast<const RArc*> (&shape2);
            if (arc2 != NULL) {
                return getIntersectionPointsAC(*arc2, *circle1, limited);
            }
            const RCircle* circle2 = dynamic_cast<const RCircle*> (&shape2);
            if (circle2 != NULL) {
                return getIntersectionPointsCC(*circle1, *circle2);
            }
            const REllipse* ellipse2 = dynamic_cast<const REllipse*> (&shape2);
            if (ellipse2 != NULL) {
                return getIntersectionPointsCE(*circle1, *ellipse2);
            }
            const RSpline* spline2 = dynamic_cast<const RSpline*> (&shape2);
            if (spline2 != NULL) {
                return getIntersectionPointsCS(*circle1, *spline2);
            }
            const RRay* ray2 = dynamic_cast<const RRay*> (&shape2);
            if (ray2 != NULL) {
                QList<RVector> ret = getIntersectionPointsLC(ray2->getLineShape(), *circle1, false);
                if (limited) ret = ray2->filterOnShape(ret, true);
                return ret;
            }
            const RXLine* xline2 = dynamic_cast<const RXLine*> (&shape2);
            if (xline2 != NULL) {
                return getIntersectionPointsLC(xline2->getLineShape(), *circle1, false);
            }

            // spline, polyline, ...:
            const RExplodable* explodable2 = dynamic_cast<const RExplodable*> (&shape2);
            if (explodable2 != NULL) {
                return getIntersectionPointsCX(*circle1, *explodable2, limited);
            }
        }
    }

    {
        const REllipse* ellipse1 = dynamic_cast<const REllipse*> (&shape1);
        if (ellipse1 != NULL) {
            if (same) {
                return empty;
            }
            const RLine* line2 = dynamic_cast<const RLine*> (&shape2);
            if (line2 != NULL) {
                return getIntersectionPointsLE(*line2, *ellipse1, limited);
            }
            const RArc* arc2 = dynamic_cast<const RArc*> (&shape2);
            if (arc2 != NULL) {
                return getIntersectionPointsAE(*arc2, *ellipse1, limited);
            }
            const RCircle* circle2 = dynamic_cast<const RCircle*> (&shape2);
            if (circle2 != NULL) {
                return getIntersectionPointsCE(*circle2, *ellipse1);
            }
            const REllipse* ellipse2 = dynamic_cast<const REllipse*> (&shape2);
            if (ellipse2 != NULL) {
                return getIntersectionPointsEE(*ellipse2, *ellipse1, limited);
            }
            const RSpline* spline2 = dynamic_cast<const RSpline*> (&shape2);
            if (spline2 != NULL) {
                return getIntersectionPointsES(*ellipse1, *spline2, limited);
            }
            const RRay* ray2 = dynamic_cast<const RRay*> (&shape2);
            if (ray2 != NULL) {
                QList<RVector> ret = getIntersectionPointsLE(ray2->getLineShape(), *ellipse1, false, limited);
                if (limited) ret = ray2->filterOnShape(ret, true);
                return ret;
            }
            const RXLine* xline2 = dynamic_cast<const RXLine*> (&shape2);
            if (xline2 != NULL) {
                return getIntersectionPointsLE(xline2->getLineShape(), *ellipse1, false, limited);
            }

            // spline, polyline, ...:
            const RExplodable* explodable2 = dynamic_cast<const RExplodable*> (&shape2);
            if (explodable2 != NULL) {
                return getIntersectionPointsEX(*ellipse1, *explodable2, limited);
            }
        }
    }

    {
        const RTriangle* triangle1 = dynamic_cast<const RTriangle*> (&shape1);
        if (triangle1 != NULL) {
            if (same) {
                return empty;
            }
            const RLine* line2 = dynamic_cast<const RLine*> (&shape2);
            if (line2 != NULL) {
                return getIntersectionPointsLT(*line2, *triangle1, limited);
            }
            const RArc* arc2 = dynamic_cast<const RArc*> (&shape2);
            if (arc2 != NULL) {
                return getIntersectionPointsAT(*arc2, *triangle1, limited);
            }
            const RRay* ray2 = dynamic_cast<const RRay*> (&shape2);
            if (ray2 != NULL) {
                QList<RVector> ret = getIntersectionPointsLT(ray2->getLineShape(), *triangle1, false, limited);
                if (limited) ret = ray2->filterOnShape(ret, true);
                return ret;
            }
            const RXLine* xline2 = dynamic_cast<const RXLine*> (&shape2);
            if (xline2 != NULL) {
                return getIntersectionPointsLT(xline2->getLineShape(), *triangle1, false, limited);
            }
        }
    }

    {
        const RSpline* spline1 = dynamic_cast<const RSpline*> (&shape1);
        if (spline1 != NULL) {
            const RLine* line2 = dynamic_cast<const RLine*> (&shape2);
            if (line2 != NULL) {
                return getIntersectionPointsLS(*line2, *spline1, limited);
            }
            const RArc* arc2 = dynamic_cast<const RArc*> (&shape2);
            if (arc2 != NULL) {
                return getIntersectionPointsAS(*arc2, *spline1, limited);
            }
            const RCircle* circle2 = dynamic_cast<const RCircle*> (&shape2);
            if (circle2 != NULL) {
                return getIntersectionPointsCS(*circle2, *spline1, limited);
            }
            const REllipse* ellipse2 = dynamic_cast<const REllipse*> (&shape2);
            if (ellipse2 != NULL) {
                return getIntersectionPointsES(*ellipse2, *spline1, limited);
            }
            const RRay* ray2 = dynamic_cast<const RRay*> (&shape2);
            if (ray2 != NULL) {
                QList<RVector> ret = getIntersectionPointsLS(ray2->getLineShape(), *spline1, false);
                if (limited) ret = ray2->filterOnShape(ret, true);
                return ret;
            }
            const RXLine* xline2 = dynamic_cast<const RXLine*> (&shape2);
            if (xline2 != NULL) {
                return getIntersectionPointsLS(xline2->getLineShape(), *spline1, false);
            }
        }
    }

    {
        const RExplodable* explodable1 = RShape::castToExplodable(&shape1);
        if (explodable1 != NULL) {
            if (!same) {
                const RLine* line2 = dynamic_cast<const RLine*> (&shape2);
                if (line2 != NULL) {
                    return getIntersectionPointsLX(*line2, *explodable1, limited);
                }
                const RArc* arc2 = dynamic_cast<const RArc*> (&shape2);
                if (arc2 != NULL) {
                    return getIntersectionPointsAX(*arc2, *explodable1, limited);
                }
                const REllipse* ellipse2 = dynamic_cast<const REllipse*> (&shape2);
                if (ellipse2 != NULL) {
                    return getIntersectionPointsEX(*ellipse2, *explodable1, limited);
                }
                const RRay* ray2 = dynamic_cast<const RRay*> (&shape2);
                if (ray2 != NULL) {
                    QList<RVector> ret = getIntersectionPointsLX(ray2->getLineShape(), *explodable1, false);
                    if (limited) ret = ray2->filterOnShape(ret, true);
                    return ret;
                }
                const RXLine* xline2 = dynamic_cast<const RXLine*> (&shape2);
                if (xline2 != NULL) {
                    return getIntersectionPointsLX(xline2->getLineShape(), *explodable1, false);
                }
            }

            // spline, polyline, ...:
            const RExplodable* explodable2 = dynamic_cast<const RExplodable*> (&shape2);
            if (explodable2 != NULL) {
                return getIntersectionPointsXX(*explodable1, *explodable2, limited, same);
            }
        }
    }

    return QList<RVector>();
}

const RExplodable* RShape::castToExplodable(const RShape* shape) {
    const RPolyline* polyline = dynamic_cast<const RPolyline*>(shape);
    if (polyline!=NULL) {
        return dynamic_cast<const RExplodable*>(polyline);
    }

    const RSpline* spline = dynamic_cast<const RSpline*>(shape);
    if (spline!=NULL) {
        return dynamic_cast<const RExplodable*>(spline);
    }

    const RTriangle* triangle = dynamic_cast<const RTriangle*>(shape);
    if (triangle!=NULL) {
        return dynamic_cast<const RExplodable*>(triangle);
    }

    return NULL;
}

QList<RVector> RShape::getIntersectionPointsLL(const RLine& line1,
        const RLine& line2, bool limited1, bool limited2) {
    QList<RVector> res;
    double a1 = line1.endPoint.y - line1.startPoint.y;
    double b1 = line1.startPoint.x - line1.endPoint.x;
    double c1 = a1 * line1.startPoint.x + b1 * line1.startPoint.y;

    double a2 = line2.endPoint.y - line2.startPoint.y;
    double b2 = line2.startPoint.x - line2.endPoint.x;
    double c2 = a2 * line2.startPoint.x + b2 * line2.startPoint.y;

    double det = a1 * b2 - a2 * b1;
    if (fabs(det) < 1.0e-6) {
        return res;
    } else {
        RVector v((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det);

        if ((!limited1 || line1.isOnShape(v)) && (!limited2 || line2.isOnShape(v))) {
            res.append(v);
            return res;
        }
    }
    return res;
}

QList<RVector> RShape::getIntersectionPointsLA(const RLine& line1,
        const RArc& arc2, bool limited1, bool limited2) {

    QList<RVector> candidates =
            RShape::getIntersectionPointsLC(
                line1, RCircle(arc2.getCenter(), arc2.getRadius()), limited1
            );
    if (!limited2) {
        return candidates;
    }

    QList<RVector> res;

    for (int i=0; i<candidates.count(); i++) {
         if (arc2.isOnShape(candidates[i])) {
             res.append(candidates[i]);
         }
    }
    // ret.setTangent(tangent);

    return res;
}

QList<RVector> RShape::getIntersectionPointsLC(const RLine& line1,
        const RCircle& circle2, bool limited) {
    QList<RVector> res;

    RVector vLineCenter = line1.getVectorTo(circle2.getCenter(), false);
    double dist = vLineCenter.getMagnitude();

    // special case: arc touches line (tangent):
    if (fabs(dist - circle2.getRadius()) < 1.0e-4) {
        res.append(circle2.getCenter() - vLineCenter);
        // ret.setTangent(true);
        return res;
    }

    RVector p = line1.getStartPoint();
    RVector d = line1.getEndPoint() - line1.getStartPoint();
    if (d.getMagnitude() < 1.0e-6) {
        return res;
    }

    RVector delta = p - circle2.getCenter();

    // root term:
    double term = RMath::pow(RVector::getDotProduct(d, delta), 2.0)
                  - RMath::pow(d.getMagnitude(), 2.0)
                  * (RMath::pow(delta.getMagnitude(), 2.0) - RMath::pow(circle2.getRadius(), 2.0));

    // no intersection:
    if (term<0.0) {
        return res;
    }

    // one or two intersections:
    double t1 = (- RVector::getDotProduct(d, delta) + sqrt(term))
                / RMath::pow(d.getMagnitude(), 2.0);
    double t2;
    bool tangent = false;

    // only one intersection:
    if (fabs(term) < RS::PointTolerance) {
        t2 = t1;
        tangent = true;
    }

    // two intersections
    else {
        t2 = (-RVector::getDotProduct(d, delta) - sqrt(term))
             / RMath::pow(d.getMagnitude(), 2.0);
    }

    RVector sol1;
    RVector sol2 = RVector::invalid;

    sol1 = p + d * t1;

    if (!tangent) {
        sol2 = p + d * t2;
    }

    if (!limited || line1.isOnShape(sol1)) {
        res.append(sol1);
    }
    if (sol2.isValid()) {
        if (!limited || line1.isOnShape(sol2)) {
            res.append(sol2);
        }
    }
    // ret.setTangent(tangent);

    return res;
}

QList<RVector> RShape::getIntersectionPointsLE(const RLine& line1,
        const REllipse& ellipse2, bool limited1, bool limited2) {

    QList<RVector> res;

    // find out if line1 is (almost) a tangent:
    QList<RLine> tangents = ellipse2.getTangents(line1.getMiddlePoint());
    for (int i=0; i<tangents.length(); i++) {
        double a = tangents[i].getAngle();
        double ad1 = fabs(RMath::getAngleDifference180(a, line1.getDirection1()));
        double ad2 = fabs(RMath::getAngleDifference180(a, line1.getDirection2()));

        if (ad1 < 1.0e-2 || ad2 < 1.0e-2) {
            res.append(tangents[i].getEndPoint());

            // no need to continue: max. one tangent possible:
            return res;
        }
    }

    // rotate into normal position:
    double ang = ellipse2.getAngle();

    double rx = ellipse2.getMajorRadius();
    double ry = ellipse2.getMinorRadius();
    RVector center = ellipse2.getCenter();
    RVector a1 = line1.getStartPoint();
    a1.rotate(-ang, center);
    RVector a2 = line1.getEndPoint();
    a2.rotate(-ang, center);
    RVector origin = a1;
    RVector dir = a2-a1;
    RVector diff = origin - center;
    RVector mDir = RVector(dir.x/(rx*rx), dir.y/(ry*ry));
    RVector mDiff = RVector(diff.x/(rx*rx), diff.y/(ry*ry));

    double a = RVector::getDotProduct(dir, mDir);
    double b = RVector::getDotProduct(dir, mDiff);
    double c = RVector::getDotProduct(diff, mDiff) - 1.0;
    double d = b*b - a*c;

    RVector res1 = RVector::invalid;
    RVector res2 = RVector::invalid;

    if (d < 0) {
        // no solution
    } else if ( d > 0 ) {
        double root = sqrt(d);
        double t_a = (-b - root) / a;
        double t_b = (-b + root) / a;

        res1 = a1.getLerp(a2, t_a).rotate(ang, center);
        res2 = a1.getLerp(a2, t_b).rotate(ang, center);
    } else {
        double t = -b/a;
        if ( 0 <= t && t <= 1 ) {
            // one solution:
            res1 = a1.getLerp(a2, t).rotate(ang, center);
        } else {
            // no solution
        }
    }

    if (res1.isValid()) {
        if ((!limited1 || line1.isOnShape(res1)) && (!limited2 || ellipse2.isOnShape(res1))) {
            res.append(res1);
        }
    }
    if (res2.isValid()) {
        if ((!limited1 || line1.isOnShape(res2)) && (!limited2 || ellipse2.isOnShape(res2))) {
            res.append(res2);
        }
    }

    return res;
}

QList<RVector> RShape::getIntersectionPointsLT(const RLine& line1,
        const RTriangle& triangle2, bool limited1, bool limited2) {

    QList<RVector> res;

    RVector normal = triangle2.getNormal();

    if (normal.getMagnitude() < 1.0e-12) {
        return res;
    }

    if (line1.getLength() < 1.0e-12) {
        return res;
    }

    double t = RVector::getDotProduct(normal, triangle2.getCorner(2) - line1.getStartPoint())
            / RVector::getDotProduct(normal, (line1.getEndPoint() - line1.getStartPoint()));

    // check if intersection point is on the line:
    if (limited1 && (t < 0.0 || t > 1.0)) {
        // not on line:
        return res;
    }

    // intersection point:
    RVector ip = line1.getStartPoint() + (line1.getEndPoint() - line1.getStartPoint()) * t;

    // check if intersection point is inside the triangle:
    if (!limited2 || triangle2.isPointInTriangle(ip)) {
        res.push_back(ip);
    }

    return res;
}

QList<RVector> RShape::getIntersectionPointsLS(const RLine& line1,
            const RSpline& spline2, bool limited) {
//    qDebug() << "RShape::getIntersectionPointsLS";

//    QList<RVector> res;
//    if (spline2.getIntersectionPointsProxy(res, line1, limited, false)) {
//        qDebug() << "RShape::getIntersectionPointsLS: from proxy";
//        return res;
//    }

    return getIntersectionPointsLX(line1, spline2, limited);
}

QList<RVector> RShape::getIntersectionPointsLX(const RLine& line1,
        const RExplodable& explodable2, bool limited) {
    Q_UNUSED(limited)

    QList<RVector> res;

    QList<QSharedPointer<RShape> > sub = explodable2.getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        // TODO: limited true for line1, not for line2:
        QSharedPointer<RLine> pLine2 = (*it).dynamicCast<RLine>();
        if (!pLine2.isNull()) {
            RLine line2 = *pLine2.data();
            res.append(RShape::getIntersectionPointsLL(line1, line2, limited, true));
            continue;
        }

        QSharedPointer<RArc> pArc2 = (*it).dynamicCast<RArc>();
        if (!pArc2.isNull()) {
            RArc arc2 = *pArc2.data();
            res.append(RShape::getIntersectionPointsLA(line1, arc2, limited, true));
            continue;
        }
    }

    return res;
}

QList<RVector> RShape::getIntersectionPointsAA(const RArc& arc1,
        const RArc& arc2, bool limited) {

    QList<RVector> candidates =
            RShape::getIntersectionPoints(
                RCircle(arc1.getCenter(), arc1.getRadius()),
                RCircle(arc2.getCenter(), arc2.getRadius())
            );
    if (!limited) {
        return candidates;
    }

    QList<RVector> res;

    for (int i=0; i<candidates.count(); i++) {
         if (arc1.isOnShape(candidates[i]) && arc2.isOnShape(candidates[i])) {
             res.append(candidates[i]);
         }
    }
    // ret.setTangent(tangent);

    return res;
}

QList<RVector> RShape::getIntersectionPointsAC(const RArc& arc1,
        const RCircle& circle2, bool limited) {
    QList<RVector> candidates =
            RShape::getIntersectionPoints(
                RCircle(arc1.getCenter(), arc1.getRadius()),
                circle2
            );
    if (!limited) {
        return candidates;
    }

    QList<RVector> res;

    for (int i=0; i<candidates.count(); i++) {
         if (arc1.isOnShape(candidates[i])) {
             res.append(candidates[i]);
         }
    }
    // ret.setTangent(tangent);

    return res;
}

QList<RVector> RShape::getIntersectionPointsAE(const RArc& arc1,
        const REllipse& ellipse2, bool limited) {
    QList<RVector> candidates =
            RShape::getIntersectionPointsCE(
                RCircle(arc1.getCenter(), arc1.getRadius()),
                ellipse2);

    if (!limited) {
        return candidates;
    }

    QList<RVector> res;

    for (int i=0; i<candidates.count(); i++) {
        RVector c = candidates[i];
        if (arc1.isOnShape(c)) {
            if (!ellipse2.isFullEllipse()) {
                double a1 = ellipse2.getCenter().getAngleTo(ellipse2.getStartPoint());
                double a2 = ellipse2.getCenter().getAngleTo(ellipse2.getEndPoint());
                double a = ellipse2.getCenter().getAngleTo(c);
                if (!RMath::isAngleBetween(a, a1, a2, ellipse2.isReversed())) {
                    continue;
                }
            }

            res.append(c);
        }
    }

    return res;
}

QList<RVector> RShape::getIntersectionPointsAT(const RArc& arc1,
            const RTriangle& triangle2, bool limited) {

    Q_UNUSED(limited)

    RTriangle plane(arc1.getCenter(), arc1.getStartPoint(), arc1.getEndPoint());
    QList<RVector> r = plane.getIntersectionPoints(RLine(triangle2.getCorner(0), triangle2.getCorner(1)));
    r.append(plane.getIntersectionPoints(RLine(triangle2.getCorner(1), triangle2.getCorner(2))));
    r.append(plane.getIntersectionPoints(RLine(triangle2.getCorner(2), triangle2.getCorner(0))));
    if (r.size()<2) {
        return QList<RVector>();
    }

    RLine l(r[0], r[1]);
    return l.getIntersectionPoints(arc1);
}

QList<RVector> RShape::getIntersectionPointsAS(const RArc& arc1,
            const RSpline& spline2, bool limited) {

//    QList<RVector> res;
//    if (spline2.getIntersectionPointsProxy(res, arc1, limited, false)) {
//        return res;
//    }

    return getIntersectionPointsAX(arc1, spline2, limited);
}

QList<RVector> RShape::getIntersectionPointsAX(const RArc& arc1,
        const RExplodable& explodable2, bool limited) {
    Q_UNUSED(limited)
    QList<RVector> res;

    QList<QSharedPointer<RShape> > sub = explodable2.getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        QSharedPointer<RLine> pLine2 = (*it).dynamicCast<RLine>();
        if (!pLine2.isNull()) {
            RLine line2 = *pLine2.data();
            res.append(RShape::getIntersectionPointsLA(line2, arc1));
            continue;
        }

        QSharedPointer<RArc> pArc2 = (*it).dynamicCast<RArc>();
        if (!pArc2.isNull()) {
            RArc arc2 = *pArc2.data();
            res.append(RShape::getIntersectionPointsAA(arc1, arc2));
            continue;
        }
    }

    return res;
}

QList<RVector> RShape::getIntersectionPointsCC(const RCircle& circle1,
        const RCircle& circle2) {

    QList<RVector> res;
    bool tangent = false;

    RVector c1 = circle1.getCenter();
    RVector c2 = circle2.getCenter();

    double r1 = circle1.getRadius();
    double r2 = circle2.getRadius();

    RVector u = c2 - c1;

    // the two circles (almost) touch in one point (tangent):
    if (RMath::fuzzyCompare(u.getMagnitude(), r1+r2, 1.0e-6)) {
        u.setMagnitude2d(r1);
        res.append(c1 + u);
        tangent = true;
        return res;
    }

    // concentric
    if (u.getMagnitude() < RS::PointTolerance) {
        return res;
    }

    RVector v = RVector(u.y, -u.x);

    double s, t1, t2, term;

    s = 1.0/2.0 * ((r1*r1 - r2*r2)/(RMath::pow(u.getMagnitude(), 2.0)) + 1.0);

    term = (r1*r1)/(RMath::pow(u.getMagnitude(), 2.0)) - s*s;

    // no intersection:
    if (term < 0.0) {
        return res;
    }

    // one or two intersections:
    t1 = sqrt(term);
    t2 = -sqrt(term);

    RVector sol1 = c1 + u*s + v*t1;
    RVector sol2 = c1 + u*s + v*t2;

    if (sol1.equalsFuzzy(sol2, 1.0e-4)) {
        res.append(sol1);
        tangent = true;
    }
    else {
        res.append(sol1);
        res.append(sol2);
    }

    return res;
}

QList<RVector> RShape::getIntersectionPointsCE(const RCircle& circle1,
        const REllipse& ellipse2) {
    REllipse ellipse1(
        circle1.getCenter(),
        RVector(circle1.getRadius(),0.),
        1.0,
        0.0,
        2.0*M_PI,
        false);

    return getIntersectionPointsEE(ellipse1,ellipse2);
}

QList<RVector> RShape::getIntersectionPointsCS(const RCircle& circle1,
            const RSpline& spline2, bool limited) {

//    QList<RVector> res;
//    if (spline2.getIntersectionPointsProxy(res, circle1, limited, false)) {
//        return res;
//    }

    return getIntersectionPointsCX(circle1, spline2, limited);
}

QList<RVector> RShape::getIntersectionPointsCX(const RCircle& circle1,
        const RExplodable& explodable2, bool limited) {
    Q_UNUSED(limited)
    QList<RVector> res;

    QList<QSharedPointer<RShape> > sub = explodable2.getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        QSharedPointer<RLine> pLine2 = (*it).dynamicCast<RLine>();
        if (!pLine2.isNull()) {
            RLine line2 = *pLine2.data();
            res.append(RShape::getIntersectionPointsLC(line2, circle1));
            continue;
        }

        QSharedPointer<RArc> pArc2 = (*it).dynamicCast<RArc>();
        if (!pArc2.isNull()) {
            RArc arc2 = *pArc2.data();
            res.append(RShape::getIntersectionPointsAC(arc2, circle1));
            continue;
        }
    }

    return res;
}

QList<RVector> RShape::getIntersectionPointsEE(const REllipse& ellipse1, const REllipse& ellipse2, bool limited) {
    QList<RVector> candidates = getIntersectionPointsEE(ellipse1, ellipse2);

    if (!limited) {
        return candidates;
    }

    QList<RVector> ret;

    for (int i=0; i<candidates.length(); i++) {
        RVector c = candidates[i];
        bool onShape = true;

        double a1 = ellipse1.getCenter().getAngleTo(ellipse1.getStartPoint());
        double a2 = ellipse1.getCenter().getAngleTo(ellipse1.getEndPoint());
        double a = ellipse1.getCenter().getAngleTo(c);
        if (!RMath::isAngleBetween(a, a1, a2, ellipse1.isReversed())) {
//            qDebug() << "1) angle NOT between: "
//                << " a: " << RMath::rad2deg(a)
//                << " a1: " << RMath::rad2deg(a1)
//                << " a2: " << RMath::rad2deg(a2)
//                << " r: " << ellipse1.isReversed();
            //ret.append(c);
            onShape = false;
        }

        a1 = ellipse2.getCenter().getAngleTo(ellipse2.getStartPoint());
        a2 = ellipse2.getCenter().getAngleTo(ellipse2.getEndPoint());
        a = ellipse2.getCenter().getAngleTo(c);
        if (!RMath::isAngleBetween(a, a1, a2, ellipse2.isReversed())) {
//            qDebug() << "2) angle NOT between: "
//                << " a: " << RMath::rad2deg(a)
//                << " a1: " << RMath::rad2deg(a1)
//                << " a2: " << RMath::rad2deg(a2)
//                << " r: " << ellipse2.isReversed();
            //ret.append(c);
            onShape = false;
        }

        if (onShape) {
            ret.append(c);
        }
    }

    return ret;
}

/**
 * Based on "Hughes and Chraibi (2011-2012), Calculating Ellipse Overlap Areas"
 */
QList<RVector> RShape::getIntersectionPointsEE(const REllipse& ellipse1, const REllipse& ellipse2) {
    QList<RVector> ret;

    // two full ellipses:
    // if bounding boxes don't intersect, ellipses don't either:
    if (ellipse1.isFullEllipse() && ellipse2.isFullEllipse() &&
        !ellipse1.getBoundingBox().intersects(ellipse2.getBoundingBox())) {

        return ret;
    }

    // normalize ellipse ratios:
    REllipse ellipse1Copy = ellipse1;
    if (ellipse1Copy.getMajorRadius() < ellipse1Copy.getMinorRadius()) {
        ellipse1Copy.switchMajorMinor();
    }
    REllipse ellipse2Copy = ellipse2;
    if (ellipse2Copy.getMajorRadius() < ellipse2Copy.getMinorRadius()) {
        ellipse2Copy.switchMajorMinor();
    }

    // for later comparison, make sure that major points are in
    // quadrant I or II (relative to the ellipse center):
    if (fabs(ellipse1Copy.getMajorPoint().y)<RS::PointTolerance) {
        if (ellipse1Copy.getMajorPoint().x<0.0) {
            ellipse1Copy.setMajorPoint(-ellipse1Copy.getMajorPoint());
        }
    }
    else {
        if (ellipse1Copy.getMajorPoint().y<0.0) {
            ellipse1Copy.setMajorPoint(-ellipse1Copy.getMajorPoint());
        }
    }
    if (fabs(ellipse2Copy.getMajorPoint().y)<RS::PointTolerance) {
        if (ellipse2Copy.getMajorPoint().x<0.0) {
            ellipse2Copy.setMajorPoint(-ellipse2Copy.getMajorPoint());
        }
    }
    else {
        if (ellipse2Copy.getMajorPoint().y<0.0) {
            ellipse2Copy.setMajorPoint(-ellipse2Copy.getMajorPoint());
        }
    }

    // for comparison:
    bool identicalCenter =
        (ellipse1Copy.getCenter() - ellipse2Copy.getCenter()).getMagnitude() < RS::PointTolerance;
//    bool identicalShape =
//        (ellipse1Copy.getMajorPoint() - ellipse2Copy.getMajorPoint()).getMagnitude() < RS::PointTolerance &&
//        fabs(ellipse1Copy.getMajorRadius() - ellipse2Copy.getMajorRadius()) < RS::PointTolerance &&
//        fabs(ellipse1Copy.getMinorRadius() - ellipse2Copy.getMinorRadius()) < RS::PointTolerance;
    bool identicalRatio = fabs(ellipse1Copy.getRatio() - ellipse2Copy.getRatio()) < 1.0e-4;
    double angleDifference = fabs(RMath::getAngleDifference180(ellipse1Copy.getAngle(), ellipse2Copy.getAngle()));
    bool identicalRotation = angleDifference < 1.0e-4 || angleDifference>M_PI-1.0e-4;

    //qDebug() << "identicalCenter" << identicalCenter;
    //qDebug() << "identicalShape" << identicalShape;

    // ellipses are identical (no intersection points):
//    if (identicalCenter && identicalShape) {
    if (identicalCenter && identicalRatio && identicalRotation) {
        //qDebug() << "RShape::getIntersectionPointsEE: identical";
        return ret;
    }

    // special case: ellipse shapes are identical (different positions):
    //if (identicalShape) {
    if (identicalRatio && identicalRotation) {
        //qDebug() << "identical ratio and rotation";

        double angle = -ellipse1Copy.getAngle();
        double yScale = 1.0 / ellipse1Copy.getRatio();

        RVector circleCenter1 = ellipse1Copy.getCenter();
        circleCenter1.rotate(angle);
        circleCenter1.scale(RVector(1.0, yScale));
        RVector circleCenter2 = ellipse2Copy.getCenter();
        circleCenter2.rotate(angle);
        circleCenter2.scale(RVector(1.0, yScale));

        RCircle circle1(circleCenter1, ellipse1Copy.getMajorRadius());
        RCircle circle2(circleCenter2, ellipse2Copy.getMajorRadius());

        ret = getIntersectionPointsCC(circle1, circle2);

        RVector::scaleList(ret, RVector(1.0, 1.0/yScale));
        RVector::rotateList(ret, -angle);

        return ret;
    }

    // transform ellipse2 to coordinate system of ellipse1:
    RVector centerOffset = -ellipse1Copy.getCenter();
    double angleOffset = -ellipse1Copy.getAngle();

    double majorRadius1 = ellipse1Copy.getMajorRadius();
    double majorRadius2 = ellipse2Copy.getMajorRadius();

    // special case: treat first ellipse as a line:
    if (ellipse1Copy.getMinorRadius() < RS::PointTolerance ||
        ellipse1Copy.getRatio() < RS::PointTolerance) {

        ellipse2Copy.move(centerOffset);
        ellipse2Copy.rotate(angleOffset);

        RLine line(RVector(-majorRadius1,0.0),RVector(majorRadius1,0.0));
        ret = getIntersectionPointsLE(line, ellipse2Copy);
        RVector::rotateList(ret, -angleOffset);
        RVector::moveList(ret, -centerOffset);

//        qDebug() << "RShape::getIntersectionPointsEE: ellipse 1 as line";
        return ret;
    }

    // special case: treat second ellipse as a line:
    if (ellipse2Copy.getMinorRadius() < RS::PointTolerance ||
        ellipse2Copy.getRatio()< RS::PointTolerance) {

        ellipse2Copy.move(centerOffset);
        ellipse2Copy.rotate(angleOffset);

        RLine line(RVector(-majorRadius2,0.),RVector(majorRadius2,0.));
        line.rotate(ellipse2Copy.getAngle(), RVector(0.,0.));
        line.move(ellipse2Copy.getCenter());
        ret = getIntersectionPointsLE(line, ellipse1Copy);
        RVector::rotateList(ret, -angleOffset);
        RVector::moveList(ret, -centerOffset);

//        qDebug() << "RShape::getIntersectionPointsEE: ellipse 2 as line";
        return ret;
    }

//    qDebug() << "e1" << ellipse1Copy;
//    qDebug() << "e2" << ellipse2Copy;

    double phi_1 = ellipse1Copy.getAngle();
    double a1 = ellipse1Copy.getMajorRadius();
    double b1 = ellipse1Copy.getMinorRadius();
    double h1 = ellipse1Copy.getCenter().x;
    double k1 = ellipse1Copy.getCenter().y;

    double phi_2 = ellipse2Copy.getAngle();
    double a2 = ellipse2Copy.getMajorRadius();
    double b2 = ellipse2Copy.getMinorRadius();
    double h2 = ellipse2Copy.getCenter().x;
    double k2 = ellipse2Copy.getCenter().y;

    int i, j, k, nroots, nychk, nintpts;
    double AA, BB, CC, DD, EE, FF, H2_TR, K2_TR, A22, B22, PHI_2R;
    double cosphi, cosphi2, sinphi, sinphi2, cosphisinphi;
    double tmp0, tmp1, tmp2, tmp3;
    double cy[5] = {0.0};
    double py[5] = {0.0};
    double r[3][5] = { {0.0} };
    double x1, x2;
    double ychk[5] = {0.0};
    double xint[5];
    double yint[5];

    // each of the ellipse axis lengths must be positive
    if ( (!(a1 > 0.0) || !(b1 > 0.0)) || (!(a2 > 0.0) || !(b2 > 0.0)) ) {
        //(*rtnCode) = ERROR_ELLIPSE_PARAMETERS;
        //qDebug() << "negative axis length";
        return QList<RVector>();
    }

    // the rotation angles should be between -2pi and 2pi (?)
    if (fabs(phi_1) > twopi) {
        phi_1 = fmod(phi_1, twopi);
    }
    if (fabs(phi_2) > twopi) {
        phi_2 = fmod(phi_2, twopi);
    }

    //qDebug() << "phi_1: " << phi_1;
    //qDebug() << "phi_2: " << phi_2;

    // determine the two ellipse equations from input parameters:

    // Finding the points of intersection between two general ellipses
    // requires solving a quartic equation. Before attempting to solve the
    // quartic, several quick tests can be used to eliminate some cases
    // where the ellipses do not intersect. Optionally, can whittle away
    // at the problem, by addressing the easiest cases first.

    // Working with the translated+rotated ellipses simplifies the
    // calculations. The ellipses are translated then rotated so that the
    // first ellipse is centered at the origin and oriented with the
    // coordinate axes. Then, the first ellipse will have the implicit
    // (polynomial) form of
    // x^2/A1^2 + y+2/B1^2 = 1

    // For the second ellipse, the center is first translated by the amount
    // required to put the first ellipse at the origin, e.g., by (-H1, -K1)
    // Then, the center of the second ellipse is rotated by the amount
    // required to orient the first ellipse with the coordinate axes, e.g.,
    // through the angle -PHI_1.
    // The translated and rotated center point coordinates for the second
    // ellipse are found with the rotation matrix, derivations are
    // described in the reference.
    cosphi = cos(phi_1);
    sinphi = sin(phi_1);
    H2_TR = (h2 - h1)*cosphi + (k2 - k1)*sinphi;
    K2_TR = (h1 - h2)*sinphi + (k2 - k1)*cosphi;
    PHI_2R = phi_2 - phi_1;
    if (fabs(PHI_2R) > twopi) {
        PHI_2R = fmod(PHI_2R, twopi);
    }

    //qDebug() << "PHI_2R: " << PHI_2R;

    // Calculate implicit (Polynomial) coefficients for the second ellipse
    // in its translated-by (-H1, -H2) and rotated-by -PHI_1 postion
    // AA*x^2 + BB*x*y + CC*y^2 + DD*x + EE*y + FF = 0
    // Formulas derived in the reference
    // To speed things up, store multiply-used expressions first
    cosphi = cos(PHI_2R);
    cosphi2 = cosphi*cosphi;
    sinphi = sin(PHI_2R);
    sinphi2 = sinphi*sinphi;
    cosphisinphi = 2.0*cosphi*sinphi;
    A22 = a2*a2;
    B22 = b2*b2;
    tmp0 = (cosphi*H2_TR + sinphi*K2_TR)/A22;
    tmp1 = (sinphi*H2_TR - cosphi*K2_TR)/B22;
    tmp2 = cosphi*H2_TR + sinphi*K2_TR;
    tmp3 = sinphi*H2_TR - cosphi*K2_TR;

    // implicit polynomial coefficients for the second ellipse
    AA = cosphi2/A22 + sinphi2/B22;
    BB = cosphisinphi/A22 - cosphisinphi/B22;
    CC = sinphi2/A22 + cosphi2/B22;
    DD = -2.0*cosphi*tmp0 - 2.0*sinphi*tmp1;
    EE = -2.0*sinphi*tmp0 + 2.0*cosphi*tmp1;
    FF = tmp2*tmp2/A22 + tmp3*tmp3/B22 - 1.0;

//    qDebug() << "second ellipse:";
//    qDebug() << "AA: " << AA;
//    qDebug() << "BB: " << BB;
//    qDebug() << "CC: " << CC;
//    qDebug() << "DD: " << DD;
//    qDebug() << "EE: " << EE;
//    qDebug() << "FF: " << FF;

//    if (BB==0.0) {
//        BB = 1.0e-12;
//    }

    // create and solve the quartic equation to find intersection points:

    // If execution arrives here, the ellipses are at least 'close' to
    // intersecting.
    // Coefficients for the Quartic Polynomial in y are calculated from
    // the two implicit equations.
    // Formulas for these coefficients are derived in the reference.

    cy[4] = pow(a1, 4.0)*AA*AA + b1*b1*(a1*a1*(BB*BB - 2.0*AA*CC) + b1*b1*CC*CC);
    cy[3] = 2.0*b1*(b1*b1*CC*EE + a1*a1*(BB*DD - AA*EE));
    cy[2] = a1*a1*((b1*b1*(2.0*AA*CC - BB*BB) + DD*DD - 2.0*AA*FF) - 2.0*a1*a1*AA*AA) + b1*b1*(2.0*CC*FF + EE*EE);
    cy[1] = 2.0*b1*(a1*a1*(AA*EE - BB*DD) + EE*FF);
    cy[0] = (a1*(a1*AA - DD) + FF)*(a1*(a1*AA + DD) + FF);

//    for (i = 0; i < 5; i++) {
//        qDebug() << "cy[" << i << "]: " << cy[i];
//    }

    // Once the coefficients for the Quartic Equation in y are known, the
    // roots of the quartic polynomial will represent y-values of the
    // intersection points of the two ellipse curves.
    // The quartic sometimes degenerates into a polynomial of lesser
    // degree, so handle all possible cases.
    if (fabs (cy[4]) > 0.0) {
        //qDebug() << "quartic";
        // quartic coefficient nonzero, use quartic formula:
        for (i = 0; i <= 3; i++) {
            py[4-i] = cy[i]/cy[4];
        }
        py[0] = 1.0;
//        for (i = 0; i < 5; i++) {
//            qDebug() << "py[" << i << "]: " << py[i];
//        }
        RMath::getBiQuadRoots(py, r);
        nroots = 4;
    }
    else if (fabs (cy[3]) > 0.0) {
        //qDebug() << "cubic";
        // quartic degenerates to cubic, use cubic formula:
        for (i = 0; i <= 2; i++) {
            py[3-i] = cy[i]/cy[3];
        }
        py[0] = 1.0;
        RMath::getCubicRoots(py, r);
        nroots = 3;
    }
    else if (fabs (cy[2]) > 0.0) {
        //qDebug() << "quadratic";
        // quartic degenerates to quadratic, use quadratic formula:
        for (i = 0; i <= 1; i++) {
            py[2-i] = cy[i]/cy[2];
        }
        py[0] = 1.0;
        RMath::getQuadRoots(py, r);
        nroots = 2;

    }
    else if (fabs (cy[1]) > 0.0) {
        //qDebug() << "linear";
        // quartic degenerates to linear: solve directly:
        // cy[1]*Y + cy[0] = 0
        r[1][1] = (-cy[0]/cy[1]);
        r[2][1] = 0.0;
        nroots = 1;
    }
    else {
        //qDebug() << "degenerate";
        // completely degenerate quartic: ellipses identical?
        // a completely degenerate quartic, which would seem to
        // indicate that the ellipses are identical. However, some
        // configurations lead to a degenerate quartic with no
        // points of intersection.
        nroots = 0;
    }

    //qDebug() << "nroots: " << nroots;

    // check roots of the quartic: are they points of intersection?
    // determine which roots are real, discard any complex roots
    nychk = 0;
    for (i = 1; i <= nroots; i++) {
        if (fabs (r[2][i]) < epsTolerance) {
            nychk++;
            ychk[nychk] = r[1][i]*b1;
            //qDebug() << "real root: ychk[nychk]: " << ychk[nychk];
        }
    }

    // sort the real roots by straight insertion
    for (j = 2; j <= nychk; j++) {
        tmp0 = ychk[j];
        for (k = j - 1; k >= 1; k--) {
            if (ychk[k] <= tmp0) {
                break;
            }
            ychk[k+1] = ychk[k];
        }
        ychk[k+1] = tmp0;
    }

    // determine whether polynomial roots are points of intersection
    // for the two ellipses
    nintpts = 0;
    for (i = 1; i <= nychk; i++) {
        //qDebug() << "ychk[i]: " << ychk[i];

        // check for multiple roots
        if ((i > 1) && (fabs(ychk[i] - ychk[i-1]) < (epsTolerance/2.0))) {
            continue;
        }
        // check intersection points for ychk[i]
        if (fabs(ychk[i]) > b1) {
            x1 = 0.0;
        }
        else {
            x1 = a1*sqrt (1.0 - (ychk[i]*ychk[i])/(b1*b1));
        }
        x2 = -x1;
//        qDebug() << "fabs(ellipse2tr(x1, ychk[i], AA, BB, CC, DD, EE, FF)): " << fabs(ellipse2tr(x1, ychk[i], AA, BB, CC, DD, EE, FF));
        if (fabs(ellipse2tr(x1, ychk[i], AA, BB, CC, DD, EE, FF)) < epsTolerance/2.0) {
//            qDebug() << "got intersection I...";
            nintpts++;
            if (nintpts > 4) {
                //(*rtnCode) = ERROR_INTERSECTION_PTS;
                return QList<RVector>();
            }
            xint[nintpts] = x1;
            yint[nintpts] = ychk[i];

//            qDebug() << "intersection I: " << xint[nintpts] << "/" << yint[nintpts];
        }

//        qDebug() << "fabs(ellipse2tr(x2, ychk[i], AA, BB, CC, DD, EE, FF))" << fabs(ellipse2tr(x2, ychk[i], AA, BB, CC, DD, EE, FF));
        if ((fabs(ellipse2tr(x2, ychk[i], AA, BB, CC, DD, EE, FF)) < epsTolerance/2.0) && (fabs(x2 - x1) > epsTolerance/2.0)) {
//            qDebug() << "got intersection II...";
            nintpts++;
            if (nintpts > 4) {
                //(*rtnCode) = ERROR_INTERSECTION_PTS;
                return QList<RVector>();
            }
            xint[nintpts] = x2;
            yint[nintpts] = ychk[i];

//            qDebug() << "intersection II: " << xint[nintpts] << "/" << yint[nintpts];
        }
    }

    //qDebug() << "nintpts: " << nintpts;

    for (int i=1; i<=nintpts; i++) {
//        qDebug() << "intersection: x/y: " << xint[i] << "/" << yint[i];
        RVector v(xint[i], yint[i]);
        v.rotate(-angleOffset);
        v.move(-centerOffset);
        ret.append(v);
    }

    return ret;
}

QList<RVector> RShape::getIntersectionPointsES(const REllipse& ellipse1,
            const RSpline& spline2, bool limited) {

//    QList<RVector> res;
//    if (spline2.getIntersectionPointsProxy(res, ellipse1, limited, false)) {
//        return res;
//    }

    return getIntersectionPointsEX(ellipse1, spline2, limited);
}

QList<RVector> RShape::getIntersectionPointsEX(const REllipse& ellipse1,
        const RExplodable& explodable2, bool limited) {
    Q_UNUSED(limited)
    QList<RVector> res;

    QList<QSharedPointer<RShape> > sub = explodable2.getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        QSharedPointer<RLine> pLine2 = (*it).dynamicCast<RLine>();
        if (!pLine2.isNull()) {
            RLine line2 = *pLine2.data();
            res.append(RShape::getIntersectionPointsLE(line2, ellipse1));
            continue;
        }
    }

    return res;
}

/**
 * \param same True if the two shapes are identical, from the same interpolated
 *      shape (e.g. spline).
 */
QList<RVector> RShape::getIntersectionPointsXX(const RExplodable& explodable1,
        const RExplodable& explodable2, bool limited, bool same) {

    Q_UNUSED(limited)
    QList<RVector> res;

    QList<QSharedPointer<RShape> > sub1 = explodable1.getExploded();
    QList<QSharedPointer<RShape> > sub2;

    if (same) {
        sub2 = sub1;
    }
    else {
        sub2 = explodable2.getExploded();
    }

    QList<QSharedPointer<RShape> >::iterator it1;
    QList<QSharedPointer<RShape> >::iterator it2;

    int c1, c2;
    for (it1=sub1.begin(), c1=0; it1!=sub1.end(); ++it1, ++c1) {
        for (it2=sub2.begin(), c2=0; it2!=sub2.end(); ++it2, ++c2) {
            // sub shapes of same, interpolated shape (e.g. spline):
            if (same) {
                /*
                QSharedPointer<RDirected> directed1 = *it1->dynamicCast<RDirected>();
                QSharedPointer<RDirected> directed2 = *it2->dynamicCast<RDirected>();
                if (!directed1.isNull() && !directed2.isNull()) {
                    if (directed1->connectsTo(*directed2)) {
                        // spline internal connection point is not an intersection:
                        continue;
                    }
                }
                */
                // segments are connected and therefore don't intersect for a spline:
                if (qAbs(c1-c2)<=1) {
                    continue;
                }
            }

            res.append(RShape::getIntersectionPoints(*it1->data(), *it2->data()));
        }
    }

    return res;
}

bool RShape::flipHorizontal() {
    return mirror(RLine(RVector(0,0), RVector(0,1)));
}

bool RShape::flipVertical() {
    return mirror(RLine(RVector(0,0), RVector(1,0)));
}

bool RShape::stretch(const RBox& area, const RVector& offset) {
    return stretch(area.getPolyline2d(), offset);
}

bool RShape::stretch(const RPolyline& area, const RVector& offset) {
    Q_UNUSED(area)
    Q_UNUSED(offset)

    return false;
}

bool RShape::scale(double scaleFactor, const RVector& center) {
    return scale(RVector(scaleFactor, scaleFactor, scaleFactor), center);
}

void RShape::print(QDebug dbg) const {
    dbg.nospace() << "RShape("
            << "address: " << QString("0x%1").arg((long int) this, 0, 16)
            << ")";
}

/**
 * Orders the given list of loops into a list of closed loops in which all
 * shapes are connected end to start point.
 * Empty loops are dropped.
 *
 * \return True if all loops are closed, false otherwise.
 */
bool RShape::order(QList<QList<QSharedPointer<RShape> > >& boundary) {
    /*
    // for debugging:
    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        qDebug() << "loop: " << i;
        for (int k=0; k<loop.size(); ++k) {
            qDebug() << "boundary shape: " << *loop.at(k);
        }
    }
    */

    QList<QList<QSharedPointer<RShape> > > newBoundary;

    for (int i=0; i<boundary.size(); ++i) {
        QList<QSharedPointer<RShape> > loop = boundary.at(i);
        RVector cursor = RVector::invalid;
        RVector loopStartPoint = RVector::invalid;
        if (loop.size()!=0) {
            newBoundary.append(QList<QSharedPointer<RShape> >());
        }

        int k=0;

        //qDebug() << "LOOP: " << i+1 << " / " << boundary.size();

        do {
            if (loop.isEmpty()) {
                break;
            }

            QSharedPointer<RShape> shape = loop.at(k);
            //qDebug() << "RShape::order: shape: " << *shape;

            // circle loop:
            QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
            if (!circle.isNull()) {
                if (k!=0 || loop.size()!=1) {
                    qWarning() << "RShape::order: loop not closed: circle in loop";
                    return false;
                }
                loop.removeAt(k);
                newBoundary.last().append(shape);
                //qDebug() << "\tloop: " << newBoundary.count() << "\t\tshape: " << *shape;
                break;
            }

            // full ellipse loop:
            QSharedPointer<REllipse> ellipseArc = shape.dynamicCast<REllipse>();
            if (!ellipseArc.isNull() && ellipseArc->isFullEllipse()) {
                if (k!=0 || loop.size()!=1) {
                    qWarning() << "RShape::order: loop not closed: full ellipse in loop";
                    return false;
                }
                loop.removeAt(k);
                newBoundary.last().append(shape);
                //qDebug() << "\tloop: " << newBoundary.count() << "\t\tshape: " << *shape;
                break;
            }

            // full spline loop:
            QSharedPointer<RSpline> spline = shape.dynamicCast<RSpline>();
            if (!spline.isNull()) {
                if (spline->isPeriodic()) {
                    if (k!=0 || loop.size()!=1) {
                        qWarning() << "RShape::order: loop not closed: closed spline in loop";
                        return false;
                    }
                    loop.removeAt(k);
                    newBoundary.last().append(shape);
                    //qDebug() << "\tloop: " << newBoundary.count() << "\t\tshape: " << *shape;
                    break;
                }
            }

            // line, arc, ellipse arc, spline loop segment:
            QSharedPointer<RDirected> directed = shape.dynamicCast<RDirected>();
            if (!directed.isNull()) {
                if (!loopStartPoint.isValid()) {
                    loopStartPoint = directed->getStartPoint();
                    //qDebug() << "RShape::order: loopStartPoint: " << loopStartPoint;
                }

                //qDebug() << "\t\tcursor before: " << cursor;
                //qDebug() << "\t\tchecking: " << *shape;

                bool sp = true;
                bool ep = false;
                if (cursor.isValid()) {
                    sp = cursor.equalsFuzzy(directed->getStartPoint(), 0.001);
                    ep = cursor.equalsFuzzy(directed->getEndPoint(), 0.001);
                    //qDebug() << "sp: " << sp << " (distance: " << cursor.getDistanceTo(directed->getStartPoint()) << ")";
                    //qDebug() << "ep: " << ep << " (distance: " << cursor.getDistanceTo(directed->getEndPoint()) << ")";
                }

                if (sp || ep) {
                    if (ep) {
                        directed->reverse();
                    }
                    loop.removeAt(k);
                    //qDebug() << "\tremove: " << k;
                    //qDebug() << "\tleft: " << loop.count();
                    newBoundary.last().append(shape);
                    //qDebug() << "\tloop: " << newBoundary.count() << "\t\tshape: " << *shape;
                    cursor = directed->getEndPoint();
                    //qDebug() << "\t\tcursor after: " << cursor;
                    k = 0;
                    continue;
                }
            }

            // loop contains more than one loop, start over with new loop:
            //qDebug() << "k is: " << k;
            //qDebug() << "loop count is: " << loop.count();
            if (!loop.isEmpty() && k==loop.count()-1) {
                //qDebug() << "RShape::order: creating new loop";
                k=0;
                cursor = RVector::invalid;
                loopStartPoint = RVector::invalid;
                newBoundary.append(QList<QSharedPointer<RShape> >());
                continue;
            }

            ++k;
        } while(!loop.isEmpty());

        /*
        // for debugging:
        if (loop.size()!=0) {
            qWarning() << "RShape::order: unconnected shapes in loop: ";
            for (int leftOver=0; leftOver<loop.size(); leftOver++) {
                qWarning() << "\t" << *loop[leftOver];
            }
            return false;
        }
        */

        if (cursor.isValid() && loopStartPoint.isValid() &&
                !cursor.equalsFuzzy(loopStartPoint, 0.001)) {

            qWarning() << "RShape::order: loop not closed: "
                       << "end (cursor): " << cursor <<  " does not connect to "
                       << "start: " << loopStartPoint << "";
            return false;
        }
    }

    boundary = newBoundary;

    return true;
}

double RShape::ellipse2tr(double x, double y, double AA, double BB,
                          double CC, double DD, double EE, double FF) {
    return (AA*x*x + BB*x*y + CC*y*y + DD*x + EE*y + FF);
}

void RShape::dump() {
    qDebug() << *this;
}
