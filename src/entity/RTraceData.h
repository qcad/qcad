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

#ifndef RTRACEDATA_H
#define RTRACEDATA_H

#include "entity_global.h"

#include "RSolidData.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a trace entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RTraceData: public RSolidData {

    friend class RTraceEntity;

protected:
    RTraceData(RDocument* document, const RTraceData& data);

public:
    RTraceData();
    RTraceData(const RVector& p1, const RVector& p2, const RVector& p3, const RVector& p4);

    virtual RS::EntityType getType() const {
        return RS::EntityTrace;
    }
};

Q_DECLARE_METATYPE(RTraceData)
Q_DECLARE_METATYPE(RTraceData*)
Q_DECLARE_METATYPE(const RTraceData*)
Q_DECLARE_METATYPE(QSharedPointer<RTraceData>)

#endif
