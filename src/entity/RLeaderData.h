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

#ifndef RLEADERDATA_H
#define RLEADERDATA_H

#include "entity_global.h"

#include "REntityData.h"
#include "RPolyline.h"
#include "RVector.h"

class RDocument;
class RLine;
class RTriangle;
class RRefPoint;

/**
 * Leader entity data class.
 *
 * \scriptable
 * \copyable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RLeaderData: public REntityData, public RPolyline {
    friend class RLeaderEntity;

protected:
    RLeaderData(RDocument* document, const RLeaderData& data);

public:
    RLeaderData();
    RLeaderData(const RPolyline& polyline, bool arrowHead);

    virtual RS::EntityType getType() const {
        return RS::EntityLeader;
    }
    virtual RShape* castToShape() {
        return this;
    }

    bool isValid() const {
        return RPolyline::isValid();
    }
    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX, QList<RObject::Id>* subEntityIds = NULL) const {
        return REntityData::getEndPoints(queryBox, subEntityIds);
    }
    virtual void setZ(double z) {
        RPolyline::setZ(z);
    }
    virtual void to2D() {
        RPolyline::to2D();
    }
    virtual bool reverse() {
        return RPolyline::reverse();
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
        return RPolyline::move(offset);
    }
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR) {
        return RPolyline::rotate(rotation, center);
    }
    virtual bool mirror(const RLine& axis) {
        return RPolyline::mirror(axis);
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

    double getDimasz(bool scale = true) const;

    void setDimasz(double v);

    double getDimscale() const;
    void setDimscale(double f);

    virtual void scaleVisualProperties(double scaleFactor);

    void setArrowHead(bool on);
    bool hasArrowHead() const {
        return arrowHead;
    }

    bool canHaveArrowHead() const;
    bool updateArrowHead() const;

//    void setPolyline(const RPolyline& polyline) {
//        *((RPolyline*)this) = polyline;
//    }

    RVector getEndPoint() const {
        return RPolyline::getEndPoint();
    }

    RVector getStartPoint() const {
        return RPolyline::getStartPoint();
    }

    int countVertices() const {
        return RPolyline::countVertices();
    }

    int countSegments() const {
        return RPolyline::countSegments();
    }

    void appendVertex(const RVector& vertex) {
        RPolyline::appendVertex(vertex);
    }

    bool isSplineShaped() const {
        return splineShaped;
    }

    void setSplineShaped(bool on) {
        splineShaped = on;
    }

    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const {
        return RPolyline::getExploded(segments);
    }

    virtual bool scale(const RVector& scaleFactors, const RVector& center);
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const;
    RTriangle getArrowShape() const;

    RObject::Id getDimLeaderBlockId() const;
    void setDimLeaderBlockId(RObject::Id id);

    virtual void update() const;

    void clearStyleOverrides() {
        dimscale = -1.0;
        dimasz = -1.0;
        update();
    }

private:
    /** Arrow head on / off */
    mutable bool arrowHead;
    /** Arrow size */
    double dimasz;
    /** Dimension scale */
    double dimscale;
    /** Block to use instead of arrow */
    RObject::Id dimLeaderBlockId;
    /** Spline shaped leader */
    bool splineShaped;
};

Q_DECLARE_METATYPE(RLeaderData)
Q_DECLARE_METATYPE(RLeaderData*)
Q_DECLARE_METATYPE(const RLeaderData*)
Q_DECLARE_METATYPE(QSharedPointer<RLeaderData>)

#endif
