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

#ifndef RPOLYLINE_H
#define RPOLYLINE_H

#include "../core_global.h"

#include <QSharedPointer>

#include "RDirected.h"
#include "RExplodable.h"
#include "RPainterPath.h"
#include "RShape.h"
#include "RVector.h"

class RBox;

#ifndef RDEFAULT_MIN1
#define RDEFAULT_MIN1 -1
#endif

/**
 * Low-level mathematical representation of an open polyline or
 * closed polyline (= polygon).
 *
 * \ingroup math
 * \scriptable
 * \sharedPointerSupport
 * \copyable
 * \hasStreamOperator
 */
class QCADCORE_EXPORT RPolyline: public RShape, public RExplodable, public RDirected {
public:
    RPolyline();
    RPolyline(const QList<RVector>& vertices, bool closed);
    RPolyline(const QList<QSharedPointer<RShape> >& segments);
    virtual ~RPolyline();

    virtual RPolyline* clone() const {
        return new RPolyline(*this);
    }

    virtual void to2D();

    void clear();
    void normalize();

    void appendShape(const RShape& shape);

    void appendVertex(const RVector& vertex, double bulge = 0.0);
    void prependVertex(const RVector& vertex, double bulge = 0.0);
    void insertVertex(int index, const RVector& vertex);
    void removeLastVertex();
    void removeVertex(int index);

    void setVertices(const QList<RVector>& vertices);
    QList<RVector> getVertices() const;
    void setVertexAt(int i, const RVector& v);
    RVector getVertexAt(int i) const;
    RVector getLastVertex() const;
    int countVertices() const;

    void setBulges(const QList<double>& b);
    QList<double> getBulges() const;
    double getBulgeAt(int i) const;
    void setBulgeAt(int i, double b);
    bool hasArcSegments() const;

    void setClosed(bool on);
    bool isClosed() const;
    bool isLogicallyClosed() const;

    bool contains(const RVector& point, bool borderIsInside=false, double tolerance=RS::PointTolerance) const;
    // TODO:
    //bool contains(const RShape& shape) const;

    virtual RVector getStartPoint() const;
    virtual RVector getEndPoint() const;

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    virtual RBox getBoundingBox() const;

    virtual double getLength() const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const;

    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true, double strictRange = RMAXDOUBLE) const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(double scaleFactor, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool reverse();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

    virtual RS::Ending getTrimEnd(const RVector& coord, const RVector& trimPoint);
    virtual void trimStartPoint(const RVector& p);
    virtual void trimEndPoint(const RVector& p);

    virtual QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const;
    virtual bool isInterpolated() const {
        return false;
    }
    int countSegments() const;
    QSharedPointer<RShape> getSegmentAt(int i) const;

    static bool isStraight(double bulge);

    RPainterPath toPainterPath() const;

    bool simplify(double angleTolerance = RS::AngleTolerance);

protected:
    bool isLineSegment(int i) const;

    void print(QDebug dbg) const;

protected:
    /**
     * \getter{getVertices}
     * \setter{setVertices}
     */
    QList<RVector> vertices;

    QList<double> bulges;

    /**
     * \getter{isClosed}
     * \setter{setClosed}
     */
    bool closed;

private:
    // TODO caching:
    //QList<QSharedPointer<RShape> > subShapes;
};

Q_DECLARE_METATYPE(const RPolyline*)
Q_DECLARE_METATYPE(RPolyline*)
Q_DECLARE_METATYPE(RPolyline)
Q_DECLARE_METATYPE(QSharedPointer<RPolyline>)
Q_DECLARE_METATYPE(QSharedPointer<RPolyline>*)

#endif
