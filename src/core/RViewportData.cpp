/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

RViewportData::RViewportData() {
}

RViewportData::RViewportData(RDocument* document, const RViewportData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RViewportData::RViewportData(const RVector& center, double width, double height, double scale) :
    center(center), width(width), height(height), scale(scale) {
}

QList<RVector> RViewportData::getReferencePoints(
        RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RVector> ret;
    ret.append(center);
    return ret;
}

bool RViewportData::moveReferencePoint(const RVector& referencePoint,
        const RVector& targetPoint) {
    bool ret = false;
    if (referencePoint.equalsFuzzy(center)) {
        center = targetPoint;
        ret = true;
    }
    return ret;
}

QList<QSharedPointer<RShape> > RViewportData::getShapes(const RBox& queryBox) const {
    Q_UNUSED(queryBox)

    return QList<QSharedPointer<RShape> >() << QSharedPointer<RShape>(new RPoint(getCenter()));
}
