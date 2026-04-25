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
#include "RBox.h"
#include "RCircle.h"
#include "RLine.h"

/**
 * Creates a circle object with invalid center and 0 radius.
 */
RCircle::RCircle() :
    center(RVector::invalid), radius(0.0) {
}

/** Creates a circle from center coordinates and radius. */
RCircle::RCircle(double cx, double cy, const double radius) :
    center(cx, cy), radius(radius) {
}

/** Creates a circle from a center point and radius. */
RCircle::RCircle(const RVector& center, const double radius) :
    center(center), radius(radius) {
}

RCircle::~RCircle() {
}

/**
 * Creates a circle with the given two points as diameter endpoints.
 * The center is the midpoint and the radius is half the distance.
 */
RCircle RCircle::createFrom2Points(const RVector& p1, const RVector& p2) {
    RVector center = (p1+p2)/2.0;
    double radius = p1.getDistanceTo(p2)/2.0;
    return RCircle(center, radius);
}

/**
 * Creates a circle through three points by finding the intersection of the
 * perpendicular bisectors of the two chords p1–p2 and p2–p3.
 * Returns an invalid circle if the three points are collinear.
 */
RCircle RCircle::createFrom3Points(const RVector& p1,
                                  const RVector& p2,
                                  const RVector& p3) {
    // intersection of two middle lines

    // middle points between first two points:
    RVector mp1 = RVector::getAverage(p1, p2);
    double a1 = p1.getAngleTo(p2) + M_PI / 2.0;
    // direction from middle point to center:
    RVector dir1 = RVector::createPolar(1.0, a1);

    // middle points between last two points:
    RVector mp2 = RVector::getAverage(p2, p3);
    double a2 = p2.getAngleTo(p3) + M_PI / 2.0;
    // direction from middle point to center:
    RVector dir2 = RVector::createPolar(1.0, a2);

    RLine midLine1(mp1, mp1 + dir1);
    RLine midLine2(mp2, mp2 + dir2);

    QList<RVector> ips = midLine1.getIntersectionPoints(midLine2, false);
    if (ips.length()!=1) {
        return RCircle();
    }

    RVector center = ips[0];
    double radius = center.getDistanceTo(p3);
//    double angle1 = center.getAngleTo(p1);
//    double angle2 = center.getAngleTo(p3);
//    bool reversed = RMath::isAngleBetween(center.getAngleTo(p2),
//                                            angle1, angle2, true);

    return RCircle(center, radius);
}

/** \return An RArc covering the full circle, starting at \c startAngle. */
RArc RCircle::toArc(double startAngle) const {
    return RArc(getCenter(), getRadius(), startAngle, startAngle + 2*M_PI, false);
}

/** Sets the Z coordinate of the center point. */
void RCircle::setZ(double z) {
    center.z = z;
}

/** \return List containing the center point (used for property-based transformations). */
QList<RVector> RCircle::getVectorProperties() const {
    return QList<RVector>() << center;
}

/** \return List of scalar properties: radius. */
QList<double> RCircle::getDoubleProperties() const {
    return QList<double>() << radius;
}

/** \return Center point of the circle. */
RVector RCircle::getCenter() const{
    return center;
}

/** Sets the center point of the circle. */
void RCircle::setCenter(const RVector& vector) {
    center = vector;
}

/** \return Radius of the circle. */
double RCircle::getRadius() const{
    return radius;
}

/** Sets the radius of the circle. */
void RCircle::setRadius(double r) {
    radius = r;
}

/** \return Axis-aligned bounding box (square of side 2*radius centred on center). */
RBox RCircle::getBoundingBox() const {
    return RBox(center - RVector(radius, radius), center + RVector(radius, radius));
}

/** \return Circumference (same as getCircumference()). */
double RCircle::getLength() const {
    return getCircumference();
}

/** \return Diameter (2 * radius). */
double RCircle::getDiameter() const {
    return 2*radius;
}

