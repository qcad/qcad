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

#ifndef RARCDATA_H
#define RARCDATA_H

#include "entity_global.h"

#include "RBox.h"
#include "REntityData.h"
#include "RVector.h"
#include "RPolyline.h"
#include "RArc.h"

class RDocument;
class REntity;
class RLine;

/**
 * Stores and manages all data that defines the geometry and
 * appearance of an arc entity.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RArcData: public REntityData, public RArc {

    friend class RArcEntity;

protected:
    RArcData(RDocument* document, const RArcData& data);

public:
    RArcData();
    RArcData(const RArc& arc);
    RArcData(const RVector& center, double radius, double startAngle,
            double endAngle, bool reversed = false);

    virtual RS::EntityType getType() const {
        return RS::EntityArc;
    }
    RArc getArc() {
        return *this;
    }


    bool isValid() const {
        return RArc::isValid();
    }
    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX, QList<RObject::Id>* subEntityIds = NULL) const {
        return REntityData::getEndPoints(queryBox, subEntityIds);
    }
    virtual void setZ(double z) {
        RArc::setZ(z);
    }
    virtual void to2D() {
        RArc::to2D();
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
        return RArc::move(offset);
    }
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR) {
        return RArc::rotate(rotation, center);
    }
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR) {
        return RArc::scale(scaleFactors, center);
    }
    virtual bool mirror(const RLine& axis) {
        return RArc::mirror(axis);
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
        return RArc::stretch(area, offset);
    }


    RVector getCenter() const {
        return RArc::getCenter();
    }
    double getRadius() const {
        return RArc::getRadius();
    }
    double getBulge() const {
        return RArc::getBulge();
    }
    double getStartAngle() const {
        return RArc::getStartAngle();
    }
    double getEndAngle() const {
        return RArc::getEndAngle();
    }
    bool isReversed() const {
        return RArc::isReversed();
    }
    double getDirection1() const {
        return RArc::getDirection1();
    }
    double getDirection2() const {
        return RArc::getDirection2();
    }
    bool reverse() {
        return RArc::reverse();
    }

    RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
        return RArc::getTrimEnd(trimPoint, clickPoint);
    }
    bool trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return RArc::trimStartPoint(trimPoint, clickPoint, extend);
    }
    bool trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false) {
        return RArc::trimEndPoint(trimPoint, clickPoint, extend);
    }

    double getLength() const {
        return RArc::getLength();
    }
    double getAngleLength(bool allowForZeroLength = false) const {
        return RArc::getAngleLength(allowForZeroLength);
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    RPolyline approximateWithLines(double segmentLength) {
        return RArc::approximateWithLines(segmentLength);
    }

    virtual RShape* castToShape() {
        return this;
    }

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const {
        Q_UNUSED(queryBox)
        Q_UNUSED(ignoreComplex)
        Q_UNUSED(segment)
        Q_UNUSED(entityIds)

        return QList<QSharedPointer<RShape> >() <<
                QSharedPointer<RShape>(new RArc(*this));
    }
};

Q_DECLARE_METATYPE(RArcData)
Q_DECLARE_METATYPE(RArcData*)
Q_DECLARE_METATYPE(const RArcData*)
Q_DECLARE_METATYPE(QSharedPointer<RArcData>)

#endif
