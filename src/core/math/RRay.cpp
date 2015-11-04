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
#include "RBox.h"
#include "RPolyline.h"
#include "RRay.h"

/**
 * Creates a ray object with invalid start and end points.
 */
RRay::RRay() :
    RXLine() {
}

RRay::RRay(const RLine& line) :
    RXLine(line) {
}

/**
 * Creates a ray object with the given base point and direction.
 */
RRay::RRay(const RVector& basePoint, const RVector& directionVector) :
    RXLine(basePoint, directionVector) {
}

RRay::RRay(const RVector& basePoint, double angle, double distance) :
    RXLine(basePoint, angle, distance) {
}

RRay::~RRay() {
}

RVector RRay::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    if (!limited) {
        return RXLine::getVectorTo(point, false, strictRange);
    }
    else {
        RVector p = RXLine::getClosestPointOnShape(point, false);
        if (fabs(RMath::getAngleDifference180(getDirection1(), getStartPoint().getAngleTo(p))) < 0.1) {
            return point-p;
        }
        return RVector::invalid;
    }
}

bool RRay::reverse() {
    return false;
}

RLine RRay::getClippedLine(const RBox& box) const {
    RLine ret = RXLine::getClippedLine(box);

    if (box.contains(getBasePoint())) {
        ret.setStartPoint(getBasePoint());
    }

    if (!RMath::isSameDirection(getDirection1(), getBasePoint().getAngleTo(ret.getEndPoint()), 0.1)) {
        ret = getLineShape();
    }

    return ret;
}

void RRay::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint) {
    Q_UNUSED(clickPoint)
    RVector tp = getClosestPointOnShape(trimPoint, false);
    directionVector = tp - basePoint;
}

QList<RVector> RRay::getPointsWithDistanceToEnd(double distance, RS::From from) const {
    QList<RVector> ret;
    double a1 = getAngle();

    RVector dv;
    dv.setPolar(distance, a1);

    if (from&RS::FromStart) {
        ret.append(basePoint + dv);
    }

    return ret;
}

bool RRay::stretch(const RPolyline& area, const RVector& offset) {
    bool ret = false;

    if (area.contains(basePoint)) {
        basePoint += offset;
        ret = true;
    }

    return ret;
}

void RRay::print(QDebug dbg) const {
//    dbg.nospace() << "RRay("
//        << startPoint.x << "," << startPoint.y << " - "
//        << endPoint.x << "," << endPoint.y << ")";
    dbg.nospace() << "RRay(";
    RShape::print(dbg);
    dbg.nospace() << ", basePoint: " << getBasePoint()
                  << ", directionVector: " << getDirectionVector() << ")";
}
