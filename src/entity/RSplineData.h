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

#ifndef RSPLINEDATA_H
#define RSPLINEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "REntityData.h"
#include "RSpline.h"
#include "RVector.h"

class RDocument;
class RLine;
class RRefPoint;
class RPolyline;

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a spline entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RSplineData: public REntityData, public RSpline {

    friend class RSplineEntity;

protected:
    RSplineData(RDocument* document, const RSplineData& data);

public:
    RSplineData();
    RSplineData(const RSpline& spline);

    virtual RS::EntityType getType() const {
        return RS::EntitySpline;
    }
    virtual RBox getBoundingBox(bool ignoreEmpty=false) const;

    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX, QList<RObject::Id>* subEntityIds = NULL) const {
        return REntityData::getEndPoints(queryBox, subEntityIds);
    }
    virtual void setZ(double z) {
        RSpline::setZ(z);
    }
    virtual void to2D() {
        RSpline::to2D();
    }
    virtual QList<RVector> getMiddlePoints(const RBox& queryBox = RDEFAULT_RBOX, QList<RObject::Id>* subEntityIds = NULL) const {
        return REntityData::getMiddlePoints(queryBox, subEntityIds);
    }
    virtual QList<RVector> getCenterPoints(const RBox& queryBox = RDEFAULT_RBOX, QList<RObject::Id>* subEntityIds = NULL) const {
        return REntityData::getCenterPoints(queryBox, subEntityIds);
    }
    virtual QList<RVector> getArcReferencePoints(const RBox& queryBox = RDEFAULT_RBOX) const {
        return REntityData::getArcReferencePoints(queryBox);
    }
    virtual QList<RVector> getPointsWithDistanceToEnd(double distance, int from = RS::FromAny, const RBox& queryBox = RDEFAULT_RBOX, QList<RObject::Id>* subEntityIds = NULL) const {
        return REntityData::getPointsWithDistanceToEnd(distance, from, queryBox, subEntityIds);
    }
    virtual QList<RVector> getIntersectionPoints(const REntityData& other, bool limited = true, bool same = false, const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = true, QList<QPair<RObject::Id, RObject::Id> >* entityIds = NULL) const {
        return REntityData::getIntersectionPoints(other, limited, same, queryBox, ignoreComplex, entityIds);
    }
    virtual QList<RVector> getIntersectionPoints(const RShape& shape, bool limited = true, const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = true) const {
        return REntityData::getIntersectionPoints(shape, limited, queryBox, ignoreComplex);
    }
    virtual RVector getVectorTo(const RVector& point, bool limited=true, double strictRange = RMAXDOUBLE) const {
        return REntityData::getVectorTo(point, limited, strictRange);
    }
    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const {
        return REntityData::getDistanceTo(point, limited, range, draft, strictRange);
    }
    virtual bool intersectsWith(const RShape& shape) const {
        return REntityData::intersectsWith(shape);
    }
    virtual bool move(const RVector& offset) {
        return RSpline::move(offset);
    }
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR) {
        return RSpline::rotate(rotation, center);
    }
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR) {
        return RSpline::scale(scaleFactors, center);
    }
    virtual bool mirror(const RLine& axis) {
        return RSpline::mirror(axis);
    }
    virtual bool mirror(const RVector& axis1, const RVector& axis2) {
        return REntityData::mirror(axis1, axis2);
    }
    virtual bool flipHorizontal() {
        return REntityData::flipHorizontal();
    }
    virtual bool flipVertical() {
        return REntityData::flipVertical();
    }
    virtual bool stretch(const RPolyline& area, const RVector& offset) {
        return RSpline::stretch(area, offset);
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    void setShape(const RSpline& s) {
        copySpline(s);
    }

    void appendControlPoint(const RVector& point) {
        RSpline::appendControlPoint(point);
    }

    void appendFitPoint(const RVector& point) {
        RSpline::appendFitPoint(point);
    }

    void prependFitPoint(const RVector& point) {
        RSpline::prependFitPoint(point);
    }

    void insertFitPointAt(const RVector& point) {
        RSpline::insertFitPointAt(point);
    }

    void removeFitPointAt(const RVector& point) {
        RSpline::removeFitPointAt(point);
    }

    void setPeriodic(bool on) {
        RSpline::setPeriodic(on);
    }

    bool isValid() const {
        return RSpline::isValid();
    }

    int getDegree() const {
        return RSpline::getDegree();
    }

    double getDirection1() const {
        return RSpline::getDirection1();
    }

    double getDirection2() const {
        return RSpline::getDirection2();
    }

    RVector getStartPoint() const {
        return RSpline::getStartPoint();
    }

    RVector getEndPoint() const {
        return RSpline::getEndPoint();
    }

    void setStartPoint(const RVector& sp) {
        RSpline::setStartPoint(sp);
    }

    void setEndPoint(const RVector& ep) {
        RSpline::setEndPoint(ep);
    }

    bool reverse() {
        return RSpline::reverse();
    }

    RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
        return RSpline::getTrimEnd(trimPoint, clickPoint);
    }
    bool trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return RSpline::trimStartPoint(trimPoint, clickPoint, extend);
    }
    bool trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return RSpline::trimEndPoint(trimPoint, clickPoint, extend);
    }

    bool isClosed() const  {
        return RSpline::isClosed();
    }

    bool isPeriodic() const  {
        return RSpline::isPeriodic();
    }

    RVector getTangentAtStart() const {
        return RSpline::getTangentAtStart();
    }

    RVector getTangentAtEnd() const {
        return RSpline::getTangentAtEnd();
    }

    //void updateTangentsPeriodic() {
    //    RSpline::updateTangentsPeriodic();
    //}

    QList<RVector> getControlPoints() const {
        return RSpline::getControlPoints();
    }

    QList<RVector> getControlPointsWrapped() const {
        return RSpline::getControlPointsWrapped();
    }

    QList<RVector> getFitPoints() const {
        return RSpline::getFitPoints();
    }

    QList<double> getKnotVector() const {
        return RSpline::getKnotVector();
    }

    QList<double> getActualKnotVector() const {
        return RSpline::getActualKnotVector();
    }

    QList<double> getWeights() const {
        return RSpline::getWeights();
    }

    double getLength() const {
        return RSpline::getLength();
    }
    RVector getPointAt(double t) const {
        return RSpline::getPointAt(t);
    }
    RVector getPointAtDistance(double distance) const {
        return RSpline::getPointAtDistance(distance);
    }
    double getAngleAt(double distance, RS::From from = RS::FromStart) const {
        return RSpline::getAngleAt(distance, from);
    }

    RPolyline toPolyline(int segments) const;

    RPolyline approximateWithArcs(double tolerance, double radiusLimit=RDEFAULT_MIN1) const;

    void simplify(double tolerance) {
        RSpline s = RSpline::simplify(tolerance);
        setShape(s);
    }

    //RSpline getSubSpline(double d1, double d2) const {
    //    return RSpline::getSubSpline(d1, d2);
    //}

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const;

    virtual void update() const {
        //RSpline::update();
    }
};

Q_DECLARE_METATYPE(RSplineData)
Q_DECLARE_METATYPE(RSplineData*)
Q_DECLARE_METATYPE(const RSplineData*)
Q_DECLARE_METATYPE(QSharedPointer<RSplineData>)

#endif
