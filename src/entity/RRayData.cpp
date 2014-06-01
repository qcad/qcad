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
#include "RRayData.h"
#include "RLineEntity.h"

RRayData::RRayData() {
}

RRayData::RRayData(RDocument* document, const RRayData& data)
    : RXLineData(document, data) {
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RRayData::RRayData(const RLine& line) :
    RXLineData(line) {
}

RRayData::RRayData(const RVector& basePoint, const RVector& dir) :
    RXLineData(basePoint, dir) {
}

RLine RRayData::getXLineShape() const {
    RLine ray = *this;
    ray.setLength(1e6);
    return ray;
}


RVector RRayData::getVectorTo(const RVector& point, bool limited) const {
    return getXLineShape().getVectorTo(point, limited);
}
