/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

#ifndef RARC_H
#define RARC_H

#include "../core_global.h"

#include "RDirected.h"
#include "RShape.h"
#include "RVector.h"

class RBox;
class RPolyline;

/**
 * Low-level mathematical representation of an arc.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RArc: public RShape, public RDirected {
public:
    RArc();
    RArc(const RVector& center, double radius, double startAngle,
            double endAngle, bool reversed = false);
    virtual ~RArc();

    virtual RArc* clone() const {
        return new RArc(*this);
    }

    virtual void to2D();

    bool isValid() const;
    bool isFullCircle() const;

    static RArc createFrom3Points(const RVector& startPoint,
                                  const RVector& point,
                                  const RVector& endPoint);
    static RArc createFrom2PBulge(const RVector& startPoint,
                                  const RVector& endPoint,
                                  double bulge);
    static RArc createTangential(const RVector& startPoint,
                                 const RVector& pos,
                                 double direction,
                                 double radius);

    virtual RBox getBoundingBox() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true, double strictRange = RMAXDOUBLE) const;

    RVector getCenter() const;
    void setCenter(const RVector& vector);
    double getRadius() const;
    void setRadius(double radius);
    double getStartAngle() const;
    void setStartAngle(double startAngle);
    double getEndAngle() const;
    void setEndAngle(double endAngle);
    bool isReversed() const;
    void setReversed(bool reversed);
    double getAngleLength(bool allowForZeroLength = false) const;
    bool isAngleWithinArc(double a) {
        return RMath::isAngleBetween(a, startAngle, endAngle, reversed);
    }

    double getDiameter() const;
    void setDiameter(double d);
    void setLength(double l);
    double getArea() const;
    void setArea(double a);

    double getDirection1() const;
    double getDirection2() const;

    RS::Side getSideOfPoint(const RVector& point) const;

    double getSweep() const;
    void setSweep(double s);
    double getLength() const;

    virtual RVector getStartPoint() const;
    virtual RVector getEndPoint() const;
    virtual RVector getPointAtAngle(double a) const;
    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;
    RVector getMiddlePoint() const;

    void moveStartPoint(const RVector& pos);
    void moveEndPoint(const RVector& pos);
    double getBulge() const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool reverse();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

    virtual RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint);
    virtual void trimStartPoint(const RVector& p);
    virtual void trimEndPoint(const RVector& p);
    virtual double getDistanceFromStart(const RVector& p) const;

    RPolyline approximateWithLines(double segmentLength);
    RPolyline approximateWithLinesTan(double segmentLength);

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
    /**
     * \getter{getStartAngle}
     * \setter{setStartAngle}
     */
    double startAngle;
    /**
     * \getter{getEndAngle}
     * \setter{setEndAngle}
     */
    double endAngle;
    /**
     * \getter{isReversed}
     * \setter{setReversed}
     */
    bool reversed;
};

Q_DECLARE_METATYPE(const RArc*)
Q_DECLARE_METATYPE(RArc*)
Q_DECLARE_METATYPE(RArc)
Q_DECLARE_METATYPE(QSharedPointer<RArc>)
Q_DECLARE_METATYPE(QSharedPointer<RArc>*)

#endif
