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

#ifndef RSPLINE_H
#define RSPLINE_H

#include "../core_global.h"

#include "RArc.h"
#include "RBox.h"
#include "RDirected.h"
#include "RExplodable.h"
#include "RShape.h"
#include "RVector.h"

#ifndef R_NO_OPENNURBS
#include "opennurbs/opennurbs.h"
#endif

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Low-level mathematical representation of a 2nd or 3rd degree spline.
 *
 * The spline may be defined by its control points or by its fit points but
 * not both.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 */
class QCADCORE_EXPORT RSpline: public RShape, public RExplodable, public RDirected {
public:
    typedef RSpline (*UpdateFromFitPointsFunction)(const RSpline& spline, bool useTangents);

    RSpline();
    RSpline(const QList<RVector>& controlPoints, int degree);
    virtual ~RSpline();

    virtual RSpline* clone() const {
        return new RSpline(*this);
    }

    static QList<RSpline> createSplinesFromArc(const RArc& arc);
    static RSpline createBezierFromSmallArc(double r, double a1, double a2);

    virtual void to2D();

    virtual bool isInterpolated() const {
        return true;
    }

    //virtual RVector getClosestPointOnShape(const RVector& p, bool limited) const;

    void appendControlPoint(const RVector& point);
    void removeLastControlPoint();
    void setControlPoints(const QList<RVector>& points);
    QList<RVector> getControlPoints() const;
    QList<RVector> getControlPointsWrapped() const;
    int countControlPoints() const;

    void appendFitPoint(const RVector& point);
    void removeLastFitPoint();
    void setFitPoints(const QList<RVector>& points);
    QList<RVector> getFitPoints() const;
    int countFitPoints() const;
    bool hasFitPoints() const;

    QList<double> getKnotVector() const;
    void setKnotVector(const QList<double>& knots);
    void appendKnot(double k);
    QList<double> getWeights() const;

    void setDegree(int d);
    int getDegree() const;

    int getOrder() const;

    void setPeriodic(bool on);
    //bool isClosedPeriodic() const;

    bool isClosed() const;
    bool isPeriodic() const;

    virtual double getDirection1() const;
    virtual double getDirection2() const;

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

    virtual QList<RVector> getEndPoints() const;
    RVector getMiddlePoint() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true) const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool flipHorizontal();
    virtual bool flipVertical();
    virtual bool reverse();

    virtual RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint);
    virtual void trimStartPoint(const RVector& p);
    virtual void trimEndPoint(const RVector& p);

    virtual QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const;

    QList<RSpline> getBezierSegments() const;

    bool isValid() const;
    double getTDelta() const;
    double getTMin() const;
    double getTMax() const;

    void updateFromControlPoints() const;
    void updateFromFitPoints(bool useTangents = false) const;
    void update() const;

    /**
     * \nonscriptable
     */
    static void setUpdateFromFitPointsFunction(UpdateFromFitPointsFunction f) {
        updateFromFitPointsFunction = f;
    }

protected:
    void invalidate() const;
    void updateInternal() const;
    void updateBoundingBox() const;

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

protected:
    virtual void print(QDebug dbg) const;

private:
#ifndef R_NO_OPENNURBS
    mutable ON_NurbsCurve curve;
#endif
    mutable RBox boundingBox;
    mutable QList<QSharedPointer<RShape> > exploded;

    static UpdateFromFitPointsFunction updateFromFitPointsFunction;
};

Q_DECLARE_METATYPE(const RSpline*)
Q_DECLARE_METATYPE(RSpline*)
Q_DECLARE_METATYPE(RSpline)
Q_DECLARE_METATYPE(QList<RSpline>)
Q_DECLARE_METATYPE(QSharedPointer<RSpline>)
Q_DECLARE_METATYPE(QSharedPointer<RSpline>*)

#endif
