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
#include "RLeaderData.h"
#include "RUnit.h"

RLeaderData::RLeaderData()
    : arrowHead(true),
      dimaszOverride(0.0),
      dimScaleOverride(0.0),
      dimLeaderBlockId(REntity::INVALID_ID) {
}

RLeaderData::RLeaderData(RDocument* document, const RLeaderData& data)
    : REntityData(document) {
    *this = data;
    this->document = document;
    if (document!=NULL) {
        linetypeId = document->getLinetypeByLayerId();
    }
}

RLeaderData::RLeaderData(const RPolyline& polyline, bool arrowHead)
    : RPolyline(polyline),
      arrowHead(arrowHead), dimaszOverride(-1), dimScaleOverride(1.0), dimLeaderBlockId(REntity::INVALID_ID) {

}

void RLeaderData::setDimaszOverride(double v) {
    dimaszOverride = v;
}

double RLeaderData::getDimasz() const {
    double dimasz = 2.5;

    if (document!=NULL) {
        dimasz = document->getKnownVariable(RS::DIMASZ, dimasz).toDouble();
    }
    else {
        qWarning() << "RLeaderData::getDimasz: no document set";
    }

    return dimasz * getDimScale();
}

void RLeaderData::setDimScaleOverride(double v) {
    dimScaleOverride = v;
    updateArrowHead();
}

double RLeaderData::getDimScale(bool fromDocument) const {
    double ret = dimScaleOverride;

    if (document!=NULL && fromDocument && RMath::fuzzyCompare(ret, 0.0)) {
        ret = document->getKnownVariable(RS::DIMSCALE, 1.0).toDouble();
    }

    return ret;
}

void RLeaderData::scaleVisualProperties(double scaleFactor) {
    if (dimScaleOverride>RS::PointTolerance) {
        setDimScaleOverride(dimScaleOverride * scaleFactor);
    }
    else {
        double s = getDimScale();
        setDimScaleOverride(scaleFactor * s);
    }
}

void RLeaderData::setArrowHead(bool on) {
    arrowHead = on;
    updateArrowHead();
}

/**
 * \return true if this leader can have an arrow head (i.e. first
 * segment is >= DIMASZ * DIMSCALE * 2.
 */
bool RLeaderData::canHaveArrowHead() const {
    if (countSegments()==0) {
        return false;
    }

    QSharedPointer<RShape> firstSegment = getSegmentAt(0);
    if (firstSegment.isNull()) {
        return false;
    }

    if (firstSegment->getLength() < getDimasz() * 2) {
        return false;
    }

    return true;
}

QList<RRefPoint> RLeaderData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    return RRefPoint::toRefPointList(getVertices());
}

bool RLeaderData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    QList<RVector>::iterator it;
    for (it=vertices.begin(); it!=vertices.end(); ++it) {
        if (referencePoint.equalsFuzzy(*it)) {
            (*it) = targetPoint;
            ret = true;
        }
    }

    ret |= updateArrowHead();

    return ret;
}

bool RLeaderData::scale(const RVector& scaleFactors, const RVector& center) {
    bool ret = RPolyline::scale(scaleFactors, center);
    ret |= updateArrowHead();
    return ret;
}

bool RLeaderData::stretch(const RPolyline &area, const RVector &offset) {
    bool ret = RPolyline::stretch(area, offset);
    ret |= updateArrowHead();
    return ret;
}

RTriangle RLeaderData::getArrowShape() const {
    RVector p = getStartPoint();
    double direction = getDirection1() + M_PI;
    double dimasz = getDimasz();
    return RTriangle::createArrow(p, direction, dimasz);
}

bool RLeaderData::updateArrowHead() const {
    if (arrowHead && !canHaveArrowHead()) {
        arrowHead = false;
        return true;
    }

    return false;
}

REntity::Id RLeaderData::getDimLeaderBlockId() const {
    return dimLeaderBlockId;
}

void RLeaderData::setDimLeaderBlockId(REntity::Id id) {
    dimLeaderBlockId = id;
}

void RLeaderData::update() const {
    REntityData::update();

    updateArrowHead();
}
