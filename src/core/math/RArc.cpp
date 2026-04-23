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
#include <cmath>

#include <QDebug>

#include "RArc.h"
#include "RCircle.h"
#include "RBox.h"
#include "RLine.h"
#include "RMath.h"
#include "RPolyline.h"

RArcProxy* RArc::arcProxy = NULL;

/**
 * Creates an arc shape with an invalid center.
 */
RArc::RArc() :
    center(RVector::invalid),
    radius(0.0),
    startAngle(0.0),
    endAngle(0.0),
    reversed(false) {
}

/**
 * Creates an arc from center coordinates, radius, start/end angles (in rad) and direction.
 */
RArc::RArc(double cx, double cy, double radius, double startAngle,
         double endAngle, bool reversed) :
    center(cx, cy),
    radius(radius),
    startAngle(startAngle),
    endAngle(endAngle),
    reversed(reversed) {
}

/**
 * Creates an arc from a center point, radius, start/end angles (in rad) and direction.
 */
RArc::RArc(const RVector& center, double radius, double startAngle,
        double endAngle, bool reversed) :
    center(center),
    radius(radius),
    startAngle(startAngle),
    endAngle(endAngle),
    reversed(reversed) {
}

/**
 * Sets the Z coordinate of the center point.
 */
void RArc::setZ(double z) {
    center.z = z;
}

/**
 * \return List containing the center point (used for property-based transformations).
 */
QList<RVector> RArc::getVectorProperties() const {
    return QList<RVector>() << center;
}

/**
 * \return List of scalar properties: radius, startAngle, endAngle.
 */
QList<double> RArc::getDoubleProperties() const {
    return QList<double>() << radius << startAngle << endAngle;
}

/**
 * \return List of boolean properties: reversed.
 */
QList<bool> RArc::getBoolProperties() const {
    return QList<bool>() << reversed;
}

/**
 * \return True if the center is valid and the radius is positive.
 */
bool RArc::isValid() const {
    return center.isValid() && radius>0.0;
}

/**
 * \return True if the start and end angles are equal within \c tolerance,
 *         indicating that this arc spans a full circle.
 */
bool RArc::isFullCircle(double tolerance) const {
    return fabs(RMath::getAngleDifference180(
                    RMath::getNormalizedAngle(startAngle),
                    RMath::getNormalizedAngle(endAngle))) < tolerance;
}

/**
 * Creates an arc from 3 points.
 */
RArc RArc::createFrom3Points(const RVector& startPoint,
                              const RVector& point,
                              const RVector& endPoint) {
    // intersection of two middle lines

    // middle points between first two points:
    RVector mp1 = RVector::getAverage(startPoint, point);
    double a1 = startPoint.getAngleTo(point) + M_PI / 2.0;
    // direction from middle point to center:
    RVector dir1 = RVector::createPolar(1.0, a1);

    // middle points between last two points:
    RVector mp2 = RVector::getAverage(point, endPoint);
    double a2 = point.getAngleTo(endPoint) + M_PI / 2.0;
    // direction from middle point to center:
    RVector dir2 = RVector::createPolar(1.0, a2);

    RLine midLine1(mp1, mp1 + dir1);
    RLine midLine2(mp2, mp2 + dir2);

    QList<RVector> ips = midLine1.getIntersectionPoints(midLine2, false);
    if (ips.length()!=1) {
        return RArc();
    }

    RVector center = ips[0];
    double radius = center.getDistanceTo(endPoint);
    double angle1 = center.getAngleTo(startPoint);
    double angle2 = center.getAngleTo(endPoint);
    bool reversed = RMath::isAngleBetween(center.getAngleTo(point), angle1, angle2, true);

    return RArc(center, radius, angle1, angle2, reversed);
}

/**
 * Creates an arc from its startpoint, endpoint and bulge (= tan(angle/4)).
 */
RArc RArc::createFrom2PBulge(const RVector& startPoint,
        const RVector& endPoint, double bulge) {

    RArc arc;

    arc.reversed = (bulge < 0.0);
    double alpha = atan(bulge) * 4.0;

    RVector middle = (startPoint + endPoint) / 2.0;
    double dist = startPoint.getDistanceTo(endPoint) / 2.0;

    // alpha can't be 0.0 at this point
    arc.radius = fabs(dist / sin(alpha / 2.0));

    double wu = fabs(arc.radius * arc.radius - dist * dist);
    double h = sqrt(wu);
    double angle = startPoint.getAngleTo(endPoint);

    if (bulge > 0.0) {
        angle += M_PI / 2.0;
    } else {
        angle -= M_PI / 2.0;
    }

    if (fabs(alpha) > M_PI) {
        h *= -1.0;
    }

    arc.center.setPolar(h, angle);
    arc.center += middle;
    arc.startAngle = arc.center.getAngleTo(startPoint);
    arc.endAngle = arc.center.getAngleTo(endPoint);

    return arc;
}

