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
#include "RGraphicsView.h"
#include "RMouseEvent.h"
#include "RS.h"
#include "RSettings.h"
#include "RSnapAuto.h"
#include "RSnapCenter.h"
#include "RSnapEnd.h"
#include "RSnapGrid.h"
#include "RSnapIntersection.h"
#include "RSnapMiddle.h"
#include "RSnapOnEntity.h"
#include "RSnapPerpendicular.h"
#include "RSnapTangential.h"
#include "RSnapReference.h"

bool RSnapAuto::initialized = false;
RSnapAuto::Modes RSnapAuto::modes = RSnapAuto::None;

//bool RSnapAuto::intersections = false;
//bool RSnapAuto::endPoints = false;
//bool RSnapAuto::middlePoints = false;
//bool RSnapAuto::centerPoints = false;
//bool RSnapAuto::perpendicular = false;
//bool RSnapAuto::tangential = false;
//bool RSnapAuto::referencePoints = false;
//bool RSnapAuto::gridPoints = false;
//bool RSnapAuto::pointsOnEntity = false;
//bool RSnapAuto::freePositioning = false;

RVector RSnapAuto::snap(const RVector& position, RGraphicsView& view, double range) {
    entityIds.clear();

    RDocument* document = view.getDocument();
    if (document==NULL) {
        lastSnap = position;
        return lastSnap;
    }

    RSnapAuto::init();

    if (RMath::isNaN(range)) {
        int rangePixels = RSettings::getSnapRange();
        range = view.mapDistanceFromView(rangePixels);
    }

    if (range<RS::PointTolerance) {
        return lastSnap;
    }

    // matching ids per query range:
    QList<QSet<RObject::Id> > idsList;
    QList<RBox> queryBoxList;
    bool foundEntities = false;

    for (double r=range/1.0; r<=range+RS::PointTolerance; r+=range/1.0) {
        RBox queryBox(position, r);
        queryBoxList.append(queryBox);

        QMap<RObject::Id, QSet<int> > ids = document->queryIntersectedShapesXY(
                queryBox, true, true, RObject::INVALID_ID
                    // 20151027: allow snapping to hatch end points, etc:
                    /*, QList<RS::EntityType>() << RS::EntityHatch*/);

        if (ids.isEmpty()) {
            continue;
        }

        idsList.append(RS::toSet(ids.keys()));

        foundEntities = true;

        // intersection
        if (getIntersections()) {
            RSnapIntersection snapIntersection;
            lastSnap = snapIntersection.snap(position, view, ids, queryBox);
            if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                status = RSnap::Intersection;
                entityIds = snapIntersection.getEntityIds();
                return lastSnap;
            }
        }
        lastSnap = RVector::invalid;
    }

    // interrupted by mouse move:
    if (RMouseEvent::hasMouseMoved()) {
        if (!getFreePositioning()) {
            // no free positioning, try grid as fallback:
            if (getGridPoints()) {
                RSnapGrid snapGrid;
                lastSnap = snapGrid.snap(position, view, range);
                if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                    status = RSnap::Grid;
                    return lastSnap;
                }
                lastSnap = RVector::invalid;
            }
            else {
                // no grid, no free positioning:
                return RVector::invalid;
            }
        }
        status = RSnap::Free;
        return position;
    }

    // end points:
    if (foundEntities && getEndPoints()) {
        for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
            // query box and matching IDs cached from intersection snap:
            RBox queryBox = queryBoxList.at(k);
            QSet<RObject::Id> ids = idsList.at(k);

            RSnapEnd snapEnd;
            lastSnap = snapEnd.snap(position, view, ids, queryBox);
            if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                status = RSnap::Endpoint;
                entityIds = snapEnd.getEntityIds();
                return lastSnap;
            }
        }
        lastSnap = RVector::invalid;
    }

    // middle points:
    if (foundEntities && getMiddlePoints()) {
        for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
            // query box and matching IDs cached from intersection snap:
            RBox queryBox = queryBoxList.at(k);
            QSet<RObject::Id> ids = idsList.at(k);

            RSnapMiddle snapMiddle;
            lastSnap = snapMiddle.snap(position, view, ids, queryBox);
            if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                status = RSnap::Middle;
                entityIds = snapMiddle.getEntityIds();
                return lastSnap;
            }
        }
        lastSnap = RVector::invalid;
    }

    // center points:
    if (foundEntities && getCenterPoints()) {
        for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
            // query box and matching IDs cached from intersection snap:
            RBox queryBox = queryBoxList.at(k);
            QSet<RObject::Id> ids = idsList.at(k);

            RSnapCenter snapCenter;
            lastSnap = snapCenter.snap(position, view, ids, queryBox);
            if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                status = RSnap::Center;
                entityIds = snapCenter.getEntityIds();
                return lastSnap;
            }
        }
        lastSnap = RVector::invalid;
    }

    // perpendicular:
    if (foundEntities && getPerpendicular()) {
        for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
            // query box and matching IDs cached from intersection snap:
            RBox queryBox = queryBoxList.at(k);
            QSet<RObject::Id> ids = idsList.at(k);

            RSnapPerpendicular snapPerpendicular;
            lastSnap = snapPerpendicular.snap(position, view, ids, queryBox);
            if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                status = RSnap::Perpendicular;
                entityIds = snapPerpendicular.getEntityIds();
                return lastSnap;
            }
        }
        lastSnap = RVector::invalid;
    }

    // tangential:
    if (foundEntities && getTangential()) {
        for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
            // query box and matching IDs cached from intersection snap:
            RBox queryBox = queryBoxList.at(k);
            QSet<RObject::Id> ids = idsList.at(k);

            RSnapTangential snapTangential;
            lastSnap = snapTangential.snap(position, view, ids, queryBox);
            if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                status = RSnap::Tangential;
                entityIds = snapTangential.getEntityIds();
                return lastSnap;
            }
        }
        lastSnap = RVector::invalid;
    }

    // reference points:
    if (foundEntities && getReferencePoints()) {
        for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
            // query box and matching IDs cached from intersection snap:
            RBox queryBox = queryBoxList.at(k);
            QSet<RObject::Id> ids = idsList.at(k);

            RSnapReference snapReference;
            lastSnap = snapReference.snap(position, view, ids, queryBox);
            if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                status = RSnap::Reference;
                entityIds = snapReference.getEntityIds();
                return lastSnap;
            }
        }
        lastSnap = RVector::invalid;
    }

    // grid points:
    if (getGridPoints()) {
        RSnapGrid snapGrid;
        lastSnap = snapGrid.snap(position, view, range);
        if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
            status = RSnap::Grid;
            return lastSnap;
        }
        lastSnap = RVector::invalid;
    }

    // on entity snap is slow and almost never used:
    if (foundEntities && getPointsOnEntity()) {
        for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
            // query box and matching IDs cached from intersection snap:
            RBox queryBox = queryBoxList.at(k);
            QSet<RObject::Id> ids = idsList.at(k);

            // on entity
            RSnapOnEntity snapOnEntity;
            lastSnap = snapOnEntity.snap(position, view, ids, queryBox);
            if (lastSnap.isValid() && lastSnap.getDistanceTo2D(position) < range) {
                status = RSnap::OnEntity;
                entityIds = snapOnEntity.getEntityIds();
                return lastSnap;
            }
        }
        lastSnap = RVector::invalid;
    }

    // free:
    if (getFreePositioning()) {
        lastSnap = position;
        status = RSnap::Free;
        return lastSnap;
    }

    return RVector::invalid;
}

void RSnapAuto::init(bool force) {
    if (initialized && !force) {
        return;
    }

    setIntersections(RSettings::getBoolValue("AutoSnap/Intersections", true));
    setEndPoints(RSettings::getBoolValue("AutoSnap/EndPoints", true));
    setMiddlePoints(RSettings::getBoolValue("AutoSnap/MiddlePoints", true));
    setCenterPoints(RSettings::getBoolValue("AutoSnap/CenterPoints", false));
    setPerpendicular(RSettings::getBoolValue("AutoSnap/Perpendicular", true));
    setTangential(RSettings::getBoolValue("AutoSnap/Tangential", true));
    setReferencePoints(RSettings::getBoolValue("AutoSnap/ReferencePoints", true));
    setGridPoints(RSettings::getBoolValue("AutoSnap/GridPoints", true));
    setPointsOnEntity(RSettings::getBoolValue("AutoSnap/PointsOnEntity", false));
    setFreePositioning(RSettings::getBoolValue("AutoSnap/FreePositioning", true));

    initialized = true;
}
