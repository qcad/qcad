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

#ifndef RVIEWPORTENTITY_H
#define RVIEWPORTENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RViewportData.h"

class RDocument;
class RExporter;

/**
 * Viewport entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup core
 */
class QCADCORE_EXPORT RViewportEntity: public REntity {

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
    static RPropertyTypeId PropertyWidth;
    static RPropertyTypeId PropertyHeight;
    static RPropertyTypeId PropertyScale;

public:
    RViewportEntity(RDocument* document, const RViewportData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RViewportEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RViewportEntity));
    }

    virtual RViewportEntity* clone() const {
        return new RViewportEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityViewport;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual void exportEntity(RExporter& e, bool preview=false) const;

    virtual RViewportData& getData() {
        return data;
    }

    virtual const RViewportData& getData() const {
        return data;
    }

    RVector getCenter() const {
        return data.getCenter();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RViewportData data;
};

Q_DECLARE_METATYPE(RViewportEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RViewportEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RViewportEntity>*)

#endif
