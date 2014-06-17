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
#include "RXLineData.h"
#include "RLineEntity.h"

RXLineData::RXLineData() {
}

RXLineData::RXLineData(RDocument* document, const RXLineData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RXLineData::RXLineData(const RXLine &line) :
    RXLine(line) {
}

RXLineData::RXLineData(const RVector& basePoint, const RVector& dir) :
    RXLine(basePoint, dir) {
}

QList<RVector> RXLineData::getReferencePoints(
        RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RVector> ret;
    ret.append(basePoint);
    ret.append(getSecondPoint());
    return ret;
}

// prevent recursion
//RBox RXLineData::getBoundingBox() const {
//    return RLine::getBoundingBox();
//}

//bool RXLineData::intersectsWith(const RShape& shape) const {
//    RLine xLine = getXLineShape();
//    return xLine.intersectsWith(shape);
//}

//QList<RVector> RXLineData::getIntersectionPoints(
//        const REntityData& other, bool limited, bool same, const RBox& queryBox) const {

//    QList<RVector> ret;
//    RLine shape1 = getXLineShape();
//    QList<QSharedPointer<RShape> > shapes2 = other.getShapes(queryBox);

//    for (int k=0; k<shapes2.size(); k++) {
//        ret.append(shape1.getIntersectionPoints(*shapes2.at(k), limited, same));
//    }

//    return ret;
//}

//QList<RVector> RXLineData::getIntersectionPoints(const RShape& shape, bool limited, const RBox& queryBox) const {
//    qDebug() << "RXLineData::getIntersectionPoints";
//    Q_UNUSED(queryBox)

//    RLine xLine = getXLineShape();
//    return xLine.getIntersectionPoints(shape, limited);
//}

//RLine RXLineData::getXLineShape() const {
//    const RDocument* doc = getDocument();
//    if (doc==NULL) {
//        return RLine();
//    }

//    RLine xLine = *this;
//    RBox bbox = doc->getBoundingBox();

    //RBox bbox(RVector(-1e6,-1e6), RVector(1e6,1e6));
    //xLine.clipToXY(bbox, true);
//    return xLine;
//}

/*
QList<QSharedPointer<RShape> > RXLineData::getShapes(const RBox& queryBox) const {
    Q_UNUSED(queryBox)

    return QList<QSharedPointer<RShape> >() << QSharedPointer<RShape>(new RLine(getXLineShape()));
}
*/

bool RXLineData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {
    bool ret = false;
    if (referencePoint.equalsFuzzy(basePoint)) {
        basePoint = targetPoint;
        ret = true;
    }
    if (referencePoint.equalsFuzzy(getSecondPoint())) {
        setSecondPoint(targetPoint);
        ret = true;
    }
    return ret;
}