/**
 * Creates an arc tangent to a given direction at \c startPoint, passing near \c pos.
 * Delegates to the arc proxy if available.
 */
RArc RArc::createTangential(const RVector& startPoint, const RVector& pos,
                            double direction, double radius, double sweep) {

    RArc ret;

    if (RArc::hasProxy()) {
        ret = RArc::getArcProxy()->createTangential(startPoint, pos, direction, radius, sweep);
    }

    return ret;
}

/**
 * Creates a biarc (pair of two arcs) with the given conditions.
 */
QList<RArc> RArc::createBiarc(const RVector& startPoint, double startDirection,
                              const RVector& endPoint, double endDirection,
                              bool secondTry) {

    double length = startPoint.getDistanceTo(endPoint);
    double angle = startPoint.getAngleTo(endPoint);

    double alpha = RMath::getAngleDifference180(startDirection, angle);
    double beta = RMath::getAngleDifference180(angle, endDirection);

    double theta;
    if ((alpha>0 && beta>0) || (alpha<0 && beta<0)) {
        // same sign: C-shaped curve:
        theta = alpha;
    }
    else {
        // different sign: S-shaped curve:
        theta = (3.0*alpha - beta)/2.0;
    }

    RVector startNormal(-sin(startDirection), cos(startDirection));
    RVector jointPointNormal(-sin(theta + startDirection), cos(theta + startDirection));

    double term1 = (length / (2.0*sin((alpha + beta)/2.0)));

    double radius1 = term1 * (sin((beta - alpha + theta)/2.0) / sin(theta/2.0));
    double radius2 = term1 * (sin((2.0 * alpha - theta)/2.0) / sin((alpha + beta - theta)/2.0));

    // failed, might succeed in reverse direction:
    if (qAbs(radius1)<RS::PointTolerance || qAbs(radius2)<RS::PointTolerance ||
        !RMath::isNormal(radius1) || !RMath::isNormal(radius2)) {

        if (secondTry) {
//            qDebug() << "biarc creation failed: ";
//            qDebug() << "radius1: " << radius1;
//            qDebug() << "radius2: " << radius2;
//            qDebug() << "startPoint: " << startPoint;
//            qDebug() << "startDirection: " << startDirection;
//            qDebug() << "endPoint: " << endPoint;
//            qDebug() << "endDirection: " << endDirection;
            return QList<RArc>();
        }

        QList<RArc> list = RArc::createBiarc(endPoint, endDirection+M_PI, startPoint, startDirection+M_PI, true);
        if (list.isEmpty()) {
            return QList<RArc>();
        }

        for (int i=0; i<list.length(); i++) {
            list[i].reverse();
        }
        return QList<RArc>() << list[1] << list[0];
//        return QList<RArc>();
    }

    RVector jointPoint = startPoint + radius1 * (startNormal - jointPointNormal);

    RVector center1 = startPoint + startNormal * radius1;
    RVector center2 = jointPoint + jointPointNormal * radius2;

    RArc arc1(center1, qAbs(radius1), center1.getAngleTo(startPoint), center1.getAngleTo(jointPoint));
    if (qAbs(RMath::getAngleDifference180(arc1.getDirection1(), startDirection))>0.1) {
        arc1.setReversed(true);
    }

    RArc arc2(center2, qAbs(radius2), center2.getAngleTo(jointPoint), center2.getAngleTo(endPoint));
    if (qAbs(RMath::getAngleDifference180(arc2.getDirection2() + M_PI, endDirection))>0.1) {
        arc2.setReversed(true);
    }

    return QList<RArc>() << arc1 << arc2;
}

/**
 * \return Tangent direction at the start point (in rad): perpendicular to the radius,
 *         pointing in the direction of travel.
 */
double RArc::getDirection1() const{
    if (!reversed) {
        return RMath::getNormalizedAngle(startAngle+M_PI/2.0);
    }
    else {
        return RMath::getNormalizedAngle(startAngle-M_PI/2.0);
    }
}

/**
 * \return Tangent direction at the end point (in rad), pointing away from the arc.
 */
double RArc::getDirection2() const{
    if (!reversed) {
        return RMath::getNormalizedAngle(endAngle-M_PI/2.0);
    }
    else {
        return RMath::getNormalizedAngle(endAngle+M_PI/2.0);
    }
}

