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

#ifndef RDIMROTATEDENTITY_H
#define RDIMROTATEDENTITY_H

#include "entity_global.h"

#include "RDimensionEntity.h"
#include "RDimRotatedData.h"

class RDocument;
class RExporter;

/**
 * Linear dimension entity class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimRotatedEntity: public RDimensionEntity {

    Q_DECLARE_TR_FUNCTIONS(RDimRotatedEntity)

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

    static RPropertyTypeId PropertyMiddleOfTextX;
    static RPropertyTypeId PropertyMiddleOfTextY;
    static RPropertyTypeId PropertyMiddleOfTextZ;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyUpperTolerance;
    static RPropertyTypeId PropertyLowerTolerance;

    static RPropertyTypeId PropertyLinearFactor;
    static RPropertyTypeId PropertyAutoTextPos;

    static RPropertyTypeId PropertyDimensionLinePosX;
    static RPropertyTypeId PropertyDimensionLinePosY;
    static RPropertyTypeId PropertyDimensionLinePosZ;

    static RPropertyTypeId PropertyExtensionPoint1X;
    static RPropertyTypeId PropertyExtensionPoint1Y;
    static RPropertyTypeId PropertyExtensionPoint1Z;

    static RPropertyTypeId PropertyExtensionPoint2X;
    static RPropertyTypeId PropertyExtensionPoint2Y;
    static RPropertyTypeId PropertyExtensionPoint2Z;

    static RPropertyTypeId PropertyAngle;

public:
    RDimRotatedEntity(RDocument* document, const RDimRotatedData& data,
                      RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RDimRotatedEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RDimRotatedEntity));
    }

    virtual RDimRotatedEntity* clone() const {
        return new RDimRotatedEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityDimRotated;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual RDimRotatedData& getData() {
        return data;
    }

    void setData(RDimRotatedData& d) {
        data = d;
    }

    virtual const RDimRotatedData& getData() const {
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

    void setRotation(double a) {
        data.setRotation(a);
    }

    double getRotation() const {
        return data.getRotation();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RDimRotatedData data;
};

Q_DECLARE_METATYPE(RDimRotatedEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RDimRotatedEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RDimRotatedEntity>*)

#endif
