/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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

#ifndef RRAY_H
#define RRAY_H

#include "../core_global.h"

#include "RXLine.h"
#include "RS.h"
#include "RShape.h"
#include "RVector.h"

class RBox;
class RPolyline;

/**
 * Low-level mathematical representation of a ray.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RRay: public RXLine {
public:
    RRay();
    RRay(const RLine& line);
    RRay(const RVector& basePoint, const RVector& directionVector);
    RRay(const RVector& basePoint, double angle, double distance);
    virtual ~RRay();

    virtual RRay* clone() const {
        return new RRay(*this);
    }

    virtual void trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid);
    virtual QList<RVector> getPointsWithDistanceToEnd(double distance, RS::From from) const;

    virtual bool reverse();
    virtual RLine getClippedLine(const RBox& box) const;
    virtual RVector getVectorTo(const RVector& point, bool limited = true, double strictRange = RMAXDOUBLE) const;

    virtual bool stretch(const RPolyline& area, const RVector& offset);

protected:
    virtual void print(QDebug dbg) const;
};

Q_DECLARE_METATYPE(const RRay*)
Q_DECLARE_METATYPE(RRay*)
Q_DECLARE_METATYPE(RRay)
Q_DECLARE_METATYPE(QSharedPointer<RRay>)
Q_DECLARE_METATYPE(QSharedPointer<RRay>*)

#endif