/**
 * \return Which side of the arc the given point is on.
 *         A point inside the circle is on the left for CCW arcs, right for CW arcs.
 */
RS::Side RArc::getSideOfPoint(const RVector& point) const {
    if (reversed) {
        if (center.getDistanceTo(point) < radius) {
            return RS::RightHand;
        }
        else {
            return RS::LeftHand;
        }
    }
    else {
        if (center.getDistanceTo(point) < radius) {
            return RS::LeftHand;
        }
        else {
            return RS::RightHand;
        }
    }
}

/**
 * Moves the start point of the arc, optionally keeping the radius.
 * If keepRadius is true and the arc is not a full circle, the arc is reconstructed
 * from the new start point and the current end point with the same bulge.
 * If keepRadius is false, the arc is reconstructed from the new start point,
 * the current middle point and end point.
 */
void RArc::moveStartPoint(const RVector& pos, bool keepRadius) {
    if (!keepRadius) {
        RArc a = RArc::createFrom3Points(pos, getMiddlePoint(), getEndPoint());
        if (a.isReversed()!=isReversed()) {
            a.reverse();
        }
        *this = a;
    }
    else {
        double bulge = getBulge();

        // full circle: trim instead of move:
        if (bulge < 1.0e-6 || bulge > 1.0e6) {
            startAngle = center.getAngleTo(pos);
        }
        else {
            *this = RArc::createFrom2PBulge(pos, getEndPoint(), bulge);
        }
    }
}

/**
 * Moves the end point of the arc, optionally keeping the radius.
 * If keepRadius is true and the arc is not a full circle, the arc is reconstructed
 * from the current start point and the new end point with the same bulge.
 * If keepRadius is false, the arc is reconstructed from the current start point,
 * the current middle point and the new end point.
 */
void RArc::moveEndPoint(const RVector& pos, bool keepRadius) {
    if (!keepRadius) {
        RArc a = RArc::createFrom3Points(pos, getMiddlePoint(), getStartPoint());
        if (a.isReversed()!=isReversed()) {
            a.reverse();
        }
        *this = a;
    }
    else {
        double bulge = getBulge();

        // full circle: trim instead of move:
        if (bulge < 1.0e-6 || bulge > 1.0e6) {
            endAngle = center.getAngleTo(pos);
        }
        else {
            *this = RArc::createFrom2PBulge(getStartPoint(), pos, bulge);
        }
    }
}

/**
 * Moves the midpoint of the arc to \c pos by reconstructing from current start/end
 * and the new middle point.
 */
void RArc::moveMiddlePoint(const RVector& pos) {
    *this = RArc::createFrom3Points(getStartPoint(), pos, getEndPoint());
}

/**
 * \return Bulge value (tan(sweep/4)), negative for clockwise arcs.
 *         Used in DXF/DWG polyline vertex encoding.
 */
double RArc::getBulge() const {
    //qDebug() << "sweep: " << getSweep();
    double bulge = tan(fabs(getSweep()) / 4.0);
    if (isReversed()) {
        bulge *= -1;
    }
    return bulge;
}

/** \return Arc length (angle length * radius). */
double RArc::getLength() const {
    return fabs(getAngleLength(false)) * radius;
}

/** \return Diameter (2 * radius). */
double RArc::getDiameter() const {
    return 2*radius;
}

/** Sets the radius from a diameter value. */
void RArc::setDiameter(double d) {
    radius = d/2.0;
}

/** Sets the arc length by adjusting the end angle (keeping start angle and radius). */
void RArc::setLength(double l) {
    double sweep = l / radius;
    if (sweep>2*M_PI) {
        sweep = 2*M_PI;
    }
    if (reversed) {
        sweep *= -1;
    }

    endAngle = startAngle + sweep;
}

/** \return Area of the circular sector (pie slice) defined by this arc. */
double RArc::getArea() const {
    return (radius*radius*getAngleLength(false)) / 2.0;
}

/** Sets the arc sweep angle by adjusting the end angle to match the given sector area. */
void RArc::setArea(double a) {
    double sweep = (a * 2.0) / (radius*radius);
    if (reversed) {
        endAngle = RMath::getNormalizedAngle(startAngle - sweep);
    }
    else {
        endAngle = RMath::getNormalizedAngle(startAngle + sweep);
    }
}

/**
 * \return Area of the circular segment bounded by the arc and its chord.
 *         Computed as sector area minus triangle area (sagitta * chord / 2),
 *         where sagitta h = radius - sqrt(radius² - (chord/2)²).
 */
double RArc::getChordArea() const {
    double a = getArea();
    double c = RLine(getStartPoint(), getEndPoint()).getLength();
    double h = radius - sqrt(radius*radius - (c/2.0)*(c/2.0));
    return a - (h*c/2.0);
}

