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

#ifndef RDIMALIGNEDENTITY_H
#define RDIMALIGNEDENTITY_H

#include "entity_global.h"

#include "RDimLinearEntity.h"
#include "RDimAlignedData.h"

class RDocument;
class RExporter;

/**
 * Aligned dimension entity class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimAlignedEntity: public RDimLinearEntity {

    Q_DECLARE_TR_FUNCTIONS(RDimAlignedEntity)

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

    static RPropertyTypeId PropertyDimensionLinePosX;
    static RPropertyTypeId PropertyDimensionLinePosY;
    static RPropertyTypeId PropertyDimensionLinePosZ;
    static RPropertyTypeId PropertyExtensionPoint1X;
    static RPropertyTypeId PropertyExtensionPoint1Y;
    static RPropertyTypeId PropertyExtensionPoint1Z;
    static RPropertyTypeId PropertyExtensionPoint2X;
    static RPropertyTypeId PropertyExtensionPoint2Y;
    static RPropertyTypeId PropertyExtensionPoint2Z;

public:
    RDimAlignedEntity(RDocument* document, const RDimAlignedData& data);
    virtual ~RDimAlignedEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RDimAlignedEntity));
    }

    virtual RDimAlignedEntity* clone() const {
        return new RDimAlignedEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual RDimAlignedData& getData() {
        return data;
    }

    void setData(RDimAlignedData& d) {
        data = d;
    }

    virtual const RDimAlignedData& getData() const {
        return data;
    }

    void setExtensionPoint1(const RVector& p) {
        data.setExtensionPoint1(p);
    }

    RVector getExtensionPoint1() const {
        return data.getExtensionPoint1();
    }

    void setExtensionPoint2(const RVector& p) {
        data.setExtensionPoint2(p);
    }

    RVector getExtensionPoint2() const {
        return data.getExtensionPoint2();
    }

    double getAngle() const {
        return data.getAngle();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RDimAlignedData data;
};

Q_DECLARE_METATYPE(RDimAlignedEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RDimAlignedEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RDimAlignedEntity>*)

#endif
