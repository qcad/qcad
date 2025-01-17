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

#ifndef RVIEWPORTDATA_H
#define RVIEWPORTDATA_H

#include "core_global.h"

#include "RBox.h"
#include "REntity.h"
#include "RPoint.h"
#include "RVector.h"
#include "RLine.h"

class RDocument;

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a viewport entity.
 *
 * \scriptable
 * \copyable
 * \ingroup core
 */
class QCADCORE_EXPORT RViewportData: public REntityData, public RPoint {

    friend class RViewportEntity;

protected:
    RViewportData(RDocument* document, const RViewportData& data);

public:
    enum Status {
        Off = 0x20000
    };

public:
    RViewportData();
//    RViewportData(const RVector& center, double width, double height, double scale,
//        const RVector& viewCenter,
//        const RVector& viewTarget);

    virtual RS::EntityType getType() const {
        return RS::EntityViewport;
    }

    bool isValid() const {
        return RPoint::isValid();
    }
    virtual QList<RVector> getEndPoints(const RBox& queryBox = RDEFAULT_RBOX, QList<RObject::Id>* subEntityIds = NULL) const {
        return REntityData::getEndPoints(queryBox, subEntityIds);
    }
    virtual void setZ(double z) {
        RPoint::setZ(z);
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
    virtual bool intersectsWith(const RShape& shape) const {
        return REntityData::intersectsWith(shape);
    }
    virtual bool move(const RVector& offset) {
        return RPoint::move(offset);
    }
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR) {
        return RPoint::rotate(rotation, center);
    }
    virtual bool mirror(const RLine& axis) {
        return RPoint::mirror(axis);
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
        return RPoint::stretch(area, offset);
    }

    virtual RBox getBoundingBox(bool ignoreEmpty) const;

    virtual void to2D();

    virtual RBox getBoundingBox() const {
        return getBoundingBox(false);
    }

    virtual RShape* castToShape() {
        return this;
    }

    int getViewportId() const {
       return viewportId;
    }

    void setViewportId(int id) {
        viewportId = id;
    }

    int getStatus() const {
        return status;
    }

    void setStatus(int s) {
        status = s;
    }

    RVector getCenter() const {
       return position;
    }

    void setCenter(const RVector& c) {
        position = c;
    }

    RVector getViewCenter() const {
       return viewCenter;
    }

    void setViewCenter(const RVector& c) {
        viewCenter = c;
    }

    RVector getViewTarget() const {
        return viewTarget;
    }

    void setViewTarget(const RVector& t) {
        viewTarget = t;
    }

    double getWidth() const {
        return width;
    }

    void setWidth(double w) {
        width = w;
    }

    double getHeight() const {
        return height;
    }

    void setHeight(double h) {
        height = h;
    }

    double getScale() const {
        return scaleFactor;
    }

    void setScale(double s) {
        scaleFactor = s;
    }

    double getRotation() const {
        return rotation;
    }

    void setRotation(double r) {
        rotation = r;
    }

    bool isOverall() const {
        return overall;
    }

    void setOverall(bool on) {
        overall = on;
    }

    bool isOff() const {
        return testStatusFlag(Off);
    }

    void setOff(bool v) {
        setStatusFlag(Off, v);
    }

    RVector getViewOffset() const;

    virtual QList<RRefPoint> getInternalReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop, QList<REntity::Id>* subEntityIds = NULL) const;
    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const;

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false, QList<RObject::Id>* entityIds = NULL) const;

    QList<RLine> getEdges() const;

    virtual bool scale(const RVector& scaleFactors, const RVector& center);

    QList<RLayer::Id> getFrozenLayerIds() const {
        return frozenLayerIds;
    }

    void setFrozenLayerIds(const QList<RLayer::Id>& layerIds) {
        frozenLayerIds = layerIds;
    }

protected:
    void setStatusFlag(Status s, bool on) {
        if (on) {
            status |= s;
        } else {
            status &= ~s;
        }
    }

    bool testStatusFlag(Status s) const {
        return (status & s) == s;
    }

private:
    int viewportId;
    int status;
    double width;
    double height;
    double scaleFactor;
    double rotation;

    RVector viewCenter;
    RVector viewTarget;

    QList<RLayer::Id> frozenLayerIds;

    bool overall;
};

Q_DECLARE_METATYPE(RViewportData)
Q_DECLARE_METATYPE(RViewportData*)
Q_DECLARE_METATYPE(const RViewportData*)
Q_DECLARE_METATYPE(QSharedPointer<RViewportData>)
Q_DECLARE_METATYPE(RViewportData::Status)

#endif
