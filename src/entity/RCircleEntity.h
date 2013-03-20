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

#ifndef RCIRCLENTITY_H
#define RCIRCLENTITY_H

#include "REntity.h"
#include "RCircleData.h"

class RDocument;
class RExporter;

/**
 * Circle entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class RCircleEntity: public REntity {

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDrawOrder;
    static RPropertyTypeId PropertyCenterX;
    static RPropertyTypeId PropertyCenterY;
    static RPropertyTypeId PropertyCenterZ;
    static RPropertyTypeId PropertyRadius;

    static RPropertyTypeId PropertyDiameter;
    static RPropertyTypeId PropertyCircumference;
    static RPropertyTypeId PropertyArea;

public:
    RCircleEntity(RDocument* document, const RCircleData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RCircleEntity();

    static void init();

    virtual RCircleEntity* clone() const {
        return new RCircleEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityCircle;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual void exportEntity(RExporter& e, bool preview=false) const;

    virtual RCircleData& getData() {
        return data;
    }

    virtual const RCircleData& getData() const {
        return data;
    }

    RVector getCenter() const {
        return data.getCenter();
    }

    double getRadius() {
        return data.getRadius();
    }

    void setRadius(double radius) {
        data.setRadius(radius);
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RCircleData data;
};

Q_DECLARE_METATYPE(RCircleEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RCircleEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RCircleEntity>*)

#endif
