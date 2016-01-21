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

#ifndef RSHAPE_H
#define RSHAPE_H

#include "../core_global.h"

#include <QList>
#include <QSharedPointer>

#include "RVector.h"
#include "RMath.h"

class RArc;
class RBox;
class RCircle;
class REllipse;
class RExplodable;
class RLine;
class RPolyline;
class RSpline;
class RTriangle;

#ifndef RDEFAULT_TOLERANCE_1E_MIN4
#define RDEFAULT_TOLERANCE_1E_MIN4 1.0e-4
#endif

/**
 * Interface for geometrical shape classes.
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 */
class QCADCORE_EXPORT RShape {
public:
    RShape() {
    }

    virtual ~RShape() {
    }

    virtual RShape* clone() const = 0;

    /**
     * Reimplement and return true if this shape relies on interpolation
     * for geometrical operations such as finding intersection points. E.g.
     * splines.
     */
    virtual bool isInterpolated() const {
        return false;
    }

    virtual RVector getClosestPointOnShape(const RVector& p,
            bool limited = true, double strictRange = RMAXDOUBLE) const;

    /**
     * \return The bounding box of this shape.
     */
    virtual RBox getBoundingBox() const = 0;

    /**
     * Flattens this shape to the X/Y plane
     */
    virtual void to2D() = 0;

    /**
     * \return The total length of this shape if applicable or NaN if not.
     */
    virtual double getLength() const = 0;

    /**
     * \return Shortest vector from this shape to the given point.
     *
     * \param point the given point
     *
     * \param limited If false, the shape is treated as an unlimited
     *      shape that extends in a logical way. For example an
     *      unlimited line for a line, full circle for an arc or
     *      a plane for a triangle.
     */
    virtual RVector getVectorTo(const RVector& point,
            bool limited = true, double strictRange = RMAXDOUBLE) const = 0;

    virtual double getDistanceTo(const RVector& point, bool limited = true, double strictRange = RMAXDOUBLE) const;
    virtual bool isOnShape(const RVector& point,
                           bool limited = true,
                           double tolerance = RDEFAULT_TOLERANCE_1E_MIN4) const;
    virtual QList<RVector> filterOnShape(const QList<RVector>& pointList,
        bool limited = true,
        double tolerance = RDEFAULT_TOLERANCE_1E_MIN4) const;
    virtual RVector getVectorFromEndpointTo(const RVector& point) const;

    /**
     * \return The end point(s) of this shape.
     */
    virtual QList<RVector> getEndPoints() const = 0;

    /**
     * \return The middle point(s) of this shape.
     */
    virtual QList<RVector> getMiddlePoints() const = 0;

    /**
     * \return The center point(s) of this shape.
     */
    virtual QList<RVector> getCenterPoints() const = 0;

    /**
     * \return All points on this shape with the given distance to an endpoint.
     */
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const = 0;

    /**
     * \return Angle on the entity at the given distance from the start point.
     */
    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const {
        Q_UNUSED(distance)
        Q_UNUSED(from)
        return RNANDOUBLE;
    }

    virtual RVector getPointAtPercent(double p) const;

    virtual bool intersectsWith(const RShape& other, 
        bool limited = true) const;

    QList<RVector> getIntersectionPoints(const RShape& other,
            bool limited = true, bool same = false, bool force = false) const;

    /**
     * \return The intersection point(s) between this shape and the given
     *      other shape.
     */
    static QList<RVector> getIntersectionPoints(const RShape& shape1,
            const RShape& shape2, bool limited = true, bool same = false, bool force = false);