/** Sets the radius from a diameter value. */
void RCircle::setDiameter(double d) {
    radius = d/2.0;
}

/** \return Circumference of the circle (2 * π * radius). */
double RCircle::getCircumference() const {
    return 2*M_PI*radius;
}

/** Sets the radius to match the given circumference. */
void RCircle::setCircumference(double c) {
    radius = c / (2.0*M_PI);
}

/** \return Area of the circle (π * radius²). */
double RCircle::getArea() const {
    return M_PI*radius*radius;
}

/** Sets the radius to match the given area. */
void RCircle::setArea(double a) {
    radius = sqrt(fabs(a)/M_PI);
}

/** \return True if \c p is strictly inside the circle (distance to center < radius). */
bool RCircle::contains(const RVector& p) const {
    return p.getDistanceTo(center) < radius;
}

//bool RCircle::touchesCircleInternally(const RCircle& other) const {
//    return contains(other.center) || other.contains(center);
//}

/** \return Empty list — circles have no endpoint snaps. */
QList<RVector> RCircle::getEndPoints() const {
    QList<RVector> ret;
    return ret;
}

/** \return Empty list — circles have no midpoint snaps. */
QList<RVector> RCircle::getMiddlePoints() const {
    QList<RVector> ret;
    return ret;
}

/** \return List containing the center point of the circle. */
QList<RVector> RCircle::getCenterPoints() const {
    QList<RVector> ret;
    ret.append(center);
    return ret;
}

/** \return The four quadrant points (0°, 90°, 180°, 270°) as snappable reference points. */
QList<RVector> RCircle::getArcReferencePoints() const {
    QList<RVector> ret;

    ret.append(center + RVector(radius, 0));
    ret.append(center + RVector(0, radius));
    ret.append(center - RVector(radius, 0));
    ret.append(center - RVector(0, radius));

    return ret;
}

/** \return Empty list — circles have no meaningful distance-to-end notion. */
QList<RVector> RCircle::getPointsWithDistanceToEnd(double distance, int from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    QList<RVector> ret;
    return ret;
}

/** \return Dense set of sample points around the full circle. Delegates to RArc::getPointCloud. */
QList<RVector> RCircle::getPointCloud(double segmentLength) const {
    RArc arc = toArc();
    return arc.getPointCloud(segmentLength);
}

/**
 * \return RNANDOUBLE — circles have no defined tangent direction at a parametric distance
 *         (they have no start point).
 */
double RCircle::getAngleAt(double distance, RS::From from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    return RNANDOUBLE;
}

/** \return Point on the circle at angle \c a (radians), preserving the center's Z coordinate. */
RVector RCircle::getPointAtAngle(double a) const {
    return RVector(center.x + cos(a) * radius, center.y + sin(a) * radius, center.z);
}

/**
 * \return Vector from the nearest point on the circle to \c point.
 *         Returns RVector::invalid if \c point is at the center (infinite solutions).
 *         \c limited and \c strictRange are ignored (circles are unlimited).
 */
RVector RCircle::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    Q_UNUSED(limited)
    Q_UNUSED(strictRange)

    RVector v = (point - center).get2D();

    // point is at the center of the circle, infinite solutions:
    if (v.getSquaredMagnitude() < RS::PointTolerance * RS::PointTolerance) {
        return RVector::invalid;
    }

    return RVector::createPolar(v.getMagnitude() - radius, v.getAngle());
}

/** \return The rightmost point of the circle (center + radius along X). */
RVector RCircle::getPointOnShape() const {
    return center + RVector(radius, 0);
}

/**
 * Moves the circle by \c offset. Returns false if the offset is invalid or negligibly small.
 * Uses squared magnitude to avoid a sqrt call; tolerance is squared accordingly.
 */
bool RCircle::move(const RVector& offset) {
    if (!offset.isValid() || offset.getSquaredMagnitude() < RS::PointTolerance * RS::PointTolerance) {
        return false;
    }
    center += offset;
    return true;
}

