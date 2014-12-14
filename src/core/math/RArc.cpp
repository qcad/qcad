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
#include <cmath>

#include "RArc.h"
#include "RBox.h"
#include "RMath.h"
#include "RPolyline.h"

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

RArc::RArc(const RVector& center, double radius, double startAngle,
        double endAngle, bool reversed) :
    center(center),
    radius(radius),
    startAngle(startAngle),
    endAngle(endAngle),
    reversed(reversed) {
}

RArc::~RArc() {
}

void RArc::to2D() {
    center.z = 0.0;
}

bool RArc::isValid() const {
    return center.isValid() && radius>0.0;
}

bool RArc::isFullCircle() const {
    return fabs(RMath::getAngleDifference180(
                    RMath::getNormalizedAngle(startAngle),
                    RMath::getNormalizedAngle(endAngle))) < RS::AngleTolerance;
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
        //this.error = qsTr("No arc possible");
        return RArc();
    }

    RVector center = ips[0];
    double radius = center.getDistanceTo(endPoint);
    double angle1 = center.getAngleTo(startPoint);
    double angle2 = center.getAngleTo(endPoint);
    bool reversed = RMath::isAngleBetween(center.getAngleTo(point),
                                            angle1, angle2, true);

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

    double wu = fabs(RMath::pow(arc.radius, 2.0) - RMath::pow(dist, 2.0));
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

RArc RArc::createTangential(const RVector& startPoint, const RVector& pos,
                            double direction, double radius) {
    RArc arc;

    arc.radius = radius;

    // orthogonal to base entity:
    RVector ortho;
    ortho.setPolar(radius, direction + M_PI/2.0);

    // two possible center points for arc:
    RVector center1 = startPoint + ortho;
    RVector center2 = startPoint - ortho;
    if (center1.getDistanceTo(pos) < center2.getDistanceTo(pos)) {
        arc.center = center1;
    } else {
        arc.center = center2;
    }

    // angles:
    arc.startAngle = arc.center.getAngleTo(startPoint);
    arc.endAngle = arc.center.getAngleTo(pos);

    // handle arc direction:
    arc.reversed = false;
    double diff = RMath::getNormalizedAngle(arc.getDirection1() - direction);
    if (fabs(diff-M_PI) < 1.0e-1) {
        arc.reversed = true;
    }

    return arc;
}

double RArc::getDirection1() const{
    if (!reversed) {
        return RMath::getNormalizedAngle(startAngle+M_PI/2.0);
    }
    else {
        return RMath::getNormalizedAngle(startAngle-M_PI/2.0);
    }
}

double RArc::getDirection2() const{
    if (!reversed) {
        return RMath::getNormalizedAngle(endAngle-M_PI/2.0);
    }
    else {
        return RMath::getNormalizedAngle(endAngle+M_PI/2.0);
    }
}

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

void RArc::moveStartPoint(const RVector& pos) {
    double bulge = getBulge();

    // full circle: trim instead of move:
    if (bulge < 1.0e-6 || bulge > 1.0e6) {
        startAngle = center.getAngleTo(pos);
    }
    else {
        *this = RArc::createFrom2PBulge(pos, getEndPoint(), bulge);
    }
}

void RArc::moveEndPoint(const RVector& pos) {
    double bulge = getBulge();

    // full circle: trim instead of move:
    if (bulge < 1.0e-6 || bulge > 1.0e6) {
        endAngle = center.getAngleTo(pos);
    }
    else {
        *this = RArc::createFrom2PBulge(getStartPoint(), pos, bulge);
    }
}

double RArc::getBulge() const {
    //qDebug() << "sweep: " << getSweep();
    double bulge = tan(fabs(getSweep()) / 4.0);
    if (isReversed()) {
        bulge *= -1;
    }
    return bulge;
}

double RArc::getLength() const {
    return fabs(getAngleLength(false)) * radius;
}

double RArc::getDiameter() const {
    return 2*radius;
}

void RArc::setDiameter(double d) {
    radius = d/2.0;
}

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

