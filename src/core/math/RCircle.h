/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

#ifndef RCIRCLE_H
#define RCIRCLE_H

#include "../core_global.h"

#include "RShape.h"
#include "RVector.h"

class RBox;

/**
 * Low-level mathematical representation of a circle.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RCircle: public RShape {
public:
    RCircle();
    RCircle(const RVector& center, const double radius);
    virtual ~RCircle();

    virtual RCircle* clone() const {
        return new RCircle(*this);
    }

    static RCircle createFrom2Points(const RVector& p1, const RVector& p2);
    static RCircle createFrom3Points(const RVector& p1, const RVector& p2, const RVector& p3);

    virtual void to2D();

    virtual RBox getBoundingBox() const;
    virtual double getLength() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true) const;

    RVector getCenter() const;
    void setCenter(const RVector& vector);
    double getRadius() const;
    void setRadius(double radius);

    double getDiameter() const;
    void setDiameter(double d);
    double getCircumference() const;
    void setCircumference(double c);
    double getArea() const;
    void setArea(double a);

    bool contains(const RVector& p) const;
    bool touchesCircleInternally(const RCircle& other) const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();

protected:
    virtual void print(QDebug dbg) const;

public:
    /**
     * \getter{getCenter}
     * \setter{setCenter}
     */
    RVector center;
    /**
     * \getter{getRadius}
     * \setter{setRadius}
     */
    double radius;
};

Q_DECLARE_METATYPE(const RCircle*)
Q_DECLARE_METATYPE(RCircle*)
Q_DECLARE_METATYPE(RCircle)
Q_DECLARE_METATYPE(QSharedPointer<RCircle>)
Q_DECLARE_METATYPE(QSharedPointer<RCircle>*)

#endif
