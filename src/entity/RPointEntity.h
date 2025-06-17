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

#ifndef RPOINTENTITY_H
#define RPOINTENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RPointData.h"

class RDocument;
class RExporter;

/**
 * Point entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RPointEntity: public REntity {

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
    static RPropertyTypeId PropertyPositionX;
    static RPropertyTypeId PropertyPositionY;
    static RPropertyTypeId PropertyPositionZ;

    // for aama file support:
    // static RPropertyTypeId PropertyThickness;
    // static RPropertyTypeId PropertyNormalX;
    // static RPropertyTypeId PropertyNormalY;
    // static RPropertyTypeId PropertyNormalZ;

public:
    RPointEntity(RDocument* document, const RPointData& data);
    RPointEntity(const RPointEntity& other);
    virtual ~RPointEntity();

    static void init();

    static RS::EntityType getRtti() {
        return RS::EntityPoint;
    }

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(RPointEntity::getRtti());
    }

    virtual QSharedPointer<RObject> clone() const {
        return QSharedPointer<RObject>(new RPointEntity(*this));
    }

    QSharedPointer<RPointEntity> cloneToPointEntity() const {
        return QSharedPointer<RPointEntity>(new RPointEntity(*this));
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual RPointData& getData() {
        return data;
    }

    virtual const RPointData& getData() const {
        return data;
    }

    RVector getPosition() const {
        return data.getPosition();
    }

    // for aama files:
    // void setThickness(double t) {
    //     data.setThickness(t);
    // }
    // double getThickness() const {
    //     return data.getThickness();
    // }

    // void setNormal(const RVector& dir) {
    //     data.setNormal(dir);
    // }
    // RVector getNormal() const {
    //     return data.getNormal();
    // }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RPointData data;
};

Q_DECLARE_METATYPE(RPointEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RPointEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RPointEntity>*)

#endif