double RArc::getArea() const {
    return (radius*radius*getAngleLength(false)) / 2.0;
}

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
        if (ret < RS::PointTolerance) {
            ret = 2 * M_PI;
        }
    }
    else {
        if (ret > 2 * M_PI - RS::PointTolerance) {
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

void RArc::setSweep(double s) {
    endAngle = startAngle + s;
    reversed = (s<0.0);
}

RVector RArc::getCenter() const{
    return center;
}

void RArc::setCenter(const RVector& vector) {
    center = vector;
}

double RArc::getRadius() const{
    return radius;
}

void RArc::setRadius(double r) {
    radius = r;
}

double RArc::getStartAngle() const {
    return startAngle;
}

void RArc::setStartAngle(double a) {
    startAngle = RMath::getNormalizedAngle(a);
}

double RArc::getEndAngle() const {
    return endAngle;
}

void RArc::setEndAngle(double a) {
    endAngle = RMath::getNormalizedAngle(a);
}

RVector RArc::getMiddlePoint() const {
    double a;
    a = startAngle + getSweep()/2.0;
    RVector v = RVector::createPolar(radius, a);
    v+=center;
    return v;
}

RVector RArc::getStartPoint() const {
    return getPointAtAngle(startAngle);
}

RVector RArc::getEndPoint() const {
    return getPointAtAngle(endAngle);
}

RVector RArc::getPointAtAngle(double a) const {
    return RVector(center.x + cos(a) * radius, center.y + sin(a) * radius);
}

double RArc::getAngleAt(double distance, RS::From from) const {
    QList<RVector> points = getPointsWithDistanceToEnd(distance, from);
    if (points.length()!=1) {
        return RNANDOUBLE;
    }
    return center.getAngleTo(points[0]) + (reversed ? -M_PI/2 : M_PI/2);
}

bool RArc::isReversed() const {
    return reversed;
}

void RArc::setReversed(bool r) {
    reversed = r;
}

RBox RArc::getBoundingBox() const {
    RVector minV;
    RVector maxV;
    double minX = qMin(getStartPoint().x, getEndPoint().x);
    double minY = qMin(getStartPoint().y, getEndPoint().y);
    double maxX = qMax(getStartPoint().x, getEndPoint().x);
    double maxY = qMax(getStartPoint().y, getEndPoint().y);

    if (getStartPoint().getDistanceTo(getEndPoint()) < 1.0e-6 && getRadius()
            > 1.0e5) {
        minV = RVector(minX, minY);
        maxV = RVector(maxX, maxY);
        return RBox(minV, maxV);
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

    minV = RVector(minX, minY);
    maxV = RVector(maxX, maxY);

    return RBox(minV, maxV);
}

QList<RVector> RArc::getEndPoints() const {
    QList<RVector> ret;
    ret.append(getStartPoint());
    ret.append(getEndPoint());
    return ret;
}

QList<RVector> RArc::getMiddlePoints() const {
    QList<RVector> ret;
    ret.append(getMiddlePoint());
    return ret;
}

QList<RVector> RArc::getCenterPoints() const {
    QList<RVector> ret;
    ret.append(getCenter());
    return ret;
}

QList<RVector> RArc::getPointsWithDistanceToEnd(double distance, RS::From from) const {
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

RVector RArc::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    Q_UNUSED(strictRange)

    double angle = center.getAngleTo(point);
    if (limited
            && !RMath::isAngleBetween(angle, startAngle, endAngle, reversed)) {
        return RVector::invalid;
    }

    RVector v = point - center;
    return RVector::createPolar(v.getMagnitude() - radius, v.getAngle());
}

bool RArc::move(const RVector& offset) {
    if (!offset.isValid() || offset.getMagnitude() < RS::PointTolerance) {
        return false;
    }
    center += offset;
    return true;
}

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

bool RArc::scale(const RVector& scaleFactors, const RVector& c) {
    // negative scaling: mirroring and scaling
    if (scaleFactors.x < 0.0) {
        mirror(RLine(center, center + RVector(0.0, 1.0)));
    }
    if (scaleFactors.y < 0.0) {
        mirror(RLine(center, center + RVector(1.0, 0.0)));
    }

    center.scale(scaleFactors, c);
    radius *= scaleFactors.x;
    if (radius < 0.0) {
        radius *= -1.0;
    }

    return true;
}

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

bool RArc::reverse() {
    double a = startAngle;
    startAngle = endAngle;
    endAngle = a;
    reversed = !reversed;
    return true;
}

bool RArc::stretch(const RPolyline& area, const RVector& offset) {
    bool ret = false;

    if (area.contains(getStartPoint()) && area.contains(getEndPoint())) {
        return move(offset);
    }

    if (area.contains(getStartPoint())) {
        moveStartPoint(getStartPoint() + offset);
        ret = true;
    }
    else if (area.contains(getEndPoint())) {
        moveEndPoint(getEndPoint() + offset);
        ret = true;
    }

    return ret;
}

/**
 * \todo Not working as expected, fix or disable
 */
QSharedPointer<RShape> RArc::getTransformed(const QTransform& transform) const {
    RVector ct = center.getTransformed2d(transform);
    RVector sp = getStartPoint();
    RVector spt = sp.getTransformed2d(transform);
    RVector ep = getEndPoint();
    RVector ept = ep.getTransformed2d(transform);
    //RVector mp = getMiddlePoint();
    //RVector mpt = mp.getTransformed2d(transform);

    RArc* ret = new RArc(
            ct,
            ct.getDistanceTo(spt),
            ct.getAngleTo(spt),
            ct.getAngleTo(ept),
            reversed
        );

//    if (!ret->getMiddlePoint().equalsFuzzy(mpt)) {
//        ret->setReversed(!reversed);
//    }

    return QSharedPointer<RShape>(ret);
}

RS::Ending RArc::getTrimEnd(const RVector& coord, const RVector& trimPoint) {
    double angEl = center.getAngleTo(trimPoint);
    double angM = center.getAngleTo(coord);

    if (RMath::getAngleDifference(angM, angEl)>M_PI) {
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

void RArc::trimStartPoint(const RVector& p) {
    startAngle = center.getAngleTo(p);
}

void RArc::trimEndPoint(const RVector& p) {
    endAngle = center.getAngleTo(p);
}

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

RPolyline RArc::approximateWithLines(double segmentLength) {
    RPolyline polyline;

    // avoid a segment length of 0:
    if (segmentLength<1.0e-6) {
        segmentLength = 1.0e-6;
    }

    double a1 = getStartAngle();
    double a2 = getEndAngle();
    double aStep = segmentLength / radius;
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


void RArc::print(QDebug dbg) const {
    dbg.nospace() << "RArc(";
    RShape::print(dbg);
    dbg.nospace() << ", center: " << getCenter()
                  << ", radius: " << getRadius()
                  << ", startAngle: " << getStartAngle()
                  << ", endAngle: " << getEndAngle()
                  << ", startPoint: " << getStartPoint()
                  << ", endPoint: " << getEndPoint()
                  << ", sweep: " << getSweep()
                  << ", reversed: " << isReversed()
                  << ")";
}
