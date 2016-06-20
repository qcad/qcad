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
#include <cmath>

#include "RArc.h"
#include "RBox.h"
#include "RCircle.h"
#include "RDirected.h"
#include "RLine.h"
#include "RPainterPath.h"
#include "RPolyline.h"

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
        QSharedPointer<RDirected> directed = it->dynamicCast<RDirected>();

        if (!directed.isNull()) {
            if (vertices.size()==0) {
                appendVertex(directed->getStartPoint(), 0.0);
            }
            appendVertex(directed->getEndPoint(), 0.0);
        }

        QSharedPointer<RArc> arc = directed.dynamicCast<RArc>();
        if (!arc.isNull()) {
            if (bulges.size()>1) {
                bulges[bulges.size()-2] = arc->getBulge();
            }
        }
    }

    autoClose();
}

RPolyline::~RPolyline() {
}

void RPolyline::to2D() {
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].z = 0.0;
    }
}

void RPolyline::clear() {
    vertices.clear();
    bulges.clear();
    startWidths.clear();
    endWidths.clear();
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

    for (int i=0; i<vertices.size(); i++) {
        RVector v = vertices[i];
        double b = bulges[i];

        if (i==0 || !v.equalsFuzzy(vPrev, tolerance)) {
            newVertices.append(v);
            newBulges.append(b);
            newStartWidths.append(startWidths[i]);
            newEndWidths.append(endWidths[i]);
        }

        vPrev = v;
    }

    vertices = newVertices;
    bulges = newBulges;
    startWidths = newStartWidths;
    endWidths = newEndWidths;
}

bool RPolyline::prependShape(const RShape& shape) {
    return appendShape(shape, true);
}

