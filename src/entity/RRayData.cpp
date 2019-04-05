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
#include "RRayData.h"
#include "RLineEntity.h"

RRayData::RRayData() {
}

RRayData::RRayData(RDocument* document, const RRayData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RRayData::RRayData(const RRay &ray) :
    RRay(ray) {
}

RRayData::RRayData(const RVector& basePoint, const RVector& dir) :
    RRay(basePoint, dir) {
}

QList<RRefPoint> RRayData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    ret.append(basePoint);
    ret.append(getSecondPoint());
    return ret;
}

bool RRayData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;
    if (referencePoint.equalsFuzzy(basePoint)) {
        basePoint = targetPoint;
        ret = true;
    }
    if (referencePoint.equalsFuzzy(getSecondPoint())) {
        setSecondPoint(targetPoint);
        ret = true;
    }
    return ret;
}
