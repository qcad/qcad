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

#ifndef RDIMORDINATEENTITY_H
#define RDIMORDINATEENTITY_H

#include "entity_global.h"

#include "RDimensionEntity.h"
#include "RDimOrdinateData.h"

class RDocument;
class RExporter;

/**
 * Ordinate dimension entity class.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RDimOrdinateEntity: public RDimensionEntity {

    Q_DECLARE_TR_FUNCTIONS(RDimOrdinateEntity)

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
    static RPropertyTypeId PropertyFontName;
    static RPropertyTypeId PropertyArrow1Flipped;
    static RPropertyTypeId PropertyArrow2Flipped;

    static RPropertyTypeId PropertyExtLineFix;
    static RPropertyTypeId PropertyExtLineFixLength;

    static RPropertyTypeId PropertyDimScale;
    static RPropertyTypeId PropertyDimBlockName;

    static RPropertyTypeId PropertyOriginX;
    static RPropertyTypeId PropertyOriginY;
    static RPropertyTypeId PropertyOriginZ;

    static RPropertyTypeId PropertyOrdinate;

    static RPropertyTypeId PropertyLeaderEndPointX;
    static RPropertyTypeId PropertyLeaderEndPointY;
    static RPropertyTypeId PropertyLeaderEndPointZ;

    static RPropertyTypeId PropertyDefiningPointX;
    static RPropertyTypeId PropertyDefiningPointY;
    static RPropertyTypeId PropertyDefiningPointZ;

public:
    RDimOrdinateEntity(RDocument* document, const RDimOrdinateData& data);
    virtual ~RDimOrdinateEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RDimOrdinateEntity));
    }

    virtual RDimOrdinateEntity* clone() const {
        return new RDimOrdinateEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual RDimOrdinateData& getData() {
        return data;
    }

    void setData(RDimOrdinateData& d) {
        data = d;
    }

    virtual const RDimOrdinateData& getData() const {
        return data;
    }

    void setLeaderEndPoint(const RVector& p) {
        data.setLeaderEndPoint(p);
    }

    RVector getLeaderEndPoint() const {
        return data.getLeaderEndPoint();
    }

    void setDefiningPoint(const RVector& p) {
        data.setDefiningPoint(p);
    }

    RVector getDefiningPoint() const {
        return data.getDefiningPoint();
    }

    void setMeasuringXAxis() {
        data.setMeasuringXAxis();
    }

    void setMeasuringYAxis() {
        data.setMeasuringYAxis();
    }

    bool isMeasuringXAxis() const {
        return data.isMeasuringXAxis();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RDimOrdinateData data;
};

Q_DECLARE_METATYPE(RDimOrdinateEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RDimOrdinateEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RDimOrdinateEntity>*)

#endif
