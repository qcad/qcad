/**
 * Copyright (c) 2011-2025 by Andrew Mustun. All rights reserved.
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

#ifndef RCUSTOMENTITY_H
#define RCUSTOMENTITY_H

#include "entity_global.h"

#include "RBlockReferenceEntity.h"
#include "RBlockReferenceData.h"

class RDocument;
class RExporter;

/**
 * Custom, automatically rendered block reference entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup core
 */
class QCADENTITY_EXPORT RCustomEntity: public RBlockReferenceEntity {

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

    static RPropertyTypeId PropertyReferencedBlock;
    static RPropertyTypeId PropertyPositionX;
    static RPropertyTypeId PropertyPositionY;
    static RPropertyTypeId PropertyPositionZ;
    static RPropertyTypeId PropertyScaleX;
    static RPropertyTypeId PropertyScaleY;
    static RPropertyTypeId PropertyScaleZ;
    static RPropertyTypeId PropertyRotation;

public:
    RCustomEntity(RDocument* document, RS::EntityType customEntityType, const RBlockReferenceData& data);
    RCustomEntity(const RCustomEntity& other);
    virtual ~RCustomEntity();

    static void init();

    virtual bool isOfType(RS::EntityType t) const {
        return t==customEntityType || t==RS::EntityBlockRef;
    }

    // void setCustomEntityType(RS::EntityType t) {
    //     customEntityType = t;
    // }
    virtual RS::EntityType getType() const {
        return customEntityType;
    }

    static RS::EntityType getRtti() {
        return RS::EntityCustom;
    }

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(RCustomEntity::getRtti());
    }

    virtual QSharedPointer<RObject> clone() const {
        return QSharedPointer<RObject>(new RCustomEntity(*this));
    }

    QSharedPointer<RCustomEntity> cloneToCustomEntity() const {
        return QSharedPointer<RCustomEntity>(new RCustomEntity(*this));
    }

    virtual void update() const;

    virtual bool setProperty(RPropertyTypeId propertyTypeId,
                             const QVariant& value, RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
        RPropertyTypeId& propertyTypeId,
        bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview = false, bool forceSelected=false) const;

    /**
     * \nonscriptable
     */
    virtual void print(QDebug dbg) const;

private:
    RS::EntityType customEntityType;
    mutable qint64 lastBlockUpdate;
    qint64 lastPropertyUpdate;
};

Q_DECLARE_METATYPE(RCustomEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RCustomEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RCustomEntity>*)

#endif
