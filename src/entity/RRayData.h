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

#ifndef RRAYDATA_H
#define RRAYDATA_H

#include "entity_global.h"

#include "RXLineData.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a ray entity.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RRayData: public RXLineData {

    friend class RRayEntity;

protected:
    RRayData(RDocument* document, const RRayData& data);

public:
    RRayData();
    RRayData(const RLine& line);
    RRayData(const RVector& basePoint, const RVector& dir);

    virtual RVector getVectorTo(const RVector& point, bool limited = true) const;

protected:
    virtual RLine getXLineShape() const;
};

Q_DECLARE_METATYPE(RRayData*)
Q_DECLARE_METATYPE(const RRayData*)
Q_DECLARE_METATYPE(QSharedPointer<RRayData>)

#endif
