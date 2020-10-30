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

include("Modify.js");

/**
 * \class ModifyCorner
 * \brief Base class for modification tools that operate on a corner
 * (Bevel, Round).
 */
function ModifyCorner(guiAction) {
    Modify.call(this, guiAction);

    // position clicked to choose corner:
    this.posCorner = undefined;

    // entity / position chosen as first edge:
    this.entity1 = undefined;
    this.shape1 = undefined;
    this.clickPos1 = undefined;

    // entity / position chosen as second edge:
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.clickPos2 = undefined;

    // trimming on / off:
    this.trim = true;

    // tool requires additional point (e.g. radius position):
    this.requiresPoint = false;
    this.posPoint = undefined;

    this.posSolution = undefined;
}

ModifyCorner.prototype = new Modify();

ModifyCorner.State = {
    ChoosingCorner : 0,
    ChoosingEntity1 : 1,
    ChoosingEntity2 : 2,
    SettingPoint : 3,
};

ModifyCorner.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(ModifyCorner.State.ChoosingEntity1);
};

ModifyCorner.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ModifyCorner.State.ChoosingCorner:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinateNoSnap);
        this.posCorner = undefined;
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.clickPos1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.clickPos2 = undefined;
        this.posSolution = undefined;
        this.posPoint = undefined;
        var trCorner = qsTr("Choose corner");
        this.setCommandPrompt(trCorner);
        this.setLeftMouseTip(trCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ModifyCorner.State.ChoosingEntity1:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.posCorner = undefined;
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.clickPos1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.clickPos2 = undefined;
        this.posSolution = undefined;
        this.posPoint = undefined;
        var trEntity1 = qsTr("Choose first entity");
        this.setCommandPrompt(trEntity1);
        this.setLeftMouseTip(trEntity1);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ModifyCorner.State.ChoosingEntity2:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.clickPos2 = undefined;
        var trEntity2 = qsTr("Choose second entity");
        this.setCommandPrompt(trEntity2);
        this.setLeftMouseTip(trEntity2);
        this.setRightMouseTip(EAction.trBack);
        break;

    case ModifyCorner.State.SettingPoint:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.posSolution = undefined;
        this.posPoint = undefined;
        var trPoint = qsTr("Set point");
        this.setCommandPrompt(trPoint);
        this.setLeftMouseTip(trPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    this.simulateMouseMoveEvent();
};

ModifyCorner.prototype.escapeEvent = function() {
    switch (this.state) {
    case ModifyCorner.State.ChoosingCorner:
        Modify.prototype.escapeEvent.call(this);
        break;

    case ModifyCorner.State.ChoosingEntity1:
        Modify.prototype.escapeEvent.call(this);
        break;

    case ModifyCorner.State.ChoosingEntity2:
        this.setState(ModifyCorner.State.ChoosingEntity1);
        break;

    case ModifyCorner.State.SettingPoint:
        this.setState(ModifyCorner.State.ChoosingEntity2);
        break;
    }
};

ModifyCorner.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();
    var op;

    if (!this.isEntitySnappable(entity)) {
        // entity not on a snappable layer:
        return;
    }

    switch (this.state) {
    case ModifyCorner.State.ChoosingEntity1:
        if (isNull(entity)) {
            this.entity1 = undefined;
            this.shape1 = undefined;
            if (preview) {
                this.updatePreview();
            }
            return;
        }

        var shape = entity.getClosestSimpleShape(pos);

        if (this.isShapeSupported(shape)) {
            this.entity1 = entity;
            this.shape1 = shape;
            this.clickPos1 = pos;

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(ModifyCorner.State.ChoosingEntity2);
            }
        }
        else {
            if (!preview) {
                this.warnUnsupportedShape();
            }
        }
        break;

    case ModifyCorner.State.ChoosingEntity2:
        if (isNull(entity)) {
            this.entity2 = undefined;
            this.shape2 = undefined;
            if (preview) {
                this.updatePreview();
            }
            return;
        }

        var shape = entity.getClosestSimpleShape(pos);

        if (this.isShapeSupported(shape)) {

            this.entity2 = entity;
            this.shape2 = shape;
            this.clickPos2 = event.getModelPosition();

            if (preview) {
                this.updatePreview();
            }
            else {
                if (this.requiresPoint) {
                    this.setState(ModifyCorner.State.SettingPoint);
                }
                else {
                    op = this.getOperation(false);
                    if (!isNull(op)) {
                        di.applyOperation(op);
                        this.setState(ModifyCorner.State.ChoosingEntity1);
                    }
                }
            }
        }
        else {
            this.entity2 = undefined;
            this.shape2 = undefined;
            if (preview) {
                this.updatePreview();
            }
            else {
                this.warnUnsupportedShape();
            }
        }
        break;
    }
};