/**
 * \return Angle length in rad.
 *
 * \param allowForZeroLength: Allow for zero length result if start
 *    and end angle are the same. Otherwise 2*PI will be returned for
 *    such an arc, assuming it is a full circle.
 *
 * \todo almost the same as getSweep
 */
double RArc::getAngleLength(bool allowForZeroLength) const {
    double ret = fabs(getSweep());

    // full circle or zero length arc:
    if (!allowForZeroLength) {
        if (ret < 1.0e-16) {
            ret = 2 * M_PI;
        }
    }
    else {
        if (ret > 2 * M_PI - 1.0e-16) {
            ret = 0.0;
        }
    }

    return ret;
}

/**
 * \return Arc sweep in rad. The sweep is the angle covered by this arc.
 * Positive for ccw, negative for cw.
 */
double RArc::getSweep() const {
    double ret = 0.0;

    if (reversed) {
        if (startAngle <= endAngle) {
            ret = -(startAngle + 2 * M_PI - endAngle);
        } else {
            ret = -(startAngle - endAngle);
        }
    } else {
        if (endAngle <= startAngle) {
            ret = endAngle + 2 * M_PI - startAngle;
        } else {
            ret = endAngle - startAngle;
        }
    }

    // full circle:
//  if (!allowForZeroLength && fabs(ret) < 1.0e-6) {
//      ret = 2 * M_PI;
//  }

    return ret;
}

/** Sets the sweep angle (end = start + s); sets reversed if s < 0. */
void RArc::setSweep(double s) {
    endAngle = startAngle + s;
    reversed = (s<0.0);
}

/** \return Center point of the arc. */
RVector RArc::getCenter() const{
    return center;
}

/** Sets the center point of the arc. */
void RArc::setCenter(const RVector& vector) {
    center = vector;
}

/** \return Radius of the arc. */
double RArc::getRadius() const{
    return radius;
}

/** Sets the radius of the arc. */
void RArc::setRadius(double r) {
    radius = r;
}

/** \return Start angle in radians (normalized to [0, 2π)). */
double RArc::getStartAngle() const {
    return startAngle;
}

/** Sets the start angle, normalizing it to [0, 2π). */
void RArc::setStartAngle(double a) {
    startAngle = RMath::getNormalizedAngle(a);
}

/** \return End angle in radians (normalized to [0, 2π)). */
double RArc::getEndAngle() const {
    return endAngle;
}

/** Sets the end angle, normalizing it to [0, 2π). */
void RArc::setEndAngle(double a) {
    endAngle = RMath::getNormalizedAngle(a);
}

/** \return Point at the midpoint of the arc (halfway along the sweep). */
RVector RArc::getMiddlePoint() const {
    double a;
    a = startAngle + getSweep()/2.0;
    RVector v = RVector::createPolar(radius, a);
    v+=center;
    return v;
}

/** \return Start point of the arc. */
RVector RArc::getStartPoint() const {
    return getPointAtAngle(startAngle);
}

/** \return End point of the arc. */
RVector RArc::getEndPoint() const {
    return getPointAtAngle(endAngle);
}

/** \return Point on the arc at the given angle \c a (in radians). */
RVector RArc::getPointAtAngle(double a) const {
    return RVector(center.x + cos(a) * radius, center.y + sin(a) * radius, center.z);
}

/**
 * \return Tangent direction angle at the point on the arc at the given arc-length
 *         distance from the start or end. Returns RNANDOUBLE if no such point exists.
 */
double RArc::getAngleAt(double distance, RS::From from) const {
    QList<RVector> points = getPointsWithDistanceToEnd(distance, from);
    if (points.length()!=1) {
        return RNANDOUBLE;
    }
    return center.getAngleTo(points[0]) + (reversed ? -M_PI/2 : M_PI/2);
}

/** \return True if the arc is clockwise (reversed). */
bool RArc::isReversed() const {
    return reversed;
}

/** Sets the arc direction: true = clockwise, false = counter-clockwise. */
void RArc::setReversed(bool r) {
    reversed = r;
}

/**
 * \return Axis-aligned bounding box of this arc.
 *         Checks which of the four quadrant extremes (0°, 90°, 180°, 270°) lie
 *         within the arc and expands the box accordingly.
 */
