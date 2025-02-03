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

#ifndef RELLIPSEDATA_H
#define RELLIPSEDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "REntityData.h"
#include "RVector.h"
#include "REllipse.h"

class RDocument;
class RLine;
class RRefPoint;
class RPolyline;

/**
 * Stores and manages all data that defines the geometry and
 * appearance of an ellipse entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT REllipseData: public REntityData, public REllipse {

    friend class REllipseEntity;

protected:
    REllipseData(RDocument* document, const REllipseData& data);

public:
    REllipseData();
    REllipseData(const REllipse& ellipse);
    REllipseData(
        const RVector& center, 
        const RVector& majorPoint, 
        double ratio, 
        double startParam, double endParam, 
        bool reversed = false);

    virtual RS::EntityType getType() const {
        return RS::EntityEllipse;
    }
    REllipse getEllipse() {
        return *this;
    }

    bool isValid() const {
        return REllipse::isValid();
    }
    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX, QList<RObject::Id>* subEntityIds = NULL) const {
        return REntityData::getEndPoints(queryBox, subEntityIds);
    }
    virtual void setZ(double z) {
        REllipse::setZ(z);
    }
    virtual void to2D() {
        REllipse::to2D();
    }
    virtual RBox getBoundingBox(bool ignoreEmpty=false) const {
        return REntityData::getBoundingBox();
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
        return REllipse::move(offset);
    }
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR) {
        return REllipse::rotate(rotation, center);
    }
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR) {
        return REllipse::scale(scaleFactors, center);
    }
    virtual bool mirror(const RLine& axis) {
        return REllipse::mirror(axis);
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
        return REllipse::stretch(area, offset);
    }

    QList<RVector> getFoci() const {
        return REllipse::getFoci();
    }
    RVector getCenter() const {
        return REllipse::getCenter();
    }
    double getMajorRadius() const {
        return REllipse::getMajorRadius();
    }
    RVector getMajorPoint() const {
        return REllipse::getMajorPoint();
    }
    RVector getMinorPoint() const {
        return REllipse::getMinorPoint();
    }
    void setMinorPoint(const RVector& p) {
        REllipse::setMinorPoint(p);
    }
    double getRatio() const {
        return REllipse::getRatio();
    }
    double getAngle() const {
        return REllipse::getAngle();
    }
    double getStartParam() const {
        return REllipse::getStartParam();
    }
    double getEndParam() const {
        return REllipse::getEndParam();
    }
    bool isFullEllipse() const {
        return REllipse::isFullEllipse();
    }

    double getParamTo(const RVector& pos) {
        return REllipse::getParamTo(pos);
    }

    double getLength() const {
        return REllipse::getLength();
    }

    double getSweep() const {
        return REllipse::getSweep();
    }

    RVector getPointAt(double angle) const {
        return REllipse::getPointAt(angle);
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual bool reverse() {
        return REllipse::reverse();
    }

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const {
        Q_UNUSED(queryBox)
        Q_UNUSED(ignoreComplex)
        Q_UNUSED(segment)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new REllipse(*this));
    }
};

Q_DECLARE_METATYPE(REllipseData)
Q_DECLARE_METATYPE(REllipseData*)
Q_DECLARE_METATYPE(const REllipseData*)
Q_DECLARE_METATYPE(QSharedPointer<REllipseData>)

#endif
