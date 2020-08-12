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

include("scripts/Modify/Modify.js");

function Stretch(guiAction) {
    Modify.call(this, guiAction);

    this.corner1 = undefined;
    this.corner2 = undefined;
    this.referencePoint = undefined;
    this.targetPoint = undefined;
}

Stretch.prototype = new Modify();

Stretch.State = {
    SettingCorner1 : 0,
    SettingCorner2 : 1,
    SettingReferencePoint : 2,
    SettingTargetPoint : 3
};

Stretch.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(Stretch.State.SettingCorner1);
};

Stretch.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Stretch.State.SettingCorner1:
        this.corner1 = undefined;
        this.corner2 = undefined;
        this.referencePoint = undefined;
        this.targetPoint = undefined;
        var trFirstCorner = qsTr("First corner");
        this.setCommandPrompt(trFirstCorner);
        this.setLeftMouseTip(trFirstCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Stretch.State.SettingCorner2:
        this.corner2 = undefined;
        this.referencePoint = undefined;
        this.targetPoint = undefined;
        var trSecondCorner = qsTr("Second corner");
        this.setCommandPrompt(trSecondCorner);
        this.setLeftMouseTip(trSecondCorner);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Stretch.State.SettingReferencePoint:
        this.referencePoint = undefined;
        this.targetPoint = undefined;
        var trReferencePoint = qsTr("Reference point");
        this.setCommandPrompt(trReferencePoint);
        this.setLeftMouseTip(trReferencePoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Stretch.State.SettingTargetPoint:
        this.targetPoint = undefined;
        var trTargetPoint = qsTr("Target point");
        this.setCommandPrompt(trTargetPoint);
        this.setLeftMouseTip(trTargetPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Stretch.prototype.escapeEvent = function() {
    switch (this.state) {
    case Stretch.State.SettingCorner1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Stretch.State.SettingCorner2:
        this.setState(Stretch.State.SettingCorner1);
        break;

    case Stretch.State.SettingReferencePoint:
        this.setState(Stretch.State.SettingCorner2);
        break;

    case Stretch.State.SettingTargetPoint:
        this.setState(Stretch.State.SettingReferencePoint);
        break;
    }
};

Stretch.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Stretch.State.SettingCorner1:
        this.corner1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.corner1);
            this.setState(Stretch.State.SettingCorner2);
        }
        break;

    case Stretch.State.SettingCorner2:
        this.corner2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.corner2);
            this.setState(Stretch.State.SettingReferencePoint);
        }
        break;

    case Stretch.State.SettingReferencePoint:
        this.referencePoint = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            di.setRelativeZero(this.referencePoint);
            this.setState(Stretch.State.SettingTargetPoint);
        }
        break;

    case Stretch.State.SettingTargetPoint:
        this.targetPoint = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                op.setText(this.getToolTitle());
                di.applyOperation(op);
                di.setRelativeZero(this.targetPoint);
                this.setState(Stretch.State.SettingCorner1);
            }
        }
        break;
    }
};

Stretch.prototype.getOperation = function(preview) {
    if (!isValidVector(this.corner1) ||
            !isValidVector(this.corner2) ||
            !isValidVector(this.referencePoint) ||
            !isValidVector(this.targetPoint)) {

        return undefined;
    }

    // increase box slightly (see FS#435)
    var minX = Math.min(this.corner1.x, this.corner2.x);
    var minY = Math.min(this.corner1.y, this.corner2.y);
    var maxX = Math.max(this.corner1.x, this.corner2.x);
    var maxY = Math.max(this.corner1.y, this.corner2.y);

    var corners = new Array(
        new RVector(minX, minY),
        new RVector(maxX, minY),
        new RVector(maxX, maxY),
        new RVector(minX, maxY)
    );

    var polygon = new RPolyline();

    for (var i=0; i<4; ++i) {
        polygon.appendVertex(corners[i]);
    }

    polygon.setClosed(true);

    var offset = this.targetPoint.operator_subtract(this.referencePoint);

    return Stretch.getStrechOperation(this.getDocument(), polygon, preview, offset);
};

/**
 * \return Operation that stretches all entities inside polygon by the given offset.
 *
 * \param document RDocument
 * \param polygon RPolyline (closed polygon)
 * \param preview True: preview mode
 * \param offset RVector offset for the stretch operation
 * \param layerId Restrict operation to this layer (optional)
 * \param op Add stretch operation to existing operation (optional)
 */
Stretch.getStrechOperation = function(document, polygon, preview, offset, layerId, op) {
    // limit search to bounding box of polygon:
    var box = polygon.getBoundingBox();

    // only stretch selected if there is a selection,
    // otherwise stretch all:
    // 20200121: only go by bounding box:
    // allows stretching of ordinate dimension origin:
    var entities = document.queryIntersectedEntitiesXY(box, true, false, RObject.INVALID_ID, [], document.hasSelection());
    //var entities = document.queryIntersectedEntitiesXY(box, false, false, RObject.INVALID_ID, [], document.hasSelection());

    if (entities.length===0 && !preview) {
        if (document.hasSelection()) {
            EAction.handleUserWarning(qsTr("No selected entities in given range"));
        }
        else {
            EAction.handleUserWarning(qsTr("No entities in given range"));
        }
    }

    if (isNull(op)) {
        op = new RAddObjectsOperation();
    }

    for (var e = 0; e < entities.length; ++e) {
        var entity = document.queryEntity(entities[e]);

        // check if the entity is editable:
        if (!EAction.assertEditable(entity, true)) {
            continue;
        }

        // check if the entity is on the given layer:
        if (!isNull(layerId) && entity.getLayerId()===layerId) {
            continue;
        }

        // check if the entity intersects with any of the polygon edges:
        var gotIntersection = false;
        if (entity.intersectsWith(polygon)) {
            gotIntersection = true;
        }

        // ordinate dimension might be completely inside stretch area and
        // still needs stretching (origin outside stretch area):
        if (isDimOrdinateEntity(entity)) {
            gotIntersection = true;
        }

        // hatch entities might be partially inside stretch area but not
        // intersect with stretch area as pattern might not intersect even
        // if boundary intersects or pattern might only contain points:
        if (isHatchEntity(entity)) {
            gotIntersection = true;
        }

        if (gotIntersection) {
            // stretch:
            if (entity.stretch(polygon, offset)) {
                op.addObject(entity, false);
            }
        }
        else {
            // check if the entity is completely inside the polygon.
            // this is the case if one point on the entity is inside the polygon
            // and the entity does not intersect with the polygon.
            var pointOnEntity = entity.getPointOnEntity();
            if (polygon.contains(pointOnEntity, true)) {
                // move entity:
                entity.move(offset);
                op.addObject(entity, false);
            }
        }
    }

    return op;
};

Stretch.prototype.getAuxPreview = function() {
    if (!isValidVector(this.corner1) || !isValidVector(this.corner2)) {
        return undefined;
    }

    var ret = [];
    var offset = undefined;
    if (isValidVector(this.referencePoint) && isValidVector(this.targetPoint)) {
        offset = this.targetPoint.operator_subtract(this.referencePoint);
    }

    var corners = new Array(
        new RVector(this.corner1.x, this.corner1.y),
        new RVector(this.corner2.x, this.corner1.y),
        new RVector(this.corner2.x, this.corner2.y),
        new RVector(this.corner1.x, this.corner2.y)
    );

    for (var i=0; i<4; ++i) {
        var line = new RLine(corners[i], corners[(i+1)%4]);
        ret.push(line);

        if (!isNull(offset)) {
            line = line.copy();
            line.move(offset);
            ret.push(line);
        }
    }

    return ret;
};

