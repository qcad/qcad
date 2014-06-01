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

RLine::~RLine() {
}

void RLine::to2D() {
    startPoint.z = 0.0;
    endPoint.z = 0.0;
}

bool RLine::isValid() const {
    return startPoint.isValid() && endPoint.isValid();
}

double RLine::getLength() const {
    return startPoint.getDistanceTo(endPoint);
}

void RLine::setLength(double l) {
    endPoint = startPoint + RVector::createPolar(l, getAngle());
}

double RLine::getAngle() const {
    return startPoint.getAngleTo(endPoint);
}

void RLine::setAngle(double a) {
    endPoint = startPoint + RVector::createPolar(getLength(), a);
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

QList<RVector> RLine::getPointsWithDistanceToEnd(double distance, RS::From from) const {
    QList<RVector> ret;
    double a1 = getAngle();

    RVector dv;
    dv.setPolar(distance, a1);

    if (from==RS::FromStart || from==RS::FromAny) {
        ret.append(startPoint + dv);
    }

    if (from==RS::FromEnd || from==RS::FromAny) {
        ret.append(endPoint - dv);
    }

    return ret;
}

RVector RLine::getVectorTo(const RVector& point, bool limited) const {

    RVector ae = endPoint - startPoint;
    RVector ap = point - startPoint;

    if (ae.getMagnitude2d() < 1.0e-6) {
        return RVector::invalid;
    }

    double b = RVector::getDotProduct(ap, ae) / RVector::getDotProduct(ae, ae);

    if (limited && (b < 0 || b > 1.0)) {
        return getVectorFromEndpointTo(point);
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


void RLine::clipToXY(const RBox& box, bool isXLine) {
    if (isXLine) {
        RPolyline pl = box.getPolyline2d();

        QList<RVector> ips = RShape::getIntersectionPointsLX(*this, pl, false);
        QList<RVector> sol;
        for (int i=0; i<ips.length(); i++) {
            if (pl.isOnShape(ips[i])) {
                sol.append(ips[i]);
            }
        }

        if (sol.length()==2) {
            RLine ret = RLine(sol[0], sol[1]);
            double diff = RMath::getAngleDifference180(ret.getAngle(), getAngle());
            *this = ret;
            if (fabs(diff) > 1.0e-2) {
                reverse();
            }
        }
        return;
    }

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

    if (area.contains(startPoint)) {
        startPoint += offset;
        ret = true;
    }
    if (area.contains(endPoint)) {
        endPoint += offset;
        ret = true;
    }

    return ret;
}

QSharedPointer<RShape> RLine::getTransformed(const QTransform& transform) const {
    return QSharedPointer<RShape>(new RLine(startPoint.getTransformed2d(transform), endPoint.getTransformed2d(transform)));
}

RS::Ending RLine::getTrimEnd(const RVector& coord, const RVector& trimPoint) {
    double angEl = getAngle();
    double angM = trimPoint.getAngleTo(coord);
    double angDif = angEl-angM;

    if (angDif<0.0) {
        angDif*=-1.0;
    }
    if (angDif>M_PI) {
        angDif=2*M_PI-angDif;
    }

    if (angDif<M_PI/2.0) {
        return RS::EndingStart;
    } else {
        return RS::EndingEnd;
    }
}

void RLine::trimStartPoint(const RVector& p) {
    RVector tp = getClosestPointOnShape(p, false);
    setStartPoint(tp);
}

void RLine::trimEndPoint(const RVector& p) {
    RVector tp = getClosestPointOnShape(p, false);
    setEndPoint(tp);
}

double RLine::getDistanceFromStart(const RVector& p) const {
    return startPoint.getDistanceTo(p);
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
