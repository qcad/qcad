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
#include <cmath>

#include "RArc.h"
#include "RBox.h"
#include "RCircle.h"
#include "REllipse.h"
#include "RLine.h"
#include "RPainterPath.h"
#include "RPolyline.h"
#include "RSettings.h"
#include "RSpline.h"

RPolylineProxy* RPolyline::polylineProxy = NULL;

/**
 * Creates a polyline object without points.
 */
RPolyline::RPolyline() :
    closed(false) {
}

/**
 * Creates a polyline object with the given points.
 */
RPolyline::RPolyline(const QList<RVector>& vertices, bool closed) :
    closed(closed) {

    setVertices(vertices);
}

/**
 * Creates a polyline from segments (lines or arcs).
 */
RPolyline::RPolyline(const QList<QSharedPointer<RShape> >& segments) :
    closed(false) {

    QList<QSharedPointer<RShape> >::const_iterator it;
    for (it=segments.begin(); it!=segments.end(); ++it) {
        QSharedPointer<RShape> segment = *it;

        if (segment->isDirected()) {
            if (vertices.size()==0) {
                appendVertex(segment->getStartPoint(), 0.0);
            }
            appendVertex(segment->getEndPoint(), 0.0);
        }

        QSharedPointer<RArc> arc = segment.dynamicCast<RArc>();
        if (!arc.isNull()) {
            if (bulges.size()>1) {
                bulges[bulges.size()-2] = arc->getBulge();
            }
        }
    }

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());

    autoClose();
}

RPolyline::~RPolyline() {
}

void RPolyline::setZ(double z) {
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].z = z;
    }
}

bool RPolyline::isFlat() const {
    double z = RNANDOUBLE;
    for (int i=0; i<vertices.size(); i++) {
        if (i==0) {
            z = vertices[i].z;
            continue;
        }

        if (!RMath::fuzzyCompare(z, vertices[i].z)) {
            return false;
        }
    }

    return true;
}

QList<RVector> RPolyline::getVectorProperties() const {
    return QList<RVector>() << vertices;
}

QList<double> RPolyline::getDoubleProperties() const {
    return QList<double>() << bulges << endWidths << startWidths;
}

QList<bool> RPolyline::getBoolProperties() const {
    return QList<bool>() << closed;
}

