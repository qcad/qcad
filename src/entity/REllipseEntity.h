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

#ifndef RELLIPSEENTITY_H
#define RELLIPSEENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "REllipseData.h"
#include "RLineweight.h"

class RDocument;
class RExporter;

/**
 * Ellipse entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT REllipseEntity: public REntity {

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
    static RPropertyTypeId PropertyMajorPointX;
    static RPropertyTypeId PropertyMajorPointY;
    static RPropertyTypeId PropertyMajorPointZ;
    static RPropertyTypeId PropertyRatio;
    static RPropertyTypeId PropertyStartParam;
    static RPropertyTypeId PropertyEndParam;
    static RPropertyTypeId PropertyStartAngle;
    static RPropertyTypeId PropertyEndAngle;
    static RPropertyTypeId PropertyReversed;

    static RPropertyTypeId PropertyStartPointX;
    static RPropertyTypeId PropertyStartPointY;
    static RPropertyTypeId PropertyStartPointZ;
    static RPropertyTypeId PropertyEndPointX;
    static RPropertyTypeId PropertyEndPointY;
    static RPropertyTypeId PropertyEndPointZ;

    static RPropertyTypeId PropertyCircumference;

public:
    REllipseEntity(RDocument* document, const REllipseData& data);
    virtual ~REllipseEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(REllipseEntity));
    }

    virtual REllipseEntity* clone() const {
        return new REllipseEntity(*this);
    }

    void setShape(const REllipse& e);

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual QSharedPointer<REntity> scaleNonUniform(const RVector& scaleFactors, const RVector& center);

    virtual REllipseData& getData() {
        return data;
    }

    virtual const REllipseData& getData() const {
        return data;
    }

    RVector getCenter() const {
        return data.getCenter();
    }

    RVector getMajorPoint() const {
        return data.getMajorPoint();
    }

    double getMajorRadius() const {
        return data.getMajorRadius();
    }

    double getMinorRadius() const {
        return data.getMinorRadius();
    }

    double getRatio() const {
        return data.getRatio();
    }

    double getAngle() const {
        return data.getAngle();
    }

    void setRatio(double ratio) {
        data.setRatio(ratio);
    }

    double getStartAngle() const {
        return data.getStartAngle();
    }

    double getStartParam() const {
        return data.getStartParam();
    }

    void setStartParam(double param) {
        data.setStartParam(param);
    }

    double getEndAngle() const {
        return data.getEndAngle();
    }

    double getEndParam() const {
        return data.getEndParam();
    }

    void setEndParam(double param) {
        data.setEndParam(param);
    }

    double getAngleLength() const {
        return data.getAngleLength();
    }

    double getAngleAt(double distance, RS::From from) const {
        return data.getAngleAt(distance, from);
    }

    bool isReversed() const {
        return data.isReversed();
    }

    void setReversed(bool reversed) {
        data.setReversed(reversed);
    }

    RVector getStartPoint() const {
        return data.getStartPoint();
    }

    RVector getEndPoint() const {
        return data.getEndPoint();
    }

    bool isFullEllipse() const {
        return data.isFullEllipse();
    }

    double getDirection1() const {
        return data.getDirection1();
    }

    double getDirection2() const {
        return data.getDirection2();
    }

    virtual bool reverse() {
        return data.reverse();
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return data.getSideOfPoint(point);
    }

    double getParamTo(const RVector& pos) {
        return data.getParamTo(pos);
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

    double getSweep() const {
        return data.getSweep();
    }

    RVector getPointAt(double angle) const {
        return data.getPointAt(angle);
    }

    QList<RSpline> approximateWithSplines() const {
        return data.approximateWithSplines();
    }

    RPolyline approximateWithArcs(int segments) const {
        return data.approximateWithArcs(segments);
    }

protected:
    virtual void print(QDebug dbg) const;

protected:
    REllipseData data;
};

Q_DECLARE_METATYPE(REllipseEntity*)
Q_DECLARE_METATYPE(QSharedPointer<REllipseEntity>)
Q_DECLARE_METATYPE(QSharedPointer<REllipseEntity>*)

#endif