ModifyCorner.prototype.isShapeSupported = function(shape) {
    return isLineBasedShape(shape) || isArcShape(shape) || isCircleShape(shape);
};

ModifyCorner.prototype.warnUnsupportedShape = function() {
    EAction.warnNotLineArcCircle();
};

ModifyCorner.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    var op;

    switch (this.state) {
    case ModifyCorner.State.ChoosingCorner:
        this.posCorner = event.getModelPosition();
        var ok = this.pickCorner(event);
        if (preview) {
            this.updatePreview();
        }
        else {
            if (ok) {
                op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                }
                this.setState(ModifyCorner.State.ChoosingCorner);
            }
        }
        break;

    case ModifyCorner.State.SettingPoint:
        this.posPoint = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
            this.setState(ModifyCorner.State.ChoosingEntity1);
        }
        break;
    }
};

ModifyCorner.prototype.pickCorner = function(event) {
    this.entity1 = undefined;
    this.entity2 = undefined;

    var di = this.getDocumentInterface();
    var doc = this.getDocument();

    // get closest entity:
    var entityId1 = di.getClosestEntity(event.getRInputEvent());
    if (entityId1===RObject.INVALID_ID) {
        return false;
    }

    this.entity1 = doc.queryEntity(entityId1);
    if (isNull(this.entity1)) {
        return false;
    }

    if (isPolylineEntity(this.entity1)) {

        // find two closest segments and click positions:
        var vc = this.entity1.countVertices();
        var vertexIndex = this.entity1.getClosestVertex(this.posCorner);
        this.entity2 = this.entity1;
        var s1 = this.entity1.getSegmentAt(RMath.absmod(vertexIndex-1, vc-1));
        var s2 = this.entity1.getSegmentAt(vertexIndex);
        this.clickPos1 = s1.getPointWithDistanceToEnd(s1.getLength()/3);
        this.clickPos2 = s2.getPointWithDistanceToStart(s2.getLength()/3);

        this.posSolution = this.posCorner;

        return true;
    }

    this.shape1 = this.entity1.getClosestSimpleShape(this.posCorner);
    this.clickPos1 = this.entity1.getClosestPointOnEntity(this.posCorner);

    // ids of entities potentially intersecting entity1:
    var entityIds = doc.queryIntersectedEntitiesXY(this.entity1.getBoundingBox(), true);

    // find intersection points on entity1:
    var minDist = undefined;
    for (var i=0; i<entityIds.length; i++) {
        var entityId = entityIds[i];
        var entity2Candidate = doc.queryEntity(entityId);

        // intersection points between entity1 and entity2:
        var ips = this.entity1.getIntersectionPoints(entity2Candidate.data());
        for (var k=0; k<ips.length; k++) {
            var ip = ips[k];
            var side1 = this.shape1.getSideOfPoint(this.posCorner);

            var dist = this.clickPos1.getDistanceTo(ip);
            if (isNull(minDist) || dist<minDist) {

                var clickPos2Candidate = entity2Candidate.getClosestPointOnEntity(this.posCorner);
                var side2 = this.shape1.getSideOfPoint(clickPos2Candidate);

                if (side1===side2) {
                    // potential closest intersection point found:
                    minDist = dist;
                    this.entity2 = entity2Candidate;
                    this.shape2 = entity2Candidate.getClosestSimpleShape(this.posCorner);
                    this.clickPos2 = clickPos2Candidate;
                }
            }
        }
    }

    this.posSolution = this.posCorner;

    return true;
};

ModifyCorner.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};

ModifyCorner.prototype.slotTrimChanged = function(value) {
    this.trim = value;
};

ModifyCorner.prototype.slotIndividualEdgesChanged = function(value) {
    if (value===true) {
        this.setState(ModifyCorner.State.ChoosingEntity1);
    }
    else {
        this.setState(ModifyCorner.State.ChoosingCorner);
    }
};
