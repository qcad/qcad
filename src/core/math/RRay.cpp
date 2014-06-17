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

RVector RRay::getVectorTo(const RVector& point, bool limited) const {
    if (!limited) {
        return RXLine::getVectorTo(point, false);
    }
    else {
        RVector p = RXLine::getClosestPointOnShape(point, false);
        if (fabs(RMath::getAngleDifference180(getDirection1(), getStartPoint().getAngleTo(p))) < 0.1) {
            return p-point;
        }
        return RVector::invalid;
    }
}

bool RRay::reverse() {
    return false;
}

RLine RRay::getClippedLine(const RBox& box) const {
    RLine ret = RXLine::getClippedLine(box);
    ret.setStartPoint(getBasePoint());
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