void RPolyline::clear() {
    vertices.clear();
    bulges.clear();
    startWidths.clear();
    endWidths.clear();

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

/**
 * Removes duplicate vertices.
 */
void RPolyline::normalize(double tolerance) {
    QList<RVector> newVertices;
    QList<double> newBulges;
    QList<double> newStartWidths;
    QList<double> newEndWidths;

    RVector vPrev;
    int newIndex = 0;

    for (int i=0; i<vertices.size(); i++) {
        RVector v = vertices[i];
        double b = bulges[i];
        double s = startWidths[i];
        double e = endWidths[i];

        if (i==0 || !v.equalsFuzzy(vPrev, tolerance)) {
            newVertices.append(v);
            newBulges.append(b);
            newStartWidths.append(s);
            newEndWidths.append(e);
            newIndex = newIndex + 1;
            vPrev = v;
        }
        else if (i > 0) {
            newBulges[newIndex - 1] = b;
            newStartWidths[newIndex - 1] = s;
            newEndWidths[newIndex - 1] = e;
        }
    }

    // remove duplicate last vertex of closed polyline:
    if (closed) {
        if (newVertices.first().equalsFuzzy(newVertices.last(), tolerance)) {
            newVertices.removeLast();
            newBulges.removeLast();
            newStartWidths.removeLast();
            newEndWidths.removeLast();
        }
    }

    vertices = newVertices;
    bulges = newBulges;
    startWidths = newStartWidths;
    endWidths = newEndWidths;

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

bool RPolyline::prependShape(const RShape& shape) {
    return appendShape(shape, true);
}

bool RPolyline::appendShape(const RShape& shape, bool prepend) {
    bool ret = true;

    // append spline as polyline approximation:
    if (shape.getShapeType()==RShape::Spline) {
        const RSpline* spl = dynamic_cast<const RSpline*>(&shape);
        if (spl!=NULL) {
            double tol = RSettings::getDoubleValue("Explode/SplineTolerance", 0.01);
            RPolyline pl = spl->approximateWithArcs(tol);
            return appendShape(pl, prepend);
        }
    }

    // append ellipse as polyline approximation:
    else if (shape.getShapeType()==RShape::Ellipse) {
        const REllipse* elp = dynamic_cast<const REllipse*>(&shape);
        if (elp!=NULL) {
            double seg = RSettings::getDoubleValue("Explode/EllipseSegments", 32);
            RPolyline pl = elp->approximateWithArcs(seg);
            return appendShape(pl, prepend);
        }
    }

    // append circle as polyline to empty polyline:
    else if (shape.getShapeType()==RShape::Circle && isEmpty()) {
        const RCircle* circle = dynamic_cast<const RCircle*>(&shape);
        if (circle!=NULL) {
            appendShape(RArc(circle->getCenter(), circle->getRadius(), 0.0, M_PI, false));
            appendShape(RArc(circle->getCenter(), circle->getRadius(), M_PI, 2*M_PI, false));
            return true;
        }
    }

    // append full circle arc as circle (two arc segments) to empty polyline:
    else if (shape.getShapeType()==RShape::Arc) {
        const RArc* arc = dynamic_cast<const RArc*>(&shape);
        if (arc!=NULL && arc->isFullCircle()) {
            appendShape(RCircle(arc->getCenter(), arc->getRadius()));
            return true;
        }
    }

    // append polyline:
    else if (shape.getShapeType()==RShape::Polyline) {
        const RPolyline* pl = dynamic_cast<const RPolyline*>(&shape);
        if (pl!=NULL) {
            if (prepend) {
                for (int i=pl->countSegments()-1; i>=0; --i) {
                    QSharedPointer<RShape> s = pl->getSegmentAt(i);
                    if (s.isNull()) {
                        continue;
                    }
                    ret = prependShape(*s) && ret;
                    setStartWidthAt(0, pl->getStartWidthAt(i));
                    setEndWidthAt(0, pl->getEndWidthAt(i));
                }
            }
            else {
                for (int i=0; i<pl->countSegments(); ++i) {
                    QSharedPointer<RShape> s = pl->getSegmentAt(i);
                    if (s.isNull()) {
                        continue;
                    }
                    setStartWidthAt(vertices.length()-1, pl->getStartWidthAt(i));
                    setEndWidthAt(vertices.length()-1, pl->getEndWidthAt(i));
                    ret = appendShape(*s) && ret;
                }
            }
            return ret;
        }
    }

    double bulge = 0.0;

    const RArc* arc = dynamic_cast<const RArc*>(&shape);
    if (arc!=NULL) {
        bulge = arc->getBulge();
    }

    if (!shape.isDirected()) {
        qWarning() << "RPolyline::appendShape: shape is not a line, arc or polyline: " << shape;
        return false;
    }

    RVector connectionPoint;
    RVector nextPoint;
    double gap;
    if (prepend) {
        // prepend:
        connectionPoint = shape.getEndPoint();
        nextPoint = shape.getStartPoint();
        if (vertices.size()==0) {
            // first point:
            appendVertex(connectionPoint);
        }
        gap = vertices.first().getDistanceTo(connectionPoint);
    }
    else {
        // append:
        connectionPoint = shape.getStartPoint();
        nextPoint = shape.getEndPoint();
        if (vertices.size()==0) {
            // first point:
            appendVertex(connectionPoint);
        }
        gap = vertices.last().getDistanceTo(connectionPoint);
    }

    if (!RMath::fuzzyCompare(gap, 0.0, 1.0e-3)) {
        qWarning() << "RPolyline::appendShape: "
                   << "arc or line not connected to polyline at " << connectionPoint << ":"
                   << "\nshape:" << shape
                   << "\ngap: " << gap;
        ret = false;
    }

    if (prepend) {
        prependVertex(nextPoint);
        setBulgeAt(0, bulge);
    }
    else {
        appendVertex(nextPoint);
        setBulgeAt(bulges.size()-2, bulge);
    }

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());

    return ret;
}

/**
 * Appends the given shape to this polyline. The shape is reversed if necessary.
 */
bool RPolyline::appendShapeAuto(const RShape& shape) {
    if (!shape.isDirected()) {
        return false;
    }

    if (countVertices()>0 && getEndPoint().equalsFuzzy(shape.getEndPoint())) {
        QSharedPointer<RShape> rev = QSharedPointer<RShape>(shape.clone());
        rev->reverse();
        return appendShape(*rev);
    }

    return appendShape(shape);
}

void RPolyline::appendVertex(const RVector& vertex, double bulge, double w1, double w2) {
    vertices.append(vertex);
    bulges.append(bulge);
    startWidths.append(w1);
    endWidths.append(w2);

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

void RPolyline::appendVertex(double x, double y, double bulge, double w1, double w2) {
    appendVertex(RVector(x, y), bulge, w1, w2);
}

void RPolyline::prependVertex(const RVector& vertex, double bulge, double w1, double w2) {
    vertices.prepend(vertex);
    bulges.prepend(bulge);
    startWidths.prepend(w1);
    endWidths.prepend(w2);

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

void RPolyline::insertVertex(int index, const RVector& vertex, double bulgeBefore, double bulgeAfter) {
    vertices.insert(index, vertex);
    if (index>0) {
        bulges[index-1] = bulgeBefore;
    }
    bulges.insert(index, bulgeAfter);
    startWidths.insert(index, RNANDOUBLE);
    endWidths.insert(index, RNANDOUBLE);

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

/**
 * Inserts a vertex at the point on the polyline closest to the given position.
 */
void RPolyline::insertVertexAt(const RVector& point) {
    int index = getClosestSegment(point);
    if (index<0) {
        return;
    }

    QSharedPointer<RShape> seg1 = getSegmentAt(index);
    if (seg1.isNull()) {
        return;
    }

    RVector p = seg1->getClosestPointOnShape(point, false);

    QSharedPointer<RShape> seg2 = QSharedPointer<RShape>(seg1->clone());

    if (!seg1->isDirected() || !seg2->isDirected()) {
        return;
    }

    seg1->trimEndPoint(p);
    seg2->trimStartPoint(p);

    insertVertex(index+1, p);

    QSharedPointer<RArc> arc1 = seg1.dynamicCast<RArc>();
    QSharedPointer<RArc> arc2 = seg2.dynamicCast<RArc>();
    if (arc1.isNull()) {
        setBulgeAt(index, 0.0);
    }
    else {
        setBulgeAt(index, arc1->getBulge());
    }

    if (arc2.isNull()) {
        setBulgeAt(index+1, 0.0);
    }
    else {
        setBulgeAt(index+1, arc2->getBulge());
    }

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

RVector RPolyline::insertVertexAtDistance(double dist) {
    if (polylineProxy!=NULL) {
        return polylineProxy->insertVertexAtDistance(*this, dist);
    }
    return RVector::invalid;
}

void RPolyline::removeFirstVertex() {
    if (vertices.isEmpty()) {
        return;
    }

    vertices.removeFirst();
    bulges.removeFirst();
    startWidths.removeFirst();
    endWidths.removeFirst();

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

void RPolyline::removeLastVertex() {
    if (vertices.isEmpty()) {
        return;
    }

    vertices.removeLast();
    bulges.removeLast();
    startWidths.removeLast();
    endWidths.removeLast();

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

void RPolyline::removeVertex(int index) {
    vertices.removeAt(index);
    bulges.removeAt(index);
    startWidths.removeAt(index);
    endWidths.removeAt(index);

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

void RPolyline::removeVerticesAfter(int index) {
    vertices = vertices.mid(0, index+1);
    bulges = bulges.mid(0, index+1);
    startWidths = startWidths.mid(0, index+1);
    endWidths = endWidths.mid(0, index+1);

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

void RPolyline::removeVerticesBefore(int index) {
    vertices = vertices.mid(index);
    bulges = bulges.mid(index);
    startWidths = startWidths.mid(index);
    endWidths = endWidths.mid(index);

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

void RPolyline::setVertices(const QList<RVector>& vertices) {
    this->vertices = vertices;

    bulges.clear();
    startWidths.clear();
    endWidths.clear();
    for (int i=0; i<vertices.size(); ++i) {
        bulges.append(0.0);
        startWidths.append(RNANDOUBLE);
        endWidths.append(RNANDOUBLE);
    }

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());
}

QList<RVector> RPolyline::getVertices() const {
    return vertices;
}

RVector RPolyline::getVertexAt(int i) const {
    if (i<0 || i>=vertices.size()) {
        Q_ASSERT(false);
        return RVector::invalid;
    }

    return vertices.at(i);
}

int RPolyline::getVertexIndex(const RVector& v, double tolerance) const {
    for (int i=0; i<vertices.length(); i++) {
        if (vertices[i].equalsFuzzy(v, tolerance)) {
            return i;
        }

        if (vertices[i].equalsFuzzy(v, 0.01)) {
            qDebug() << "almost match: " << vertices[i].getDistanceTo(v);
        }
    }

    return -1;
}

RVector RPolyline::getLastVertex() const {
    if (vertices.size()==0) {
        return RVector::invalid;
    }

    return vertices.at(vertices.size()-1);
}

void RPolyline::setVertexAt(int i, const RVector& v) {
    if (i<0 || i>=vertices.size()) {
        Q_ASSERT(false);
        return;
    }

    vertices[i] = v;
}

void RPolyline::moveVertexAt(int i, const RVector& offset) {
    if (i<0 || i>=vertices.size()) {
        Q_ASSERT(false);
        return;
    }

    vertices[i]+=offset;
}

int RPolyline::countVertices() const {
    return vertices.size();
}

void RPolyline::setBulges(const QList<double>& b) {
    bulges = b;
}

QList<double> RPolyline::getBulges() const {
    return bulges;
}

double RPolyline::getBulgeAt(int i) const {
    if (i<0 || i>=bulges.size()) {
        return RNANDOUBLE;
    }

    return bulges.at(i);
}

void RPolyline::setBulgeAt(int i, double b) {
    if (i<0 || i>=bulges.size()) {
        return;
    }

    bulges[i] = b;
}

bool RPolyline::hasArcSegments() const {
    for (int i=0; i<bulges.size(); i++) {
        if (!isStraight(bulges[i])) {
            return true;
        }
    }

    return false;
}

QList<double> RPolyline::getVertexAngles() const {
    RS::Orientation orientation = getOrientation(true);
    QList<double> ret;
    for (int i=0; i<countVertices(); i++) {
        ret.append(getVertexAngle(i, orientation));
    }
    return ret;
}

double RPolyline::getVertexAngle(int i, RS::Orientation orientation) const {
    if (!isGeometricallyClosed() && (i==0 || i==countVertices()-1)) {
        // angles at first / last vertex for open polyline:
        return 0.0;
    }

    if (countSegments()==0) {
        return 0.0;
    }


    QSharedPointer<RShape> prevSegment = getSegmentAt(RMath::absmod(i-1, countSegments()));
    QSharedPointer<RShape> nextSegment = getSegmentAt(i%countSegments());

    // angle from vertex to next segment:
    double aNext = nextSegment->getDirection1();
    // angle from vertex to previous segment:
    double aPrev = prevSegment->getDirection2();

    if (orientation==RS::UnknownOrientation) {
        orientation = getOrientation(true);
    }
    if (orientation==RS::CW) {
        return RMath::getAngleDifference(aPrev, aNext);
    }
    else {
        return RMath::getAngleDifference(aNext, aPrev);
    }
}

void RPolyline::setGlobalWidth(double w) {
    for (int i=0; i<startWidths.length(); i++) {
        startWidths[i] = w;
    }
    for (int i=0; i<endWidths.length(); i++) {
        endWidths[i] = w;
    }
}

void RPolyline::setStartWidthAt(int i, double w) {
    if (i<0 || i>=startWidths.size()) {
        return;
    }
    startWidths[i] = w;
}

double RPolyline::getStartWidthAt(int i) const {
    if (i<0 || i>=startWidths.size()) {
        return -1.0;
    }

    return startWidths.at(i);
}

void RPolyline::setEndWidthAt(int i, double w) {
    if (i<0 || i>=endWidths.size()) {
        return;
    }
    endWidths[i] = w;
}

double RPolyline::getEndWidthAt(int i) const {
    if (i<0 || i>=endWidths.size()) {
        return -1.0;
    }

    return endWidths.at(i);
}

bool RPolyline::hasWidths() const {
    for (int i=0; i<startWidths.length() && i<endWidths.length(); i++) {
        if (!RMath::isNaN(startWidths[i]) && startWidths[i]>0.0) {
            // widths in last vertex only count if closed:
            if (i!=startWidths.length()-1 || isClosed()) {
                return true;
            }
        }
        if (!RMath::isNaN(endWidths[i]) && endWidths[i]>0.0) {
            if (i!=startWidths.length()-1 || isClosed()) {
                return true;
            }
        }
    }

    return false;
}

void RPolyline::setStartWidths(const QList<double>& sw) {
    startWidths = sw;
}

QList<double> RPolyline::getStartWidths() const {
    return startWidths;
}

void RPolyline::setEndWidths(const QList<double>& ew) {
    endWidths = ew;
}

QList<double> RPolyline::getEndWidths() const {
    return endWidths;
}

/**
 * Marks the poyline as logically (explicitely) closed.
 * The first and last node are usually not identical. Logically
 * closed polylines have an additional segment from start to end point.
 */
void RPolyline::setClosed(bool on) {
    closed = on;
}

/**
 * \return True if this polyline is logically marked as closed.
 */
bool RPolyline::isClosed() const {
    return closed;
}

/**
 * \return True is this polyline is geometrically closed. If this polyline is
 * logically closed it is implicitely also geometrically closed.
 */
bool RPolyline::isGeometricallyClosed(double tolerance) const {
    return isClosed() || getStartPoint().getDistanceTo(getEndPoint()) < tolerance;
}

/**
 * Converts this geometrically closed polyline (start == end) to a
 * locically closed polyline.
 *
 * \return True on success, false if this polyline is already
 * locically closed or is not geometrically closed.
 */
bool RPolyline::toLogicallyClosed(double tolerance) {
    if (isClosed()) {
        return false;
    }

    if (!isGeometricallyClosed(tolerance)) {
        return false;
    }

    removeLastVertex();
    setClosed(true);

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());

    return true;
}

/**
 * Converts this logically closed polyline to a locically open,
 * geometrically closed polyline. An additional node is inserted
 * to make sure start == end.
 *
 * \return True on success, false if this polyline is not
 * locically closed.
 */
bool RPolyline::toLogicallyOpen() {
    if (!isClosed()) {
        return false;
    }

    appendVertex(getEndPoint(), getBulgeAt(vertices.size()-1));
    setClosed(false);

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());

    return true;
}

QList<RVector> RPolyline::getSelfIntersectionPoints() const {
    QList<RVector> ret;

    bool cl = isGeometricallyClosed();

    QList<QSharedPointer<RShape> > segments = getExploded();
    for (int i=0; i<segments.length(); i++) {
        QSharedPointer<RShape> segment = getSegmentAt(i);

        for (int k=i+1; k<segments.length(); k++) {
            QSharedPointer<RShape> otherSegment = getSegmentAt(k);

            QList<RVector> ips = segment->getIntersectionPoints(*otherSegment);
            for (int n=0; n<ips.length(); n++) {
                RVector ip = ips[n];
                if (k==i+1 && ip.equalsFuzzy(segment->getEndPoint())) {
                    // ignore intersection at vertex between two consecutive segments:
                    continue;
                }

                if (cl) {
                    if (i==0 && k==segments.length()-1 && ip.equalsFuzzy(segment->getStartPoint())) {
                        continue;
                    }
                }

                ret.append(ip);
            }
        }
    }

    return ret;
}

RS::Orientation RPolyline::getOrientation(bool implicitelyClosed) const {
    if (!implicitelyClosed && !isGeometricallyClosed(0.00001)) {
        return RS::Any;
    }

    if (countSegments()<1) {
        return RS::Any;
    }

    if (hasArcSegments()) {
        RPolyline plSegmented = convertArcToLineSegments(16);
        return plSegmented.getOrientation(implicitelyClosed);
    }

    RVector minV = RVector::invalid;
    QSharedPointer<RShape> shapeBefore;
    QSharedPointer<RShape> shapeAfter;
    QSharedPointer<RShape> shape;
    QSharedPointer<RShape> previousShape = getSegmentAt(countSegments()-1);

    // find minimum vertex (lower left corner):
    QList<QSharedPointer<RShape> > segments = getExploded();
    for (int i=0; i<segments.length(); i++) {
        shape = getSegmentAt(i);
        if (shape.isNull()) {
            continue;
        }

        if (shape->getLength()<0.001) {
            continue;
        }

        RVector v = shape->getStartPoint();
        if (!minV.isValid() || v.x<minV.x || (v.x==minV.x && v.y<minV.y)) {
            minV = v;
            shapeBefore = previousShape;
            shapeAfter = shape;
        }

        previousShape = shape;
    }

    // TOOD: fails for large arc (>180d) at bottom left corner, creating round bottom left shape:
//    double l;
//    RVector p;
//    QList<RVector> list;
//    QSharedPointer<RArc> arcBefore = shapeBefore.dynamicCast<RArc>();
//    if (!arcBefore.isNull()) {
//        l = arcBefore->getLength();
//        list = arcBefore->getPointsWithDistanceToEnd(l/10, RS::FromEnd);
//        if (!list.isEmpty()) {
//            p = list[0];
//            shapeBefore = QSharedPointer<RLine>(new RLine(p, arcBefore->getEndPoint()));
//        }
//    }

//    QSharedPointer<RArc> arcAfter = shapeAfter.dynamicCast<RArc>();
//    if (!arcAfter.isNull()) {
//        l = arcAfter->getLength();
//        list = arcAfter->getPointsWithDistanceToEnd(l/10, RS::FromStart);
//        if (!list.isEmpty()) {
//            p = list[0];
//            shapeAfter = QSharedPointer<RLine>(new RLine(arcAfter->getStartPoint(), p));
//        }
//    }

    if (shapeBefore.isNull() || shapeAfter.isNull()) {
        return RS::Any;
    }

    double xa = shapeBefore->getStartPoint().x;
    double ya = shapeBefore->getStartPoint().y;
    double xb = shapeAfter->getStartPoint().x;
    double yb = shapeAfter->getStartPoint().y;
    double xc = shapeAfter->getEndPoint().x;
    double yc = shapeAfter->getEndPoint().y;

    double det = (xb-xa) * (yc-ya) - (xc-xa) * (yb-ya);

    if (det<0.0) {
        // clockwise:
        return RS::CW;
    }
    else {
        // counter-clockwise:
        return RS::CCW;
    }
}

bool RPolyline::setOrientation(RS::Orientation orientation) {
    if (getOrientation(true)!=orientation) {
        return reverse();
    }
    return false;
}

RPolyline RPolyline::convertArcToLineSegments(int segments) const {
    RPolyline ret;

    QList<QSharedPointer<RShape> > segs = getExploded();
    for (int i=0; i<segs.length(); i++) {
        QSharedPointer<RShape> seg = segs[i];
        if (seg->getShapeType()==RShape::Arc) {
            QSharedPointer<RArc> arc = seg.dynamicCast<RArc>();
            RPolyline pl = arc->approximateWithLinesTan(arc->getLength()/segments);
            ret.appendShape(pl);
        }
        else {
            ret.appendShape(*seg);
        }
    }

    ret.autoClose();
    return ret;
}

RPolyline RPolyline::convertArcToLineSegmentsLength(double segmentLength) const {
    RPolyline ret;

    QList<QSharedPointer<RShape> > segs = getExploded();
    for (int i=0; i<segs.length(); i++) {
        QSharedPointer<RShape> seg = segs[i];
        if (seg->getShapeType()==RShape::Arc) {
            QSharedPointer<RArc> arc = seg.dynamicCast<RArc>();
            RPolyline pl = arc->approximateWithLinesTan(segmentLength);
            ret.appendShape(pl);
        }
        else {
            ret.appendShape(*seg);
        }
    }

    ret.autoClose();
    return ret;
}

/**
 * \return A QPainterPath object that represents this polyline.
 */
RPainterPath RPolyline::toPainterPath(bool addOriginalShapes) const {
    RPainterPath ret;

    if (vertices.size()<=1) {
        return ret;
    }

    ret.moveTo(vertices.at(0));

    for (int i=0; i<vertices.size(); i++) {
        if (!closed && i==vertices.size()-1) {
            break;
        }
        QSharedPointer<RShape> shape = getSegmentAt(i);
        ret.addShape(shape);
        if (addOriginalShapes) {
            ret.addOriginalShape(shape);
        }
    }

    return ret;
}

void RPolyline::stripWidths() {
    for (int i=0; i<startWidths.length(); i++) {
        startWidths[i] = 0.0;
    }
    for (int i=0; i<endWidths.length(); i++) {
        endWidths[i] = 0.0;
    }
}

void RPolyline::setMinimumWidth(double w) {
    for (int i=0; i<startWidths.length(); i++) {
        if (startWidths[i]>RS::PointTolerance) {
            startWidths[i] = qMax(startWidths[i], w);
        }
    }
    for (int i=0; i<endWidths.length(); i++) {
        if (endWidths[i]>RS::PointTolerance) {
            endWidths[i] = qMax(endWidths[i], w);
        }
    }
}

int RPolyline::getSegmentAtDist(double dist) {
    if (polylineProxy!=NULL) {
        return polylineProxy->getSegmentAtDist(*this, dist);
    }
    return -1;
}

/**
 * Relocates the start point of this closed polyline to the given point.
 * The visual appearance of the polyline does not change.
 */
bool RPolyline::relocateStartPoint(const RVector& p) {
    if (polylineProxy!=NULL) {
        return polylineProxy->relocateStartPoint(*this, p);
    }
    return false;
}

bool RPolyline::relocateStartPoint(double dist) {
    if (polylineProxy!=NULL) {
        return polylineProxy->relocateStartPoint(*this, dist);
    }
    return false;
}

bool RPolyline::convertToClosed() {
    if (isClosed()) {
        // nothing to do: polyline is already logically closed:
        return true;
    }

    if (!isGeometricallyClosed()) {
        // cannot convert geometrically open polyline to closed (use setClosed instead):
        return false;
    }

    removeLastVertex();
    setClosed(true);
    return true;
}

bool RPolyline::convertToOpen() {
    if (!isClosed()) {
        // nothing to do: polyline is already logically or geometrically open:
        return true;
    }

    QSharedPointer<RShape> last = getLastSegment();
    setClosed(false);
    appendShape(*last);
    return true;
}

/**
 * \return True if the segment at the given position is a line.
 */
bool RPolyline::isLineSegment(int i) const {
    if (i<0 || i>bulges.size()) {
        return true;
    }

    return RPolyline::isStraight(bulges.at(i));
}

/**
 * \return True if the given bulge indicates a straight line segment (i.e. is 0.0).
 */
bool RPolyline::isStraight(double bulge) {
    return fabs(bulge) < 1.0e-6;
}

/**
 * \return List of RLines and RArcs describing this polyline.
 */
QList<QSharedPointer<RShape> > RPolyline::getExploded(int segments) const {
    Q_UNUSED(segments);

    QList<QSharedPointer<RShape> > ret;

    if (vertices.size()<=1) {
        return ret;
    }

    for (int i=0; i<vertices.size(); i++) {
        if (!closed && i==vertices.size()-1) {
            break;
        }

        QSharedPointer<RShape> subShape = getSegmentAt(i);
        if (subShape.isNull()) {
            continue;
        }

        ret.append(subShape);
    }

    return ret;
}

QList<QPair<RPolyline, RPolyline> > RPolyline::getLeftRightOutline() const {
    if (RPolyline::hasProxy()) {
        return RPolyline::getPolylineProxy()->getLeftRightOutline(*this);
    }
    else {
        return QList<QPair<RPolyline, RPolyline> >();
    }
}

QList<RPolyline> RPolyline::getOutline() const {
    if (RPolyline::hasProxy()) {
        return RPolyline::getPolylineProxy()->renderThickPolyline(*this);
    }
    else {
        return QList<RPolyline>();
    }
}

/**
 * \return Number of segments. The number of segments equals the
 *      number of vertices for a closed polyline and one less for
 *      an open polyline.
 */
int RPolyline::countSegments() const {
    int ret = countVertices();
    if (!closed) {
        ret-=1;
    }
    if (ret<0) {
        ret=0;
    }
    return ret;
}

/**
 * \return Shape of segment at given position.
 */
QSharedPointer<RShape> RPolyline::getSegmentAt(int i) const {
    if (i<0 || i>=vertices.size() || i>=bulges.size()) {
        qWarning() << "RPolyline::getSegmentAt(" << i << "): i out of range";
        return QSharedPointer<RShape>();
    }

    RVector p1 = vertices.at(i);
    RVector p2 = vertices.at((i+1) % vertices.size());

    if (RPolyline::isStraight(bulges.at(i))) {
        return QSharedPointer<RShape>(new RLine(p1, p2));
    }

    else {
        double bulge = bulges.at(i);
        bool reversed = bulge<0.0;
        double alpha = atan(bulge)*4.0;

        if (fabs(alpha) > 2*M_PI-RS::PointTolerance) {
            return QSharedPointer<RShape>(new RLine(p1, p2));
            //return QSharedPointer<RShape>();
        }

        double radius;
        RVector center;
        RVector middle;
        double dist;
        double angle;

        middle = (p1+p2)/2.0;
        dist = p1.getDistanceTo(p2)/2.0;
        angle = p1.getAngleTo(p2);

        // alpha can't be 0.0 at this point
        radius = fabs(dist / sin(alpha/2.0));

        double rootTerm = fabs(radius*radius - dist*dist);
        double h = sqrt(rootTerm);

        if (bulge>0.0) {
            angle+=M_PI/2.0;
        } else {
            angle-=M_PI/2.0;
        }

        if (fabs(alpha)>M_PI) {
            h*=-1.0;
        }

        center.setPolar(h, angle);
        center+=middle;

        double a1;
        double a2;

        a1 = center.getAngleTo(p1);
        a2 = center.getAngleTo(p2);

        return QSharedPointer<RShape>(new RArc(center, radius, a1, a2, reversed));
    }
}

bool RPolyline::isArcSegmentAt(int i) const {
    if (i<0 || i>=bulges.length()) {
        return false;
    }
    return !RPolyline::isStraight(bulges[i]);
}

QSharedPointer<RShape> RPolyline::getLastSegment() const {
    if (countSegments()==0) {
        return QSharedPointer<RShape>();
    }
    return getSegmentAt(countSegments()-1);
}

QSharedPointer<RShape> RPolyline::getFirstSegment() const {
    if (countSegments()==0) {
        return QSharedPointer<RShape>();
    }
    return getSegmentAt(0);
}

/**
 * Checks if the given point is inside this closed polygon. If this
 * polyline is not closed, false is returned.
 *
 * \see setClosed
 *
 * \param borderIsInside True if a position on the polyline counts as inside.
 * \param tolerance Tolerance used to check if point is on polyline.
 */
bool RPolyline::contains(const RVector& point, bool borderIsInside, double tolerance) const {
    if (!isGeometricallyClosed(tolerance)) {
        return false;
    }

    // check if point is on polyline:
    if (isOnShape(point, true, tolerance)) {
        return borderIsInside;
    }

    if (hasArcSegments()) {
        // TODO: not always reliable:
        QPainterPath pp = toPainterPath();
        return pp.contains(QPointF(point.x, point.y));
    }

    int nvert = vertices.size();
    int i, j;
    bool c = false;
    for (i=0, j=nvert-1; i<nvert; j=i++) {
        if (((vertices[i].y>point.y) != (vertices[j].y>point.y)) &&
             (point.x < (vertices[j].x-vertices[i].x) * (point.y-vertices[i].y) / (vertices[j].y-vertices[i].y) + vertices[i].x) ) {
            c = !c;
        }
    }
    return c;
}

/**
 * Checks if the given shape is completely inside this closed polygon. If this
 * polyline is not closed, false is returned.
 *
 * \see setClosed
 *
 * If the shape touches the polyline, false is returned.
 *
 * \param shape The shape to check.
 */
bool RPolyline::containsShape(const RShape& shape) const {
    // check if the shape intersects with any of the polygon edges:
    bool gotIntersection = false;
    if (shape.intersectsWith(*this)) {
        gotIntersection = true;
    }

    if (gotIntersection) {
        // normal selection:
        // entity does not match if there is an intersection:
        return false;
    }

    if (RShape::isPolylineShape(shape)) {
        const RPolyline& pl = dynamic_cast<const RPolyline&>(shape);
        for (int i=0; i<pl.countVertices() && i<5; i++) {
            if (contains(pl.getVertexAt(i))) {
                return true;
            }
        }
        return false;
    }

    // check if the shape is completely inside the polygon.
    // this is the case if one point on the entity is inside the polygon
    // and the entity does not intersect with the polygon.
    else if (shape.isDirected()) {
        return contains(shape.getStartPoint()) && contains(shape.getEndPoint());
    }
    else {
        // circle:
        if (RShape::isCircleShape(shape)) {
            const RCircle& circle = dynamic_cast<const RCircle&>(shape);
            RVector p1 = circle.getCenter() + RVector(circle.getRadius(), 0);
            RVector p2 = circle.getCenter() + RVector(-circle.getRadius(), 0);
            if (contains(p1) || contains(p2)) {
                return true;
            }
            return false;
        }
        else {
            // other shapes:
            RVector pointOnShape = shape.getPointOnShape();
            if (contains(pointOnShape, true)) {
                return true;
            }
            return false;
        }
    }

    // unsupported shape:
    Q_ASSERT(false);
    return false;
}

/**
 * \return Any point that is inside this polyline.
 */
RVector RPolyline::getPointInside() const {
    if (polylineProxy!=NULL) {
        return polylineProxy->getPointInside(*this);
    }
    return RVector::invalid;
}

RVector RPolyline::getStartPoint() const {
    if (vertices.size()==0) {
        return RVector::invalid;
    }

    return vertices.first();
}

RVector RPolyline::getEndPoint() const {
    if (vertices.size()==0) {
        return RVector::invalid;
    }

    if (isClosed()) {
        return vertices.first();
    }

    return vertices.last();
}

RVector RPolyline::getMiddlePoint() const {
    QList<RVector> pts = getPointsWithDistanceToEnd(getLength()/2, RS::FromStart);
    if (pts.length()==1) {
        return pts[0];
    }
    return RVector::invalid;
}

void RPolyline::moveStartPoint(const RVector& pos) {
    if (vertices.isEmpty()) {
        return;
    }
    vertices.first() = pos;
}

void RPolyline::moveEndPoint(const RVector& pos) {
    if (vertices.isEmpty()) {
        return;
    }
    vertices.last() = pos;
}

void RPolyline::moveSegmentAt(int i, const RVector& offset) {
    moveVertexAt(i, offset);
    if (i+1<countVertices()) {
        moveVertexAt(i+1, offset);
    }
    else {
        if (closed) {
            moveVertexAt(0, offset);
        }
    }
}

double RPolyline::getDirection1() const {
    if (vertices.size()==0) {
        return RNANDOUBLE;
    }

    QSharedPointer<RShape> shape = getSegmentAt(0);
    return shape->getDirection1();
}

double RPolyline::getDirection2() const {
    if (vertices.size()==0) {
        return RNANDOUBLE;
    }

    int i = vertices.size() - 2;
    if (isClosed()) {
        i++;
    }

    QSharedPointer<RShape> shape = getSegmentAt(i);
    return shape->getDirection2();
}

RS::Side RPolyline::getSideOfPoint(const RVector& point) const {
    int i = getClosestSegment(point);
    if (i<0 || i>=countSegments()) {
        return RS::NoSide;
    }

    QSharedPointer<RShape> segment = getSegmentAt(i);
    if (segment.isNull()) {
        return RS::NoSide;
    }
    return segment->getSideOfPoint(point);
}

RBox RPolyline::getBoundingBox() const {
    RBox ret;

    if (hasWidths()) {
        QList<RPolyline> outline = getOutline();
        for (int i=0; i<outline.length(); i++) {
            Q_ASSERT(!outline[i].hasWidths());
            RBox bb = outline[i].getBoundingBox();
            ret.growToInclude(bb);
        }
        return ret;
    }

    if (countVertices()==1) {
        ret = RBox(vertices.at(0), vertices.at(0));
    }

    QList<QSharedPointer<RShape> > sub = getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        RBox bb = (*it)->getBoundingBox();
        ret.growToInclude(bb);
    }

    return ret;
}

/**
 * \return Area of (implicitly closed) polyline.
 */
double RPolyline::getArea() const {
    double ret = 0.0;
    if (polylineProxy!=NULL) {
        ret = polylineProxy->getArea(*this, 0.01);
    }
    return ret;
}

double RPolyline::getLength() const {
    double ret = 0.0;

    QList<QSharedPointer<RShape> > sub = getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        double l = (*it)->getLength();
        if (RMath::isNormal(l)) {
            ret += l;
        }
    }

    return ret;
}

/**
 * \return Length along polyline from start point to given point p or
 * the closest point to p on the polyline.
 */
double RPolyline::getLengthTo(const RVector& p, bool limited) const {
    double ret = 0.0;

    if (p.equalsFuzzy(getStartPoint())) {
        return 0.0;
    }

    int segIdx = getClosestSegment(p);
    if (segIdx<0) {
        return -1.0;
    }

    for (int i=0; i<segIdx; i++) {
        double l = getSegmentAt(i)->getLength();
        if (RMath::isNormal(l)) {
            ret += l;
        }
    }

    QSharedPointer<RShape> seg = getSegmentAt(segIdx);
    bool lim = limited;
    if (segIdx!=0 && segIdx!=countSegments()-1) {
        lim = true;
    }
    RVector p2 = seg->getClosestPointOnShape(p, lim);
    seg->trimEndPoint(p2);
    ret += seg->getLength();

    return ret;
}

/**
 * \return Length of all segements from first index (fromIndex) to last index (toIndex),
 * excluding toIndex.
 */
double RPolyline::getSegmentsLength(int fromIndex, int toIndex) const {
    double len = 0.0;
    for (int i=fromIndex; i<toIndex; i++) {
        QSharedPointer<RShape> segment = getSegmentAt(i);
        len+=segment->getLength();
    }
    return len;
}

QList<double> RPolyline::getDistancesFromStart(const RVector& p) const {
    QList<double> ret;

    // any segment might contain point (self intersection):
    double len = 0.0;
    for (int i=0; i<countSegments(); i++) {
        QSharedPointer<RShape> segment = getSegmentAt(i);
        if (segment->getDistanceTo(p)<0.0001) {
            ret.append(len + segment->getDistanceFromStart(p));
        }
        len+=segment->getLength();
    }

    // point is not on polyline, return distance to point closest to position:
    if (ret.isEmpty()) {
        ret.append(getLengthTo(p, true));
    }

    return ret;
}

QList<RVector> RPolyline::getEndPoints() const {
    return vertices;
}

/*
// maybe:
void RPolyline::forEachSubShape(RPolyline* instance, void (RPolyline::*callBack)()) const{
    QList<QSharedPointer<RShape> > sub = getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        (instance->*callBack)(*it);
    }
}
*/

QList<RVector> RPolyline::getMiddlePoints() const {
    QList<RVector> ret;

    QList<QSharedPointer<RShape> > sub = getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        ret.append((*it)->getMiddlePoints());
    }

    return ret;
}

QList<RVector> RPolyline::getCenterPoints() const {
    QList<RVector> ret;

    QList<QSharedPointer<RShape> > sub = getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        ret.append((*it)->getCenterPoints());
    }

    return ret;
}

RVector RPolyline::getPointAtPercent(double p) const {
    double length = getLength();
    double distance = p * length;
    QList<RVector> candidates = getPointsWithDistanceToEnd(distance, RS::FromStart|RS::AlongPolyline);
    if (candidates.length()!=1) {
        return RVector::invalid;
    }
    return candidates.at(0);
}

QList<RVector> RPolyline::getPointsWithDistanceToEnd(double distance, int from) const {
    QList<RVector> ret;

    QList<QSharedPointer<RShape> > sub = getExploded();

    if (sub.isEmpty()) {
        return ret;
    }

    if (from&RS::AlongPolyline) {
        double remainingDist;
        double len;

        if (from&RS::FromStart) {
            if (distance<0.0) {
                // extend at start:
                ret.append(sub.first()->getPointsWithDistanceToEnd(distance, RS::FromStart));
            }
            else {
                remainingDist = distance;
                for (int i=0; i<sub.length(); i++) {
                    len = sub[i]->getLength();
                    if (remainingDist>len) {
                        remainingDist-=len;
                    }
                    else {
                        ret.append(sub[i]->getPointsWithDistanceToEnd(remainingDist, RS::FromStart));
                        break;
                    }
                }
            }
        }

        if (from&RS::FromEnd) {
            if (distance<0.0) {
                // extend at end:
                ret.append(sub.last()->getPointsWithDistanceToEnd(distance, RS::FromEnd));
            }
            else {
                remainingDist = distance;
                for (int i=sub.length()-1; i>=0; i--) {
                    len = sub[i]->getLength();
                    if (remainingDist>len) {
                        remainingDist-=len;
                    }
                    else {
                        ret.append(sub[i]->getPointsWithDistanceToEnd(remainingDist, RS::FromEnd));
                        break;
                    }
                }
            }
        }
    }
    else {
        QList<QSharedPointer<RShape> >::iterator it;
        for (it=sub.begin(); it!=sub.end(); ++it) {
            ret.append((*it)->getPointsWithDistanceToEnd(distance, from));
        }
    }

    return ret;
}

QList<RVector> RPolyline::getPointCloud(double segmentLength) const {
    QList<RVector> ret;
    for (int i=0; i<countSegments(); i++) {
        QSharedPointer<RShape> seg = getSegmentAt(i);
        if (seg.isNull()) {
            continue;
        }
        ret.append(seg->getPointCloud(segmentLength));
    }
    return ret;
}

double RPolyline::getAngleAt(double distance, RS::From from) const {
    QList<QSharedPointer<RShape> > sub = getExploded();

    if (from&RS::AlongPolyline) {
        double remainingDist;
        double len;

        if (from&RS::FromStart) {
            remainingDist = distance;
            for (int i=0; i<sub.length(); i++) {
                len = sub[i]->getLength();
                if (remainingDist>len) {
                    remainingDist-=len;
                }
                else {
                    return sub[i]->getAngleAt(remainingDist, RS::FromStart);
                }
            }
        }

        if (from&RS::FromEnd) {
            remainingDist = distance;
            for (int i=sub.length()-1; i>=0; i--) {
                len = sub[i]->getLength();
                if (remainingDist>len) {
                    remainingDist-=len;
                }
                else {
                    return sub[i]->getAngleAt(remainingDist, RS::FromEnd);
                }
            }
        }
    }
    //else {
        // not implemented / never used
    //    Q_ASSERT(false);
    //}

    return RNANDOUBLE;
}

RVector RPolyline::getVectorTo(const RVector& point, bool limited, double strictRange) const {
    RVector ret = RVector::invalid;

    QList<QSharedPointer<RShape> > sub = getExploded();
    for (int i=0; i<sub.length(); i++) {
        QSharedPointer<RShape> shape = sub.at(i);
        bool lim = limited;
        if (i!=0 && i!=sub.length()-1) {
            // segments in the middle: always limited:
            lim = true;
        }
        RVector v = shape->getVectorTo(point, lim, strictRange);
        if (v.isValid() && (!ret.isValid() || v.getMagnitude()<ret.getMagnitude())) {
            ret = v;
        }
    }

    return ret;
}

double RPolyline::getDistanceTo(const RVector& point, bool limited, double strictRange) const {
    if (!hasWidths()) {
        return RShape::getDistanceTo(point, limited, strictRange);
    }

    Q_UNUSED(limited)

    if (!getBoundingBox().grow(strictRange).contains(point)) {
        return RNANDOUBLE;
    }

    double ret = RNANDOUBLE;

    QList<RPolyline> outline = getOutline();
    for (int i=0; i<outline.length(); i++) {
        Q_ASSERT(!outline[i].hasWidths());
        double d = outline[i].getDistanceTo(point);
        if (RMath::isNaN(ret) || d<ret) {
            ret = d;
        }

        if (outline[i].isGeometricallyClosed()) {
            if (outline[i].contains(point)) {
                if (RMath::isNaN(ret) || strictRange<ret) {
                    ret = strictRange;
                }
            }
        }
    }

    return ret;
}

int RPolyline::getClosestSegment(const RVector& point) const {
    int ret = -1;
    double minDist = -1;

    for (int i=0; i<countSegments(); i++) {
        QSharedPointer<RShape> segment = getSegmentAt(i);
        if (segment.isNull()) {
            break;
        }
        double dist = segment->getDistanceTo(point, true);
        if (!RMath::isNormal(dist)) {
            continue;
        }
        if (minDist<0 || dist<minDist) {
            minDist = dist;
            ret = i;
        }
    }

    return ret;
}

int RPolyline::getClosestVertex(const RVector& point) const {
    return point.getClosestIndex(getVertices());
}

bool RPolyline::move(const RVector& offset) {
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].move(offset);
    }
    return true;
}

bool RPolyline::rotate(double rotation, const RVector& center) {
    if (fabs(rotation) < RS::AngleTolerance) {
        return false;
    }
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].rotate(rotation, center);
    }
    return true;
}

