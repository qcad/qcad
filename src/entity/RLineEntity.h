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

#ifndef RLINEENTITY_H
#define RLINEENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RLineData.h"

class RDocument;
class RExporter;

/**
 * Line entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RLineEntity: public REntity {

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

    static RPropertyTypeId PropertyStartPointX;
    static RPropertyTypeId PropertyStartPointY;
    static RPropertyTypeId PropertyStartPointZ;
    static RPropertyTypeId PropertyEndPointX;
    static RPropertyTypeId PropertyEndPointY;
    static RPropertyTypeId PropertyEndPointZ;

    static RPropertyTypeId PropertyAngle;
    static RPropertyTypeId PropertyLength;
    static RPropertyTypeId PropertyTotalLength;

public:
    RLineEntity(RDocument* document, const RLineData& data);
    RLineEntity(const RLineEntity& other);
    virtual ~RLineEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RLineEntity));
    }

    virtual RLineEntity* clone() const {
        return new RLineEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual RLineData& getData() {
        return data;
    }

    virtual const RLineData& getData() const {
        return data;
    }

    void setShape(const RLine& l);

    void setStartPoint(const RVector& p) {
        data.setStartPoint(p);
    }

    RVector getStartPoint() const {
        return data.getStartPoint();
    }

    void setEndPoint(const RVector& p) {
        data.setEndPoint(p);
    }

    RVector getEndPoint() const {
        return data.getEndPoint();
    }

    RVector getMiddlePoint() const {
        return getData().getMiddlePoint();
    }

    double getAngle() const {
        return data.getAngle();
    }

    double getAngleAt(double distance, RS::From from) const {
        return data.getAngleAt(distance, from);
    }

    double getDirection1() const {
        return data.getDirection1();
    }

    double getDirection2() const {
        return data.getDirection2();
    }

    bool reverse() {
        return data.reverse();
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return data.getSideOfPoint(point);
    }

    RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
        return data.getTrimEnd(trimPoint, clickPoint);
    }

    bool trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return data.trimStartPoint(trimPoint, clickPoint, extend);
    }
    bool trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return data.trimEndPoint(trimPoint, clickPoint, extend);
    }

    double getLength() const {
        return data.getLength();
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RLineData data;
};

Q_DECLARE_METATYPE(RLineEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RLineEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RLineEntity>*)

#endif
