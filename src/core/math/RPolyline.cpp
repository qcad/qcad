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
#include <cmath>

#include "RArc.h"
#include "RBox.h"
#include "RCircle.h"
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

    for (int i=0; i<vertices.size(); i++) {
        RVector v = vertices.at(i);
        double b = bulges.at(i);
        if (i==0 || !v.equalsFuzzy(vertices.at(i-1))) {
            newVertices.append(v);
            newBulges.append(b);
        }
    }

    vertices = newVertices;
    bulges = newBulges;
}

void RPolyline::appendShape(const RShape& shape) {
    const RDirected* directed = dynamic_cast<const RDirected*>(&shape);
    if (directed==NULL) {
        qWarning("RPolyline::appendShape: shape is not a line, arc or polyline");
        return;
    }

    const RPolyline* pl = dynamic_cast<const RPolyline*>(&shape);
    if (pl!=NULL) {
        for (int i=0; i<pl->countSegments(); ++i) {
            QSharedPointer<RShape> s = pl->getSegmentAt(i);
            if (s.isNull()) {
                continue;
            }
            appendShape(*s.data());
        }
    }

    double bulge = 0.0;
    const RArc* arc = dynamic_cast<const RArc*>(&shape);
    if (arc!=NULL) {
        bulge = arc->getBulge();
    }

    if (vertices.size()==0) {
        appendVertex(directed->getStartPoint());
    }

    appendVertex(directed->getEndPoint());
    setBulgeAt(bulges.size()-2, bulge);
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

bool RPolyline::isLogicallyClosed() const {
    return isClosed() || getStartPoint().getDistanceTo(getEndPoint()) < RS::PointTolerance;
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
        qWarning() << "RPolyline::getSubShapeAt(" << i << "): i out of range";
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
bool RPolyline::contains(const RVector& point) const {
    if (!closed) {
        return false;
    }

    QPainterPath pp = toPainterPath();
    return pp.contains(QPointF(point.x, point.y));
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
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        ret.append((*it)->getPointsWithDistanceToEnd(distance, from));
    }

    return ret;
}

RVector RPolyline::getVectorTo(const RVector& point, bool limited) const {
    RVector ret = RVector::invalid;

    QList<QSharedPointer<RShape> > sub = getExploded();
    QList<QSharedPointer<RShape> >::iterator it;
    for (it=sub.begin(); it!=sub.end(); ++it) {
        RVector v = (*it)->getVectorTo(point, limited);
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

bool RPolyline::flipHorizontal() {
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].flipHorizontal();
    }
    return true;
}

bool RPolyline::flipVertical() {
    for (int i=0; i<vertices.size(); i++) {
        vertices[i].flipVertical();
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
    //ret.appendVertex(getStartPoint());

    RS::EntityType type = RS::EntityUnknown;
    double angle = RMAXDOUBLE;
    //double radius = 0;
    //RVector center;
    //RVector vertex;

    for (int i=0; i<countSegments(); i++) {
        QSharedPointer<RShape> seg = getSegmentAt(i);

        QSharedPointer<RLine> line = seg.dynamicCast<RLine>();
        if (!line.isNull()) {
            double angleDiff = qAbs(RMath::getAngleDifference180(line->getAngle(), angle));
//            qDebug() << "angle diff: " << angleDiff;
//            qDebug() << "tol: " << angleTolerance;
            if (type==RS::EntityLine && angleDiff<angleTolerance) {

                //vertex = line->getEndPoint();
                ret = true;
            }
            else {
                //qDebug() << "start: " << line->getStartPoint();
                newPolyline.appendVertex(line->getStartPoint());
                angle = line->getAngle();
                type = RS::EntityLine;
            }
        }

        QSharedPointer<RArc> arc = seg.dynamicCast<RArc>();
        if (!arc.isNull()) {
            // TODO
            newPolyline.appendVertex(arc->getStartPoint(), arc->getBulge());
        }
    }

    if (isClosed()) {
        newPolyline.setClosed(true);
    }
    else {
        newPolyline.appendVertex(getEndPoint());
    }

//    qDebug() << "old polyline: " << *this;
//    qDebug() << "new polyline: " << newPolyline;

    //*this = newPolyline;

    //clear();
    vertices = newPolyline.vertices;
    bulges = newPolyline.bulges;
    closed = newPolyline.closed;

    return ret;
}