bool RPolyline::scale(double scaleFactor, const RVector& center) {
    return RShape::scale(scaleFactor, center);
}

bool RPolyline::scale(const RVector& scaleFactors, const RVector& center) {
    if (hasArcSegments() && !RMath::fuzzyCompare(scaleFactors.x, scaleFactors.y)) {
        // non-uniform scaling of polyline with arcs:
        RPolyline pl;
        for (int i=0; i<countSegments(); i++) {
            QSharedPointer<RShape> seg = getSegmentAt(i);
            if (seg.isNull()) {
                continue;
            }

            // TODO: apply widths to new segments:
            //double w1 = getStartWidthAt(i);
            //double w2 = getStartWidthAt((i+1)%countVertices());

            QSharedPointer<RShape> newSeg;
            if (RShape::isLineShape(*seg)) {
                newSeg = seg;
                newSeg->scale(scaleFactors, center);
            }
            else {
                newSeg = RShape::scaleArc(*seg, scaleFactors, center);
            }

            if (!newSeg.isNull()) {
                pl.appendShape(*newSeg);
            }
        }
        // new polyline with tangentially connected small arc segments for original arc segments:
        *this = pl;
        return true;
    }

    for (int i=0; i<vertices.size(); i++) {
        vertices[i].scale(scaleFactors, center);
    }
    for (int i=0; i<startWidths.size(); i++) {
        if (startWidths[i]>0.0) {
            startWidths[i]*=fabs(scaleFactors.x);
        }
    }
    for (int i=0; i<endWidths.size(); i++) {
        if (endWidths[i]>0.0) {
            endWidths[i]*=fabs(scaleFactors.x);
        }
    }
    // factor in x or in y is negative -> mirror:
    if ((scaleFactors.x<0) != (scaleFactors.y<0)) {
        for (int i=0; i<bulges.size(); i++) {
            bulges[i] *= -1;
        }
    }
    return true;
}

