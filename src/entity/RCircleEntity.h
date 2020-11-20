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

#ifndef RCIRCLENTITY_H
#define RCIRCLENTITY_H

#include "entity_global.h"

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
class QCADENTITY_EXPORT RCircleEntity: public REntity {

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyProtected;
    static RPropertyTypeId PropertyWorkingSet;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDisplayedColor;
    static RPropertyTypeId PropertyDrawOrder;
    static RPropertyTypeId PropertyCenterX;
    static RPropertyTypeId PropertyCenterY;
    static RPropertyTypeId PropertyCenterZ;
    static RPropertyTypeId PropertyRadius;

    static RPropertyTypeId PropertyDiameter;
    static RPropertyTypeId PropertyCircumference;
    static RPropertyTypeId PropertyArea;
    static RPropertyTypeId PropertyTotalArea;

public:
    RCircleEntity(RDocument* document, const RCircleData& data);
    RCircleEntity(const RCircleEntity& other);
    virtual ~RCircleEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RCircleEntity));
    }

    virtual RCircleEntity* clone() const {
        return new RCircleEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual QSharedPointer<REntity> scaleNonUniform(const RVector& scaleFactors, const RVector& center);

    virtual RCircleData& getData() {
        return data;
    }

    virtual const RCircleData& getData() const {
        return data;
    }

    RVector getCenter() const {
        return data.getCenter();
    }

    double getRadius() const {
        return data.getRadius();
    }

    void setRadius(double radius) {
        data.setRadius(radius);
    }

    double getLength() const {
        return data.getLength();
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
