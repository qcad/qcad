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

#ifndef RATTRIBUTEENTITY_H
#define RATTRIBUTEENTITY_H

#include "entity_global.h"

#include "RTextBasedEntity.h"
#include "RAttributeData.h"

class RDocument;
class RExporter;

/**
 * Attribute entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RAttributeEntity: public RTextBasedEntity {

    Q_DECLARE_TR_FUNCTIONS(RAttributeEntity)

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

    static RPropertyTypeId PropertyAngle;
    static RPropertyTypeId PropertyBold;
    static RPropertyTypeId PropertyFontName;
    static RPropertyTypeId PropertyHAlign;
    static RPropertyTypeId PropertyHeight;
    static RPropertyTypeId PropertyItalic;
    static RPropertyTypeId PropertyLineSpacingFactor;
    static RPropertyTypeId PropertyPositionX;
    static RPropertyTypeId PropertyPositionY;
    static RPropertyTypeId PropertyPositionZ;
    static RPropertyTypeId PropertyTag;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyVAlign;

public:
    RAttributeEntity(RDocument* document, const RAttributeData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RAttributeEntity();

    static void init();

    virtual RAttributeEntity* clone() const {
        return new RAttributeEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityAttribute;
    }

    virtual RAttributeData& getData() {
        return data;
    }

    virtual const RAttributeData& getData() const {
        return data;
    }

//    virtual bool isPartOfBlockReference(RBlockReferenceEntity::Id blockRefId) const {
//        return blockRefId==data.getBlockReferenceId();
//    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

//    virtual void setSelected(bool on);

    void exportEntity(RExporter& e, bool preview) const;

    QString getTag() const {
        return data.getTag();
    }

    void setTag(const QString& t) {
        data.setTag(t);
    }

//    RBlockReferenceEntity::Id getBlockReferenceId() const {
//        return data.getBlockReferenceId();
//    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RAttributeData data;
};

Q_DECLARE_METATYPE(RAttributeEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RAttributeEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RAttributeEntity>*)

#endif