bool RPolyline::mirror(const RLine& axis) {
    int i;
    for (i=0; i<vertices.size(); i++) {
        vertices[i].mirror(axis);
    }
    for (i=0; i<bulges.size(); i++) {
        bulges[i] *= -1;
    }
    return true;
}

bool RPolyline::reverse() {
    RPolyline nPolyline;
    QList<QSharedPointer<RShape> > segments = getExploded();

    for (int i=segments.count()-1; i>=0; i--) {
        QSharedPointer<RShape> seg = segments.at(i);
        seg->reverse();
        nPolyline.appendShape(*seg);
    }
    if (closed) {
        nPolyline.convertToClosed();
    }
    *this = nPolyline;

    Q_ASSERT(vertices.length()==bulges.length());
    Q_ASSERT(vertices.length()==startWidths.length());
    Q_ASSERT(vertices.length()==endWidths.length());

    return true;
}

RPolyline RPolyline::getReversed() const {
    RPolyline ret = *this;
    ret.reverse();
    return ret;
}

bool RPolyline::stretch(const RPolyline& area, const RVector& offset) {
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].stretch(area, offset);
    }
    return true;
}

QSharedPointer<RShape> RPolyline::getTransformed(const QTransform& transform) const {
    QSharedPointer<RPolyline> ret = QSharedPointer<RPolyline>(new RPolyline());

    for (int i=0; i<countSegments(); i++) {
        QSharedPointer<RShape> s = getSegmentAt(i);
        QSharedPointer<RShape> st = s->getTransformed(transform);
        ret->appendShape(*st);
    }

    return ret;
}

