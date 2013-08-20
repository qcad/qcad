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

#ifndef RELLIPSE_H
#define RELLIPSE_H

#include "../core_global.h"

#include "RShape.h"
#include "RDirected.h"
#include "RLine.h"
#include "RVector.h"

class RBox;

/**
 * Low-level mathematical representation of an ellipse or ellipse arc.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT REllipse: public RShape, public RDirected {
public:
    REllipse();
    REllipse(const RVector& center,
             const RVector& majorPoint,
             double ratio,
             double startParam, double endParam,
             bool reversed);
    virtual ~REllipse();

    virtual REllipse* clone() const {
        return new REllipse(*this);
    }

    bool isValid();

    virtual void to2D();

    virtual RBox getBoundingBox() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true) const;

    void moveStartPoint(const RVector& pos, bool changeAngleOnly=false);
    void moveEndPoint(const RVector& pos, bool changeAngleOnly=false);

    QList<RVector> getFoci() const;

    RVector getCenter() const;
    void setCenter(const RVector& vector);
    RVector getMajorPoint() const;
    RVector getMinorPoint() const;
    void setMajorPoint(const RVector& vector);
    void setMinorPoint(const RVector &p);
    bool switchMajorMinor();
    double getRatio() const;
    void setRatio(double radius);

    double getStartParam() const;
    void setStartParam(double startParam);

    double getEndParam() const;
    void setEndParam(double endParam);

    double getStartAngle() const;
    void setStartAngle(double a);

    double angleToParam(double a) const;

    double getEndAngle() const;
    void setEndAngle(double a);

    double getAngleLength(bool allowForZeroLength = false) const;

    bool isReversed() const;
    void setReversed(bool reversed);

    double getDirection1() const;
    double getDirection2() const;

    virtual RVector getStartPoint() const;
    virtual RVector getEndPoint() const;
    double getMajorRadius() const;
    double getMinorRadius() const;
    double getAngle() const;
    void setAngle(double a);
    bool isFullEllipse() const;
    bool isCircular() const;
    double getLength() const;
    double getSimpsonLength(double f1, double f2) const;

    double getParamTo(const RVector& pos) const;
    double getRadiusAt(double angle) const;
    RVector getPointAt(double angle) const;
    RVector getMiddlePoint() const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);

    virtual bool reverse();

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

    virtual RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint);
    virtual void trimStartPoint(const RVector& p);
    virtual void trimEndPoint(const RVector& p);

    void correctMajorMinor();
    double getSweep() const;

    QList<RVector> getBoxCorners();

    QList<RLine> getTangents(const RVector& point) const;

protected:
    virtual void print(QDebug dbg) const;

public:
    /**
     * \getter{getCenter}
     * \setter{setCenter}
     */
    RVector center;
    /**
     * \getter{getMajorPoint}
     * \setter{setMajorPoint}
     */
    RVector majorPoint;
    /**
     * \getter{getRatio}
     * \setter{setRatio}
     */
    double ratio;
    /**
     * \getter{getStartParam}
     * \setter{setStartParam}
     */
    double startParam;
    /**
     * \getter{getEndParam}
     * \setter{setEndParam}
     */
    double endParam;
    /**
     * \getter{isReversed}
     * \setter{setReversed}
     */
    bool reversed;
};

Q_DECLARE_METATYPE(const REllipse*)
Q_DECLARE_METATYPE(REllipse*)
Q_DECLARE_METATYPE(REllipse)
Q_DECLARE_METATYPE(QSharedPointer<REllipse>)
Q_DECLARE_METATYPE(QSharedPointer<REllipse>*)

#endif
