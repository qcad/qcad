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

#ifndef RPOLYLINE_H
#define RPOLYLINE_H

#include "../core_global.h"

#include <QSharedPointer>

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
class QCADCORE_EXPORT RPolyline: public RShape, public RExplodable {
public:
    RPolyline();
    RPolyline(const QList<RVector>& vertices, bool closed);
    RPolyline(const QList<QSharedPointer<RShape> >& segments);
    virtual ~RPolyline();

    virtual RShape::Type getShapeType() const {
        return Polyline;
    }

    virtual RPolyline* clone() const {
        return new RPolyline(*this);
    }

    virtual bool isDirected() const {
        return true;
    }

    virtual void setZ(double z);
    bool isFlat() const;

    virtual QList<RVector> getVectorProperties() const;
    virtual QList<double> getDoubleProperties() const;
    virtual QList<bool> getBoolProperties() const;

    void clear();
    void normalize(double tolerance = RS::PointTolerance);

    bool prependShape(const RShape& shape);
    bool appendShape(const RShape& shape, bool prepend = false);
    bool appendShapeAuto(const RShape& shape);

    void appendVertex(const RVector& vertex, double bulge = 0.0, double w1 = 0.0, double w2 = 0.0);
    void appendVertex(double x, double y, double bulge = 0.0, double w1 = 0.0, double w2 = 0.0);
    void prependVertex(const RVector& vertex, double bulge = 0.0, double w1 = 0.0, double w2 = 0.0);
    void insertVertex(int index, const RVector& vertex, double bulgeBefore = 0.0, double bulgeAfter = 0.0);
    void insertVertexAt(const RVector& point);
    RVector insertVertexAtDistance(double dist);
    void removeFirstVertex();
    void removeLastVertex();
    void removeVertex(int index);
    void removeVerticesAfter(int index);
    void removeVerticesBefore(int index);

    bool isEmpty() const {
        return countVertices()==0;
    }

    void setVertices(const QList<RVector>& vertices);
    QList<RVector> getVertices() const;
    void setVertexAt(int i, const RVector& v);
    void moveVertexAt(int i, const RVector& offset);
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
    double getVertexAngle(int i, RS::Orientation orientation = RS::UnknownOrientation) const;

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
    bool autoClose(double tolerance=RS::PointTolerance) {
        return toLogicallyClosed(tolerance);
    }
    bool toLogicallyClosed(double tolerance=RS::PointTolerance);
    bool toLogicallyOpen();

    QList<RVector> getSelfIntersectionPoints() const;

    RS::Orientation getOrientation(bool implicitelyClosed = false) const;
    bool setOrientation(RS::Orientation orientation);

    RPolyline convertArcToLineSegments(int segments) const;
    RPolyline convertArcToLineSegmentsLength(double segmentLength) const;

    bool contains(const RVector& point, bool borderIsInside=false, double tolerance=RS::PointTolerance) const;
    bool containsShape(const RShape& shape) const;

    RVector getPointInside() const;

    virtual RVector getStartPoint() const;
    virtual RVector getEndPoint() const;
    virtual RVector getMiddlePoint() const;

    void moveStartPoint(const RVector& pos);
    void moveEndPoint(const RVector& pos);

    void moveSegmentAt(int i, const RVector& offset);

    virtual double getDirection1() const;
    virtual double getDirection2() const;

    virtual RS::Side getSideOfPoint(const RVector& point) const;

    virtual RBox getBoundingBox() const;

    double getArea() const;

    virtual double getLength() const;

    virtual double getDistanceFromStart(const RVector& p) const {
        QList<double> res = getDistancesFromStart(p);
        if (res.isEmpty()) {
            return RMAXDOUBLE;
        }
        return res.first();
    }
    virtual QList<double> getDistancesFromStart(const RVector& p) const;
    double getLengthTo(const RVector& p, bool limited = true) const;
    double getSegmentsLength(int fromIndex, int toIndex) const;

    virtual QList<RVector> getEndPoints() const;
    virtual QList<RVector> getMiddlePoints() const;
    virtual QList<RVector> getCenterPoints() const;
    virtual RVector getPointAtPercent(double p) const;
    virtual QList<RVector> getPointsWithDistanceToEnd(
        double distance, int from = RS::FromAny) const;
    virtual QList<RVector> getPointCloud(double segmentLength) const;

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
    virtual RPolyline getReversed() const;
    virtual bool stretch(const RPolyline& area, const RVector& offset);

    virtual QSharedPointer<RShape> getTransformed(const QTransform& transform) const;

    virtual RS::Ending getTrimEnd(const RVector& trimPoint, const RVector& clickPoint);
    virtual bool trimStartPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false);
    virtual bool trimEndPoint(const RVector& trimPoint, const RVector& clickPoint = RVector::invalid, bool extend = false);
    virtual bool trimStartPoint(double trimDist);
    virtual bool trimEndPoint(double trimDist);

    virtual QList<QSharedPointer<RShape> > getExploded(int segments = RDEFAULT_MIN1) const;
    QList<RPolyline> getOutline() const;
    QList<QPair<RPolyline, RPolyline> > getLeftRightOutline() const;
    virtual bool isInterpolated() const {
        return false;
    }
    int countSegments() const;
    QSharedPointer<RShape> getSegmentAt(int i) const;
    bool isArcSegmentAt(int i) const;
    QSharedPointer<RShape> getLastSegment() const;
    QSharedPointer<RShape> getFirstSegment() const;

    static bool isStraight(double bulge);

    RPainterPath toPainterPath(bool addOriginalShapes = false) const;

    bool simplify(double tolerance = RS::PointTolerance);
    QList<RVector> verifyTangency(double toleranceMin = RS::AngleTolerance, double toleranceMax = M_PI_4);

    void stripWidths();
    void setMinimumWidth(double w);

    int getSegmentAtDist(double dist);
    bool relocateStartPoint(const RVector& p);
    bool relocateStartPoint(double dist);
    bool convertToClosed();
    bool convertToOpen();

    RPolyline modifyPolylineCorner(
            const RShape& trimmedShape1, RS::Ending ending1, int segmentIndex1,
            const RShape& trimmedShape2, RS::Ending ending2, int segmentIndex2,
            const RShape* cornerShape = NULL) const;

    bool isConcave() const;
    QList<RVector> getConvexVertices(bool convex = true) const;
    QList<RVector> getConcaveVertices() const;

    QList<RPolyline> splitAtDiscontinuities(double tolerance) const;
    QList<RPolyline> splitAtSegmentTypeChange() const;

    double getBaseAngle() const;
    double getWidth() const;
    bool setWidth(double v);
    double getHeight() const;
    bool setHeight(double v);

    QList<RPolyline> morph(const RPolyline& target, int steps, RS::Easing easing = RS::Linear, bool zLinear = true, double customFactor = RNANDOUBLE) const;
    RPolyline roundAllCorners(double radius) const;
    RPolyline getPolygonHull(double angle, double tolerance, bool inner = false) const;

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