RS::Ending RPolyline::getTrimEnd(const RVector& trimPoint, const RVector& clickPoint) {
    if (polylineProxy!=NULL) {
        return polylineProxy->getTrimEnd(*this, trimPoint, clickPoint);
    }
    return RS::EndingNone;
}

bool RPolyline::trimStartPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    if (polylineProxy!=NULL) {
        return polylineProxy->trimStartPoint(*this, trimPoint, clickPoint, extend);
    }
    return false;
}

bool RPolyline::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint, bool extend) {
    if (polylineProxy!=NULL) {
        return polylineProxy->trimEndPoint(*this, trimPoint, clickPoint, extend);
    }
    return false;
}

bool RPolyline::trimStartPoint(double trimDist) {
    if (polylineProxy!=NULL) {
        return polylineProxy->trimStartPoint(*this, trimDist);
    }
    return false;
}

bool RPolyline::trimEndPoint(double trimDist) {
    if (polylineProxy!=NULL) {
        return polylineProxy->trimEndPoint(*this, trimDist);
    }
    return false;
}

void RPolyline::print(QDebug dbg) const {
    dbg.nospace() << "\nRPolyline(";
    RShape::print(dbg);
    dbg.nospace() << ", ";
    dbg.nospace() << "vertices: " << vertices << ", ";
    dbg.nospace() << "bulges: " << bulges << ", ";
    dbg.nospace() << "start widths: " << startWidths << ", ";
    dbg.nospace() << "end widths: " << endWidths << ", ";
    dbg.nospace() << "closed: " << closed << ", ";
//    QList<QSharedPointer<RShape> > sub = getExploded();
//    QList<QSharedPointer<RShape> >::iterator it;
//    for (it=sub.begin(); it!=sub.end(); ++it) {
//        dbg.nospace() << "\n" << *it->data() << ", ";
//    }
    dbg.nospace() << ")";
}

