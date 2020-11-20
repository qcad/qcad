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
#include "RBox.h"
#include "RPolyline.h"
#include "RRay.h"
#include "RXLine.h"

/**
 * Creates an xline object with invalid base point and direction.
 */
RXLine::RXLine() :
    basePoint(RVector::invalid),
    directionVector(RVector::invalid) {
}

RXLine::RXLine(const RLine& line) :
    basePoint(line.getStartPoint()), directionVector(line.getEndPoint()-line.getStartPoint()) {
}

/**
 * Creates an xline object with the given base point and direction.
 */
RXLine::RXLine(const RVector& basePoint, const RVector& directionVector) :
    basePoint(basePoint),
    directionVector(directionVector) {
}

RXLine::RXLine(const RVector& basePoint, double angle, double distance) :
    basePoint(basePoint),
    directionVector(RVector::createPolar(distance, angle)) {
}

RXLine::~RXLine() {
}

RBox RXLine::getBoundingBox() const {
    return RBox(
        RVector::getMinimum(basePoint, getSecondPoint()),
        RVector::getMaximum(basePoint, getSecondPoint())
    );
}

void RXLine::setZ(double z) {
    basePoint.z = z;
    directionVector.z = z;
}

QList<RVector> RXLine::getVectorProperties() const {
    return QList<RVector>() << basePoint << directionVector;
}

double RXLine::getLength() const {
    return RNANDOUBLE;
}

double RXLine::getAngle() const {
    return directionVector.getAngle();
}

void RXLine::setAngle(double a) {
    directionVector.setAngle(a);
}

void RXLine::setLength(double l) {
    Q_UNUSED(l)
    return;
}

double RXLine::getDirection1() const {
    return directionVector.getAngle();
}

double RXLine::getDirection2() const {
    return getSecondPoint().getAngleTo(basePoint);
}

RS::Side RXLine::getSideOfPoint(const RVector& point) const {
    return getLineShape().getSideOfPoint(point);
}

RVector RXLine::getStartPoint() const {
    return basePoint;
}

RVector RXLine::getEndPoint() const {
    return getSecondPoint();
}

bool RXLine::trimStartPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    RVector tp = getClosestPointOnShape(trimPoint, false);
    if (!tp.isValid()) {
        return false;
    }
    basePoint = tp;
    return true;
}

bool RXLine::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    RVector tp = getClosestPointOnShape(trimPoint, false);
    if (!tp.isValid()) {
        return false;
    }
    basePoint = tp;
    directionVector = -directionVector;
    return true;
}

RS::Ending RXLine::getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
    return getLineShape().getTrimEnd(trimPoint, clickPoint);
}

double RXLine::getDistanceFromStart(const RVector& p) const {
    double ret = basePoint.getDistanceTo(p);

    RVector p2 = getClosestPointOnShape(p, false);
    double angle = basePoint.getAngleTo(p2);
    if (RMath::isSameDirection(getAngle(), angle, M_PI/2)) {
        return ret;
    }
    else {
        return -ret;
    }
}

RVector RXLine::getBasePoint() const {
    return basePoint;
}

void RXLine::setBasePoint(const RVector& vector) {
    basePoint = vector;
}

RVector RXLine::getSecondPoint() const {
    return basePoint + directionVector;
}

void RXLine::setSecondPoint(const RVector& vector) {
    directionVector = vector - basePoint;
}

RVector RXLine::getDirectionVector() const {
    return directionVector;
}

void RXLine::setDirectionVector(const RVector& vector) {
    directionVector = vector;
}

RVector RXLine::getMiddlePoint() const {
    return RVector::invalid;
}

QList<RVector> RXLine::getEndPoints() const {
    return QList<RVector>();
}

QList<RVector> RXLine::getMiddlePoints() const {
    return QList<RVector>();
}

QList<RVector> RXLine::getCenterPoints() const {
    return QList<RVector>();
}

QList<RVector> RXLine::getPointsWithDistanceToEnd(double distance, int from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)
    return QList<RVector>();
}

