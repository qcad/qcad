/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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

#ifndef RDIMANGULARENTITY_H
#define RDIMANGULARENTITY_H

#include "entity_global.h"

#include "RDimensionEntity.h"
#include "RDimAngularData.h"

class RDocument;
class RExporter;

/**
 * Aligned dimension entity class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimAngularEntity: public RDimensionEntity {

    Q_DECLARE_TR_FUNCTIONS(RDimAngularEntity)

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

    static RPropertyTypeId PropertyMiddleOfTextX;
    static RPropertyTypeId PropertyMiddleOfTextY;
    static RPropertyTypeId PropertyMiddleOfTextZ;
    static RPropertyTypeId PropertyText;
    static RPropertyTypeId PropertyUpperTolerance;
    static RPropertyTypeId PropertyLowerTolerance;
    static RPropertyTypeId PropertyMeasuredValue;
    static RPropertyTypeId PropertyFontName;

    static RPropertyTypeId PropertyExtensionLine1StartX;
    static RPropertyTypeId PropertyExtensionLine1StartY;
    static RPropertyTypeId PropertyExtensionLine1StartZ;

    static RPropertyTypeId PropertyExtensionLine1EndX;
    static RPropertyTypeId PropertyExtensionLine1EndY;
    static RPropertyTypeId PropertyExtensionLine1EndZ;

    static RPropertyTypeId PropertyExtensionLine2StartX;
    static RPropertyTypeId PropertyExtensionLine2StartY;
    static RPropertyTypeId PropertyExtensionLine2StartZ;

    static RPropertyTypeId PropertyExtensionLine2EndX;
    static RPropertyTypeId PropertyExtensionLine2EndY;
    static RPropertyTypeId PropertyExtensionLine2EndZ;

    static RPropertyTypeId PropertyDimArcPositionX;
    static RPropertyTypeId PropertyDimArcPositionY;
    static RPropertyTypeId PropertyDimArcPositionZ;

public:
    RDimAngularEntity(RDocument* document, const RDimAngularData& data,
                      RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RDimAngularEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RDimAngularEntity));
    }

    virtual RDimAngularEntity* clone() const {
        return new RDimAngularEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityDimAngular;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual RDimAngularData& getData() {
        return data;
    }

    void setData(RDimAngularData& d) {
        data = d;
    }

    virtual const RDimAngularData& getData() const {
        return data;
    }

    void setExtensionLine1Start(const RVector& p) {
        getData().setExtensionLine1Start(p);
    }

    RVector getExtensionLine1Start() const {
        return getData().getExtensionLine1Start();
    }

    void setExtensionLine1End(const RVector& p) {
        getData().setExtensionLine1End(p);
    }

    RVector getExtensionLine1End() const {
        return getData().getExtensionLine1End();
    }

    void setExtensionLine2Start(const RVector& p) {
        getData().setExtensionLine2Start(p);
    }

    RVector getExtensionLine2Start() const {
        return getData().getExtensionLine2Start();
    }

    void setExtensionLine2End(const RVector& p) {
        getData().setExtensionLine2End(p);
    }

    RVector getExtensionLine2End() const {
        return getData().getExtensionLine2End();
    }

    void setDimArcPosition(const RVector& p) {
        getData().setDimArcPosition(p);
    }

    RVector getDimArcPosition() const {
        return getData().getDimArcPosition();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RDimAngularData data;
};

Q_DECLARE_METATYPE(RDimAngularEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RDimAngularEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RDimAngularEntity>*)

#endif
