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
#include "RDimStyle.h"
#include "RDocument.h"
#include "RRefPoint.h"
#include "RTriangle.h"

RLeaderData::RLeaderData()
    : arrowHead(true),
      dimasz(-1.0),
      dimscale(-1.0),
      dimLeaderBlockId(RObject::INVALID_ID),
      splineShaped(false) {
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
      arrowHead(arrowHead),
      dimasz(-1.0),
      dimscale(-1.0),
      dimLeaderBlockId(RObject::INVALID_ID),
      splineShaped(false) {

}

double RLeaderData::getDimasz(bool scale) const {
    double v = 2.5;

    // get value from override:
    if (dimasz>0.0) {
        v = dimasz;
    }

    else if (document!=NULL) {
        QSharedPointer<RDimStyle> dimStyle = document->queryDimStyleDirect();
        if (!dimStyle.isNull()) {
            // get value from dimension style:
            v = dimStyle->getDouble(RS::DIMASZ);
        }
        else {
            // TODO: get value from document (should never happen):
            Q_ASSERT(false);
        }
    }

    if (scale) {
        v *= getDimscale();
    }

    return v;
}

void RLeaderData::setDimasz(double v) {
    dimasz = v;
    update();
}

double RLeaderData::getDimscale() const {
    // get value from override:
    if (dimscale>0.0) {
        return dimscale;
    }

    double v = 1.0;
    if (document!=NULL) {
        QSharedPointer<RDimStyle> dimStyle = document->queryDimStyleDirect();
        if (!dimStyle.isNull()) {
            // get value from dimension style:
            v = dimStyle->getDouble(RS::DIMSCALE);
        }
        else {
            // TODO: get value from document (should never happen):
            Q_ASSERT(false);
        }
    }

    return v;
}

void RLeaderData::setDimscale(double f) {
    dimscale = f;
    update();
}


void RLeaderData::scaleVisualProperties(double scaleFactor) {
    setDimscale(getDimscale() * scaleFactor);
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
//    if (countSegments()==0) {
//        return false;
//    }

//    QSharedPointer<RShape> firstSegment = getSegmentAt(0);
//    if (firstSegment.isNull()) {
//        return false;
//    }

//    if (firstSegment->getLength() < getDimasz() * 2) {
//        return false;
//    }

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

QList<QSharedPointer<RShape> > RLeaderData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment, QList<RObject::Id>* entityIds) const {
    Q_UNUSED(queryBox)
    Q_UNUSED(ignoreComplex)
    Q_UNUSED(segment)

    QList<QSharedPointer<RShape> > ret;
    ret << QSharedPointer<RShape>(new RPolyline(*this));
    if (arrowHead) {
        ret << QSharedPointer<RShape>(new RTriangle(getArrowShape()));
    }
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

RObject::Id RLeaderData::getDimLeaderBlockId() const {
    return dimLeaderBlockId;
}

void RLeaderData::setDimLeaderBlockId(RObject::Id id) {
    dimLeaderBlockId = id;
}

void RLeaderData::update() const {
    REntityData::update();

    updateArrowHead();
}
