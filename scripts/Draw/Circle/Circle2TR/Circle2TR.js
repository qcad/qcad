/**
 * Copyright (c) 2011-2014 by Andrew Mustun. All rights reserved.
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

include("../Circle.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Circle2TR
 * \brief Circle from radius and two tangential entities.
 * \ingroup ecma_draw_circle
 */
function Circle2TR(guiAction) {
    Circle.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.radius = undefined;
    this.center = undefined;

    this.setUiOptions("Circle2TR.ui");
}

Circle2TR.prototype = new Circle();

Circle2TR.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1
};

Circle2TR.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(Circle2TR.State.ChoosingShape1);
};

Circle2TR.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Circle2TR.State.ChoosingShape1:
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.center = undefined;
        var trFirstEntity = qsTr("First line, arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Circle2TR.State.ChoosingShape2:
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.center = undefined;
        var trSecondEntity = qsTr("Second line, arc or circle");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    this.simulateMouseMoveEvent();
};

Circle2TR.prototype.escapeEvent = function() {
    switch (this.state) {
    case Circle2TR.State.ChoosingShape1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Circle2TR.State.ChoosingShape2:
        this.setState(Circle2TR.State.ChoosingShape1);
        break;
    }
};

Circle2TR.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    var shape = undefined;
    if (!isNull(entity)) {
        shape = getClosestSimpleShape(entity, pos);

        if (!isLineBasedShape(shape) &&
            !isArcShape(shape) &&
            !isCircleShape(shape)) {

            if (!preview) {
                EAction.warnNotLineArcCircle();
                return;
            }

            shape = undefined;
        }
    }

    switch (this.state) {
    case Circle2TR.State.ChoosingShape1:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Circle2TR.State.ChoosingShape2);
        }
        break;

    case Circle2TR.State.ChoosingShape2:
        this.entity2 = entity;
        this.shape2 = shape;
        this.pos2 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(Circle2TR.State.ChoosingShape1);
            }
            else {
                this.setState(Circle2TR.State.ChoosingShape1);
                this.error = qsTr("No solution");
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Circle2TR.prototype.getOperation = function(preview) {
    var shape = this.getCircle2TR(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();

    var entity = new RCircleEntity(doc, new RCircleData(shape));

    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

Circle2TR.prototype.getCircle2TR = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2) || !isNumber(this.radius)) {
        return undefined;
    }

    if (this.radius <= 0.0 || this.radius > 1.0e6) {
        if (!preview) {
            this.error = qsTr("Invalid radius");
        }
        return undefined;
    }

    var i,k,ips;

    var offset1 = ShapeAlgorithms.getOffsetShapes(this.shape1, this.radius, 1, RS.BothSides);
    var offset2 = ShapeAlgorithms.getOffsetShapes(this.shape2, this.radius, 1, RS.BothSides);

    var candidates = [];
    for (i=0; i<offset1.length; i++) {
        for (k=0; k<offset2.length; k++) {
            ips = offset1[i].getIntersectionPoints(offset2[k], false);
            candidates = candidates.concat(ips);
        }
    }

    if (candidates.length===0) {
        if (!preview) {
            this.error = qsTr("No solution");
        }
        return undefined;
    }

    var minDist = -1;
    var circle = undefined;
    for (i=0; i<candidates.length; i++) {
        var c = new RCircle(candidates[i], this.radius);
        var dist = c.getDistanceTo(this.pos2);
        if (minDist<0 || dist<minDist) {
            minDist = dist;
            circle = c;
            this.center = candidates[i];
        }
    }

    return circle;
};

Circle2TR.prototype.slotRadiusChanged = function(value) {
    this.radius = value;
    this.updatePreview(true);
};

Circle2TR.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};


Circle2TR.prototype.getAuxPreview = function() {
    var ret = [];
    var a;

    if (isVector(this.center)) {
        if (isArcShape(this.shape1)) {
            a = this.shape1.getCenter().getAngleTo(this.center);
            if (!this.shape1.isAngleWithinArc(a)) {
                ret.push(new RCircle(this.shape1.getCenter(), this.shape1.getRadius()));
            }
        }
        if (isArcShape(this.shape2)) {
            a = this.shape2.getCenter().getAngleTo(this.center);
            if (!this.shape2.isAngleWithinArc(a)) {
                ret.push(new RCircle(this.shape2.getCenter(), this.shape2.getRadius()));
            }
        }
    }

    return ret;
};
