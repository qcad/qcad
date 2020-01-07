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

#ifndef RFACEDATA_H
#define RFACEDATA_H

#include "entity_global.h"

#include "RSolidData.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a face entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RFaceData: public RSolidData {

    friend class RFaceEntity;

protected:
    RFaceData(RDocument* document, const RFaceData& data);

public:
    RFaceData();
    RFaceData(const RVector& p1, const RVector& p2, const RVector& p3, const RVector& p4);

    virtual RS::EntityType getType() const {
        return RS::EntityFace;
    }
};

Q_DECLARE_METATYPE(RFaceData)
Q_DECLARE_METATYPE(RFaceData*)
Q_DECLARE_METATYPE(const RFaceData*)
Q_DECLARE_METATYPE(QSharedPointer<RFaceData>)

#endif