RBox RArc::getBoundingBox() const {
    if (!isValid()) {
        return RBox();
    }

    RVector sp = getStartPoint();
    RVector ep = getEndPoint();
    double minX = qMin(sp.x, ep.x);
    double minY = qMin(sp.y, ep.y);
    double maxX = qMax(sp.x, ep.x);
    double maxY = qMax(sp.y, ep.y);

    if (sp.getDistanceTo(ep) < 1.0e-6 && radius > 1.0e5) {
        return RBox(RVector(minX, minY), RVector(maxX, maxY));
    }

    double a1 = RMath::getNormalizedAngle(!isReversed() ? startAngle : endAngle);
    double a2 = RMath::getNormalizedAngle(!isReversed() ? endAngle : startAngle);

    // check for left limit:
    if ((a1<M_PI && a2>M_PI) ||
            (a1>a2-1.0e-12 && a2>M_PI) ||
            (a1>a2-1.0e-12 && a1<M_PI) ) {

        minX = qMin(center.x - radius, minX);
    }

    // check for right limit:
    if (a1 > a2-1.0e-12) {
        maxX = qMax(center.x + radius, maxX);
    }

    // check for bottom limit:
    if ((a1<(M_PI_2*3) && a2>(M_PI_2*3)) ||
            (a1>a2-1.0e-12    && a2>(M_PI_2*3)) ||
            (a1>a2-1.0e-12    && a1<(M_PI_2*3)) ) {

        minY = qMin(center.y - radius, minY);
    }

    // check for top limit:
    if ((a1<M_PI_2 && a2>M_PI_2) ||
            (a1>a2-1.0e-12   && a2>M_PI_2) ||
            (a1>a2-1.0e-12   && a1<M_PI_2) ) {

        maxY = qMax(center.y + radius, maxY);
    }

    RBox ret(RVector(minX, minY), RVector(maxX, maxY));

    // if center is almost within bounding box, increase bounding box to include center
    // this enables snapping to the center point with auto snap for (almost) 180 degree arcs:
    RBox larger = ret;
    larger.growXY(RS::PointTolerance * 100);
    if (larger.contains(center)) {
        minX = qMin(center.x, minX);
        maxX = qMax(center.x, maxX);
        minY = qMin(center.y, minY);
        maxY = qMax(center.y, maxY);

        ret = RBox(RVector(minX, minY), RVector(maxX, maxY));
    }

    return ret;
}

/** \return List containing the start and end points of the arc. */
QList<RVector> RArc::getEndPoints() const {
    QList<RVector> ret;
    ret.append(getStartPoint());
    ret.append(getEndPoint());
    return ret;
}

/** \return List containing the midpoint of the arc. */
QList<RVector> RArc::getMiddlePoints() const {
    QList<RVector> ret;
    ret.append(getMiddlePoint());
    return ret;
}

/** \return List containing the center point of the arc. */
QList<RVector> RArc::getCenterPoints() const {
    QList<RVector> ret;
    ret.append(getCenter());
    return ret;
}

/**
 * \return The quadrant extremes (0°, 90°, 180°, 270° points on the circle)
 *         that lie within the arc. Used as snappable reference points.
 */
QList<RVector> RArc::getArcReferencePoints() const {
    QList<RVector> ret;

    QList<RVector> p;
    p.append(center + RVector(radius, 0));
    p.append(center + RVector(0, radius));
    p.append(center - RVector(radius, 0));
    p.append(center - RVector(0, radius));

    for (int i=0; i<p.size(); i++) {
        if (RMath::isAngleBetween(center.getAngleTo(p[i]), startAngle, endAngle, reversed)) {
            ret.append(p[i]);
        }
    }

    return ret;
}

/**
 * \return Point(s) on the arc at arc-length \c distance from the start and/or end,
 *         controlled by the \c from bitmask (RS::FromStart, RS::FromEnd, RS::FromAny).
 */
QList<RVector> RArc::getPointsWithDistanceToEnd(double distance, int from) const {
    QList<RVector> ret;

    if (radius<RS::PointTolerance) {
        return ret;
    }

    double a1;
    double a2;
    RVector p;
    double aDist = distance / radius;

    if (isReversed()) {
        a1 = getStartAngle() - aDist;
        a2 = getEndAngle() + aDist;
    } else {
        a1 = getStartAngle() + aDist;
        a2 = getEndAngle() - aDist;
    }

    if (from&RS::FromStart) {
        p.setPolar(radius, a1);
        p += center;
        ret.append(p);
    }

    if (from&RS::FromEnd) {
        p.setPolar(radius, a2);
        p += center;
        ret.append(p);
    }

    return ret;
}

/**
 * \return Dense set of points sampling the arc. Combines vertices from both
 *         the inscribed and circumscribed polyline approximations.
 */
QList<RVector> RArc::getPointCloud(double segmentLength) const {
    QList<RVector> ret;
    RPolyline pl = approximateWithLines(segmentLength);
    ret.append(pl.getVertices());
    pl = approximateWithLinesTan(segmentLength);
    ret.append(pl.getVertices());
    return ret;
}

