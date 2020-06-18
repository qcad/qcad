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
#include "RArc.h"
#include "RPolylineData.h"
#include "RPolylineEntity.h"

RPolylineData::RPolylineData() {
}

RPolylineData::RPolylineData(RDocument* document, const RPolylineData& data)
    : REntityData(document) {

    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RPolylineData::RPolylineData(const RPolyline& line) :
    RPolyline(line), polylineGen(true) {
}

QList<RBox> RPolylineData::getBoundingBoxes(bool ignoreEmpty) const {
    Q_UNUSED(ignoreEmpty)

    QList<RBox> ret;

    if (hasWidths()) {
        QList<RPolyline> outline = getOutline();
        for (int i=0; i<outline.length(); i++) {
            Q_ASSERT(!outline[i].hasWidths());
            ret.append(outline[i].getBoundingBox());
        }
        return ret;
    }

    QList<QSharedPointer<RShape> > shapes = getExploded();
    for (int i=0; i<shapes.size(); i++) {
        ret.append(shapes.at(i)->getBoundingBox());
    }
    return ret;
}

QList<RRefPoint> RPolylineData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret = RRefPoint::toRefPointList(getVertices());
    if (!ret.isEmpty()) {
        // mark start and end points:
        ret.first().setStart(true);
        ret.last().setEnd(true);
    }
    for (int i=0; i<countSegments(); i++) {
        QSharedPointer<RShape> segment = getSegmentAt(i);
        //if (isArcSegmentAt(i)) {
            //QSharedPointer<RArc> arc = getSegmentAt(i).dynamicCast<RArc>();
            //if (!arc.isNull()) {
                ret.append(RRefPoint(segment->getMiddlePoint(), RRefPoint::Secondary));
            //}
        //}
    }
    // make sure start point is on top of end point for closed polyline:
    if (!ret.isEmpty()) {
        ret.append(ret.takeFirst());
    }
    return ret;
}

bool RPolylineData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    QList<RVector>::iterator it;
    for (it=vertices.begin(); it!=vertices.end(); ++it) {
        if (referencePoint.equalsFuzzy(*it)) {
            (*it) = targetPoint;
            ret = true;
        }
    }

    if (ret) {
        return ret;
    }

    for (int i=0; i<countSegments(); i++) {
        QSharedPointer<RShape> segment = getSegmentAt(i);
        if (segment.isNull()) {
            continue;
        }
        if (!referencePoint.equalsFuzzy(segment->getMiddlePoint())) {
            continue;
        }

        if (isArcSegmentAt(i)) {
            QSharedPointer<RArc> arc = segment.dynamicCast<RArc>();
            if (!arc.isNull()) {
                RArc a = RArc::createFrom3Points(arc->getStartPoint(), targetPoint, arc->getEndPoint());
                setBulgeAt(i, a.getBulge());
                ret = true;
            }
        }
        else {
            moveSegmentAt(i, targetPoint-referencePoint);
            ret = true;
        }
    }

    return ret;
}

/**
 * \return Points on entity which are intersection points with the
 *     given other entity. If \c same is true, the two datas originate
 *     from the same entity.
 */
QList<RVector> RPolylineData::getIntersectionPoints(
        const REntityData& other, bool limited, bool same,
        const RBox& queryBox, bool ignoreComplex) const {

    Q_UNUSED(ignoreComplex)

    QList<RVector> ret;

    QList<QSharedPointer<RShape> > shapes1 = getShapes(queryBox, true); //getExploded();
    QList<QSharedPointer<RShape> > shapes2;
    if (same) {
        shapes2 = shapes1;
    }
    else {
        bool ignoreComplexLocal = (other.getType()==RS::EntityHatch || other.getType()==RS::EntityPolyline);
        shapes2 = other.getShapes(queryBox, ignoreComplexLocal);
    }

    for (int i1=0; i1<shapes1.size(); i1++) {
        int i2Start = 0;
        if (same) {
            i2Start = i1+1;
        }
        for (int i2=i2Start; i2<shapes2.size(); i2++) {
            // very same polyline segments can't intersect:
            if (same && i1==i2) {
                continue;
            }

            QSharedPointer<RShape> shape1 = shapes1.at(i1);
            QSharedPointer<RShape> shape2 = shapes2.at(i2);
            QList<RVector> candidates = shape1->getIntersectionPoints(*shape2, limited, false);
            if (same) {
                // polyline internal intersections:
                if (shape1->isDirected() && shape2->isDirected()) {
                    // ignore polyline nodes:
                    for (int c=0; c<candidates.size(); c++) {
                        if (candidates[c].equalsFuzzy(shape1->getStartPoint())) {
                            continue;
                        }
                        if (candidates[c].equalsFuzzy(shape1->getEndPoint())) {
                            continue;
                        }
                        if (candidates[c].equalsFuzzy(shape2->getStartPoint())) {
                            continue;
                        }
                        if (candidates[c].equalsFuzzy(shape2->getEndPoint())) {
                            continue;
                        }
                        ret.append(candidates[c]);
                    }
                }
            }
            else {
                ret.append(candidates);
            }
        }
    }

    return ret;
}

QList<QSharedPointer<RShape> > RPolylineData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(segment)

    if (!ignoreComplex) {
        return QList<QSharedPointer<RShape> >() << QSharedPointer<RShape>(new RPolyline(*this));
    }
    else {
        QList<QSharedPointer<RShape> > candidates = getExploded();
        if (!queryBox.isValid()) {
            return candidates;
        }

        QList<QSharedPointer<RShape> > ret;
        // filter candidates based on query box:
        for (int i=0; i<candidates.length(); i++) {
            if (candidates[i]->getBoundingBox().intersects(queryBox)) {
                ret.append(candidates[i]);
            }
        }
        return ret;
    }
}

void RPolylineData::setElevation(double v) {
    for (int i=0; i<countVertices(); i++) {
        RVector ver = getVertexAt(i);
        ver.z = v;
        setVertexAt(i, ver);
    }
}

double RPolylineData::getElevation() const {
    if (isFlat()) {
        if (countVertices()>0) {
            return getVertexAt(0).z;
        }
    }
    return 0.0;
}
