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
#include "RGraphicsView.h"
#include "RSnapTangential.h"
#include "RArc.h"
#include "REllipse.h"
#include "RCircle.h"

QList<RVector> RSnapTangential::snapEntity(
        QSharedPointer<REntity> entity,
        const RVector& point,
        const RBox& queryBox,
        RGraphicsView& view) {

    QList<RVector> ret;

    RDocumentInterface* di = view.getDocumentInterface();
    if (di==NULL) {
        return ret;
    }

    QSharedPointer<RShape> shape = entity->getClosestShape(point, queryBox.getWidth()/2, true);
    if (shape.isNull()) {
        return ret;
    }

    QSharedPointer<RCircle> circle = shape.dynamicCast<RCircle>();
    if (!circle.isNull()) {
        QList<RLine> lines = circle->getTangents(di->getLastPosition());
        for (int i=0; i<lines.length(); i++) {
            ret.append(lines[i].getEndPoint());
        }
    }

    QSharedPointer<RArc> arc = shape.dynamicCast<RArc>();
    if (!arc.isNull()) {
        QList<RLine> lines = arc->getTangents(di->getLastPosition());
        for (int i=0; i<lines.length(); i++) {
            ret.append(lines[i].getEndPoint());
        }
    }

    QSharedPointer<REllipse> ellipse = shape.dynamicCast<REllipse>();
    if (!ellipse.isNull()) {
        QList<RLine> lines = ellipse->getTangents(di->getLastPosition());
        for (int i=0; i<lines.length(); i++) {
            ret.append(lines[i].getEndPoint());
        }
    }

    return ret;
}
