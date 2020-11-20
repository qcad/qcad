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

#ifndef RDIMARCLENGTHENTITY_H
#define RDIMARCLENGTHENTITY_H

#include "entity_global.h"

#include "RDimAngularEntity.h"
#include "RDimArcLengthData.h"

class RDocument;
class RExporter;

/**
 * Arc length dimension entity class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimArcLengthEntity: public RDimAngularEntity {

    Q_DECLARE_TR_FUNCTIONS(RDimArcLengthEntity)

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

    static RPropertyTypeId PropertyMiddleOfTextX;
    static RPropertyTypeId PropertyMiddleOfTextY;
    static RPropertyTypeId PropertyMiddleOfTextZ;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyUpperTolerance;
    static RPropertyTypeId PropertyLowerTolerance;
    static RPropertyTypeId PropertyMeasuredValue;

    static RPropertyTypeId PropertyLinearFactor;
    static RPropertyTypeId PropertyDimScale;
    static RPropertyTypeId PropertyDimBlockName;
    static RPropertyTypeId PropertyAutoTextPos;
    static RPropertyTypeId PropertyFontName;
    static RPropertyTypeId PropertyArrow1Flipped;
    static RPropertyTypeId PropertyArrow2Flipped;

    static RPropertyTypeId PropertyExtLineFix;
    static RPropertyTypeId PropertyExtLineFixLength;

    static RPropertyTypeId PropertyCenterX;
    static RPropertyTypeId PropertyCenterY;
    static RPropertyTypeId PropertyCenterZ;

    static RPropertyTypeId PropertyExtensionLine1EndX;
    static RPropertyTypeId PropertyExtensionLine1EndY;
    static RPropertyTypeId PropertyExtensionLine1EndZ;

    static RPropertyTypeId PropertyExtensionLine2EndX;
    static RPropertyTypeId PropertyExtensionLine2EndY;
    static RPropertyTypeId PropertyExtensionLine2EndZ;

    static RPropertyTypeId PropertyDimArcPositionX;
    static RPropertyTypeId PropertyDimArcPositionY;
    static RPropertyTypeId PropertyDimArcPositionZ;

    static RPropertyTypeId PropertyDimArcSymbolType;

public:
    RDimArcLengthEntity(RDocument* document, const RDimArcLengthData& data);
    virtual ~RDimArcLengthEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RDimArcLengthEntity));
    }

    virtual RDimArcLengthEntity* clone() const {
        return new RDimArcLengthEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual RDimArcLengthData& getData() {
        return data;
    }

    void setData(RDimArcLengthData& d) {
        data = d;
    }

    virtual const RDimArcLengthData& getData() const {
        return data;
    }

    void setCenter(const RVector& p) {
        getData().setCenter(p);
    }

    RVector getCenter() const {
        return getData().getCenter();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RDimArcLengthData data;
};

Q_DECLARE_METATYPE(RDimArcLengthEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RDimArcLengthEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RDimArcLengthEntity>*)

#endif
