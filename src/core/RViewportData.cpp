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
#include "RViewportData.h"
#include "RMouseEvent.h"

RViewportData::RViewportData()
    : viewportId(RObject::INVALID_ID),
      status(0),
      width(0.0),
      height(0.0),
      scaleFactor(1.0),
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
//    scaleFactor(scale),
//    viewCenter(viewCenterPoint),
//    viewTarget(viewTargetPoint) {

//}

RBox RViewportData::getBoundingBox(bool ignoreEmpty) const {
    Q_UNUSED(ignoreEmpty)

    return RBox(position, width, height);
}

void RViewportData::to2D() {
    RPoint::to2D();

    viewCenter = viewCenter.get2D();
    viewTarget = viewTarget.get2D();
}

/**
 * \return Offset or position of 0/0 of view (model space block) for this viewport.
 */
RVector RViewportData::getViewOffset() const {
    RVector offset(0,0);
    offset -= viewCenter.get2D() * scaleFactor;
    offset -= viewTarget.get2D() * scaleFactor;
    return position + offset;
}

QList<RRefPoint> RViewportData::getInternalReferencePoints(RS::ProjectionRenderingHint hint) const {
    QList<RRefPoint> ret;

    QList<QSharedPointer<RShape> > shapes = getShapes();
    for (int i=0; i<shapes.size(); i++) {
        QSharedPointer<RShape> shape = shapes[i];

        QList<RVector> ps = shape->getArcReferencePoints();
        for (int k=0; k<ps.length(); k++) {
            ret.append(RRefPoint(ps[k], RRefPoint::Tertiary));
        }
    }

    return ret;
}

QList<RRefPoint> RViewportData::getReferencePoints(RS::ProjectionRenderingHint hint) const {
    Q_UNUSED(hint)

    QList<RRefPoint> ret;
    ret.append(RRefPoint(position, RRefPoint::Center));

    ret.append(RRefPoint(position + RVector(0,height/4), RRefPoint::Center));

    ret.append(position + RVector( width/2,  height/2));
    ret.append(position + RVector(-width/2,  height/2));
    ret.append(position + RVector(-width/2, -height/2));
    ret.append(position + RVector( width/2, -height/2));

    return ret;
}

bool RViewportData::moveReferencePoint(const RVector& referencePoint, const RVector& targetPoint, Qt::KeyboardModifiers modifiers) {
    Q_UNUSED(modifiers)

    bool ret = false;

    RVector offset = targetPoint - referencePoint;

    if (referencePoint.equalsFuzzy(position)) {
        position = targetPoint;
        ret = true;
    }
    else if (referencePoint.equalsFuzzy(position + RVector(0,height/4))) {
        viewCenter -= offset/scaleFactor;
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

double RViewportData::getDistanceTo(const RVector& point, bool limited, double range, bool draft, double strictRange) const {
    double ret = RMAXDOUBLE;

    RBox viewportBox(position, width, height);
    if (viewportBox.contains(point)) {
        ret = strictRange;
    }

    return qMin(ret, REntityData::getDistanceTo(point, limited, range, draft, strictRange));
}

QList<QSharedPointer<RShape> > RViewportData::getShapes(const RBox& queryBox, bool ignoreComplex, bool segment) const {
    Q_UNUSED(segment)

    QList<QSharedPointer<RShape> > ret;

    // border:
    QList<RLine> lines = RBox(position, width, height).getLines2d();
    for (int i=0; i<lines.length(); i++) {
        ret.append(QSharedPointer<RShape>(lines[i].clone()));
    }

    // shapes inside viewport:

    // query entities in query box that are part of the block definition:
    QSet<REntity::Id> ids;
    RBox queryBoxNeutral;
    QList<RVector> corners;

    if (queryBox.isValid()) {
        corners.append(RVector(queryBox.c1.x, queryBox.c1.y));
        corners.append(RVector(queryBox.c1.x, queryBox.c2.y));
        corners.append(RVector(queryBox.c2.x, queryBox.c1.y));
        corners.append(RVector(queryBox.c2.x, queryBox.c2.y));
    }
    else {
        corners.append(position + RVector( width/2,  height/2));
        corners.append(position + RVector(-width/2,  height/2));
        corners.append(position + RVector(-width/2, -height/2));
        corners.append(position + RVector( width/2, -height/2));
    }
    RVector::rotateList(corners, -rotation, position);
    RVector::moveList(corners, -getViewOffset());
    RVector::scaleList(corners, 1/scaleFactor);
    queryBoxNeutral = RBox(RVector::getMinimum(corners), RVector::getMaximum(corners));

    ids = document->queryIntersectedEntitiesXY(queryBoxNeutral, true, true, document->getModelSpaceBlockId());

    QSet<REntity::Id>::iterator it;
    for (it = ids.begin(); it != ids.end(); it++) {
        if (RMouseEvent::hasMouseMoved()) {
            //recursionDepth--;
            return QList<QSharedPointer<RShape> >();
        }

        QSharedPointer<REntity> entity = document->queryEntity(*it);
        if (entity.isNull()) {
            continue;
        }

        entity->scale(scaleFactor);
        entity->move(getViewOffset());

        entity->rotate(rotation, position);

        RS::EntityType t = entity->getType();

        // ignore complex entities for operations like snap (hatches, texts):
        if (ignoreComplex && REntity::isComplex(t)) {
            continue;
        }

        ret.append(entity->getShapes(queryBox, ignoreComplex));
    }

    return ret;
}

QList<RLine> RViewportData::getEdges() const {
    RBox viewportBox(position, width, height);
    return viewportBox.getLines2d();
}

bool RViewportData::scale(const RVector& scaleFactors, const RVector& center) {
    width*=scaleFactors.x;
    height*=scaleFactors.y;
    scaleFactor*=scaleFactors.x;

    position.scale(scaleFactors, center);

    return true;

    // TODO: crashes:
    //return REntityData::scale(scaleFactors, center);
}
