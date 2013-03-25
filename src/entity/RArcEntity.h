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

#ifndef RARCENTITY_H
#define RARCENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RArcData.h"
#include "RLineweight.h"

class RDocument;
class RExporter;

/**
 * Arc entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RArcEntity: public REntity {

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
    static RPropertyTypeId PropertyCenterX;
    static RPropertyTypeId PropertyCenterY;
    static RPropertyTypeId PropertyCenterZ;
    static RPropertyTypeId PropertyRadius;
    static RPropertyTypeId PropertyStartAngle;
    static RPropertyTypeId PropertyEndAngle;
    static RPropertyTypeId PropertyReversed;

    static RPropertyTypeId PropertyDiameter;
    static RPropertyTypeId PropertyLength;
    static RPropertyTypeId PropertyArea;

public:
    RArcEntity(RDocument* document, const RArcData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RArcEntity();

    static void init();

    virtual RArcEntity* clone() const {
        return new RArcEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntityArc;
    }

    void setShape(const RArc& a);

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual void exportEntity(RExporter& e, bool preview=false) const;

    virtual RArcData& getData() {
        return data;
    }

    virtual const RArcData& getData() const {
        return data;
    }

    RVector getCenter() const {
        return data.getCenter();
    }

    double getRadius() const {
        return data.getRadius();
    }

    void setRadius(double radius) {
        data.setRadius(radius);
    }

    double getBulge() const {
        return data.getBulge();
    }

    double getStartAngle() const {
        return data.getStartAngle();
    }

    void setStartAngle(double angle) {
        data.setStartAngle(angle);
    }

    double getEndAngle() const {
        return data.getEndAngle();
    }

    void setEndAngle(double angle) {
        data.setEndAngle(angle);
    }

    bool isReversed() const {
        return data.isReversed();
    }

    void setReversed(bool reversed) {
        data.setReversed(reversed);
    }

    double getDirection1() const {
        return data.getDirection1();
    }

    double getDirection2() const {
        return data.getDirection2();
    }

    RVector getStartPoint() const {
        return data.getStartPoint();
    }

    RVector getEndPoint() const {
        return data.getEndPoint();
    }

    bool reverse() {
        return data.reverse();
    }

    RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint) {
        return data.getTrimEnd(coord, trimPoint);
    }

    void trimStartPoint(const RVector& p) {
        return data.trimStartPoint(p);
    }
    void trimEndPoint(const RVector& p) {
        return data.trimEndPoint(p);
    }

    double getLength() const {
        return data.getLength();
    }
    double getAngleLength(bool allowForZeroLength = false) const {
        return data.getAngleLength(allowForZeroLength);
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    RArcData data;
};

Q_DECLARE_METATYPE(RArcEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RArcEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RArcEntity>*)

#endif
