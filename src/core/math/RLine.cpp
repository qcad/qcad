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

#include "RLine.h"
#include "RBox.h"
#include "RPolyline.h"

/**
 * Creates a line object with invalid start and end points.
 */
RLine::RLine() :
    startPoint(RVector::invalid),
    endPoint(RVector::invalid) {
}

RLine::RLine(double x1, double y1, double x2, double y2) :
    startPoint(x1, y1),
    endPoint(x2, y2) {
}

/**
 * Creates a line object with the given start and end point.
 */
RLine::RLine(const RVector& startPoint, const RVector& endPoint) :
    startPoint(startPoint),
    endPoint(endPoint) {
}

RLine::RLine(const RVector& startPoint, double angle, double distance) :
    startPoint(startPoint) {

    endPoint = startPoint + RVector::createPolar(distance, angle);
}

void RLine::setZ(double z) {
    startPoint.z = z;
    endPoint.z = z;
}

QList<RVector> RLine::getVectorProperties() const {
    return QList<RVector>() << startPoint << endPoint;
}

bool RLine::isValid() const {
    return startPoint.isSane() && endPoint.isSane();
}

double RLine::getLength() const {
    return startPoint.getDistanceTo(endPoint);
}

void RLine::setLength(double l, bool fromStart) {
    if (fromStart) {
        endPoint = startPoint + RVector::createPolar(l, getAngle());
    }
    else {
        startPoint = endPoint - RVector::createPolar(l, getAngle());
    }
}

double RLine::getAngle() const {
    return startPoint.getAngleTo(endPoint);
}

void RLine::setAngle(double a) {
    endPoint = startPoint + RVector::createPolar(getLength(), a);
}

bool RLine::isParallel(const RLine& line) const {
    double a = getAngle();
    double oa = line.getAngle();

    return RMath::isSameDirection(a, oa) || RMath::isSameDirection(a, oa + M_PI);
}

/**
 * \return True if the line is vertical.
 * If the start and end points of the line are identical, the line is both vertical and horizontal.
 */
bool RLine::isVertical(double tolerance) const {
    return RMath::fuzzyCompare(startPoint.x, endPoint.x, tolerance);
}

/**
 * \return True if the line is horizontal.
 * If the start and end points of the line are identical, the line is both vertical and horizontal.
 */
bool RLine::isHorizontal(double tolerance) const {
    return RMath::fuzzyCompare(startPoint.y, endPoint.y, tolerance);
}

double RLine::getDirection1() const {
    return startPoint.getAngleTo(endPoint);
}

double RLine::getDirection2() const {
    return endPoint.getAngleTo(startPoint);
}

RVector RLine::getStartPoint() const {
    return startPoint;
}

void RLine::setStartPoint(const RVector& vector) {
    startPoint = vector;
}

RVector RLine::getEndPoint() const {
    return endPoint;
}

void RLine::setEndPoint(const RVector& vector) {
    endPoint = vector;
}

RVector RLine::getMiddlePoint() const {
    return (startPoint + endPoint) / 2.0;
}

RBox RLine::getBoundingBox() const {
    return RBox(RVector::getMinimum(startPoint, endPoint), RVector::getMaximum(
            startPoint, endPoint));
}

QList<RVector> RLine::getEndPoints() const {
    QList<RVector> ret;
    ret.append(startPoint);
    ret.append(endPoint);
    return ret;
}

QList<RVector> RLine::getMiddlePoints() const {
    QList<RVector> ret;
    ret.append(getMiddlePoint());
    return ret;
}

QList<RVector> RLine::getCenterPoints() const {
    return getMiddlePoints();
}

QList<RVector> RLine::getPointsWithDistanceToEnd(double distance, int from) const {
    QList<RVector> ret;

    if (from&RS::FromStart) {
        RVector normalStart = (endPoint-startPoint).getNormalized();
        ret.append(startPoint + normalStart*distance);
    }
    if (from&RS::FromEnd) {
        RVector normalEnd = (startPoint-endPoint).getNormalized();
        ret.append(endPoint + normalEnd*distance);
    }

    return ret;
}

QList<RVector> RLine::getPointCloud(double segmentLength) const {
    Q_UNUSED(segmentLength)
    QList<RVector> ret;
    ret.append(startPoint);
    for (double d = segmentLength; d<getLength(); d+=segmentLength) {
        ret.append(getPointWithDistanceToStart(d));
    }
    ret.append(endPoint);
    return ret;
}

double RLine::getAngleAt(double distance, RS::From from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    return getAngle();
}

RVector RLine::getVectorTo(const RVector& point, bool limited, double strictRange) const {

    RVector ae = endPoint - startPoint;
    RVector ap = point - startPoint;

    if (ae.getMagnitude2D() < 1.0e-6) {
        return RVector::invalid;
    }

    if (ap.getMagnitude2D() < 1.0e-6) {
        // distance to start point is very small:
        return RVector(0,0);
    }

    double b = RVector::getDotProduct(ap, ae) / RVector::getDotProduct(ae, ae);

    if (limited && (b < 0 || b > 1.0)) {
        // orthogonal to line does not cross line, use distance to end point:
        RVector ret = getVectorFromEndpointTo(point);
        if (ret.getMagnitude()<strictRange) {
            return ret;
        }
        else {
            // not within given range:
            return RVector::invalid;
        }
    }

    RVector closestPoint = startPoint + ae * b;

    return point - closestPoint;
}

RS::Side RLine::getSideOfPoint(const RVector& point) const {
    double entityAngle = getAngle();
    double angleToCoord = startPoint.getAngleTo(point);
    double angleDiff = RMath::getAngleDifference(entityAngle, angleToCoord);

    if (angleDiff<M_PI) {
        return RS::LeftHand;
    }
    else {
        return RS::RightHand;
    }
}


