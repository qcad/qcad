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
#include "RDocument.h"
#include "RDocumentInterface.h"
#include "RGraphicsView.h"
#include "RMouseEvent.h"
#include "RSettings.h"
#include "RSnapEntityBase.h"



RVector RSnapEntityBase::snap(
        const RVector& position,
        RGraphicsView& view,
        double range) {

    entityIds.clear();
    RDocument* document = view.getDocument();

    lastSnap = RVector::invalid;

    if (document==NULL) {
        lastSnap = position;
        lastSnap.valid = false;
        return lastSnap;
    }

    if (RMath::isNaN(range)) {
        int rangePixels = RSettings::getSnapRange();
        range = view.mapDistanceFromView(rangePixels);
    }

    RBox queryBox(position, range);

    QSet<REntity::Id> candidates =
            document->queryIntersectedEntitiesXY(
                queryBox, true, true, RBlock::INVALID_ID);

    return snap(position, view, candidates, queryBox);
}

RVector RSnapEntityBase::snap(
        const RVector& position,
        RGraphicsView& view,
        const QSet<REntity::Id>& candidates,
        const RBox& queryBox) {

    RDocument* document = view.getDocument();
    if (document==NULL) {
        return lastSnap;
    }

    REntity::Id entityId;
    double minDist = RMAXDOUBLE;
    double dist;

    QSet<REntity::Id>::const_iterator it;
    for (it=candidates.begin(); it!=candidates.end(); it++) {
        // 20111112: query direct:
        //QSharedPointer<REntity> e = document->queryEntityDirect(*it);
        QSharedPointer<REntity> e = document->queryEntity(*it);
        if (e.isNull()) {
            continue;
        }

        // check if layer is snappable:
        RLayer::Id layerId = e->getLayerId();
        QSharedPointer<RLayer> layer = document->queryLayerDirect(layerId);
        if (!layer->isSnappable() || !document->isParentLayerSnappable(*layer)) {
            continue;
        }

        RVector candidate =
            position.getClosest2D(
                snapEntity(e, position, queryBox, view)
            );

        dist = candidate.getDistanceTo2D(position);
        if (dist<minDist) {
            lastSnap = candidate;
            minDist = dist;
            entityId = e->getId();
        }
    }

    if (!lastSnap.isValid()) {
        lastSnap = position;
        lastSnap.valid = false;
        return lastSnap;
    }
    else {
        entityIds.insert(entityId);
        return lastSnap;
    }
}
