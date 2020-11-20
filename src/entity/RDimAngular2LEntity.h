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

#ifndef RDIMANGULAR2LENTITY_H
#define RDIMANGULAR2LENTITY_H

#include "entity_global.h"

#include "RDimAngularEntity.h"
#include "RDimAngular2LData.h"

class RDocument;
class RExporter;

/**
 * Angular dimension entity from 2 lines class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimAngular2LEntity: public RDimAngularEntity {

    Q_DECLARE_TR_FUNCTIONS(RDimAngular2LEntity)

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

    static RPropertyTypeId PropertyDimScale;
    static RPropertyTypeId PropertyDimBlockName;
    static RPropertyTypeId PropertyAutoTextPos;
    static RPropertyTypeId PropertyFontName;
    static RPropertyTypeId PropertyArrow1Flipped;
    static RPropertyTypeId PropertyArrow2Flipped;

    static RPropertyTypeId PropertyExtLineFix;
    static RPropertyTypeId PropertyExtLineFixLength;

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
    RDimAngular2LEntity(RDocument* document, const RDimAngular2LData& data);
    virtual ~RDimAngular2LEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RDimAngular2LEntity));
    }

    virtual RDimAngular2LEntity* clone() const {
        return new RDimAngular2LEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual RDimAngular2LData& getData() {
        return data;
    }

    void setData(RDimAngular2LData& d) {
        data = d;
    }

    virtual const RDimAngular2LData& getData() const {
        return data;
    }

    void setExtensionLine1Start(const RVector& p) {
        getData().setExtensionLine1Start(p);
    }

    RVector getExtensionLine1Start() const {
        return getData().getExtensionLine1Start();
    }

    void setExtensionLine2Start(const RVector& p) {
        getData().setExtensionLine2Start(p);
    }

    RVector getExtensionLine2Start() const {
        return getData().getExtensionLine2Start();
    }

    RVector getCenter() const {
        return getData().getCenter();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RDimAngular2LData data;
};

Q_DECLARE_METATYPE(RDimAngular2LEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RDimAngular2LEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RDimAngular2LEntity>*)

#endif
