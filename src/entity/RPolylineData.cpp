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
    RPolyline(line) {
}

QList<RBox> RPolylineData::getBoundingBoxes() const {
    QList<RBox> ret;
    QList<QSharedPointer<RShape> > shapes = getExploded();
    for (int i=0; i<shapes.size(); i++) {
        ret.append(shapes.at(i)->getBoundingBox());
    }
    return ret;
}

QList<RVector> RPolylineData::getReferencePoints(
        RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    return getVertices();
}

bool RPolylineData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {
    bool ret = false;

    QList<RVector>::iterator it;
    for (it=vertices.begin(); it!=vertices.end(); ++it) {
        if (referencePoint.getDistanceTo(*it) < RS::PointTolerance) {
            (*it) = targetPoint;
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
        const RBox& queryBox
        /*const QSet<int>& pos,
        const QSet<int>& posOther*/) const {

//    if (!same) {
//        return REntityData::getIntersectionPoints(other, limited, same, queryBox, pos, posOther);
//    }


    QList<RVector> ret;

    //RDebug::startTimer(8);
    QList<QSharedPointer<RShape> > shapes1All = getExploded();
    QList<QSharedPointer<RShape> > shapes2All;
    const RPolylineData* otherPl = dynamic_cast<const RPolylineData*>(&other);
    if (otherPl!=NULL) {
        shapes2All = otherPl->getExploded();
    }
    else {
        shapes2All = other.getShapes(queryBox);
    }
    //RDebug::stopTimer(8, "RPolylineData::getIntersectionPoints: exploding");

    QList<QSharedPointer<RShape> > shapes1;
    QList<QSharedPointer<RShape> > shapes2;

    // filter out shapes that are not in query box:
    //RDebug::startTimer(8);
    if (queryBox.isValid()) {
        for (int i=0; i<shapes1All.size(); i++) {
            if (queryBox.intersects(shapes1All.at(i)->getBoundingBox())) {
                shapes1.append(shapes1All.at(i));
            }
        }
        for (int i=0; i<shapes2All.size(); i++) {
            if (queryBox.intersects(shapes2All.at(i)->getBoundingBox())) {
                shapes2.append(shapes2All.at(i));
            }
        }
    }
    else {
        shapes1 = shapes1All;
        shapes2 = shapes2All;
    }
    //RDebug::stopTimer(8, "RPolylineData::getIntersectionPoints: filtering");

    //RDebug::startTimer(8);
    for (int i=0; i<shapes1.size(); i++) {
        for (int k=0; k<shapes2.size(); k++) {
            // very same polyline segments can't intersect:
            if (same && i==k) {
                continue;
            }
            // sequential line segments touch but don't intersect for polylines:
            if (same && abs(i-k)==1) {
                QSharedPointer<RLine> l1 = shapes1.at(i).dynamicCast<RLine>();
                QSharedPointer<RLine> l2 = shapes2.at(k).dynamicCast<RLine>();
                if (!l1.isNull() && !l2.isNull()) {
                    continue;
                }
            }
            ret.append(
                shapes1.at(i)->getIntersectionPoints(*shapes2.at(k), limited, same)
            );
        }
    }
    //RDebug::stopTimer(8, "RPolylineData::getIntersectionPoints: intersecting");

    return ret;
}
