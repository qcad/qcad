/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

#ifndef RSOLIDENTITY_H
#define RSOLIDENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RSolidData.h"

class RDocument;
class RExporter;

/**
 * Solid entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RSolidEntity: public REntity {

public:
    static RPropertyTypeId PropertyCustom;
    static RPropertyTypeId PropertyHandle;
    static RPropertyTypeId PropertyType;
    static RPropertyTypeId PropertyBlock;
    static RPropertyTypeId PropertyLayer;
    static RPropertyTypeId PropertyLinetype;
    static RPropertyTypeId PropertyLinetypeScale;
    static RPropertyTypeId PropertyLineweight;
    static RPropertyTypeId PropertyColor;
    static RPropertyTypeId PropertyDrawOrder;

    static RPropertyTypeId PropertyPoint1X;
    static RPropertyTypeId PropertyPoint1Y;
    static RPropertyTypeId PropertyPoint1Z;
    static RPropertyTypeId PropertyPoint2X;
    static RPropertyTypeId PropertyPoint2Y;
    static RPropertyTypeId PropertyPoint2Z;
    static RPropertyTypeId PropertyPoint3X;
    static RPropertyTypeId PropertyPoint3Y;
    static RPropertyTypeId PropertyPoint3Z;
    static RPropertyTypeId PropertyPoint4X;
    static RPropertyTypeId PropertyPoint4Y;
    static RPropertyTypeId PropertyPoint4Z;

    static RPropertyTypeId PropertyLength;

public:
    RSolidEntity(RDocument* document, const RSolidData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RSolidEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RSolidEntity));
    }

    virtual RSolidEntity* clone() const {
        return new RSolidEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntitySolid;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual RSolidData& getData() {
        return data;
    }

    virtual const RSolidData& getData() const {
        return data;
    }

    RVector getVertexAt(int i) const {
        return data.getVertexAt(i);
    }

    int countVertices() const {
        return data.countVertices();
    }

    RVector getStartPoint() const {
        return data.getStartPoint();
    }

    RVector getEndPoint() const {
        return data.getEndPoint();
    }

    double getDirection1() const {
        return data.getDirection1();
    }

    double getDirection2() const {
        return data.getDirection2();
    }

    bool reverse() {
        return data.reverse();
    }

    RS::Ending getTrimEnd(const RVector& coord,
                            const RVector& trimPoint) {
        return data.getTrimEnd(coord, trimPoint);
    }

    void trimStartPoint(const RVector& p) {
        return data.trimStartPoint(p);
    }
    void trimEndPoint(const RVector& p) {
        return data.trimEndPoint(p);
    }

    double getLength() const {
        return data.getLength();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RSolidData data;
};

Q_DECLARE_METATYPE(RSolidEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RSolidEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RSolidEntity>*)

#endif
