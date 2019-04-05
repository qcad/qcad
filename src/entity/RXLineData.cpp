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
#include "RXLineData.h"
#include "RLineEntity.h"

RXLineData::RXLineData() {
}

RXLineData::RXLineData(RDocument* document, const RXLineData& data)
    : REntityData(document), fixedAngle(false) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RXLineData::RXLineData(const RXLine &line) :
    RXLine(line), fixedAngle(false) {
}

RXLineData::RXLineData(const RVector& basePoint, const RVector& dir) :
    RXLine(basePoint, dir), fixedAngle(false) {
}

QList<RRefPoint> RXLineData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    ret.append(basePoint);
    if (!hasFixedAngle()) {
        ret.append(getSecondPoint());
    }
    return ret;
}

bool RXLineData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
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
