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

#include "RArc.h"
#include "RBox.h"
#include "RCircle.h"
#include "RTriangle.h"
#include "RPolyline.h"

/**
 * Creates a circle object with invalid center and 0 radius.
 */
RCircle::RCircle() :
    center(RVector::invalid), radius(0.0) {
}

RCircle::RCircle(double cx, double cy, const double radius) :
    center(cx, cy), radius(radius) {
}

RCircle::RCircle(const RVector& center, const double radius) :
    center(center), radius(radius) {
}

RCircle::~RCircle() {
}

RCircle RCircle::createFrom2Points(const RVector& p1, const RVector& p2) {
    RVector center = (p1+p2)/2.0;
    double radius = p1.getDistanceTo(p2)/2.0;
    return RCircle(center, radius);
}

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

RArc RCircle::toArc(double startAngle) const {
    return RArc(getCenter(), getRadius(), startAngle, startAngle + 2*M_PI, false);
}

void RCircle::setZ(double z) {
    center.z = z;
}

QList<RVector> RCircle::getVectorProperties() const {
    return QList<RVector>() << center;
}

QList<double> RCircle::getDoubleProperties() const {
    return QList<double>() << radius;
}

RVector RCircle::getCenter() const{
    return center;
}

void RCircle::setCenter(const RVector& vector) {
    center = vector;
}

double RCircle::getRadius() const{
    return radius;
}

void RCircle::setRadius(double r) {
    radius = r;
}

RBox RCircle::getBoundingBox() const {
    return RBox(center - RVector(radius, radius), center + RVector(radius,
            radius));
}

double RCircle::getLength() const {
    return 2 * radius * M_PI;
}

double RCircle::getDiameter() const {
    return 2*radius;
}

void RCircle::setDiameter(double d) {
    radius = d/2.0;
}

double RCircle::getCircumference() const {
    return radius*2*M_PI;
}

void RCircle::setCircumference(double c) {
    radius = c/M_PI/2.0;
}

double RCircle::getArea() const {
    return radius*radius*M_PI;
}

void RCircle::setArea(double a) {
    radius = sqrt(fabs(a)/M_PI);
}

bool RCircle::contains(const RVector& p) const {
    return p.getDistanceTo(center) < radius;
    // TODO: + RS::PointTolerance ?
}

//bool RCircle::touchesCircleInternally(const RCircle& other) const {
//    return contains(other.center) || other.contains(center);
//}

QList<RVector> RCircle::getEndPoints() const {
    QList<RVector> ret;
    return ret;
}

QList<RVector> RCircle::getMiddlePoints() const {
    QList<RVector> ret;
    return ret;
}

QList<RVector> RCircle::getCenterPoints() const {
    QList<RVector> ret;
    ret.append(center);
    return ret;
}

QList<RVector> RCircle::getArcReferencePoints() const {
    QList<RVector> ret;

    ret.append(center + RVector(radius, 0));
    ret.append(center + RVector(0, radius));
    ret.append(center - RVector(radius, 0));
    ret.append(center - RVector(0, radius));

    return ret;
}

QList<RVector> RCircle::getPointsWithDistanceToEnd(double distance, int from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    QList<RVector> ret;
    return ret;
}

QList<RVector> RCircle::getPointCloud(double segmentLength) const {
    RArc arc = toArc();
    return arc.getPointCloud(segmentLength);
}

double RCircle::getAngleAt(double distance, RS::From from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    return RNANDOUBLE;
}

RVector RCircle::getPointAtAngle(double a) const {
    return RVector(center.x + cos(a) * radius, center.y + sin(a) * radius);
}

RVector RCircle::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    Q_UNUSED(limited)
    Q_UNUSED(strictRange)

    RVector v = point - center;

    // point is at the center of the circle, infinite solutions:
    if (v.getMagnitude()<RS::PointTolerance) {
        return RVector::invalid;
    }

    return RVector::createPolar(v.getMagnitude() - radius, v.getAngle());
}

bool RCircle::move(const RVector& offset) {
    if (!offset.isValid() || offset.getMagnitude() < RS::PointTolerance) {
        return false;
    }
    center += offset;
    return true;
}

bool RCircle::rotate(double rotation, const RVector& c) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    center.rotate(rotation, c);
    return true;
}

bool RCircle::scale(const RVector& scaleFactors, const RVector& c) {
    center.scale(scaleFactors, c);
    radius *= scaleFactors.x;
    if (radius < 0.0) {
        radius *= -1.0;
    }
    return true;
}

bool RCircle::mirror(const RLine& axis) {
    center.mirror(axis);
    return true;
}

bool RCircle::flipHorizontal() {
    center.flipHorizontal();
    return true;
}

bool RCircle::flipVertical() {
    center.flipVertical();
    return true;
}

QSharedPointer<RShape> RCircle::getTransformed(const QTransform& transform) const {
    RVector ct = center.getTransformed2D(transform);
    RVector sp = center + RVector(radius, 0);
    RVector spt = sp.getTransformed2D(transform);

    return QSharedPointer<RShape>(
        new RCircle(
            ct,
            ct.getDistanceTo(spt)
        )
    );
}

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

void RCircle::print(QDebug dbg) const {
    dbg.nospace() << "RCircle(";
    RShape::print(dbg);
    dbg.nospace() << ", center: " << getCenter()
                  << ", radius: " << getRadius()
                  << ")";
}
