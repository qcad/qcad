/**
 * Copyright (c) 2011-2015 by Andrew Mustun. All rights reserved.
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
RPolyline::RPolyline(const QList<QSharedPointer<RShape> >& segments) {
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
}

void RPolyline::normalize() {
    QList<RVector> newVertices;
    QList<double> newBulges;

    RVector vPrev;

    for (int i=0; i<vertices.size(); i++) {
        RVector v = vertices[i];
        double b = bulges.at(i);

        if (i==0 || !v.equalsFuzzy(vPrev)) {
            newVertices.append(v);
            newBulges.append(b);
        }

        vPrev = v;
    }

    vertices = newVertices;
    bulges = newBulges;
}

void RPolyline::prependShape(const RShape& shape) {
    appendShape(shape, true);
//    const RDirected* directed = dynamic_cast<const RDirected*>(&shape);
//    if (directed==NULL) {
//        qWarning() << "RPolyline::prependShape: shape is not a line, arc or polyline: " << shape;
//        return;
//    }

//    const RPolyline* pl = dynamic_cast<const RPolyline*>(&shape);
//    if (pl!=NULL) {
//        for (int i=pl->countSegments()-1; i>=0; --i) {
//            QSharedPointer<RShape> s = pl->getSegmentAt(i);
//            if (s.isNull()) {
//                continue;
//            }
//            prependShape(*s.data());
//        }
//    }

//    double bulge = 0.0;
//    const RArc* arc = dynamic_cast<const RArc*>(&shape);
//    if (arc!=NULL) {
//        bulge = arc->getBulge();
//    }

//    const RLine* line = dynamic_cast<const RLine*>(&shape);
//    if (line!=NULL) {
//        directed = line;
//    }

//    if (vertices.size()==0) {
//        prependVertex(directed->getEndPoint());
//    }

//    if (!vertices.last().equalsFuzzy(directed->getEndPoint())) {
//        qWarning("RPolyline::prependShape: arc not connected to polyline");
//    }

//    prependVertex(directed->getStartPoint());
//    setBulgeAt(0, bulge);
}

void RPolyline::appendShape(const RShape& shape, bool prepend) {
//    const RDirected* directed = dynamic_cast<const RDirected*>(&shape);
//    if (directed==NULL) {
//        qWarning() << "RPolyline::appendShape: shape is not a line, arc or polyline: " << shape;
//        return;
//    }

    const RPolyline* pl = dynamic_cast<const RPolyline*>(&shape);
    if (pl!=NULL) {
        if (prepend) {
            for (int i=pl->countSegments()-1; i>=0; --i) {
                QSharedPointer<RShape> s = pl->getSegmentAt(i);
                if (s.isNull()) {
                    continue;
                }
                prependShape(*s);
            }
        }
        else {
            for (int i=0; i<pl->countSegments(); ++i) {
                QSharedPointer<RShape> s = pl->getSegmentAt(i);
                if (s.isNull()) {
                    continue;
                }
                appendShape(*s);
            }
        }
        return;
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
        return;
    }

    RVector connectionPoint;
    RVector nextPoint;
    double gap;
    if (prepend) {
        connectionPoint = directed->getEndPoint();
        nextPoint = directed->getStartPoint();
        if (vertices.size()==0) {
            appendVertex(connectionPoint);
        }
        gap = vertices.first().getDistanceTo(connectionPoint);
    }
    else {
        connectionPoint = directed->getStartPoint();
        nextPoint = directed->getEndPoint();
        if (vertices.size()==0) {
            appendVertex(connectionPoint);
        }
        gap = vertices.last().getDistanceTo(connectionPoint);
    }

    if (!RMath::fuzzyCompare(gap, 0.0, 1.0e-4)) {
        qWarning() << "RPolyline::appendShape: arc or line not connected to polyline, gap: " << gap;
    }

    if (prepend) {
        prependVertex(nextPoint);
        setBulgeAt(0, bulge);
    }
    else {
        appendVertex(nextPoint);
        setBulgeAt(bulges.size()-2, bulge);
    }
}

void RPolyline::appendVertex(const RVector& vertex, double bulge) {
    vertices.append(vertex);
    bulges.append(bulge);
}

void RPolyline::prependVertex(const RVector& vertex, double bulge) {
    vertices.prepend(vertex);
    bulges.prepend(bulge);
}

void RPolyline::insertVertex(int index, const RVector& vertex) {
    vertices.insert(index, vertex);
    if (index>0) {
        bulges[index-1] = 0.0;
    }
    bulges.insert(index, 0.0);
}

void RPolyline::removeLastVertex() {
    vertices.removeLast();
    bulges.removeLast();
}

void RPolyline::removeVertex(int index) {
    vertices.removeAt(index);
    bulges.removeAt(index);
}

void RPolyline::setVertices(const QList<RVector>& vertices) {
    this->vertices = vertices;

    bulges.clear();
    for (int i=0; i<vertices.size(); ++i) {
        bulges.append(0.0);
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

void RPolyline::setClosed(bool on) {
    closed = on;
}

bool RPolyline::isClosed() const {
    return closed;
}

bool RPolyline::isGeometricallyClosed(double tolerance) const {
    return isClosed() || getStartPoint().getDistanceTo(getEndPoint()) < tolerance;
}

RS::Orientation RPolyline::getOrientation() const {
    if (!isGeometricallyClosed()) {
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

/**
 * \return Number of segments. The number of segments equals the
 *      number of vertices for a closed polyline and one less for
 *      an open polyline.
 */
