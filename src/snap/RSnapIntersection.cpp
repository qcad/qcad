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
#include "REntity.h"
#include "RGraphicsView.h"
#include "RLayer.h"
#include "RMouseEvent.h"
#include "RSnapIntersection.h"
#include "RSettings.h"

RVector RSnapIntersection::snap(
        const RVector& position,
        RGraphicsView& view,
        double range) {

    entityIds.clear();
    RDocument* document = view.getDocument();

    if (document==NULL) {
        lastSnap = position;
        return lastSnap;
    }

    if (RMath::isNaN(range)) {
        int rangePixels = RSettings::getSnapRange();
        range = view.mapDistanceFromView(rangePixels);
    }

    RBox queryBox(position, range);

    QMap<REntity::Id, QSet<int> > ids =
        document->queryIntersectedShapesXY(
            queryBox, true /*false?*/, true, RObject::INVALID_ID,
                QList<RS::EntityType>() << RS::EntityHatch);
    
    return snap(position, view, ids, queryBox);
}

RVector RSnapIntersection::snap(
        const RVector& position,
        RGraphicsView& view,
        const QMap<REntity::Id, QSet<int> >& candidates,
        const RBox& queryBox) {

    RDocument* document = view.getDocument();
    if (document==NULL) {
        return lastSnap;
    }

    // main entity Ids (e.g. line or block reference):
    REntity::Id mainEntityId1 = REntity::INVALID_ID;
    REntity::Id mainEntityId2 = REntity::INVALID_ID;

    // sub entity Ids (e.g. line in block):
    REntity::Id subEntityId1 = REntity::INVALID_ID;
    REntity::Id subEntityId2 = REntity::INVALID_ID;

    lastSnap = RVector::invalid;
    double minDist = RMAXDOUBLE;
    double dist;

    QMap<REntity::Id, QSet<int> >::const_iterator it1;
    for (it1=candidates.begin(); it1!=candidates.end(); it1++) {
        if (RMouseEvent::hasMouseMoved()) {
            lastSnap = RVector::invalid;
            return RVector::invalid;
        }
        QSharedPointer<REntity> e1 = document->queryEntityDirect(it1.key());
        if (e1.isNull()) {
            continue;
        }

        if (e1->getType()==RS::EntityText ||
            e1->getType()==RS::EntityAttribute ||
            e1->getType()==RS::EntityAttributeDefinition) {
            continue;
        }

        // check if layer is snappable:
        RLayer::Id layer1Id = e1->getLayerId();
        QSharedPointer<RLayer> layer1 = document->queryLayerDirect(layer1Id);
        if (!layer1->isSnappable() || !document->isParentLayerSnappable(*layer1)) {
            continue;
        }

        QMap<REntity::Id, QSet<int> >::const_iterator it2;
        for (it2=it1; it2!=candidates.end(); it2++) {
            if (RMouseEvent::hasMouseMoved()) {
                lastSnap = RVector::invalid;
                return RVector::invalid;
            }
            QSharedPointer<REntity> e2 = document->queryEntityDirect(it2.key());
            if (e2.isNull()) {
                continue;
            }
            if (e2->getType()==RS::EntityText ||
                e2->getType()==RS::EntityAttribute ||
                e2->getType()==RS::EntityAttributeDefinition) {
                continue;
            }
            // check if layer is snappable:
            RLayer::Id layer2Id = e2->getLayerId();
            QSharedPointer<RLayer> layer2 = document->queryLayerDirect(layer2Id);
            if (!layer2->isSnappable() || !document->isParentLayerSnappable(*layer2)) {
                continue;
            }

            // list of sub entity Ids of candidates:
            QList<QPair<REntity::Id, REntity::Id> > subEntityIdsCandidates;
            QList<RVector> ipsCandidates = e1->getIntersectionPoints(*e2, true, queryBox, true, &subEntityIdsCandidates);

            if (ipsCandidates.isEmpty()) {
                continue;
            }

            // find closest intersection point:
            int idx = position.getClosestIndex(ipsCandidates);
            if (idx<0) {
                continue;
            }
            RVector ipCandidate = ipsCandidates[idx];

            // choose matching pair of sub entity Ids:
            QPair<REntity::Id, REntity::Id> subEntityIds(REntity::INVALID_ID, REntity::INVALID_ID);
            if (idx<subEntityIdsCandidates.length()) {
                subEntityIds = subEntityIdsCandidates[idx];
            }

            dist = ipCandidate.getDistanceTo(position);
            if (dist<minDist) {
                lastSnap = ipCandidate;
                minDist = dist;

                mainEntityId1 = e1->getId();
                subEntityId1 = subEntityIds.first;

                mainEntityId2 = e2->getId();
                subEntityId2 = subEntityIds.second;
            }
        }
    }

    if (!lastSnap.isValid()) {
        lastSnap = position;
        lastSnap.valid = false;
        return lastSnap;
    }
    else {
        entityIds.append(mainEntityId1);
        if (subEntityId1!=REntity::INVALID_ID) {
            entityIds.append(-subEntityId1);
        }
        entityIds.append(mainEntityId2);
        if (subEntityId2!=REntity::INVALID_ID) {
            entityIds.append(-subEntityId2);
        }
        return lastSnap;
    }
}
