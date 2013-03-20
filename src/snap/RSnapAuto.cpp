/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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
#include "RSettings.h"
#include "RSnapAuto.h"
#include "RSnapEnd.h"
#include "RSnapGrid.h"
#include "RSnapIntersection.h"
#include "RSnapMiddle.h"
#include "RSnapOnEntity.h"
#include "RSnapPerpendicular.h"
#include "RSnapReference.h"


RVector RSnapAuto::snap(const RVector& position, RGraphicsView& view, double range) {
    //RDebug::startTimer(1);
    entityIds.clear();

    if (RMath::isNaN(range)) {
        int rangePixels = RSettings::getSnapRange();
        range = view.mapDistanceFromView(rangePixels);
    }

    RDocument* document = view.getDocument();
    if (document==NULL) {
        lastSnap = position;
        return lastSnap;
    }

    if (RMath::isNaN(range)) {
        int rangePixels = RSettings::getSnapRange();
        range = view.mapDistanceFromView(rangePixels);
    }


    // matching ids per query range:
    QList<QSet<REntity::Id> > idsList;
    QList<RBox> queryBoxList;
    bool foundEntities = false;

    //RDebug::startTimer(1);
    for (double r=range/10.0; r<=range+RS::PointTolerance; r+=range/10.0) {
        RBox queryBox(position, r);
        queryBoxList.append(queryBox);

        //RDebug::startTimer(2);
        QMap<REntity::Id, QSet<int> > ids = document->queryIntersectedShapesXY(
                queryBox, true /*false?*/, true, RBlock::INVALID_ID,
                    QList<RS::EntityType>() << RS::EntityHatch);
        idsList.append(ids.keys().toSet());
        //RDebug::stopTimer(2, "query");

        //qDebug() << "RSnapAuto::snap: ids: " << ids;

        if (ids.isEmpty()) {
            continue;
        }
//        else {
//            qDebug() << ids.size() << " entities found";
//            if (ids.size()==1) {
//                qDebug() << ids[0].size() << " shapes found";
//            }
//        }

        foundEntities = true;

        // intersection
        //RDebug::startTimer(2);
        RSnapIntersection snapIntersection;
        lastSnap = snapIntersection.snap(position, view, ids, queryBox);
        //RDebug::stopTimer(2, "inters");
        if (lastSnap.isValid() && lastSnap.getDistanceTo(position) < range) {
            status = RSnap::Intersection;
            entityIds = snapIntersection.getEntityIds();
            return lastSnap;
        }
    }
    //RDebug::stopTimer(1, "no inters");

    //RDebug::startTimer(1);
    if (foundEntities) {
    for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
        // query box and matching IDs cached from intersection snap:
        RBox queryBox = queryBoxList.at(k);
        QSet<REntity::Id> ids = idsList.at(k);

        // endpoint
        //RDebug::startTimer(2);
        RSnapEnd snapEnd;
        lastSnap = snapEnd.snap(position, view, ids, queryBox);
        //RDebug::stopTimer(2, "end");
        if (lastSnap.isValid() && lastSnap.getDistanceTo(position) < range) {
            status = RSnap::Endpoint;
            entityIds = snapEnd.getEntityIds();
            return lastSnap;
        }
    }
    }
    //RDebug::stopTimer(1, "no end");

    //RDebug::startTimer(1);
    if (foundEntities) {
    for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
        // query box and matching IDs cached from intersection snap:
        RBox queryBox = queryBoxList.at(k);
        QSet<REntity::Id> ids = idsList.at(k);

        // middle
        //RDebug::startTimer(2);
        RSnapMiddle snapMiddle;
        lastSnap = snapMiddle.snap(position, view, ids, queryBox);
        //RDebug::stopTimer(2, "middle");
        if (lastSnap.isValid() && lastSnap.getDistanceTo(position) < range) {
            status = RSnap::Middle;
            entityIds = snapMiddle.getEntityIds();
            return lastSnap;
        }
    }
    }
    //RDebug::stopTimer(1, "no middle");

    //RDebug::startTimer(1);
    if (foundEntities) {
    for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
        // query box and matching IDs cached from intersection snap:
        RBox queryBox = queryBoxList.at(k);
        QSet<REntity::Id> ids = idsList.at(k);

        // perpendicular
        //RDebug::startTimer(2);
        RSnapPerpendicular snapPerpendicular;
        lastSnap = snapPerpendicular.snap(position, view, ids, queryBox);
        //RDebug::stopTimer(2, "perpend");
        if (lastSnap.isValid() && lastSnap.getDistanceTo(position) < range) {
            status = RSnap::Perpendicular;
            entityIds = snapPerpendicular.getEntityIds();
            return lastSnap;
        }
    }
    }
    //RDebug::stopTimer(1, "no perpendicular");

    //RDebug::startTimer(1);
    if (foundEntities) {
    for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
        // query box and matching IDs cached from intersection snap:
        RBox queryBox = queryBoxList.at(k);
        QSet<REntity::Id> ids = idsList.at(k);

        // reference
        //RDebug::startTimer(2);
        RSnapReference snapReference;
        lastSnap = snapReference.snap(position, view, ids, queryBox);
        //RDebug::stopTimer(2, "ref");
        if (lastSnap.isValid() && lastSnap.getDistanceTo(position) < range) {
            status = RSnap::Reference;
            entityIds = snapReference.getEntityIds();
            return lastSnap;
        }
    }
    }
    //RDebug::stopTimer(1, "no reference");

    //RDebug::startTimer(1);
    // grid
    //RDebug::startTimer(2);
    RSnapGrid snapGrid;
    lastSnap = snapGrid.snap(position, view, range);
    //RDebug::stopTimer(2, "grid");
    if (lastSnap.isValid() && lastSnap.getDistanceTo(position) < range) {
        status = RSnap::Grid;
        return lastSnap;
    }
    //RDebug::stopTimer(1, "no grid");

    /*
    // on entity snap is slow and almost never used:
    //RDebug::startTimer(1);
    if (foundEntities) {
    for (int k=0; k<idsList.size() && k<queryBoxList.size(); k++) {
        // query box and matching IDs cached from intersection snap:
        RBox queryBox = queryBoxList.at(k);
        QSet<REntity::Id> ids = idsList.at(k);

        // on entity
        //RDebug::startTimer(2);
        RSnapOnEntity snapOnEntity;
        lastSnap = snapOnEntity.snap(position, view, ids, queryBox);
        //RDebug::stopTimer(2, "on ent");
        if (lastSnap.isValid() && lastSnap.getDistanceTo(position) < range) {
            status = RSnap::OnEntity;
            entityIds = snapOnEntity.getEntityIds();
            return lastSnap;
        }
    }
    }
    //RDebug::stopTimer(1, "no on entity");
    */

    // free:
    lastSnap = position;
    status = RSnap::Free;

    //RDebug::stopTimer(1, "no snap point found: free");

    // free (no snap)
    return position;
}