/**
 * Simplify by attempting to skip nodes within given tolerance.
 * \return True if nodes have been skipped.
 */
bool RPolyline::simplify(double tolerance) {
    if (RPolyline::hasProxy()) {
        return RPolyline::getPolylineProxy()->simplify(*this, tolerance);
    }
    else {
        return false;
    }
}

/**
 * Verifies the tangency of this polyline.
 */
QList<RVector> RPolyline::verifyTangency(double toleranceMin, double toleranceMax) {
    if (RPolyline::hasProxy()) {
        return RPolyline::getPolylineProxy()->verifyTangency(*this, toleranceMin, toleranceMax);
    }
    else {
        return QList<RVector>();
    }
}

/**
 * Modifies (bevels, rounds, trims) the corner of this polyline between segmentIndex1 and segmentIndex2
 * at the given segment endings. The given cornerShape (bevel, rouding) is inserted between.
 */
RPolyline RPolyline::modifyPolylineCorner(const RShape& trimmedShape1, RS::Ending ending1, int segmentIndex1,
                                     const RShape& trimmedShape2, RS::Ending ending2, int segmentIndex2,
                                     const RShape* cornerShape) const {
    QSharedPointer<RShape> segment;

    RPolyline pl;

    if (segmentIndex1<segmentIndex2 && ending1==RS::EndingEnd && ending2==RS::EndingStart) {
        for (int i=0; i<segmentIndex1; i++) {
            segment = getSegmentAt(i);
            pl.appendShape(*segment);
            pl.setStartWidthAt(pl.startWidths.size()-2, getStartWidthAt(i));
            pl.setEndWidthAt(pl.endWidths.size()-2, getEndWidthAt(i));
        }

        pl.appendShapeAuto(trimmedShape1);
        if (cornerShape!=NULL) {
            pl.appendShapeAuto(*cornerShape);
        }
        pl.appendShapeAuto(trimmedShape2);

        for (int i=segmentIndex2+1; i<countSegments(); i++) {
            segment = getSegmentAt(i);
            pl.appendShape(*segment);
            pl.setStartWidthAt(pl.startWidths.size()-2, getStartWidthAt(i));
            pl.setEndWidthAt(pl.endWidths.size()-2, getEndWidthAt(i));
        }
    }
    else if (segmentIndex1>segmentIndex2 && ending1==RS::EndingStart && ending2==RS::EndingEnd) {
        for (int i=0; i<segmentIndex2; i++) {
            segment = getSegmentAt(i);
            pl.appendShape(*segment);
            pl.setStartWidthAt(pl.startWidths.size()-2, getStartWidthAt(i));
            pl.setEndWidthAt(pl.endWidths.size()-2, getEndWidthAt(i));
        }

        pl.appendShapeAuto(trimmedShape2);
        if (cornerShape!=NULL) {
            pl.appendShapeAuto(*cornerShape);
        }
        pl.appendShapeAuto(trimmedShape1);

        for (int i=segmentIndex1+1; i<countSegments(); i++) {
            segment = getSegmentAt(i);
            pl.appendShape(*segment);
            pl.setStartWidthAt(pl.startWidths.size()-2, getStartWidthAt(i));
            pl.setEndWidthAt(pl.endWidths.size()-2, getEndWidthAt(i));
        }
    }
    else if (segmentIndex1<segmentIndex2 && ending1==RS::EndingStart && ending2==RS::EndingEnd) {
        pl.appendShapeAuto(trimmedShape1);
        for (int i=segmentIndex1+1; i<segmentIndex2; i++) {
            segment = getSegmentAt(i);
            pl.appendShape(*segment);
            pl.setStartWidthAt(pl.startWidths.size()-2, getStartWidthAt(i));
            pl.setEndWidthAt(pl.endWidths.size()-2, getEndWidthAt(i));
        }
        pl.appendShapeAuto(trimmedShape2);
        if (cornerShape!=NULL) {
            pl.appendShapeAuto(*cornerShape);
        }
    }
    else if (segmentIndex1>segmentIndex2 && ending1==RS::EndingEnd && ending2==RS::EndingStart) {
        pl.appendShapeAuto(trimmedShape2);
        for (int i=segmentIndex2+1; i<segmentIndex1; i++) {
            segment = getSegmentAt(i);
            pl.appendShape(*segment);
            pl.setStartWidthAt(pl.startWidths.size()-2, getStartWidthAt(i));
            pl.setEndWidthAt(pl.endWidths.size()-2, getEndWidthAt(i));
        }
        pl.appendShapeAuto(trimmedShape1);
        if (cornerShape!=NULL) {
            pl.appendShapeAuto(*cornerShape);
        }
    }

    return pl;
}

