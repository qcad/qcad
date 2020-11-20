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

#ifndef RTEXTENTITY_H
#define RTEXTENTITY_H

#include "entity_global.h"

#include "RTextBasedEntity.h"
#include "RTextData.h"

class RDocument;
class RExporter;

/**
 * Linear dimension entity class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RTextEntity: public RTextBasedEntity {

    Q_DECLARE_TR_FUNCTIONS(RTextBasedEntity)

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

    static RPropertyTypeId PropertySimple;
    static RPropertyTypeId PropertyPositionX;
    static RPropertyTypeId PropertyPositionY;
    static RPropertyTypeId PropertyPositionZ;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyPlainText;
    static RPropertyTypeId PropertyFontName;
    static RPropertyTypeId PropertyHeight;
    static RPropertyTypeId PropertyAngle;
    static RPropertyTypeId PropertyXScale;
    static RPropertyTypeId PropertyBold;
    static RPropertyTypeId PropertyItalic;
    static RPropertyTypeId PropertyLineSpacingFactor;
    static RPropertyTypeId PropertyHAlign;
    static RPropertyTypeId PropertyVAlign;
    static RPropertyTypeId PropertyBackward;
    static RPropertyTypeId PropertyUpsideDown;

public:
    RTextEntity(RDocument* document, const RTextData& data);
    virtual ~RTextEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RTextEntity));
    }

    virtual RTextEntity* clone() const {
        return new RTextEntity(*this);
    }

    virtual RTextData& getData() {
        return data;
    }

    void setData(RTextData& d) {
        data = d;
    }

    virtual const RTextData& getData() const {
        return data;
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RTextData data;
};

Q_DECLARE_METATYPE(RTextEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RTextEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RTextEntity>*)

#endif