void RLine::clipToXY(const RBox& box) {
    double x1 = startPoint.x;
    double y1 = startPoint.y;
    double x2 = endPoint.x;
    double y2 = endPoint.y;
    double xmin = box.getMinimum().x;
    double ymin = box.getMinimum().y;
    double xmax = box.getMaximum().x;
    double ymax = box.getMaximum().y;

    double deltaX, deltaY, p, q;
    double u1 = 0.0, u2 = 1.0;
    double r;

    deltaX = (x2 - x1);
    deltaY = (y2 - y1);

    // left edge, right edge, bottom edge and top edge checking
    double pPart[] = {-1 * deltaX, deltaX, -1 * deltaY, deltaY};
    double qPart[] = {x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};

    bool accept = true;

    for (int i=0; i<4; i++) {
        p = pPart[i];
        q = qPart[i];

        if (p==0 && q<0) {
            accept = false;
            break;
        }

        r = q/p;

        if (p<0) {
            u1=qMax(u1, r);
        }

        if (p>0) {
            u2 = qMin(u2, r);
        }

        if (u1>u2) {
            accept = false;
            break;
        }
    }

    if (accept) {
        if (u2 < 1) {
            x2 = x1 + u2 * deltaX;
            y2 = y1 + u2 * deltaY;
        }
        if (u1 > 0) {
            x1 = x1 + u1 * deltaX;
            y1 = y1 + u1 * deltaY;
        }

        startPoint = RVector(x1, y1);
        endPoint = RVector(x2, y2);
    }
    else {
        startPoint = RVector::invalid;
        endPoint = RVector::invalid;
    }
}

bool RLine::move(const RVector& offset) {
    if (!offset.isValid() || offset.getMagnitude() < RS::PointTolerance) {
        return false;
    }
    startPoint += offset;
    endPoint += offset;
    return true;
}

bool RLine::rotate(double rotation, const RVector& center) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    startPoint.rotate(rotation, center);
    endPoint.rotate(rotation, center);
    return true;
}

bool RLine::scale(const RVector& scaleFactors, const RVector& center) {
    startPoint.scale(scaleFactors, center);
    endPoint.scale(scaleFactors, center);
    return true;
}

bool RLine::mirror(const RLine& axis) {
    startPoint.mirror(axis);
    endPoint.mirror(axis);
    return true;
}

bool RLine::flipHorizontal() {
    startPoint.flipHorizontal();
    endPoint.flipHorizontal();
    return true;
}

bool RLine::flipVertical() {
    startPoint.flipVertical();
    endPoint.flipVertical();
    return true;
}

bool RLine::reverse() {
    RVector v = startPoint;
    startPoint = endPoint;
    endPoint = v;
    return true;
}

bool RLine::stretch(const RPolyline& area, const RVector& offset) {
    bool ret = false;

    if (area.contains(startPoint, true)) {
        startPoint += offset;
        ret = true;
    }
    if (area.contains(endPoint, true)) {
        endPoint += offset;
        ret = true;
    }

    return ret;
}

bool RLine::moveTo(const RVector& dest) {
    RVector offset = dest - startPoint;
    return move(offset);
}

QSharedPointer<RShape> RLine::getTransformed(const QTransform& transform) const {
    return QSharedPointer<RShape>(new RLine(startPoint.getTransformed2D(transform), endPoint.getTransformed2D(transform)));
}

RS::Ending RLine::getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
    double lineAngle = getAngle();
    double angleToClickPoint = trimPoint.getAngleTo(clickPoint);
    double angleDifference = lineAngle-angleToClickPoint;

    if (angleDifference<0.0) {
        angleDifference*=-1.0;
    }
    if (angleDifference>M_PI) {
        angleDifference=2*M_PI-angleDifference;
    }

    if (angleDifference<M_PI/2.0) {
        return RS::EndingStart;
    } else {
        return RS::EndingEnd;
    }
}

bool RLine::trimStartPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    RVector tp = getClosestPointOnShape(trimPoint, false);
    if (!tp.isValid()) {
        return false;
    }
    setStartPoint(tp);
    return true;
}

bool RLine::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    RVector tp = getClosestPointOnShape(trimPoint, false);
    if (!tp.isValid()) {
        return false;
    }
    setEndPoint(tp);
    return true;
}

double RLine::getDistanceFromStart(const RVector& p) const {
    double ret = startPoint.getDistanceTo(p);

    RVector p2 = getClosestPointOnShape(p, false);
    double angle = startPoint.getAngleTo(p2);
    if (RMath::isSameDirection(getAngle(), angle, M_PI/2)) {
        return ret;
    }
    else {
        return -ret;
    }
}

QList<QSharedPointer<RShape> > RLine::splitAt(const QList<RVector>& points) const {
    if (points.length()==0) {
        return RShape::splitAt(points);
    }

    QList<QSharedPointer<RShape> > ret;

    QList<RVector> sortedPoints = RVector::getSortedByDistance(points, startPoint);

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

        ret.append(QSharedPointer<RShape>(new RLine(sortedPoints[i], sortedPoints[i+1])));
    }

    return ret;
}

void RLine::print(QDebug dbg) const {
//    dbg.nospace() << "RLine("
//        << startPoint.x << "," << startPoint.y << " - "
//        << endPoint.x << "," << endPoint.y << ")";
    dbg.nospace() << "RLine(";
    RShape::print(dbg);
    dbg.nospace() << ", startPoint: " << getStartPoint() << ", endPoint: "
            << getEndPoint() << ")";
}
