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

    static RPropertyTypeId PropertyCenterX;
    static RPropertyTypeId PropertyCenterY;
    static RPropertyTypeId PropertyCenterZ;
    static RPropertyTypeId PropertyRadius;
    static RPropertyTypeId PropertyStartAngle;
    static RPropertyTypeId PropertyEndAngle;
    static RPropertyTypeId PropertyReversed;

    static RPropertyTypeId PropertyDiameter;
    static RPropertyTypeId PropertyLength;
    static RPropertyTypeId PropertyTotalLength;
    static RPropertyTypeId PropertySweepAngle;
    static RPropertyTypeId PropertyArea;
    static RPropertyTypeId PropertyTotalArea;

public:
    RArcEntity(RDocument* document, const RArcData& data);
    RArcEntity(const RArcEntity& other);
    virtual ~RArcEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RArcEntity));
    }

    virtual RArcEntity* clone() const {
        return new RArcEntity(*this);
    }

    void setShape(const RArc& a);

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual QSharedPointer<REntity> scaleNonUniform(const RVector& scaleFactors, const RVector& center);
    static QSharedPointer<REntity> scaleNonUniform(REntity& entity, const RVector& scaleFactors, const RVector& center);

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

    RVector getMiddlePoint() const {
        return data.getMiddlePoint();
    }

    bool reverse() {
        return data.reverse();
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return data.getSideOfPoint(point);
    }

    double getSweep() const {
        return data.getSweep();
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
    double getAngleLength(bool allowForZeroLength = false) const {
        return data.getAngleLength(allowForZeroLength);
    }

    double getAngleAt(double distance, RS::From from) const {
        return data.getAngleAt(distance, from);
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