QList<RVector> RXLine::getPointCloud(double segmentLength) const {
    Q_UNUSED(segmentLength)
    return QList<RVector>();
}

double RXLine::getAngleAt(double distance, RS::From from) const {
    Q_UNUSED(distance)
    Q_UNUSED(from)

    return getAngle();
}

RVector RXLine::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    Q_UNUSED(limited)
    return getLineShape().getVectorTo(point, false, strictRange);
}

RLine RXLine::getClippedLine(const RBox& box) const {
    RLine ret = getLineShape();

    RPolyline pl = box.getPolyline2d();

    QList<RVector> ips = RShape::getIntersectionPointsLX(getLineShape(), pl, false);
    QList<RVector> sol;
    for (int i=0; i<ips.length(); i++) {
        if (pl.isOnShape(ips[i])) {
            RVector p = ips[i].getClosest(sol);
            if (p.equalsFuzzy(ips[i])) {
                continue;
            }
            sol.append(ips[i]);
        }
    }

    if (sol.length()==2) {
        ret = RLine(sol[0], sol[1]);
        if (!RMath::isSameDirection(ret.getDirection1(), getDirection1(), 1.0e-2)) {
            ret.reverse();
        }
    }

    return ret;
}

bool RXLine::move(const RVector& offset) {
    if (!offset.isValid() || offset.getMagnitude() < RS::PointTolerance) {
        return false;
    }
    basePoint += offset;
    return true;
}

bool RXLine::rotate(double rotation, const RVector& center) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    basePoint.rotate(rotation, center);
    directionVector.rotate(rotation);
    return true;
}

bool RXLine::scale(const RVector& scaleFactors, const RVector& center) {
    basePoint.scale(scaleFactors, center);
    directionVector.scale(scaleFactors);
    return true;
}

bool RXLine::mirror(const RLine& axis) {
    RVector sp = getSecondPoint();
    basePoint.mirror(axis);
    sp.mirror(axis);
    setSecondPoint(sp);
    return true;
}

bool RXLine::reverse() {
    RVector sp = getSecondPoint();
    RVector bp = basePoint;
    setBasePoint(sp);
    setSecondPoint(bp);
    return true;
}

bool RXLine::stretch(const RPolyline& area, const RVector& offset) {
    Q_UNUSED(area)
    Q_UNUSED(offset)

    return false;
}

QSharedPointer<RShape> RXLine::getTransformed(const QTransform& transform) const {
    QSharedPointer<RShape> line = getLineShape().getTransformed(transform);
    return QSharedPointer<RShape>(new RXLine(*line.dynamicCast<RLine>()));
}

QList<QSharedPointer<RShape> > RXLine::splitAt(const QList<RVector>& points) const {
    if (points.length()==0) {
        return RShape::splitAt(points);
    }

    QList<QSharedPointer<RShape> > ret;

    QList<RVector> sortedPoints = RVector::getSortedByDistance(points, basePoint - directionVector*1e9);

    ret.append(QSharedPointer<RShape>(new RRay(sortedPoints[0], -directionVector)));

    for (int i=0; i<sortedPoints.length()-1; i++) {
        if (sortedPoints[i].equalsFuzzy(sortedPoints[i+1])) {
            continue;
        }

        ret.append(QSharedPointer<RShape>(new RLine(sortedPoints[i], sortedPoints[i+1])));
    }

    ret.append(QSharedPointer<RShape>(new RRay(sortedPoints[sortedPoints.length()-1], directionVector)));

    return ret;
}

void RXLine::print(QDebug dbg) const {
//    dbg.nospace() << "RXLine("
//        << startPoint.x << "," << startPoint.y << " - "
//        << endPoint.x << "," << endPoint.y << ")";
    dbg.nospace() << "RXLine(";
    RShape::print(dbg);
    dbg.nospace() << ", basePoint: " << getBasePoint()
                  << ", directionVector: " << getDirectionVector() << ")";
}
