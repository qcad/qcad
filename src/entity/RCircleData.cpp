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
#include "RCircleData.h"
#include "RCircleEntity.h"

RCircleData::RCircleData() {
}

RCircleData::RCircleData(const RCircle& circle) : RCircle(circle) {
}

RCircleData::RCircleData(RDocument* document, const RCircleData& data) {
    *this = data;
    this->document = document;
}

RCircleData::RCircleData(const RVector& center, double radius) :
    RCircle(center, radius) {
}

QList<RRefPoint> RCircleData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    ret.append(RRefPoint(center, RRefPoint::Center));
    ret.append(RRefPoint(center + RVector(radius, 0), RRefPoint::Secondary));
    ret.append(RRefPoint(center + RVector(0, radius), RRefPoint::Secondary));
    ret.append(RRefPoint(center - RVector(radius, 0), RRefPoint::Secondary));
    ret.append(RRefPoint(center - RVector(0, radius), RRefPoint::Secondary));
    return ret;
}

bool RCircleData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;
    if (referencePoint.equalsFuzzy(center)) {
        center = targetPoint;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(center + RVector(radius, 0)) ||
             referencePoint.equalsFuzzy(center + RVector(0, radius)) ||
             referencePoint.equalsFuzzy(center - RVector(radius, 0)) ||
             referencePoint.equalsFuzzy(center - RVector(0, radius))) {
        radius = center.getDistanceTo(targetPoint);
        ret = true;
    }
    return ret;
}
