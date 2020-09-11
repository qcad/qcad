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

#ifndef RSPLINE_H
#define RSPLINE_H

#include "../core_global.h"

#include "RArc.h"
#include "RBox.h"
#include "RExplodable.h"
#include "RShape.h"
#include "RSplineProxy.h"
#include "RVector.h"

#include "RPolyline.h"

#ifndef R_NO_OPENNURBS
#include "opennurbs/opennurbs.h"
#endif

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Low-level mathematical representation of a spline.
 *
 * The spline may be defined by its control points or by its fit points but
 * not both.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RSpline: public RShape, public RExplodable {
public:
    RSpline();
    RSpline(const RSpline& other);
    RSpline(const QList<RVector>& controlPoints, int degree);
    //virtual ~RSpline();

    RSpline& operator =(const RSpline& other);

    virtual RShape::Type getShapeType() const {
        return Spline;
    }

    virtual RSpline* clone() const {
        return new RSpline(*this);
    }

    virtual bool isDirected() const {
        return true;
    }

    void copySpline(const RSpline& other);

    static QList<RSpline> createSplinesFromArc(const RArc& arc);
    static RSpline createBezierFromSmallArc(double r, double a1, double a2);

    virtual void setZ(double z);

    virtual QList<RVector> getVectorProperties() const;
    virtual QList<int> getIntProperties() const;
    virtual QList<double> getDoubleProperties() const;
    virtual QList<bool> getBoolProperties() const;

    virtual bool isInterpolated() const {
        return true;
    }

    //virtual RVector getClosestPointOnShape(const RVector& p, bool limited) const;

    void appendControlPoint(const RVector& point);
    void appendControlPoints(const QList<RVector>& points);
    void removeLastControlPoint();
    void setControlPoints(const QList<RVector>& points);
    QList<RVector> getControlPoints() const;
    QList<RVector> getControlPointsWrapped() const;
    int countControlPoints() const;
    RVector getControlPointAt(int i) const;

    void appendFitPoint(const RVector& point);
    void prependFitPoint(const RVector& point);
    void insertFitPointAt(const RVector& point);
    void insertFitPointAt(double t, const RVector& point);
    void removeFitPointAt(const RVector& point);
    void removeFirstFitPoint();
    void removeLastFitPoint();
    void setFitPoints(const QList<RVector>& points);
    QList<RVector> getFitPoints() const;
    int countFitPoints() const;
    bool hasFitPoints() const;
    RVector getFitPointAt(int i) const;

    QList<double> getKnotVector() const;
    QList<double> getActualKnotVector() const;
    void setKnotVector(const QList<double>& knots);
    void appendKnot(double k);
    QList<double> getWeights() const;

    void setDegree(int d);
    int getDegree() const;

    int getOrder() const;

    void setPeriodic(bool on);
    //bool isClosedPeriodic() const;

    bool isClosed() const;
    bool isGeometricallyClosed(double tolerance=RS::PointTolerance) const;
    bool isPeriodic() const;

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    virtual RS::Side getSideOfPoint(const RVector& point) const;

    virtual RVector getStartPoint() const;
    virtual RVector getEndPoint() const;

    void setStartPoint(const RVector& v);
    void setEndPoint(const RVector& v);

    void setTangents(const RVector& start, const RVector& end);
    void unsetTangents();

    void setTangentAtStart(const RVector& t);
    RVector getTangentAtStart() const;
    void unsetTangentAtStart();
    void setTangentAtEnd(const RVector& t);
    RVector getTangentAtEnd() const;
    void unsetTangentAtEnd();

    void updateTangentsPeriodic();

    virtual RBox getBoundingBox() const;

    virtual double getLength() const;
    RVector getPointAt(double t) const;
    RVector getPointAtDistance(double distance) const;
    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;

    virtual QList<RVector> getEndPoints() const;
    virtual RVector getMiddlePoint() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, int from = RS::FromAny) const;
    virtual QList<RVector> getPointCloud(double segmentLength) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true, double strictRange = RMAXDOUBLE) const;
    virtual bool isOnShape(const RVector& point,
                           bool limited = true,
                           double tolerance = RDEFAULT_TOLERANCE_1E_MIN4) const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();
    virtual bool reverse();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

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

    QList<RSpline> splitAtPoints(const QList<RVector>& points) const;
    QList<RSpline> splitAtParams(const QList<double>& params) const;

    RPolyline toPolyline(int segments) const;
    RPolyline approximateWithArcs(double tolerance) const;

    virtual QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const;
    QList<QSharedPointer<RShape> > getExplodedBezier(int segments) const;
    QList<QSharedPointer<RShape> > getExplodedWithSegmentLength(double segmentLength) const;

    QList<RSpline> getBezierSegments(const RBox& queryBox = RDEFAULT_RBOX) const;

    bool isValid() const;
    double getTDelta() const;
    double getTMin() const;
    double getTMax() const;
    double getTAtPoint(const RVector& point) const;
    double getTAtDistance(double distance) const;
    double getDistanceAtT(double t) const;
    QList<RSpline> getSegments(const QList<RVector>& points) const;

    QList<RVector> getDiscontinuities() const;
    RSpline simplify(double tolerance);

    void updateFromControlPoints() const;
    void updateFromFitPoints() const;
    void update() const;

    virtual QList<QSharedPointer<RShape> > splitAt(const QList<RVector>& points) const;

    bool isDirty() const {
        return dirty;
    }

    QList<RVector> getSelfIntersectionPoints() const;

    static bool hasProxy() {
        return splineProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setSplineProxy(RSplineProxy* p) {
        if (splineProxy!=NULL) {
            delete splineProxy;
        }
        splineProxy = p;
    }

    /**
     * \nonscriptable
     */
    static RSplineProxy* getSplineProxy() {
        return splineProxy;
    }

protected:
    void appendToExploded(const RLine& line) const;
    //void appendToExploded(QList<QSharedPointer<RShape> >& list) const;
    void invalidate() const;
    void updateInternal() const;
    void updateBoundingBox() const;

    virtual void print(QDebug dbg) const;

public:
    // members are mutable, so the spline can update itself from fit points

    /**
     * \getter{getControlPoints}
     * \setter{setControlPoints}
     */
    mutable QList<RVector> controlPoints;

    /**
     * \getter{getKnotVector}
     */
    mutable QList<double> knotVector;

    /**
     * \getter{getWeights}
     */
    mutable QList<double> weights;

    /**
     * \getter{getFitPoints}
     * \setter{setFitPoints}
     */
    QList<RVector> fitPoints;

    /**
     * \getter{getDegree}
     * \setter{setDegree}
     */
    mutable int degree;

    /**
     * Unit vector start tangent.
     */
    mutable RVector tangentStart;

    /**
     * Unit vector end tangent.
     */
    mutable RVector tangentEnd;

    /**
     * Closed periodic flag.
     */
    mutable bool periodic;

    mutable bool dirty;
    mutable bool updateInProgress;

private:
#ifndef R_NO_OPENNURBS
    mutable ON_NurbsCurve curve;
#endif
    mutable RBox boundingBox;
    mutable QList<QSharedPointer<RShape> > exploded;
    // cached length:
    mutable double length;

    static RSplineProxy* splineProxy;
};

Q_DECLARE_METATYPE(const RSpline*)
Q_DECLARE_METATYPE(RSpline*)
Q_DECLARE_METATYPE(RSpline)
Q_DECLARE_METATYPE(QList<RSpline>)
Q_DECLARE_METATYPE(QSharedPointer<RSpline>)
Q_DECLARE_METATYPE(QSharedPointer<RSpline>*)

#endif
