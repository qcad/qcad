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

QList<RRefPoint> RArcData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    ret.append(RRefPoint(center, RRefPoint::Center));
    ret.append(RRefPoint(getStartPoint(), RRefPoint::Start));
    ret.append(RRefPoint(getEndPoint(), RRefPoint::End));
    ret.append(RRefPoint(getMiddlePoint(), RRefPoint::Secondary));

    QList<RRefPoint> p;
    p.append(RRefPoint(center + RVector(radius, 0), RRefPoint::Tertiary));
    p.append(RRefPoint(center + RVector(0, radius), RRefPoint::Tertiary));
    p.append(RRefPoint(center - RVector(radius, 0), RRefPoint::Tertiary));
    p.append(RRefPoint(center - RVector(0, radius), RRefPoint::Tertiary));

    for (int i=0; i<p.size(); i++) {
        if (RMath::isAngleBetween(center.getAngleTo(p[i]), startAngle, endAngle, reversed)) {
            ret.append(p[i]);
        }
    }

    return ret;
}

bool RArcData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;
    if (referencePoint.equalsFuzzy(center)) {
        center = targetPoint;
        ret = true;
    } else if (referencePoint.equalsFuzzy(getStartPoint())) {
        moveStartPoint(targetPoint);
        ret = true;
    } else if (referencePoint.equalsFuzzy(getEndPoint())) {
        moveEndPoint(targetPoint);
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(center + RVector(radius, 0)) ||
             referencePoint.equalsFuzzy(center + RVector(0, radius)) ||
             referencePoint.equalsFuzzy(center - RVector(radius, 0)) ||
             referencePoint.equalsFuzzy(center - RVector(0, radius))) {
        radius = center.getDistanceTo(targetPoint);
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(getMiddlePoint())) {
        moveMiddlePoint(targetPoint);
        ret = true;
    }
    return ret;
}
