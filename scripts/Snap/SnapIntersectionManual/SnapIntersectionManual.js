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

include("scripts/Snap/Snap.js");

/**
 * \class SnapIntersectionManual
 * \ingroup ecma_snap
 * \brief Snap to intersection points by selecting two entities.
 */
function SnapIntersectionManual(guiAction) {
    Snap.call(this, guiAction);

    this.autoTerminate = RSettings.getBoolValue("SnapIntersectionManual/AutoTerminate", true);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.entityId1 = -1;
}

SnapIntersectionManual.prototype = new Snap();

SnapIntersectionManual.State = {
    PickingEntity1 : 0,
    PickingEntity2 : 1
};

SnapIntersectionManual.getPreferencesCategory = function() {
    return [qsTr("Snap"), qsTr("Intersection Manual")];
};

SnapIntersectionManual.prototype.setState = function(state) {
    Snap.prototype.setState.call(this, state);

    switch (this.state) {
    case SnapIntersectionManual.State.PickingEntity1:
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.entityId1 = -1;
        var trFirstEntity = qsTr("First entity");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        this.di = this.getDocumentInterface();
        this.di.setSnap(null);
        this.di.setClickMode(RAction.PickEntity);
        this.di.setCursorOverride(true);
        break;

    case SnapIntersectionManual.State.PickingEntity2:
        var trSecondEntity = qsTr("Second entity");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;
    }
};

SnapIntersectionManual.prototype.beginEvent = function() {
    Snap.prototype.beginEvent.call(this);
    this.base = this.getOverrideBase();
    if (isNull(this.base)) {
        qWarning("No base action to override");
        this.terminate();
        return;
    }
    this.setState(SnapIntersectionManual.State.PickingEntity1);
//    if (this.base.getClickMode()!==RAction.PickCoordinate) {
//        qWarning("No coordinate requested at this point");
//        this.terminate();
//    }
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

    if (this.state===SnapIntersectionManual.State.PickingEntity1) {
        var id = EAction.getEntityId(this.di, this, event, true);
        this.entity1 = doc.queryEntity(id);
        if (!this.entity1.isNull()) {
            this.shape1 = this.entity1.getClosestSimpleShape(pos);
            this.entityId1 = EAction.prototype.getEntityId.call(this, event, false);
            this.setState(SnapIntersectionManual.State.PickingEntity2);
        }
    }
    else {
        var ip = this.getIntersection(event, false);

        if (!isNull(this.base) && ip.isValid()) {
            ip = this.restrict(ip);

            this.base.coordinateEvent(
                new RCoordinateEvent(ip,
                    event.getGraphicsScene(),
                    event.getGraphicsView()
                )
            );
        }
        if (this.autoTerminate) {
            this.terminate();
        }
        else {
            this.setState(SnapIntersectionManual.State.PickingEntity1);
        }
    }
};

SnapIntersectionManual.prototype.entityPickEventPreview = function(event) {
    if (this.state===SnapIntersectionManual.State.PickingEntity1) {
        if (event.getEntityId()!==-1) {
            this.di.highlightEntity(event.getEntityId());
        }
        this.di.setCursorPosition(RVector.invalid);
    }
    else if (this.state===SnapIntersectionManual.State.PickingEntity2) {
        if (this.entityId1!==-1) {
            this.di.highlightEntity(this.entityId1);
        }

        if (event.getEntityId()!==-1) {
            this.di.highlightEntity(event.getEntityId());
        }

        var ip = this.getIntersection(event, true);
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

SnapIntersectionManual.prototype.getIntersection = function(event, preview) {
    var position = event.getModelPosition();
    var id = EAction.getEntityId(this.getDocumentInterface(), this, event, preview);
    var entity2 = this.getDocument().queryEntity(id);
    if (entity2.isNull()) {
        return RVector.invalid;
    }
    this.entity2 = entity2;
    this.shape2 = entity2.getClosestSimpleShape(position);
    if (this.shape2.isNull()) {
        return RVector.invalid;
    }

    var ips = this.shape1.getIntersectionPoints(this.shape2.data(), false, false, true);

    return position.getClosest(ips);
};