bool RPolyline::isConcave() const {
    return !getConcaveVertices().isEmpty();
}

QList<RVector> RPolyline::getConvexVertices(bool convex) const {
    if (!isGeometricallyClosed()) {
        return QList<RVector>();
    }

    RPolyline pl = *this;
    pl.autoClose();

    RS::Orientation ori = pl.getOrientation();

    QList<RVector> ret;

    for (int i=0; i<pl.vertices.count(); i++) {
        int iPrev = RMath::absmod(i-1, pl.vertices.count());
        QSharedPointer<RShape> segmentPrev = pl.getSegmentAt(iPrev);
        QSharedPointer<RShape> segmentNext = pl.getSegmentAt(i);

        double aPrev = segmentPrev->getDirection2() + M_PI;
        double aNext = segmentNext->getDirection1();

        RVector pPrev = RVector::createPolar(1.0, aPrev);
        RVector pNext = RVector::createPolar(1.0, aNext);

        RVector cp = RVector::getCrossProduct(pPrev, pNext);

        if (convex) {
            if (ori==RS::CW && cp.z<0.0 || ori==RS::CCW && cp.z>0.0) {
                ret.append(pl.vertices[i]);
            }
        }
        else {
            if (ori==RS::CCW && cp.z<0.0 || ori==RS::CW && cp.z>0.0) {
                ret.append(pl.vertices[i]);
            }
        }
    }

    return ret;
}

