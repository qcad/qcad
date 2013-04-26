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
#include "RLineData.h"
#include "RLineEntity.h"

RLineData::RLineData() {
}

RLineData::RLineData(RDocument* document, const RLineData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RLineData::RLineData(const RLine& line) :
    RLine(line) {
}

RLineData::RLineData(const RVector& startPoint, const RVector& endPoint) :
    RLine(startPoint, endPoint) {
}

//RBox RLineData::getBoundingBox() const {
//    return RBox(RVector::getMinimum(startPoint, endPoint), RVector::getMaximum(startPoint, endPoint));
//}

/*
RVector RLineData::getStartPoint() const {
    return RLine::startPoint;
}

RVector RLineData::getEndPoint() const {
    return RLine::endPoint;
}
*/

QList<RVector> RLineData::getReferencePoints(
        RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RVector> ret;
    ret.append(startPoint);
    ret.append(endPoint);
    return ret;
}

/*
QList<RVector> RLineData::getIntersectionPoints(
    const REntityData& other, bool limited) const {

    const RLineData* otherLine = dynamic_cast<const RLineData*>(&other);
    if (otherLine!=NULL) {
//        return RLine::getIntersectionPoints(*otherLine, limited);
        return RShape::getIntersectionPoints(*this, *otherLine, limited);
    }
    // TODO other entity types

    return QList<RVector>();
}

RVector RLineData::getVectorTo(const RVector& point, bool limited) const {
    return RLine::getVectorTo(point, limited);
}

RVector RLineData::getVectorTo(const RLine& line, bool limited) const {
    return RLine::getVectorTo(line, limited);
}

QList<RVector> RLineData::getPointsWithDistanceToEnd(double distance) const {
    return RLine::getPointsWithDistanceToEnd(distance);
}
*/

/*
bool RLineData::intersectsWith(const RTriangle& triangle) const {
    return RLine::intersectsWith(triangle);
}
*/

bool RLineData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {
    bool ret = false;
    if (referencePoint.equalsFuzzy(startPoint)) {
        startPoint = targetPoint;
        ret = true;
    }
    if (referencePoint.equalsFuzzy(endPoint)) {
        endPoint = targetPoint;
        ret = true;
    }
    return ret;
}
