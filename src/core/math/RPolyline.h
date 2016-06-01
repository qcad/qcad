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

#ifndef RPOLYLINE_H
#define RPOLYLINE_H

#include "../core_global.h"

#include <QSharedPointer>

#include "RDirected.h"
#include "RExplodable.h"
#include "RPainterPath.h"
#include "RPolylineProxy.h"
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
    void normalize(double tolerance = RS::PointTolerance);

    bool prependShape(const RShape& shape);
    bool appendShape(const RShape& shape, bool prepend = false);

    void appendVertex(const RVector& vertex, double bulge = 0.0, double w1 = 0.0, double w2 = 0.0);
    void prependVertex(const RVector& vertex, double bulge = 0.0, double w1 = 0.0, double w2 = 0.0);
    void insertVertex(int index, const RVector& vertex);
    void insertVertexAt(const RVector& point);
    void removeFirstVertex();
    void removeLastVertex();
    void removeVertex(int index);
    void removeVerticesAfter(int index);
    void removeVerticesBefore(int index);

    void setVertices(const QList<RVector>& vertices);
    QList<RVector> getVertices() const;
    void setVertexAt(int i, const RVector& v);
    RVector getVertexAt(int i) const;
    int getVertexIndex(const RVector& v, double tolerance=RS::PointTolerance) const;
    RVector getLastVertex() const;
    int countVertices() const;

    void setBulges(const QList<double>& b);
    QList<double> getBulges() const;
    double getBulgeAt(int i) const;
    void setBulgeAt(int i, double b);
    bool hasArcSegments() const;

    QList<double> getVertexAngles() const;
    double getVertexAngle(int i) const;

    void setGlobalWidth(double w);
    void setStartWidthAt(int i, double w);
    double getStartWidthAt(int i) const;
    void setEndWidthAt(int i, double w);
    double getEndWidthAt(int i) const;
    bool hasWidths() const;
    void setStartWidths(const QList<double>& sw);
    QList<double> getStartWidths() const;
    void setEndWidths(const QList<double>& ew);
    QList<double> getEndWidths() const;

    void setClosed(bool on);
    bool isClosed() const;
    bool isGeometricallyClosed(double tolerance=RS::PointTolerance) const;
    bool autoClose();

    RS::Orientation getOrientation(bool implicitelyClosed = false) const;

    bool contains(const RVector& point, bool borderIsInside=false, double tolerance=RS::PointTolerance) const;
    bool containsShape(const RShape& shape) const;

    RVector getPointInside() const;

    virtual RVector getStartPoint() const;
    virtual RVector getEndPoint() const;

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    virtual RS::Side getSideOfPoint(const RVector& point) const;

    virtual RBox getBoundingBox() const;

    double getArea() const;

    virtual double getLength() const;
    double getLengthTo(const RVector& p, bool limited = true) const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, RS::From from = RS::FromAny) const;

    virtual double getAngleAt(double distance, RS::From from = RS::FromStart) const;

    virtual RVector getVectorTo(const RVector& point,
            bool limited = true, double strictRange = RMAXDOUBLE) const;
    virtual double getDistanceTo(const RVector& point, bool limited = true, double strictRange = RMAXDOUBLE) const;

    int getClosestSegment(const RVector& point) const;
    int getClosestVertex(const RVector& point) const;

    virtual bool move(const RVector& offset);
    virtual bool rotate(double rotation, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(double scaleFactor, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool scale(const RVector& scaleFactors, const RVector& center = RDEFAULT_RVECTOR);
    virtual bool mirror(const RLine& axis);
    virtual bool reverse();
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

    virtual RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint);
    virtual bool trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid);
    virtual bool trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid);

    virtual QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const;
    QList<RPolyline> getOutline() const;
    virtual bool isInterpolated() const {
        return false;
    }
    int countSegments() const;
    QSharedPointer<RShape> getSegmentAt(int i) const;
    bool isArcSegmentAt(int i) const;
    QSharedPointer<RShape> getLastSegment() const;
    QSharedPointer<RShape> getFirstSegment() const;

    static bool isStraight(double bulge);

    RPainterPath toPainterPath() const;

    bool simplify(double angleTolerance = RS::AngleTolerance);
    QList<RVector> verifyTangency(double toleranceMin = RS::AngleTolerance, double toleranceMax = M_PI_4);

    void stripWidths();

    bool relocateStartPoint(const RVector& p);
    bool convertToClosed();
    bool convertToOpen();

    static bool hasProxy() {
        return polylineProxy!=NULL;
    }

    /**
     * \nonscriptable
     */
    static void setPolylineProxy(RPolylineProxy* p) {
        if (polylineProxy!=NULL) {
            delete polylineProxy;
        }
        polylineProxy = p;
    }

    /**
     * \nonscriptable
     */
    static RPolylineProxy* getPolylineProxy() {
        return polylineProxy;
    }

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

    QList<double> endWidths;
    QList<double> startWidths;

    /**
     * \getter{isClosed}
     * \setter{setClosed}
     */
    bool closed;

private:
    // TODO caching:
    //QList<QSharedPointer<RShape> > subShapes;
    static RPolylineProxy* polylineProxy;
};

Q_DECLARE_METATYPE(const RPolyline*)
Q_DECLARE_METATYPE(RPolyline*)
Q_DECLARE_METATYPE(RPolyline)
Q_DECLARE_METATYPE(QSharedPointer<RPolyline>)
Q_DECLARE_METATYPE(QSharedPointer<RPolyline>*)

#endif
