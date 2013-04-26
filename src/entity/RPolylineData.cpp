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
        if (referencePoint.equals(*it)) {
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
        const RBox& queryBox) const {

    QList<RVector> ret;

    QList<QSharedPointer<RShape> > shapes1All = getExploded();
    QList<QSharedPointer<RShape> > shapes2All;
    if (same) {
        shapes2All = shapes1All;
    }
    else {
        const RPolylineData* otherPl = dynamic_cast<const RPolylineData*>(&other);
        if (otherPl!=NULL) {
            shapes2All = otherPl->getExploded();
        }
        else {
            shapes2All = other.getShapes(queryBox);
        }
    }

    QList<QSharedPointer<RShape> > shapes1;
    QList<QSharedPointer<RShape> > shapes2;

    // filter out shapes that are not in query box:
    if (queryBox.isValid()) {
        for (int i1=0; i1<shapes1All.size(); i1++) {
            QSharedPointer<RShape> shape1 = shapes1All.at(i1);
            if (queryBox.intersects(shape1->getBoundingBox())) {
                shapes1.append(shape1);
            }
        }
        if (same) {
           shapes2 = shapes1;
        }
        else {
            for (int i2=0; i2<shapes2All.size(); i2++) {
                QSharedPointer<RShape> shape2 = shapes2All.at(i2);
                if (queryBox.intersects(shape2->getBoundingBox())) {
                    shapes2.append(shape2);
                }
            }
        }
    }
    else {
        shapes1 = shapes1All;
        shapes2 = shapes2All;
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
                // polygon internal intersections:
                QSharedPointer<RDirected> dir1 = shape1.dynamicCast<RDirected>();
                QSharedPointer<RDirected> dir2 = shape2.dynamicCast<RDirected>();
                if (!dir1.isNull() && !dir2.isNull()) {
                    // ignore polyline nodes:
                    for (int c=0; c<candidates.size(); c++) {
                        if (candidates[c].equals(dir1->getStartPoint())) {
                            continue;
                        }
                        if (candidates[c].equals(dir1->getEndPoint())) {
                            continue;
                        }
                        if (candidates[c].equals(dir2->getStartPoint())) {
                            continue;
                        }
                        if (candidates[c].equals(dir2->getEndPoint())) {
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
