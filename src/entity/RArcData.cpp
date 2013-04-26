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
#include "RArcData.h"
#include "RArcEntity.h"

RArcData::RArcData() {
}

RArcData::RArcData(const RArc& arc) : RArc(arc) {
}

RArcData::RArcData(RDocument* document, const RArcData& data) {
    *this = data;
    this->document = document;
}

RArcData::RArcData(const RVector& center, double radius, double startAngle,
        double endAngle, bool reversed) :
    RArc(center, radius, startAngle, endAngle, reversed) {
}

QList<RVector> RArcData::getReferencePoints(
        RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RVector> ret;
    ret.append(center);
    ret.append(getStartPoint());
    ret.append(getEndPoint());

    QList<RVector> p;
    p.append(center + RVector(radius, 0));
    p.append(center + RVector(0, radius));
    p.append(center - RVector(radius, 0));
    p.append(center - RVector(0, radius));

    for (int i=0; i<p.size(); i++) {
        if (RMath::isAngleBetween(center.getAngleTo(p[i]), startAngle, endAngle, reversed)) {
            ret.append(p[i]);
        }
    }

    return ret;
}

bool RArcData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {
    bool ret = false;
    if (referencePoint.equals(center)) {
        center = targetPoint;
        ret = true;
    } else if (referencePoint.equals(getStartPoint())) {
        moveStartPoint(targetPoint);
        ret = true;
    } else if (referencePoint.equals(getEndPoint())) {
        moveEndPoint(targetPoint);
        ret = true;
    }
    else if (referencePoint.equals(center + RVector(radius, 0)) ||
             referencePoint.equals(center + RVector(0, radius)) ||
             referencePoint.equals(center - RVector(radius, 0)) ||
             referencePoint.equals(center - RVector(0, radius))) {
        radius = center.getDistanceTo(targetPoint);
        ret = true;
    }
    return ret;
}