/**
 * \return Vector from the nearest point on the arc to \c point, or RVector::invalid
 *         if \c limited is true and the projection falls outside the arc span.
 *         Note: \c strictRange is not implemented.
 */
RVector RArc::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    Q_UNUSED(strictRange)

    double angle = center.getAngleTo(point);
    if (limited && !RMath::isAngleBetween(angle, startAngle, endAngle, reversed)) {
        return RVector::invalid;
    }

    RVector v = (point - center).get2D();
    return RVector::createPolar(v.getMagnitude() - radius, v.getAngle());
}

/**
 * Moves the arc by \c offset. Returns false if the offset is invalid or negligibly small.
 * Uses squared magnitude to avoid a sqrt call; tolerance is squared accordingly.
 */
bool RArc::move(const RVector& offset) {
    if (!offset.isValid() || offset.getSquaredMagnitude() < RS::PointTolerance * RS::PointTolerance) {
        return false;
    }
    center += offset;
    return true;
}

/** Rotates the arc around \c c by \c rotation radians. Skips angle update for full circles. */
bool RArc::rotate(double rotation, const RVector& c) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }

    center.rotate(rotation, c);

    // important for circle shaped in hatch boundaries:
    if (!isFullCircle()) {
        startAngle = RMath::getNormalizedAngle(startAngle + rotation);
        endAngle = RMath::getNormalizedAngle(endAngle + rotation);
    }

    return true;
}

/**
 * Scales the arc by \c scaleFactors relative to \c c.
 * Negative scale factors are decomposed into a mirror plus a positive scale.
 * Only uniform XY scaling is supported for the radius (scaleFactors.x is used).
 */
bool RArc::scale(const RVector& scaleFactors, const RVector& c) {
    // negative scaling: mirroring and scaling
    if (scaleFactors.x < 0.0) {
        mirror(RLine(center, center + RVector(0.0, 1.0)));
    }
    if (scaleFactors.y < 0.0) {
        mirror(RLine(center, center + RVector(1.0, 0.0)));
    }

    center.scale(scaleFactors, c);
    radius = fabs(radius * scaleFactors.x);

    return true;
}

/**
 * Mirrors the arc about \c axis. Reverses the arc direction and reflects
 * the start/end angles. Full circles only need their center mirrored.
 */
bool RArc::mirror(const RLine& axis) {
    center.mirror(axis);

    if (isFullCircle()) {
        return true;
    }

    reversed = (!reversed);

    RVector v;
    v.setPolar(1.0, startAngle);
    v.mirror(RVector(0.0, 0.0), axis.endPoint - axis.startPoint);
    startAngle = v.getAngle();

    v.setPolar(1.0, endAngle);
    v.mirror(RVector(0.0, 0.0), axis.endPoint - axis.startPoint);
    endAngle = v.getAngle();

    return true;
}

/** Reverses the arc direction by swapping start/end angles and toggling the reversed flag. */
bool RArc::reverse() {
    RMath::swap(startAngle, endAngle);
    reversed = !reversed;
    return true;
}

/**
 * Stretches the arc by moving endpoint(s) inside \c area by \c offset.
 * If both endpoints are inside, the whole arc is moved.
 */
bool RArc::stretch(const RPolyline& area, const RVector& offset) {
    bool ret = false;

    if (area.contains(getStartPoint(), true) && area.contains(getEndPoint(), true)) {
        return move(offset);
    }

    if (area.contains(getStartPoint(), true)) {
        moveStartPoint(getStartPoint() + offset);
        ret = true;
    }
    else if (area.contains(getEndPoint(), true)) {
        moveEndPoint(getEndPoint() + offset);
        ret = true;
    }

    return ret;
}

/**
 * \todo Not working as expected, fix or disable
 */
QSharedPointer<RShape> RArc::getTransformed(const QTransform& transform) const {
    // TODO: return transformed polyline with line segments

    RVector ct = center.getTransformed2D(transform);
    RVector sp = getStartPoint();
    RVector spt = sp.getTransformed2D(transform);
    RVector ep = getEndPoint();
    RVector ept = ep.getTransformed2D(transform);
    RVector mp = getMiddlePoint();
    RVector mpt = mp.getTransformed2D(transform);

    RArc* ret = new RArc(
            ct,
            ct.getDistanceTo(spt),
            ct.getAngleTo(spt),
            ct.getAngleTo(ept),
            reversed
        );

    if (!ret->getMiddlePoint().equalsFuzzy(mpt, 0.01)) {
        ret->setReversed(!reversed);
    }

    return QSharedPointer<RShape>(ret);
}

