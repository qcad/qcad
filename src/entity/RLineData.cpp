/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

RPolyline RLineData::getHull(double offset) const {
    RVector vRight = RVector::createPolar(offset, getAngle()-M_PI/2);

    RPolyline ret;
    ret.appendVertex(startPoint - vRight);
    ret.appendVertex(startPoint + vRight);
    ret.appendVertex(endPoint + vRight);
    ret.appendVertex(endPoint - vRight);
    ret.setClosed(true);

    return ret;
}

QList<RRefPoint> RLineData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    ret.append(startPoint);
    ret.append(endPoint);
    return ret;
}

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
