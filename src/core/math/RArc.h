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

#ifndef RARC_H
#define RARC_H

#include "../core_global.h"

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
class QCADCORE_EXPORT RArc: public RShape {
public:
    RArc();
    RArc(double cx, double cy, double radius, double startAngle,
         double endAngle, bool reversed = false);
    RArc(const RVector& center, double radius, double startAngle,
            double endAngle, bool reversed = false);

    virtual RShape::Type getShapeType() const {
        return Arc;
    }

    virtual RArc* clone() const {
        return new RArc(*this);
    }

    virtual bool isDirected() const {
        return true;
    }

    virtual void setZ(double z);

    virtual QList<RVector> getVectorProperties() const;
    virtual QList<double> getDoubleProperties() const;
    virtual QList<bool> getBoolProperties() const;

    bool isValid() const;
    bool isFullCircle(double tolerance = RS::AngleTolerance) const;

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
    static QList<RArc> createBiarc(const RVector& startPoint, double startDirection,
                                   const RVector& endPoint, double endDirection, bool secondTry = false);

    virtual RBox getBoundingBox() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getArcReferencePoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, int from = RS::FromAny) const;
    virtual QList<RVector> getPointCloud(double segmentLength) const;

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
    bool isAngleWithinArc(double a) const {
        return RMath::isAngleBetween(a, startAngle, endAngle, reversed);
    }

    double getDiameter() const;
    void setDiameter(double d);
    void setLength(double l);
    double getArea() const;
    void setArea(double a);
    double getChordArea() const;

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    virtual RS::Side getSideOfPoint(const RVector& point) const;

    double getSweep() const;
    void setSweep(double s);
    double getLength() const;

    virtual RVector getStartPoint() const;
    virtual RVector getEndPoint() const;
    RVector getPointAtAngle(double a) const;
    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;
    virtual RVector getMiddlePoint() const;

    void moveStartPoint(const RVector& pos);
    void moveEndPoint(const RVector& pos);
    void moveMiddlePoint(const RVector& pos);
    double getBulge() const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool reverse();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

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

    RPolyline approximateWithLines(double segmentLength, double angle = 0.0) const;
    RPolyline approximateWithLinesTan(double segmentLength, double angle = 0.0) const;

    QList<RLine> getTangents(const RVector& point) const;

    virtual QList<QSharedPointer<RShape> > getOffsetShapes(double distance, int number, RS::Side side, const RVector& position = RVector::invalid) {
        return RShape::getOffsetArcs(*this, distance, number, side, position);
    }

    virtual QList<QSharedPointer<RShape> > splitAt(const QList<RVector>& points) const;

    QList<RArc> splitAtQuadrantLines() const;

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
