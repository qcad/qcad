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
#include "RDocumentInterface.h"
#include "REntity.h"
#include "RGraphicsView.h"
#include "RSnapPerpendicular.h"
#include "RLine.h"
#include "RCircle.h"

QList<RVector> RSnapPerpendicular::snapEntity(
        QSharedPointer<REntity> entity,
        const RVector& point,
        const RBox& queryBox,
        RGraphicsView& view,
        QList<REntity::Id>* subEntityIds) {

    QList<RVector> ret;

    RDocumentInterface* di = view.getDocumentInterface();
    if (di==NULL) {
        return ret;
    }

    RObject::Id subEntityId = REntity::INVALID_ID;
    QSharedPointer<RShape> shape = entity->getClosestShape(point, queryBox.getWidth()/2, true, &subEntityId);
    if (shape.isNull()) {
        return ret;
    }

    if (shape->getShapeType()==RShape::Circle || shape->getShapeType()==RShape::Arc) {
        RVector closestPoint = shape->getClosestPointOnShape(di->getLastPosition());
        // find two perpendicular points:
        RLine line(di->getLastPosition(), closestPoint);
        QList<RVector> ips = line.getIntersectionPoints(*shape.data(), false);
        ret = ips;
    }
    else {
        ret.append(shape->getClosestPointOnShape(di->getLastPosition(), false));
    }

    if (subEntityIds!=NULL) {
        subEntityIds->append(subEntityId);
    }


    return ret;
}
