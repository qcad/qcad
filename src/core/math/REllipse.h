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

#ifndef RELLIPSE_H
#define RELLIPSE_H

#include "../core_global.h"

#include "RShape.h"
#include "RSpline.h"
#include "REllipseProxy.h"
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
class QCADCORE_EXPORT REllipse: public RShape {
public:
    REllipse();
    REllipse(const RVector& center,
             const RVector& majorPoint,
             double ratio,
             double startParam, double endParam,
             bool reversed);
    virtual ~REllipse();

    static REllipse createInscribed(const RVector& p1, const RVector& p2, const RVector& p3, const RVector& p4);

    virtual RShape::Type getShapeType() const {
        return Ellipse;
    }

    virtual REllipse* clone() const {
        return new REllipse(*this);
    }

    virtual bool isDirected() const {
        return true;
    }

    bool isValid();

    virtual void setZ(double z);

    virtual QList<RVector> getVectorProperties() const;
    virtual QList<double> getDoubleProperties() const;
    virtual QList<bool> getBoolProperties() const;

    virtual RBox getBoundingBox() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, int from = RS::FromAny) const;
    virtual QList<RVector> getPointCloud(double segmentLength) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true, double strictRange = RMAXDOUBLE) const;

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

    bool isAngleWithinArc(double a) const {
        if (isFullEllipse()) {
            return true;
        }
        return RMath::isAngleBetween(a, getStartAngle(), getEndAngle(), reversed);
    }
    bool isParamWithinArc(double a) const {
        if (isFullEllipse()) {
            return true;
        }
        return RMath::isAngleBetween(a, getStartParam(), getEndParam(), reversed);
    }

    bool isReversed() const;
    void setReversed(bool reversed);

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    virtual RS::Side getSideOfPoint(const RVector& point) const;

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

    bool contains(const RVector& p) const;

    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;

    double getAngleAtPoint(const RVector& pos) const;
    double getParamTo(const RVector& pos) const;
    double getRadiusAt(double param) const;
    RVector getPointAt(double param) const;
    RVector getMiddlePoint() const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);

    virtual bool reverse();

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

    void correctMajorMinor();
    double getSweep() const;

    QList<RVector> getBoxCorners();

    QList<RLine> getTangents(const RVector& point) const;

    QList<RSpline> approximateWithSplines() const;
    RPolyline approximateWithArcs(int segments) const;

    virtual QList<QSharedPointer<RShape> > getOffsetShapes(double distance, int number, RS::Side side, const RVector& position = RVector::invalid);
    virtual QList<QSharedPointer<RShape> > splitAt(const QList<RVector>& points) const;

    static bool hasProxy() {
        return ellipseProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setEllipseProxy(REllipseProxy* p) {
        if (ellipseProxy!=NULL) {
            delete ellipseProxy;
        }
        ellipseProxy = p;
    }

    /**
     * \nonscriptable
     */
    static REllipseProxy* getEllipseProxy() {
        return ellipseProxy;
    }

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

private:
    static REllipseProxy* ellipseProxy;
};

Q_DECLARE_METATYPE(const REllipse*)
Q_DECLARE_METATYPE(REllipse*)
Q_DECLARE_METATYPE(REllipse)
Q_DECLARE_METATYPE(QSharedPointer<REllipse>)
Q_DECLARE_METATYPE(QSharedPointer<REllipse>*)

#endif