QList<RVector> RPolyline::getConcaveVertices() const {
    return getConvexVertices(false);
}

QList<RPolyline> RPolyline::splitAtDiscontinuities(double tolerance) const {
    if (polylineProxy!=NULL) {
        return polylineProxy->splitAtDiscontinuities(*this, tolerance);
    }
    return QList<RPolyline>() << *this;
}

/**
 * Splits the polyline into polylines with exclusively line or arc segments.
 */
QList<RPolyline> RPolyline::splitAtSegmentTypeChange() const {
    if (polylineProxy!=NULL) {
        return polylineProxy->splitAtSegmentTypeChange(*this);
    }
    return QList<RPolyline>() << *this;
}

double RPolyline::getBaseAngle() const {
    if (polylineProxy!=NULL) {
        return polylineProxy->getBaseAngle(*this);
    }
    return 0.0;
}

double RPolyline::getWidth() const {
    if (polylineProxy!=NULL) {
        return polylineProxy->getWidth(*this);
    }
    return 0.0;
}

bool RPolyline::setWidth(double v) {
    if (polylineProxy!=NULL) {
        return polylineProxy->setWidth(*this, v);
    }
    return false;
}

double RPolyline::getHeight() const {
    if (polylineProxy!=NULL) {
        return polylineProxy->getHeight(*this);
    }
    return 0.0;
}

bool RPolyline::setHeight(double v) {
    if (polylineProxy!=NULL) {
        return polylineProxy->setHeight(*this, v);
    }
    return false;
}

QList<RPolyline> RPolyline::morph(const RPolyline& target, int steps, RS::Easing easing, bool zLinear, double customFactor) const {
    if (polylineProxy!=NULL) {
        return polylineProxy->morph(*this, target, steps, easing, zLinear, customFactor);
    }
    return QList<RPolyline>();
}

RPolyline RPolyline::roundAllCorners(double radius) const {
    if (polylineProxy!=NULL) {
        return polylineProxy->roundAllCorners(*this, radius);
    }
    return *this;
}

RPolyline RPolyline::getPolygonHull(double angle, double tolerance, bool inner) const {
    if (polylineProxy!=NULL) {
        return polylineProxy->getPolygonHull(*this, angle, tolerance, inner);
    }
    return *this;
}