/**
 * \return Which end of the arc is closer to \c clickPoint relative to \c trimPoint.
 *         Used to decide which end to trim when the user clicks near a trim point.
 */
RS::Ending RArc::getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
    double angleToTrimPoint = center.getAngleTo(trimPoint);
    double angleToClickPoint = center.getAngleTo(clickPoint);

    if (RMath::getAngleDifference(angleToClickPoint, angleToTrimPoint)>M_PI) {
        if (reversed) {
            return RS::EndingEnd;
        } else {
            return RS::EndingStart;
        }
    } else {
        if (reversed) {
            return RS::EndingStart;
        } else {
            return RS::EndingEnd;
        }
    }
}

/** Trims the start of the arc to the angle corresponding to \c trimPoint. */
bool RArc::trimStartPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    startAngle = center.getAngleTo(trimPoint);
    return true;
}

/** Trims the end of the arc to the angle corresponding to \c trimPoint. */
bool RArc::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    endAngle = center.getAngleTo(trimPoint);
    return true;
}

/**
 * \return Arc-length distance from the start point to the projection of \c p
 *         onto the arc's circle (i.e. the point at the angle from center to \c p).
 */
double RArc::getDistanceFromStart(const RVector& p) const {
    double a1 = getStartAngle();
    double ap = center.getAngleTo(p);
    if (reversed) {
        return RMath::getAngleDifference(ap, a1) * radius;
    }
    else {
        return RMath::getAngleDifference(a1, ap) * radius;
    }
}

/**
 * \return Polyline approximation of arc with line segments of given length or (if length is 0) given angle.
 * Polyline is on the inside of the arc.
 */
RPolyline RArc::approximateWithLines(double segmentLength, double angle) const {
    RPolyline polyline;

    double aStep;
    if (segmentLength<RS::PointTolerance && angle>RS::PointTolerance) {
        aStep = angle;
    }
    else {
        // avoid a segment length of 0:
        if (segmentLength>0.0 && segmentLength<1.0e-6) {
            segmentLength = 1.0e-6;
        }
        if (segmentLength>0.0) {
            aStep = segmentLength / radius;
        }
        else {
            // negative segment length: auto:
            aStep = 1.0;
        }
    }

    double a1 = getStartAngle();
    double a2 = getEndAngle();
    double a, cix, ciy;

    polyline.appendVertex(getStartPoint());
    if (!reversed) {
        // Arc Counterclockwise:
        if (a1>a2-1.0e-10) {
            a2+=2*M_PI;
        }
        for (a=a1+aStep; a<=a2; a+=aStep) {
            cix = center.x + cos(a) * radius;
            ciy = center.y + sin(a) * radius;
            polyline.appendVertex(RVector(cix, ciy));
        }
    } else {
        // Arc Clockwise:
        if (a1<a2+1.0e-10) {
            a2-=2*M_PI;
        }
        for (a=a1-aStep; a>=a2; a-=aStep) {
            cix = center.x + cos(a) * radius;
            ciy = center.y + sin(a) * radius;
            polyline.appendVertex(RVector(cix, ciy));
        }
    }
    polyline.appendVertex(getEndPoint());

    return polyline;
}

/**
 * \return Polyline approximation of arc with line segments of given length or (if length is 0) given angle.
 * Polyline is on the outside of the arc.
 */
RPolyline RArc::approximateWithLinesTan(double segmentLength, double angle) const {
    RPolyline polyline;

    double aStep;
    if (segmentLength<RS::PointTolerance && angle>RS::PointTolerance) {
        aStep = angle;
        double sw = fabs(getSweep());
        if (aStep>sw) {
            // make sure aStep is not too large for arc:
            aStep = sw/2;
        }
    }
    else {
        // avoid a segment length of 0:
        if (segmentLength<1.0e-6) {
            segmentLength = 1.0e-6;
        }

        // ideal angle step to satisfy segmentLength:
        aStep = segmentLength / radius;

        int steps = ceil(fabs(getSweep()) / aStep);
        // real angle step:
        aStep = fabs(getSweep()) / steps;
        if (fabs(cos(aStep/2))<RS::PointTolerance) {
            qWarning() << "RArc::approximateWithLinesTan: segmentLength to coarse to yield meaningful result";
            polyline.appendVertex(getStartPoint());
            polyline.appendVertex(getEndPoint());
            return polyline;
        }
    }

    double r2 = radius / cos(aStep/2);

    double a1 = getStartAngle();
    double a2 = getEndAngle();

    double a, cix, ciy;

    polyline.appendVertex(getStartPoint());
    if (!reversed) {
        // Arc Counterclockwise:
        if (a1>a2-1.0e-10) {
            a2+=2*M_PI;
        }
        for (a=a1+aStep/2; a<a2; a+=aStep) {
            cix = center.x + cos(a) * r2;
            ciy = center.y + sin(a) * r2;
            polyline.appendVertex(RVector(cix, ciy));
        }
    } else {
        // Arc Clockwise:
        if (a1<a2+1.0e-10) {
            a2-=2*M_PI;
        }
        for (a=a1-aStep/2; a>a2; a-=aStep) {
            cix = center.x + cos(a) * r2;
            ciy = center.y + sin(a) * r2;
            polyline.appendVertex(RVector(cix, ciy));
        }
    }

    if (polyline.countVertices()==1) {
        // only got start point, add point in the middle:
        a = getAngleAtPercent(0.5);
        cix = center.x + cos(a) * r2;
        ciy = center.y + sin(a) * r2;
        polyline.appendVertex(RVector(cix, ciy));
    }

    polyline.appendVertex(getEndPoint());

    return polyline;
}