int RPolyline::countSegments() const {
    if (closed) {
        return countVertices();
    }
    else {
        return countVertices() - 1;
    }
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

        if (fabs(alpha) > 2*M_PI-RS::AngleTolerance) {
            return QSharedPointer<RShape>();
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

/*
// TODO
bool RPolyline::contains(const RShape& shape) const {
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
    else {
        // check if the shape is completely inside the polygon.
        // this is the case if one point on the entity is inside the polygon
        // and the entity does not intersect with the polygon.
        RVector pointOnEntity = shape.getPointOnShape();
        if (contains(pointOnEntity)) {
            return true;
        }
    }
}
*/

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

RBox RPolyline::getBoundingBox() const {
    RBox ret;

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
                    ret.append(sub[i]->getPointsWithDistanceToEnd(remainingDist, RS::FromStart));
                    break;
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
                    ret.append(sub[i]->getPointsWithDistanceToEnd(remainingDist, RS::FromEnd));
                    break;
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
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        RVector v = (*it)->getVectorTo(point, limited, strictRange);
        if (v.isValid() && (!ret.isValid() || v.getMagnitude()<ret.getMagnitude())) {
            ret = v;
        }
    }

    return ret;
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

    // skip last segment if polyline is closed and add flag instead:
    int iLast = segments.count()-1;
    if (isClosed()) {
        iLast--;
    }

    for (int i=iLast; i>=0; i--) {
        QSharedPointer<RShape> seg = segments.at(i);
        QSharedPointer<RDirected> directed = seg.dynamicCast<RDirected>();
        directed->reverse();
        nPolyline.appendShape(*seg);
    }
    nPolyline.setClosed(closed);
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

RS::Ending RPolyline::getTrimEnd(const RVector& coord, const RVector& trimPoint) {
    // TODO: implement
    return RS::EndingNone;
}

void RPolyline::trimStartPoint(const RVector& p) {
    Q_ASSERT(false);
}

void RPolyline::trimEndPoint(const RVector& p) {
    Q_ASSERT(false);
}

void RPolyline::print(QDebug dbg) const {
    dbg.nospace() << "RPolyline(";
    RShape::print(dbg);
    dbg.nospace() << ", ";
    dbg.nospace() << "vertices: " << countVertices() << ", ";
    dbg.nospace() << "bulges: " << bulges.length() << ", ";
    dbg.nospace() << "closed: " << closed << ", ";
    QList<QSharedPointer<RShape> > sub = getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        dbg.nospace() << "\n" << *it->data() << ", ";
    }
    dbg.nospace() << ")";
}

bool RPolyline::simplify(double angleTolerance) {
    bool ret = false;
    RPolyline newPolyline;

    RS::EntityType type = RS::EntityUnknown;
    double angle = RMAXDOUBLE;

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
        }

        QSharedPointer<RArc> arc = seg.dynamicCast<RArc>();
        if (!arc.isNull()) {
            // TODO: simplify anything if possible:
            newPolyline.appendVertex(arc->getStartPoint(), arc->getBulge());
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

    return ret;
}