    virtual bool move(const RVector& offset)=0;
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR)=0;
    virtual bool scale(double scaleFactor, const RVector& center = RVector());
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RVector())=0;
    virtual bool mirror(const RLine& axis)=0;
    virtual bool flipHorizontal();
    virtual bool flipVertical();
    virtual bool stretch(const RBox& area, const RVector& offset);
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const = 0;

    static bool order(QList<QList<QSharedPointer<RShape> > >& boundary);

    static QList<RVector> getIntersectionPointsLL(const RLine& line1,
            const RLine& line2, bool limited = true) {
        return getIntersectionPointsLL(line1, line2, limited, limited);
    }
    static QList<RVector> getIntersectionPointsLL(const RLine& line1,
            const RLine& line2, bool limited1, bool limited2);
    static QList<RVector> getIntersectionPointsLA(const RLine& line1,
           const RArc& arc2, bool limited = true) {
        return getIntersectionPointsLA(line1, arc2, limited, limited);
    }
    static QList<RVector> getIntersectionPointsLA(const RLine& line1,
            const RArc& arc2, bool limited1, bool limited2);
    static QList<RVector> getIntersectionPointsLC(const RLine& line1,
            const RCircle& circle2, bool limited = true);
    static QList<RVector> getIntersectionPointsLE(const RLine& line1,
            const REllipse& ellipse2, bool limited = true) {
        return getIntersectionPointsLE(line1, ellipse2, limited, limited);
    }
    static QList<RVector> getIntersectionPointsLE(const RLine& line1,
            const REllipse& ellipse2, bool limited1, bool limited2);
    static QList<RVector> getIntersectionPointsLT(const RLine& line1,
            const RTriangle& triangle2, bool limited = true) {
        return getIntersectionPointsLT(line1, triangle2, limited, limited);
    }
    static QList<RVector> getIntersectionPointsLT(const RLine& line1,
            const RTriangle& triangle2, bool limited1, bool limited2);
    static QList<RVector> getIntersectionPointsLS(const RLine& line1,
            const RSpline& spline2, bool limited = true);
    static QList<RVector> getIntersectionPointsLX(const RLine& line1,
            const RExplodable& explodable2, bool limited = true);

    static QList<RVector> getIntersectionPointsAA(const RArc& arc1,
            const RArc& arc2, bool limited = true);
    static QList<RVector> getIntersectionPointsAC(const RArc& arc1,
            const RCircle& circle2, bool limited = true);
    static QList<RVector> getIntersectionPointsAE(const RArc& arc1,
            const REllipse& ellipse2, bool limited = true);
    static QList<RVector> getIntersectionPointsAT(const RArc& arc1,
            const RTriangle& triangle2, bool limited = true);
    static QList<RVector> getIntersectionPointsAS(const RArc& arc1,
            const RSpline& spline2, bool limited = true);
    static QList<RVector> getIntersectionPointsAX(const RArc& arc1,
            const RExplodable& explodable2, bool limited = true);

    static QList<RVector> getIntersectionPointsCC(const RCircle& circle1,
            const RCircle& circle2);
    static QList<RVector> getIntersectionPointsCE(const RCircle& circle1,
            const REllipse& ellipse2);
    static QList<RVector> getIntersectionPointsCS(const RCircle& circle1,
            const RSpline& spline2, bool limited = true);
    static QList<RVector> getIntersectionPointsCX(const RCircle& circle1,
            const RExplodable& explodable2, bool limited = true);

    static QList<RVector> getIntersectionPointsEE(const REllipse& ellipse1,
            const REllipse& ellipse2);
    static QList<RVector> getIntersectionPointsEE(const REllipse& ellipse1,
            const REllipse& ellipse2, bool limited);
    static QList<RVector> getIntersectionPointsES(const REllipse& ellipse1,
            const RSpline& spline2, bool limited = true);
    static QList<RVector> getIntersectionPointsEX(const REllipse& ellipse1,
            const RExplodable& explodable2, bool limited = true);

    static QList<RVector> getIntersectionPointsSS(const RSpline& spline1,
            const RSpline& spline2, bool limited = true, bool same = false);

    static QList<RVector> getIntersectionPointsXX(const RExplodable& explodable1,
            const RExplodable& explodable2, bool limited = true, bool same = false);

    static const RExplodable* castToExplodable(const RShape* shape);

    void dump();

    /**
     * \nonscriptable
     */
    friend QDebug operator<<(QDebug dbg, const RShape& s) {
        s.print(dbg);
        return dbg;
    }

private:
    static double ellipse2tr(double x, double y, double AA, double BB,
                        double CC, double DD, double EE, double FF);

private:
    static double twopi;
    static double epsTolerance;

protected:
    virtual void print(QDebug dbg) const;
};

Q_DECLARE_METATYPE(RShape*)
Q_DECLARE_METATYPE(const RShape*)
Q_DECLARE_METATYPE(QSharedPointer<RShape>)
Q_DECLARE_METATYPE(QSharedPointer<const RShape>)
Q_DECLARE_METATYPE(QSharedPointer<RShape>*)
Q_DECLARE_METATYPE(QList<QSharedPointer<RShape> >)
Q_DECLARE_METATYPE(QList<QSharedPointer<RShape> >*)
Q_DECLARE_METATYPE(QList<QSharedPointer<const RShape> >)

#endif
