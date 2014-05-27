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
#include "RXLineData.h"
#include "RLineEntity.h"

RXLineData::RXLineData() {
}

RXLineData::RXLineData(RDocument* document, const RXLineData& data)
    : RLineData(document, data) {
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RXLineData::RXLineData(const RLine& line) :
    RLineData(line) {
}

RXLineData::RXLineData(const RVector& basePoint, const RVector& dir) :
    RLineData(basePoint, basePoint + dir) {
}

bool RXLineData::intersectsWith(const RShape& shape) const {
    const RDocument* doc = getDocument();
    if (doc==NULL) {
        return false;
    }

    RLine xLine = *this;
    RBox bbox = doc->getBoundingBox();

    xLine.clipToXY(bbox, true);

    return xLine.intersectsWith(shape);
}
