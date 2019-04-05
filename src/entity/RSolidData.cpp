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
#include "RSolidData.h"
#include "RSolidEntity.h"

RSolidData::RSolidData()
    : REntityData() {
}

RSolidData::RSolidData(RDocument* document, const RSolidData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RSolidData::RSolidData(const RTriangle& triangle) :
    RPolyline() {

    appendVertex(triangle.corner[0]);
    appendVertex(triangle.corner[1]);
    appendVertex(triangle.corner[2]);
    setClosed(true);
}

RSolidData::RSolidData(const RVector& p1, const RVector& p2, const RVector& p3) :
    RPolyline() {

    appendVertex(p1);
    appendVertex(p2);
    appendVertex(p3);
    setClosed(true);
}

RSolidData::RSolidData(const RVector& p1, const RVector& p2, const RVector& p3, const RVector& p4) :
    RPolyline() {

    appendVertex(p1);
    appendVertex(p2);
    appendVertex(p3);
    appendVertex(p4);
    setClosed(true);
}

QList<RRefPoint> RSolidData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    return RRefPoint::toRefPointList(getVertices());
}

bool RSolidData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;
    for (int i=0; i<vertices.count(); i++) {
        if (referencePoint.equalsFuzzy(getVertexAt(i))) {
            setVertexAt(i, targetPoint);
            ret = true;
        }
    }
    return ret;
}