/**
 * \return The tangent lines from the external \c point to this arc's circle.
 *         Delegates to RCircle::getTangents.
 */
QList<RLine> RArc::getTangents(const RVector& point) const {
    RCircle circle(center, radius);
    return circle.getTangents(point);
}

/**
 * Splits this arc at the given \c points (sorted by angle from start).
 * Reversed arcs are temporarily flipped, split, then the result list is reversed.
 */
QList<QSharedPointer<RShape> > RArc::splitAt(const QList<RVector>& points) const {
    if (points.length()==0) {
        return RShape::splitAt(points);
    }

    QList<QSharedPointer<RShape> > ret;

    if (reversed) {
        RArc arc = *this;
        arc.reverse();
        ret = arc.splitAt(points);
        return RShape::getReversedShapeList(ret);
    }

    RVector startPoint = getStartPoint();
    RVector endPoint = getEndPoint();

    QList<RVector> sortedPoints = RVector::getSortedByAngle(points, center, getStartAngle());

    if (!startPoint.equalsFuzzy(sortedPoints[0])) {
        sortedPoints.prepend(startPoint);
    }
    if (!endPoint.equalsFuzzy(sortedPoints[sortedPoints.length()-1])) {
        sortedPoints.append(endPoint);
    }

    for (int i=0; i<sortedPoints.length()-1; i++) {
        if (sortedPoints[i].equalsFuzzy(sortedPoints[i+1])) {
            continue;
        }

        QSharedPointer<RArc> seg = clone().dynamicCast<RArc>();
        if (!seg.isNull()) {
            double a1 = center.getAngleTo(sortedPoints[i]);
            double a2 = center.getAngleTo(sortedPoints[i+1]);
            if (fabs(RMath::getAngleDifference180(a1, a2)*radius)<0.001) {
                continue;
            }
            seg->setStartAngle(a1);
            seg->setEndAngle(a2);
            ret.append(seg);
        }
    }

    return ret;
}

/**
 * \return This arc split at the quadrant angles (0°, 90°, 180°, 270°) that
 *         lie within the arc span. Useful for bounding-box calculations.
 */
QList<RArc> RArc::splitAtQuadrantLines() const {
    QVector<double> angles;
    angles.append(0.0);
    angles.append(M_PI/2);
    angles.append(M_PI);
    angles.append(M_PI/2*3);

    QList<RVector> points;
    for (int i=0; i<angles.size(); i++) {
        if (isAngleWithinArc(angles[i])) {
            points.append(center + RVector::createPolar(radius, angles[i]));
        }
    }

    QList<QSharedPointer<RShape> > segments = splitAt(points);

    QList<RArc> ret;
    for (int i=0; i<segments.length(); i++) {
        QSharedPointer<RArc> seg = segments[i].dynamicCast<RArc>();
        if (!seg.isNull()) {
            ret.append(*seg);
        }
    }
    return ret;
}

/** Prints arc properties to \c dbg for debugging. */
void RArc::print(QDebug dbg) const {
    dbg.nospace() << "RArc(";
    RShape::print(dbg);
    dbg.nospace() << ", center: " << getCenter()
                  << ", radius: " << getRadius()
                  << ", startAngle: " << RMath::rad2deg(getStartAngle())
                  << ", endAngle: " << RMath::rad2deg(getEndAngle())
                  << ", startPoint: " << getStartPoint()
                  << ", endPoint: " << getEndPoint()
                  << ", sweep: " << getSweep()
                  << ", reversed: " << isReversed()
                  << ")";
}