bool RPolyline::appendShape(const RShape& shape, bool prepend) {
    bool ret = true;

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

    const RDirected* directed = NULL;
    double bulge = 0.0;

    const RLine* line = dynamic_cast<const RLine*>(&shape);
    if (line!=NULL) {
        directed = line;
    }
    else {
        const RArc* arc = dynamic_cast<const RArc*>(&shape);
        if (arc!=NULL) {
            bulge = arc->getBulge();
            directed = arc;
        }
    }

    if (directed==NULL) {
        qWarning() << "RPolyline::appendShape: shape is not a line, arc or polyline: " << shape;
        return false;
    }

    RVector connectionPoint;
    RVector nextPoint;
    double gap;
    if (prepend) {
        // prepend:
        connectionPoint = directed->getEndPoint();
        nextPoint = directed->getStartPoint();
        if (vertices.size()==0) {
            appendVertex(connectionPoint);
        }
        gap = vertices.first().getDistanceTo(connectionPoint);
    }
    else {
        // append:
        connectionPoint = directed->getStartPoint();
        nextPoint = directed->getEndPoint();
        if (vertices.size()==0) {
            appendVertex(connectionPoint);
        }
        gap = vertices.last().getDistanceTo(connectionPoint);
    }

    if (!RMath::fuzzyCompare(gap, 0.0, 1.0e-4)) {
        qWarning() << "RPolyline::appendShape: arc or line not connected to polyline:\nshape:" << shape << "\ngap: " << gap;
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

    return ret;
}

void RPolyline::appendVertex(const RVector& vertex, double bulge, double w1, double w2) {
    vertices.append(vertex);
    bulges.append(bulge);
    startWidths.append(w1);
    endWidths.append(w2);
}

void RPolyline::prependVertex(const RVector& vertex, double bulge, double w1, double w2) {
    vertices.prepend(vertex);
    bulges.prepend(bulge);
    startWidths.prepend(w1);
    endWidths.prepend(w2);
}

void RPolyline::insertVertex(int index, const RVector& vertex) {
    vertices.insert(index, vertex);
    if (index>0) {
        bulges[index-1] = 0.0;
    }
    bulges.insert(index, 0.0);
    startWidths.insert(index, RNANDOUBLE);
    endWidths.insert(index, RNANDOUBLE);
}

/**
 * Inserts a git point at the point on the spline closest to the given position.
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

    QSharedPointer<RDirected> dir1 = seg1.dynamicCast<RDirected>();
    QSharedPointer<RDirected> dir2 = seg2.dynamicCast<RDirected>();

    if (dir1.isNull() || dir2.isNull()) {
        return;
    }

    dir1->trimEndPoint(p);
    dir2->trimStartPoint(p);

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
}

void RPolyline::removeFirstVertex() {
    if (vertices.isEmpty()) {
        return;
    }
    vertices.removeFirst();
    bulges.removeFirst();
    startWidths.removeFirst();
    endWidths.removeFirst();
}

void RPolyline::removeLastVertex() {
    if (vertices.isEmpty()) {
        return;
    }
    vertices.removeLast();
    bulges.removeLast();
    startWidths.removeLast();
    endWidths.removeLast();
}

void RPolyline::removeVertex(int index) {
    vertices.removeAt(index);
    bulges.removeAt(index);
    startWidths.removeAt(index);
    endWidths.removeAt(index);
}

void RPolyline::removeVerticesAfter(int index) {
    vertices = vertices.mid(0, index+1);
    bulges = bulges.mid(0, index+1);
    startWidths = startWidths.mid(0, index+1);
    endWidths = endWidths.mid(0, index+1);
}

void RPolyline::removeVerticesBefore(int index) {
    vertices = vertices.mid(index);
    bulges = bulges.mid(index);
    startWidths = startWidths.mid(index);
    endWidths = endWidths.mid(index);
}

void RPolyline::setVertices(const QList<RVector>& vertices) {
    this->vertices = vertices;

    bulges.clear();
    for (int i=0; i<vertices.size(); ++i) {
        bulges.append(0.0);
        startWidths.append(RNANDOUBLE);
        endWidths.append(RNANDOUBLE);
    }
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
    QSharedPointer<RDirected> prevDir = prevSegment.dynamicCast<RDirected>();
    QSharedPointer<RDirected> nextDir = nextSegment.dynamicCast<RDirected>();
    if (prevDir.isNull() || nextDir.isNull()) {
        return 0.0;
    }

    // angle from vertex to next segment:
    double aNext = nextDir->getDirection1();
    // angle from vertex to previous segment:
    double aPrev = prevDir->getDirection2();

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
        if (startWidths[i]>0.0) {
            // widths in last vertex only count if closed:
            if (i!=startWidths.length()-1 || isClosed()) {
                return true;
            }
        }
        if (endWidths[i]>0.0) {
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

void RPolyline::setClosed(bool on) {
    closed = on;
}

bool RPolyline::isClosed() const {
    return closed;
}

bool RPolyline::isGeometricallyClosed(double tolerance) const {
    return isClosed() || getStartPoint().getDistanceTo(getEndPoint()) < tolerance;
}

bool RPolyline::autoClose() {
    if (isClosed()) {
        return false;
    }

    if (!isGeometricallyClosed()) {
        return false;
    }

    removeLastVertex();
    setClosed(true);
    return true;
}

RS::Orientation RPolyline::getOrientation(bool implicitelyClosed) const {
    if (!implicitelyClosed && !isGeometricallyClosed()) {
        return RS::Any;
    }

    if (countSegments()<1) {
        return RS::Any;
    }

    RVector minV = RVector::invalid;
    QSharedPointer<RDirected> shapeBefore;
    QSharedPointer<RDirected> shapeAfter;
    QSharedPointer<RShape> shape;
    QSharedPointer<RDirected> previousShape = getSegmentAt(countSegments()-1).dynamicCast<RDirected>();

    // find minimum vertex (lower left corner):
    QList<QSharedPointer<RShape> > segments = getExploded();
    for (int i=0; i<segments.length(); i++) {
        shape = getSegmentAt(i);
        if (shape.isNull()) {
            continue;
        }
        QSharedPointer<RDirected> directed = shape.dynamicCast<RDirected>();
        if (directed.isNull()) {
            continue;
        }

        RVector v = directed->getStartPoint();
        if (!minV.isValid() || v.x<minV.x || (v.x==minV.x && v.y<minV.y)) {
            minV = v;
            shapeBefore = previousShape;
            shapeAfter = directed;
        }

        previousShape = directed;
    }

    double l;
    RVector p;
    QSharedPointer<RArc> arcBefore = shapeBefore.dynamicCast<RArc>();
    if (!arcBefore.isNull()) {
        l = arcBefore->getLength();
        p = arcBefore->getPointsWithDistanceToEnd(l/10, RS::FromStart)[0];
        shapeBefore = QSharedPointer<RLine>(new RLine(p, arcBefore->getEndPoint()));
    }

    QSharedPointer<RArc> arcAfter = shapeAfter.dynamicCast<RArc>();
    if (!arcAfter.isNull()) {
        l = arcAfter->getLength();
        p = arcAfter->getPointsWithDistanceToEnd(l/10, RS::FromEnd)[0];
        shapeAfter = QSharedPointer<RLine>(new RLine(arcAfter->getStartPoint(), p));
    }

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

/**
 * \return A QPainterPath object that represents this polyline.
 */
RPainterPath RPolyline::toPainterPath() const {
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

/**
 * Relocates the start point of this closed polyline to the given point.
 * The visual appearance of the polyline does not change.
 */
bool RPolyline::relocateStartPoint(const RVector& p) {
    if (!isGeometricallyClosed()) {
        return false;
    }

    // convert closed to open polyline with start in p:
    // find closest segment of polyline:
    int segmentIndex = getClosestSegment(p);
    if (segmentIndex<0) {
        return false;
    }

    RPolyline newShape;

    QSharedPointer<RShape> firstSegment = getSegmentAt(segmentIndex);
    QSharedPointer<RDirected> firstDirected = firstSegment.dynamicCast<RDirected>();
    if (firstSegment.isNull() || firstDirected.isNull()) {
        return false;
    }
    QSharedPointer<RShape> lastSegment = getSegmentAt(segmentIndex);
    QSharedPointer<RDirected> lastDirected = lastSegment.dynamicCast<RDirected>();
    if (lastSegment.isNull() || lastDirected.isNull()) {
        return false;
    }

    // trim segment start to p
    firstDirected->trimStartPoint(p);

    // start polyline with second part of split segment:
    newShape.appendShape(*firstSegment);

    // append rest of polyline:
    for (int i=segmentIndex+1; i<countSegments(); i++) {
        newShape.appendShape(*getSegmentAt(i));
    }
    for (int i=0; i<segmentIndex; i++) {
        newShape.appendShape(*getSegmentAt(i));
    }

    // trim segment end to p
    lastDirected->trimEndPoint(p);

    // end polyline with second part of split segment:
    newShape.appendShape(*lastSegment);
    newShape.setClosed(false);
    *this = newShape;

    return true;
}

bool RPolyline::convertToClosed() {
    if (!isGeometricallyClosed()) {
        return false;
    }

    if (isClosed()) {
        return true;
    }

    removeLastVertex();
    setClosed(true);
    return true;
}

bool RPolyline::convertToOpen() {
    if (!isClosed()) {
        return false;
    }

    if (isGeometricallyClosed()) {
        return true;
    }

    QSharedPointer<RShape> last = getLastSegment();
    setClosed(false);
    removeLastVertex();
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
 * polyline is not closed (\see setClosed), false is returned.
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

    // check if the shape is completely inside the polygon.
    // this is the case if one point on the entity is inside the polygon
    // and the entity does not intersect with the polygon.
    const RDirected* dir = dynamic_cast<const RDirected*>(&shape);
    if (dir!=NULL) {
        return contains(dir->getStartPoint()) && contains(dir->getEndPoint());
    }

    Q_ASSERT("shape not supported");
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

double RPolyline::getDirection1() const {
    if (vertices.size()==0) {
        return RNANDOUBLE;
    }

    QSharedPointer<RShape> shape = getSegmentAt(0);
    QSharedPointer<RDirected> dirShape = shape.dynamicCast<RDirected>();
    if (dirShape.isNull()) {
        return RNANDOUBLE;
    }

    return dirShape->getDirection1();
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
    QSharedPointer<RDirected> dirShape = shape.dynamicCast<RDirected>();
    if (dirShape.isNull()) {
        return RNANDOUBLE;
    }

    return dirShape->getDirection2();
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

    QSharedPointer<RDirected> directed = segment.dynamicCast<RDirected>();
    if (directed.isNull()) {
        return RS::NoSide;
    }

    return directed->getSideOfPoint(point);
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
 * \author Robert S.
 */
double RPolyline::getArea() const {
//    double control = 0.0;
//    if (polylineProxy!=NULL) {
//        control = polylineProxy->getArea(*this, 0.01);
//    }

    RPolyline closedCopy = *this;
    if (!closedCopy.isGeometricallyClosed()) {
        closedCopy.setClosed(true);
    }

    // polygonal area (all segments treated as lines):
    QList<RVector> pts = closedCopy.getVertices();
    double area = 0;
    int nPts = closedCopy.countVertices();
    int j = nPts - 1;
    RVector p1;
    RVector p2;

    for (int i=0; i<nPts; j=i++) {
        p1 = pts[i];
        p2 = pts[j];
        area += p1.x * p2.y;
        area -= p1.y * p2.x;
    }
    area /= 2;
    area = fabs(area);

    // add / subtract arc segment sector area:
    if (closedCopy.hasArcSegments()) {
        bool plReversed = (closedCopy.getOrientation()==RS::CW);
        for (int i = 0; i < closedCopy.countSegments(); i++) {
            if (closedCopy.isArcSegmentAt(i)) {
                QSharedPointer<RShape> shape = closedCopy.getSegmentAt(i);
                QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
                if (!arc.isNull()) {
                    double chordArea = arc->getChordArea();

                    if (arc->isReversed()==plReversed) {
                        // arc has same orientation as polyline: add
                        area = area + chordArea;
                    }
                    else {
                        // arc has opposite orientation of polyline: subtract
                        area = area - chordArea;
                    }
                }
            }
        }
    }

    area = fabs(area);
    //qDebug() << "error: " << fabs(area - control);
    return area;
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
    QSharedPointer<RDirected> dir = seg.dynamicCast<RDirected>();
    dir->trimEndPoint(p2);
    ret += seg->getLength();

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

QList<RVector> RPolyline::getPointsWithDistanceToEnd(double distance, RS::From from) const {
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
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].scale(scaleFactors, center);
    }
    for (int i=0; i<startWidths.size(); i++) {
        if (startWidths[i]>0.0) {
            startWidths[i]*=scaleFactors.x;
        }
    }
    for (int i=0; i<endWidths.size(); i++) {
        if (endWidths[i]>0.0) {
            endWidths[i]*=scaleFactors.x;
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
        QSharedPointer<RDirected> directed = seg.dynamicCast<RDirected>();
        directed->reverse();
        nPolyline.appendShape(*seg);
    }
    if (closed) {
        nPolyline.convertToClosed();
    }
    *this = nPolyline;
    return true;
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

bool RPolyline::trimStartPoint(const RVector& trimPoint, const RVector& clickPoint) {
    if (polylineProxy!=NULL) {
        return polylineProxy->trimStartPoint(*this, trimPoint, clickPoint);
    }
    return false;
}

bool RPolyline::trimEndPoint(const RVector& trimPoint, const RVector& clickPoint) {
    if (polylineProxy!=NULL) {
        return polylineProxy->trimEndPoint(*this, trimPoint, clickPoint);
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

bool RPolyline::simplify(double angleTolerance) {
    bool ret = false;
    RPolyline newPolyline;

    RS::EntityType type = RS::EntityUnknown;
    double angle = RMAXDOUBLE;
    double radius = RMAXDOUBLE;
    RVector center = RVector::invalid;

    for (int i=0; i<countSegments(); i++) {
        QSharedPointer<RShape> seg = getSegmentAt(i);

        QSharedPointer<RLine> line = seg.dynamicCast<RLine>();
        if (!line.isNull()) {
            if (line->getLength()<RS::PointTolerance) {
                ret = true;
            }
            else {
                double angleDiff = qAbs(RMath::getAngleDifference180(line->getAngle(), angle));
                if (type==RS::EntityLine && angleDiff<angleTolerance) {
                    ret = true;
                }
                else {
                    newPolyline.appendVertex(line->getStartPoint());
                    angle = line->getAngle();
                    type = RS::EntityLine;
                }
            }
            radius = RMAXDOUBLE;
            center = RVector::invalid;
        }

        QSharedPointer<RArc> arc = seg.dynamicCast<RArc>();
        if (!arc.isNull()) {
            // simplify consecutive arcs:
            if (arc->getCenter().equalsFuzzy(center, 0.001) && RMath::fuzzyCompare(arc->getRadius(), radius, 0.001)) {
                arc->setStartAngle(arc->getCenter().getAngleTo(newPolyline.getEndPoint()));
                newPolyline.removeLastVertex();
            }
            newPolyline.appendVertex(arc->getStartPoint(), arc->getBulge());
            angle = RMAXDOUBLE;
            radius = arc->getRadius();
            center = arc->getCenter();
        }
    }

    if (isClosed()) {
        newPolyline.setClosed(true);
    }
    else {
        newPolyline.appendVertex(getEndPoint());
    }

    vertices = newPolyline.vertices;
    bulges = newPolyline.bulges;
    closed = newPolyline.closed;
    startWidths = newPolyline.startWidths;
    endWidths = newPolyline.endWidths;

    return ret;
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
