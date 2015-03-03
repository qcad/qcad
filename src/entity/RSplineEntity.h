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

#ifndef RSPLINEENTITY_H
#define RSPLINEENTITY_H

#include "entity_global.h"

#include "REntity.h"
#include "RSplineData.h"

class RDocument;
class RExporter;

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Spline entity.
 *
 * \scriptable
 * \sharedPointerSupport
 * \ingroup entity
 */
class QCADENTITY_EXPORT RSplineEntity: public REntity {

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

    static RPropertyTypeId PropertyControlPointNX;
    static RPropertyTypeId PropertyControlPointNY;
    static RPropertyTypeId PropertyControlPointNZ;
    static RPropertyTypeId PropertyFitPointNX;
    static RPropertyTypeId PropertyFitPointNY;
    static RPropertyTypeId PropertyFitPointNZ;
    static RPropertyTypeId PropertyKnotN;
    static RPropertyTypeId PropertyPeriodic;
    static RPropertyTypeId PropertyDegree;

    static RPropertyTypeId PropertyLength;

public:
    RSplineEntity(RDocument* document, const RSplineData& data,
        RObject::Id objectId = RObject::INVALID_ID);
    virtual ~RSplineEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RSplineEntity));
    }

    virtual RSplineEntity* clone() const {
        return new RSplineEntity(*this);
    }

    virtual RS::EntityType getType() const {
        return RS::EntitySpline;
    }

    bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false);

    virtual void exportEntity(RExporter& e, bool preview=false, bool forceSelected=false) const;

    virtual void setUndone(bool on) {
        REntity::setUndone(on);
        data.update();
    }

    virtual RSplineData& getData() {
        return data;
    }

    virtual const RSplineData& getData() const {
        return data;
    }

    void setShape(const RSpline& s);

    bool isValid() const {
        return data.isValid();
    }

    int getDegree() const {
        return data.getDegree();
    }

    double getDirection1() const {
        return data.getDirection1();
    }

    double getDirection2() const {
        return data.getDirection2();
    }

    RS::Ending getTrimEnd(const RVector& coord,
                            const RVector& trimPoint) {
        return data.getTrimEnd(coord, trimPoint);
    }

    void trimStartPoint(const RVector& p) {
        return data.trimStartPoint(p);
    }
    void trimEndPoint(const RVector& p) {
        return data.trimEndPoint(p);
    }

    RVector getTangentAtStart() const {
        return data.getTangentAtStart();
    }

    RVector getTangentAtEnd() const {
        return data.getTangentAtEnd();
    }

    bool isClosed() const {
        return data.isClosed();
    }

    bool isPeriodic() const {
        return data.isPeriodic();
    }

    void appendControlPoint(const RVector& point) {
        data.appendControlPoint(point);
    }

    void setPeriodic(bool on) {
        data.setPeriodic(on);
    }

    QList<RVector> getControlPoints() const {
        return data.getControlPoints();
    }

    QList<RVector> getControlPointsWrapped() const {
        return data.getControlPointsWrapped();
    }

    int countControlPoints() const {
        return data.countControlPoints();
    }

    QList<RVector> getFitPoints() const {
        return data.getFitPoints();
    }

    bool hasFitPoints() const {
        return data.hasFitPoints();
    }

    QList<double> getKnotVector() const {
        return data.getKnotVector();
    }

    QList<double> getActualKnotVector() const {
        return data.getActualKnotVector();
    }

    QList<double> getWeights() const {
        return data.getWeights();
    }

    //RSpline getSubSpline(double d1, double d2) const {
    //    return data.getSubSpline(d1, d2);
    //}

    double getLength() const {
        return data.getLength();
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

    virtual int getComplexity() const;

    QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const {
        return data.getExploded(segments);
    }

    /*
    double getAngle() const {
        return data.getAngle();
    }

    double getDirection1() const {
        return data.getDirection1();
    }

    double getDirection2() const {
        return data.getDirection2();
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return data.getSideOfPoint(point);
    }
    */

protected:
    virtual void print(QDebug dbg) const;

protected:
    RSplineData data;
};

Q_DECLARE_METATYPE(RSplineEntity*)
Q_DECLARE_METATYPE(QSharedPointer<RSplineEntity>)
Q_DECLARE_METATYPE(QSharedPointer<RSplineEntity>*)

#endif
