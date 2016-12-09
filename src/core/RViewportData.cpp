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
#include "RViewportData.h"

RViewportData::RViewportData()
    : viewportId(RObject::INVALID_ID),
      status(0),
      width(0.0),
      height(0.0),
      scale(1.0),
      rotation(0.0),
      overall(false) {
}

RViewportData::RViewportData(RDocument* document, const RViewportData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

//RViewportData::RViewportData(const RVector& center, double width, double height, double scale,
//                             const RVector& viewCenterPoint,
//                             const RVector& viewTargetPoint) :

//    center(center),
//    width(width), height(height),
//    scale(scale),
//    viewCenter(viewCenterPoint),
//    viewTarget(viewTargetPoint) {

//}

RBox RViewportData::getBoundingBox(bool ignoreEmpty) const {
    Q_UNUSED(ignoreEmpty)

    return RBox(position, width, height);
}

QList<RRefPoint> RViewportData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    ret.append(RRefPoint(position, RRefPoint::Center));

    ret.append(position + RVector( width/2,  height/2));
    ret.append(position + RVector(-width/2,  height/2));
    ret.append(position + RVector(-width/2, -height/2));
    ret.append(position + RVector( width/2, -height/2));

    return ret;
}

bool RViewportData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {
    bool ret = false;

    RVector offset = targetPoint - referencePoint;

    if (referencePoint.equalsFuzzy(position)) {
        position = targetPoint;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(position + RVector(width/2, height/2))) {
        position.x += offset.x/2;
        position.y += offset.y/2;
        width += offset.x;
        height += offset.y;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(position + RVector(-width/2, height/2))) {
        position.x += offset.x/2;
        position.y += offset.y/2;
        width -= offset.x;
        height += offset.y;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(position + RVector(-width/2, -height/2))) {
        position.x += offset.x/2;
        position.y += offset.y/2;
        width -= offset.x;
        height -= offset.y;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(position + RVector(width/2, -height/2))) {
        position.x += offset.x/2;
        position.y += offset.y/2;
        width += offset.x;
        height -= offset.y;
        ret = true;
    }
    return ret;
}

QList<QSharedPointer<RShape> > RViewportData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QList<QSharedPointer<RShape> > ret;

    QList<RLine> lines = RBox(position, width, height).getLines2d();
    for (int i=0; i<lines.length(); i++) {
        ret.append(QSharedPointer<RShape>(lines[i].clone()));
    }

    return ret;
}
