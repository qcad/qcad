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

#ifndef RATTRIBUTEENTITY_H
#define RATTRIBUTEENTITY_H

#include "entity_global.h"

#include "RTextBasedEntity.h"
#include "RAttributeDefinitionEntity.h"
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

    static RPropertyTypeId PropertyAngle;
    static RPropertyTypeId PropertyXScale;
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
    static RPropertyTypeId PropertyPlainText;
    static RPropertyTypeId PropertyVAlign;
    static RPropertyTypeId PropertyInvisible;
    static RPropertyTypeId PropertyBackward;
    static RPropertyTypeId PropertyUpsideDown;

public:
    RAttributeEntity(RDocument* document, const RAttributeData& data);
    virtual ~RAttributeEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RAttributeEntity));
    }

    virtual RAttributeEntity* clone() const {
        return new RAttributeEntity(*this);
    }

    virtual RAttributeData& getData() {
        return data;
    }

    virtual const RAttributeData& getData() const {
        return data;
    }

    void setData(RAttributeData& d) {
        data = d;
    }


    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    void exportEntity(RExporter& e, bool preview, bool forceSelected=false) const;

    QString getTag() const {
        return data.getTag();
    }

    void setTag(const QString& t) {
        data.setTag(t);
    }

    bool isInvisible() const {
        return data.isInvisible();
    }

    void setInvisible(bool i) {
        data.setInvisible(i);
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RAttributeData data;
};

Q_DECLARE_METATYPE(RAttributeEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RAttributeEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RAttributeEntity>*)

#endif