/** Rotates the circle center around \c c by \c rotation radians (radius is invariant). */
bool RCircle::rotate(double rotation, const RVector& c) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    center.rotate(rotation, c);
    return true;
}

/**
 * Scales the circle by \c scaleFactors relative to \c c.
 * Only scaleFactors.x is used for the radius (uniform XY scaling assumed).
 */
bool RCircle::scale(const RVector& scaleFactors, const RVector& c) {
    center.scale(scaleFactors, c);
    radius = fabs(radius * scaleFactors.x);
    return true;
}

/** Mirrors the circle center about \c axis (radius is invariant). */
bool RCircle::mirror(const RLine& axis) {
    center.mirror(axis);
    return true;
}

/** Flips the circle center horizontally (negates X; radius is invariant). */
bool RCircle::flipHorizontal() {
    center.flipHorizontal();
    return true;
}

/** Flips the circle center vertically (negates Y; radius is invariant). */
bool RCircle::flipVertical() {
    center.flipVertical();
    return true;
}

/**
 * \return A new circle obtained by applying the 2D affine \c transform to the center
 *         and deriving the new radius from the transformed rightmost point.
 * \todo Return a transformed polyline for non-uniform transforms.
 */
QSharedPointer<RShape> RCircle::getTransformed(const QTransform& transform) const {
    RVector ct = center.getTransformed2D(transform);
    RVector sp = center + RVector(radius, 0);
    RVector spt = sp.getTransformed2D(transform);

    return QSharedPointer<RShape>(new RCircle(ct, ct.getDistanceTo(spt)));
}

/**
 * \return The (up to two) tangent lines from \c point to this circle.
 *         Uses the Thales circle construction: the tangent points are the intersections
 *         of this circle with the circle whose diameter is the segment from \c point to
 *         the center. Returns an empty list if \c point is inside the circle.
 *         The condition thalesRadius < radius/2 is equivalent to
 *         distance(point, center) < radius (point inside circle).
 */
QList<RLine> RCircle::getTangents(const RVector& point) const {
    QList<RLine> ret;

    // create temporary thales circle:
    RVector thalesCenter = (point + getCenter())/2;
    double thalesRadius = point.getDistanceTo(thalesCenter);

    if (thalesRadius < getRadius()/2.0) {
        return ret;
    }

    RCircle thalesCircle(thalesCenter, thalesRadius);

    // get the two intersection points which are the tangent points:
    QList<RVector> ips = thalesCircle.getIntersectionPoints(*this, false);

    if (ips.length()>0) {
        ret.append(RLine(point, ips[0]));
        if (ips.length()>1) {
            ret.append(RLine(point, ips[1]));
        }
    }

    return ret;
}

/**
 * Splits the circle at the given \c points, returning a list of RArc segments.
 * Points are sorted by angle from the first split point. The result is a set of
 * arcs that together cover the full circle.
 */
QList<QSharedPointer<RShape> > RCircle::splitAt(const QList<RVector>& points) const {
    if (points.length()==0) {
        return RShape::splitAt(points);
    }

    QList<QSharedPointer<RShape> > ret;

    double refAngle = center.getAngleTo(points[0]);
    RVector startPoint;
    RVector endPoint;

    startPoint = endPoint = center + RVector::createPolar(radius, refAngle);

    QList<RVector> sortedPoints = RVector::getSortedByAngle(points, center, refAngle);

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

        ret.append(QSharedPointer<RShape>(new RArc(center, radius, center.getAngleTo(sortedPoints[i]), center.getAngleTo(sortedPoints[i+1]), false)));
    }

    return ret;
}

/** Prints circle properties to \c dbg for debugging. */
void RCircle::print(QDebug dbg) const {
    dbg.nospace() << "RCircle(";
    RShape::print(dbg);
    dbg.nospace() << ", center: " << getCenter()
                  << ", radius: " << getRadius()
                  << ")";
}
