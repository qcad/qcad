/**
 * Copyright (c) 2011-2024 by Andrew Mustun. All rights reserved.
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
#include "RWipeoutData.h"
#include "RWipeoutEntity.h"

RWipeoutData::RWipeoutData() {
}

RWipeoutData::RWipeoutData(RDocument* document, const RWipeoutData& data)
    : RPolylineData(document), showFrame(false) {

    *this = data;
}

RWipeoutData::RWipeoutData(const RPolyline& polyline) :
    RPolylineData(polyline), showFrame(false) {
}

double RWipeoutData::getDistanceTo(const RVector& point, bool limited, double range, bool draft, double strictRange) const {
    Q_UNUSED(range)
    Q_UNUSED(draft)
    Q_UNUSED(strictRange)

    double minDist = RPolyline::getDistanceTo(point, limited, strictRange);

    // point not close to frame:
    if (RMath::isNaN(minDist) || strictRange<minDist) {
        if (RPolyline::contains(point)) {
            minDist = strictRange;
        }
    }

    if (RMath::isNaN(minDist)) {
        return RMAXDOUBLE;
    }

    return minDist;
}
