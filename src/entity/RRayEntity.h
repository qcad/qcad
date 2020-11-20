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

#ifndef RRAYENTITY_H
#define RRAYENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RRayData.h"

class RDocument;
class RExporter;

/**
 * Infinite ray entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RRayEntity: public REntity {

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

    static RPropertyTypeId PropertyBasePointX;
    static RPropertyTypeId PropertyBasePointY;
    static RPropertyTypeId PropertyBasePointZ;
    static RPropertyTypeId PropertySecondPointX;
    static RPropertyTypeId PropertySecondPointY;
    static RPropertyTypeId PropertySecondPointZ;

    static RPropertyTypeId PropertyDirectionX;
    static RPropertyTypeId PropertyDirectionY;
    static RPropertyTypeId PropertyDirectionZ;

    static RPropertyTypeId PropertyAngle;
    static RPropertyTypeId PropertyFixedAngle;

public:
    RRayEntity(RDocument* document, const RRayData& data);
    virtual ~RRayEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RRayEntity));
    }

    virtual RRayEntity* clone() const {
        return new RRayEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual RRayData& getData() {
        return data;
    }

    virtual const RRayData& getData() const {
        return data;
    }

    void setShape(const RRay& r);

    void setBasePoint(const RVector& p) {
        data.setBasePoint(p);
    }

    RVector getBasePoint() const {
        return data.getBasePoint();
    }

    void setSecondPoint(const RVector& p) {
        data.setSecondPoint(p);
    }

    RVector getSecondPoint() const {
        return data.getSecondPoint();
    }

    void setDirectionVectorPoint(const RVector& v) {
        data.setDirectionVector(v);
    }

    RVector getDirectionVector() const {
        return data.getDirectionVector();
    }

    double getAngle() const {
        return data.getAngle();
    }

    bool hasFixedAngle() const {
        return data.hasFixedAngle();
    }

    void setFixedAngle(bool on) {
        data.setFixedAngle(on);
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
    RRayData data;
};

Q_DECLARE_METATYPE(RRayEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RRayEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RRayEntity>*)

#endif
