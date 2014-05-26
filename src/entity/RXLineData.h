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

#ifndef RXLINEDATA_H
#define RXLINEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "RDocument.h"
#include "REntity.h"
#include "RLineData.h"
#include "RVector.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a line entity.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RXLineData: public RLineData {

    friend class RXLineEntity;

protected:
    RXLineData(RDocument* document, const RXLineData& data);

public:
    RXLineData();
    RXLineData(const RLine& line);
    RXLineData(const RVector& basePoint, const RVector& dir);

    void setBasePoint(const RVector& v) {
        RLine::setStartPoint(v);
    }

    RVector getBasePoint() const {
        return RLine::getStartPoint();
    }

    void setSecondPoint(const RVector& v) {
        RLine::setEndPoint(v);
    }

    RVector getSecondPoint() const {
        return RLine::getEndPoint();
    }

    void setDirectionVector(const RVector& v) {
        RLine::setEndPoint(RLine::getStartPoint() + v);
    }

    RVector getDirectionVector() const {
        return RLine::getEndPoint() - RLine::getStartPoint();
    }

};

Q_DECLARE_METATYPE(RXLineData*)
Q_DECLARE_METATYPE(const RXLineData*)
Q_DECLARE_METATYPE(QSharedPointer<RXLineData>)

#endif
