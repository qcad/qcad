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

#ifndef RPOINT_H
#define RPOINT_H

#include "../core_global.h"

#include "RShape.h"
#include "RVector.h"
#include "RBox.h"

class RLine;

/**
 * Low-level mathematical representation of a point.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RPoint: public RShape {
public:
    RPoint();
    RPoint(double x, double y);
    RPoint(const RVector& position);
    virtual ~RPoint();

    virtual RShape::Type getShapeType() const {
        return Point;
    }

    virtual QSharedPointer<RShape> clone() const {
        return QSharedPointer<RShape>(new RPoint(*this));
    }

    QSharedPointer<RPoint> cloneToPoint() const {
        return QSharedPointer<RPoint>(new RPoint(*this));
    }

    virtual void setZ(double z);

    virtual QList<RVector> getVectorProperties() const;

    RVector getPosition() const {
       return position;
    }

    void setPosition(const RVector& p) {
       position = p;
    }

    virtual RBox getBoundingBox() const;
    virtual double getLength() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, int from = RS::FromAny) const;
    virtual QList<RVector> getPointCloud(double segmentLength) const;

    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true, double strictRange = RMAXDOUBLE) const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

#if QT_VERSION >= 0x060000
    /**
     * copy function for Qt 6 scripts:
     * \nonscriptable
     */
    RPoint copy() const {
        return *this;
    }
#endif

protected:
    virtual void print(QDebug dbg) const;

public:
    /**
     * \getter{getPosition}
     * \setter{setPosition}
     */
    RVector position;
    double thickness;
    RVector normal;
};

Q_DECLARE_METATYPE(RPoint)
Q_DECLARE_METATYPE(RPoint*)
Q_DECLARE_METATYPE(QSharedPointer<RPoint>)
Q_DECLARE_METATYPE(QSharedPointer<RPoint>*)

#endif
