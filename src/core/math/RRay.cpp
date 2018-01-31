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

QList<RVector> RRay::getVectorProperties() const {
    return QList<RVector>() << basePoint << directionVector;
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

bool RRay::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    Q_UNUSED(clickPoint)
    Q_UNUSED(extend)
    RVector tp = getClosestPointOnShape(trimPoint, false);
    if (!tp.isValid()) {
        return false;
    }
    directionVector = tp - basePoint;
    return true;
}

QList<RVector> RRay::getPointsWithDistanceToEnd(double distance, int from) const {
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

    if (area.contains(basePoint, true)) {
        basePoint += offset;
        ret = true;
    }

    return ret;
}

QList<QSharedPointer<RShape> > RRay::splitAt(const QList<RVector>& points) const {
    if (points.length()==0) {
        return RShape::splitAt(points);
    }

    QList<QSharedPointer<RShape> > ret;

    QList<RVector> sortedPoints = RVector::getSortedByDistance(points, basePoint);

    if (!basePoint.equalsFuzzy(sortedPoints[0])) {
        sortedPoints.prepend(basePoint);
    }

    for (int i=0; i<sortedPoints.length()-1; i++) {
        if (sortedPoints[i].equalsFuzzy(sortedPoints[i+1])) {
            continue;
        }

        ret.append(QSharedPointer<RShape>(new RLine(sortedPoints[i], sortedPoints[i+1])));
    }

    ret.append(QSharedPointer<RShape>(new RRay(sortedPoints[sortedPoints.length()-1], directionVector)));

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
