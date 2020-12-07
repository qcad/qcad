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
#include "RDocument.h"
#include "REntity.h"
#include "RPoint.h"
#include "RVector.h"
#include "RLine.h"

/**
 * Stores and manages all data that defines the geometry and
 * appearance of a viewport entity.
 *
 * \scriptable
 * \copyable
 * \ingroup core
 */
class QCADCORE_EXPORT RViewportData: public REntityData, protected RPoint {

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

    virtual QList<RRefPoint> getInternalReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;
    virtual QList<RRefPoint> getReferencePoints(RS::ProjectionRenderingHint hint = RS::RenderTop) const;

    virtual bool moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers = Qt::NoModifier);

    virtual double getDistanceTo(const RVector& point, bool limited = true, double range = 0.0, bool draft = false, double strictRange = RMAXDOUBLE) const;

    virtual QList<QSharedPointer<RShape> > getShapes(const RBox& queryBox = RDEFAULT_RBOX, bool ignoreComplex = false, bool segment = false) const;

    QList<RLine> getEdges() const;

    virtual bool scale(const RVector& scaleFactors, const RVector& center);

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

    bool overall;
};

Q_DECLARE_METATYPE(RViewportData)
Q_DECLARE_METATYPE(RViewportData*)
Q_DECLARE_METATYPE(const RViewportData*)
Q_DECLARE_METATYPE(QSharedPointer<RViewportData>)
Q_DECLARE_METATYPE(RViewportData::Status)

#endif
