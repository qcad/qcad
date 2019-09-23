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

#ifndef RLINE_H
#define RLINE_H

#include "../core_global.h"

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
class QCADCORE_EXPORT RLine: public RShape {
public:
    RLine();
    RLine(double x1, double y1, double x2, double y2);
    RLine(const RVector& startPoint, const RVector& endPoint);
    RLine(const RVector& startPoint, double angle, double distance);

    virtual RShape::Type getShapeType() const {
        return Line;
    }

    virtual RLine* clone() const {
        return new RLine(*this);
    }

    virtual bool isDirected() const {
        return true;
    }

    virtual void setZ(double z);

    virtual QList<RVector> getVectorProperties() const;

    bool isValid() const;

    virtual RBox getBoundingBox() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, int from = RS::FromAny) const;
    virtual QList<RVector> getPointCloud(double segmentLength) const;

    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true, double strictRange = RMAXDOUBLE) const;

    virtual RVector getStartPoint() const;
    void setStartPoint(const RVector& vector);
    virtual RVector getEndPoint() const;
    void setEndPoint(const RVector& vector);

    virtual RVector getMiddlePoint() const;
    
    double getLength() const;
    double getAngle() const;

    void setLength(double l, bool fromStart = true);
    void setAngle(double a);

    bool isParallel(const RLine& line) const;

    bool isVertical(double tolerance = RS::PointTolerance) const;
    bool isHorizontal(double tolerance = RS::PointTolerance) const;

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    virtual RS::Side getSideOfPoint(const RVector& point) const;

    void clipToXY(const RBox& box);

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();
    virtual bool reverse();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual bool moveTo(const RVector& dest);

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

    virtual RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint);
    virtual bool trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false);
    virtual bool trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false);
    virtual bool trimStartPoint(double trimDist) {
        return RShape::trimStartPoint(trimDist);
    }
    virtual bool trimEndPoint(double trimDist) {
        return RShape::trimEndPoint(trimDist);
    }
    virtual double getDistanceFromStart(const RVector& p) const;

    virtual QList<QSharedPointer<RShape> > getOffsetShapes(double distance, int number, RS::Side side, const RVector& position = RVector::invalid) {
        return RShape::getOffsetLines(*this, distance, number, side, position);
    }

    virtual QList<QSharedPointer<RShape> > splitAt(const QList<RVector>& points) const;

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
