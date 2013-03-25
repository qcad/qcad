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

#ifndef RLINE_H
#define RLINE_H

#include "../core_global.h"

#include "RDirected.h"
#include "RS.h"
#include "RShape.h"
#include "RVector.h"

class RBox;
class RPolyline;

/**
 * Low-level mathematical representation of a line.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RLine: public RShape, public RDirected {
public:
    RLine();
    RLine(const RVector& startPoint, const RVector& endPoint);
    virtual ~RLine();

    virtual RLine* clone() const {
        return new RLine(*this);
    }

    virtual void to2D();

    bool isValid() const;

    virtual RBox getBoundingBox() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true) const;

    virtual RVector getStartPoint() const;
    void setStartPoint(const RVector& vector);
    virtual RVector getEndPoint() const;
    void setEndPoint(const RVector& vector);

    RVector getMiddlePoint() const;
    
    double getLength() const;
    double getAngle() const;

    void setLength(double l);
    void setAngle(double a);

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    RS::Side getSideOfPoint(const RVector& point) const;

    void clipToXY(const RBox& box);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();
    virtual bool reverse();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint);
    virtual void trimStartPoint(const RVector& p);
    virtual void trimEndPoint(const RVector& p);
    virtual double getDistanceFromStart(const RVector& p) const;

protected:
    virtual void print(QDebug dbg) const;

public:
    /**
     * \getter{getStartPoint}
     * \setter{setStartPoint}
     */
    RVector startPoint;
    /**
     * \getter{getEndPoint}
     * \setter{setEndPoint}
     */
    RVector endPoint;
};

Q_DECLARE_METATYPE(const RLine*)
Q_DECLARE_METATYPE(RLine*)
Q_DECLARE_METATYPE(RLine)
Q_DECLARE_METATYPE(QSharedPointer<RLine>)
Q_DECLARE_METATYPE(QSharedPointer<RLine>*)

#endif
