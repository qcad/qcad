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

include("../Snap.js");

/**
 * \class SnapIntersectionManual
 * \ingroup ecma_snap
 * \brief Snap to intersection points by selecting two entities.
 */
function SnapIntersectionManual(guiAction) {
    Snap.call(this, guiAction);

    this.State = {
        PickingEntity1 : 0,
        PickingEntity2 : 1
    };

    this.state = this.State.PickingEntity1;
    this.entity1 = undefined;
    this.shape1 = undefined;
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.entityId1 = -1;
}

SnapIntersectionManual.prototype = new Snap();

SnapIntersectionManual.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    this.di = this.getDocumentInterface();
    this.di.setSnap(null);
    this.di.setClickMode(RAction.PickEntity);
    this.di.setCursorOverride(true);
    this.base = this.getOverrideBase();
    if (isNull(this.base)) {
        qWarning("No base action to override");
        //this.di.setCursorOverride(false);
        this.terminate();
        return;
    }
    if (this.base.getClickMode()!=RAction.PickCoordinate) {
        qWarning("No coordinate requested at this point");
        this.terminate();
    }
};

SnapIntersectionManual.prototype.finishEvent = function() {
    this.di.setCursorOverride(false);
    Snap.prototype.finishEvent.call(this);
};

SnapIntersectionManual.prototype.entityPickEvent = function(event) {
    var doc = this.getDocument();
    if (isNull(doc)) {
        return;
    }

    var pos = event.getModelPosition();

    if (this.state===this.State.PickingEntity1) {
        this.entity1 = doc.queryEntity(event.getEntityId());
        if (!this.entity1.isNull()) {
            this.shape1 = this.entity1.getClosestShape(pos);
            this.entityId1 = event.getEntityId();
            this.state = this.State.PickingEntity2;
        }
    }
    else {
        var ip = this.getIntersection(event);

        if (!isNull(this.base) && ip.isValid()) {
            ip = this.restrict(ip);

            this.base.coordinateEvent(
                new RCoordinateEvent(ip,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
        }
        //this.di.setCursorOverride(false);
        this.terminate();
    }
};

SnapIntersectionManual.prototype.entityPickEventPreview = function(event) {
    if (this.state===this.State.PickingEntity1) {
        if (event.getEntityId()!==-1) {
            this.di.highlightEntity(event.getEntityId());
        }
        this.di.setCursorPosition(RVector.invalid);
    }
    else if (this.state===this.State.PickingEntity2) {
        if (this.entityId1!==-1) {
            this.di.highlightEntity(this.entityId1);
        }

        if (event.getEntityId()!==-1) {
            this.di.highlightEntity(event.getEntityId());
        }

        var ip = this.getIntersection(event);
        if (!isNull(this.base) && ip.isValid()) {
            ip = this.restrict(ip);
            this.base.coordinateEventPreview(
                new RCoordinateEvent(ip,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
            this.di.setCursorPosition(ip);
        }
        else {
            this.di.setCursorPosition(RVector.invalid);
        }
    }
};

SnapIntersectionManual.prototype.getIntersection = function(event) {
    var position = event.getModelPosition();
    var entity2 = this.getDocument().queryEntity(event.getEntityId());
    if (entity2.isNull()) {
        return RVector.invalid;
    }
    this.entity2 = entity2;
    this.shape2 = entity2.getClosestShape(position);
    if (this.shape2.isNull()) {
        return RVector.invalid;
    }

    var ips = this.shape1.getIntersectionPoints(this.shape2.data(), false, false, true);

    return position.getClosest(ips);
};

