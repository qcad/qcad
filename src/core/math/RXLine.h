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

#ifndef RXLINE_H
#define RXLINE_H

#include "../core_global.h"

#include "RLine.h"
#include "RS.h"
#include "RShape.h"
#include "RVector.h"

class RBox;
class RPolyline;

/**
 * Low-level mathematical representation of an infinite line.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RXLine: public RShape, public RDirected {
public:
    RXLine();
    RXLine(const RLine& line);
    RXLine(const RVector& basePoint, const RVector& directionVector);
    RXLine(const RVector& basePoint, double angle, double distance);
    virtual ~RXLine();

    RLine getLineShape() const {
        return RLine(basePoint, basePoint + directionVector);
    }

    virtual RXLine* clone() const {
        return new RXLine(*this);
    }

    RBox getBoundingBox() const;
    void to2D();

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const;

    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;

    virtual RVector getVectorTo(const RVector& point, bool limited = true, double strictRange = RMAXDOUBLE) const;

    RVector getBasePoint() const;
    void setBasePoint(const RVector& vector);
    RVector getSecondPoint() const;
    void setSecondPoint(const RVector& vector);
    RVector getDirectionVector() const;
    void setDirectionVector(const RVector& vector);

    RVector getMiddlePoint() const;
    
    double getLength() const;
    void setLength(double l);
    double getAngle() const;
    void setAngle(double a);

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    virtual RS::Side getSideOfPoint(const RVector& point) const;

    virtual RVector getStartPoint() const;
    virtual RVector getEndPoint() const;

    virtual void trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid);
    virtual void trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid);
    virtual RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint);

    virtual RLine getClippedLine(const RBox& box) const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool reverse();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

protected:
    virtual void print(QDebug dbg) const;

public:
    /**
     * \getter{getBasePoint}
     * \setter{setBasePoint}
     */
    RVector basePoint;
    /**
     * \getter{getDirectionVector}
     * \setter{setDirectionVector}
     */
    RVector directionVector;
};

Q_DECLARE_METATYPE(const RXLine*)
Q_DECLARE_METATYPE(RXLine*)
Q_DECLARE_METATYPE(RXLine)
Q_DECLARE_METATYPE(QSharedPointer<RXLine>)
Q_DECLARE_METATYPE(QSharedPointer<RXLine>*)

#endif
