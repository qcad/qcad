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

    static RPropertyTypeId PropertyControlPointNX;
    static RPropertyTypeId PropertyControlPointNY;
    static RPropertyTypeId PropertyControlPointNZ;
    static RPropertyTypeId PropertyFitPointNX;
    static RPropertyTypeId PropertyFitPointNY;
    static RPropertyTypeId PropertyFitPointNZ;
    static RPropertyTypeId PropertyKnotN;
    static RPropertyTypeId PropertyPeriodic;
    static RPropertyTypeId PropertyDegree;

    static RPropertyTypeId PropertyUseStartTangent;
    static RPropertyTypeId PropertyStartTangentX;
    static RPropertyTypeId PropertyStartTangentY;
    static RPropertyTypeId PropertyStartTangentZ;
    static RPropertyTypeId PropertyUseEndTangent;
    static RPropertyTypeId PropertyEndTangentX;
    static RPropertyTypeId PropertyEndTangentY;
    static RPropertyTypeId PropertyEndTangentZ;

    static RPropertyTypeId PropertyLength;
    static RPropertyTypeId PropertyTotalLength;

public:
    RSplineEntity(RDocument* document, const RSplineData& data);
    RSplineEntity(const RSplineEntity& other);
    virtual ~RSplineEntity();

    static void init();

    static QSet<RPropertyTypeId> getStaticPropertyTypeIds() {
        return RPropertyTypeId::getPropertyTypeIds(typeid(RSplineEntity));
    }

    virtual RSplineEntity* clone() const {
        return new RSplineEntity(*this);
    }

    virtual bool setProperty(RPropertyTypeId propertyTypeId, const QVariant& value,
        RTransaction* transaction=NULL);
    virtual QPair<QVariant, RPropertyAttributes> getProperty(
            RPropertyTypeId& propertyTypeId,
            bool humanReadable = false, bool noAttributes = false, bool showOnRequest = false);

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

    double getTDelta() const {
        return data.getTDelta();
    }

    double getTMin() const {
        return data.getTMin();
    }

    double getTMax() const {
        return data.getTMax();
    }

    double getTAtPoint(const RVector& point) const {
        return data.getTAtPoint(point);
    }

    double getTAtDistance(double distance) const {
        return data.getTAtDistance(distance);
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

    RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
        return data.getTrimEnd(trimPoint, clickPoint);
    }

    bool trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return data.trimStartPoint(trimPoint, clickPoint, extend);
    }
    bool trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return data.trimEndPoint(trimPoint, clickPoint, extend);
    }

    QList<RSpline> splitAtPoints(const QList<RVector>& points) const {
        return data.splitAtPoints(points);
    }
    QList<RSpline> splitAtParams(const QList<double>& params) const {
        return data.splitAtParams(params);
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

    bool isGeometricallyClosed(double tolerance=RS::PointTolerance) const {
        return data.isGeometricallyClosed(tolerance);
    }

    bool isPeriodic() const {
        return data.isPeriodic();
    }

    void appendControlPoint(const RVector& point) {
        data.appendControlPoint(point);
    }

    void appendFitPoint(const RVector& point) {
        data.appendFitPoint(point);
    }

    void prependFitPoint(const RVector& point) {
        data.prependFitPoint(point);
    }

    void insertFitPointAt(const RVector& point) {
        data.insertFitPointAt(point);
    }

    void removeFitPointAt(const RVector& point) {
        data.removeFitPointAt(point);
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

    RVector getControlPointAt(int i) const {
        return data.getControlPointAt(i);
    }

    QList<RVector> getFitPoints() const {
        return data.getFitPoints();
    }

    bool hasFitPoints() const {
        return data.hasFitPoints();
    }

    int countFitPoints() const {
        return data.countFitPoints();
    }

    RVector getFitPointAt(int i) const {
        return data.getFitPointAt(i);
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

    RVector getPointAt(double t) const {
        return data.getPointAt(t);
    }

    RVector getPointAtDistance(double distance) const {
        return data.getPointAtDistance(distance);
    }

    double getAngleAt(double distance, RS::From from = RS::FromStart) const {
        return data.getAngleAt(distance, from);
    }

    RVector getStartPoint() const {
        return data.getStartPoint();
    }

    RVector getEndPoint() const {
        return data.getEndPoint();
    }

    void setStartPoint(const RVector& sp) {
        return data.setStartPoint(sp);
    }

    void setEndPoint(const RVector& ep) {
        return data.setEndPoint(ep);
    }

    RPolyline toPolyline(int segments) const {
        return data.toPolyline(segments);
    }

    RPolyline approximateWithArcs(double tolerance) const {
        return data.approximateWithArcs(tolerance);
    }

    bool reverse() {
        return data.reverse();
    }

    RS::Side getSideOfPoint(const RVector& point) const {
        return data.getSideOfPoint(point);
    }

    virtual int getComplexity() const;

    QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const {
        return data.getExploded(segments);
    }

    void simplify(double tolerance) {
        data.simplify(tolerance);
    }

    QList<RSpline> getBezierSegments(const RBox& queryBox = RDEFAULT_RBOX) const {
        return data.getBezierSegments(queryBox);
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
