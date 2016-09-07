/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
    this.entity2Id = undefined;
    this.shape2 = undefined;
    this.radius = undefined;
    this.center = undefined;
    this.pos = undefined;

    this.candidates = undefined;

    this.setUiOptions("Circle2TR.ui");
}

Circle2TR.prototype = new Circle();

Circle2TR.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1,
    ChoosingSolution : 2
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
        this.entity2Id = undefined;
        this.shape2 = undefined;
        this.center = undefined;
        this.pos = undefined;
        this.candidates = undefined;
        var trFirstEntity = qsTr("First line, arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Circle2TR.State.ChoosingShape2:
        this.entity2 = undefined;
        this.entity2Id = undefined;
        this.shape2 = undefined;
        this.center = undefined;
        this.pos = undefined;
        this.candidates = undefined;
        var trSecondEntity = qsTr("Second line, arc or circle");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case Circle2TR.State.ChoosingSolution:
        this.pos = undefined;
        var trSolution = qsTr("Choose solution");
        this.setCommandPrompt(trSolution);
        this.setLeftMouseTip(trSolution);
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

    case Circle2TR.State.ChoosingSolution:
        this.setState(Circle2TR.State.ChoosingShape2);
        break;
    }
};

Circle2TR.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    var shape = undefined;
    if (this.state!==Circle2TR.State.ChoosingSolution) {
        if (isNull(entity)) {
            return;
        }
        else {
            shape = entity.getClosestSimpleShape(pos);

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
    }

    switch (this.state) {
    case Circle2TR.State.ChoosingShape1:
        this.entity1 = entity;
        this.shape1 = shape;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Circle2TR.State.ChoosingShape2);
        }
        break;

    case Circle2TR.State.ChoosingShape2:
        if (entityId!==this.entity2Id) {
            this.candidates = undefined;
        }
        this.entity2 = entity;
        this.entity2Id = entityId;
        this.shape2 = shape;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
//                di.applyOperation(op);
//                this.setState(Circle2TR.State.ChoosingShape1);
                // only one solution:
                if (this.candidates.length===1) {
                    di.applyOperation(op);
                    this.setState(Circle2TR.State.ChoosingShape1);
                }
                // multiple solutions:
                else {
                    this.setState(Circle2TR.State.ChoosingSolution);
                }
            }
            else {
                this.setState(Circle2TR.State.ChoosingShape1);
                this.error = qsTr("No solution");
            }
        }
        break;

    case Circle2TR.State.ChoosingSolution:
        this.pos = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(Circle2TR.State.ChoosingShape1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Circle2TR.prototype.getOperation = function(preview) {
    var shapes = this.getCircles2TR(preview);

    if (isNull(shapes)) {
        return undefined;
    }

    var doc = this.getDocument();

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    for (var i=0; i<shapes.length; i++) {
        var entity = new RCircleEntity(doc, new RCircleData(shapes[i]));
        op.addObject(entity);
    }
    return op;
};

Circle2TR.prototype.getCircles2TR = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2) || !isNumber(this.radius)) {
        return undefined;
    }

    if (this.radius <= 0.0 || this.radius > 1.0e6) {
        if (!preview) {
            this.error = qsTr("Invalid radius");
        }
        return undefined;
    }

    var i,k,ips,s;

    if (isNull(this.candidates)) {
        var offset1 = ShapeAlgorithms.getOffsetShapes(this.shape1, this.radius, 1, RS.BothSides);
        var offset2 = ShapeAlgorithms.getOffsetShapes(this.shape2, this.radius, 1, RS.BothSides);

        if (isCircleShape(this.shape1) || isArcShape(this.shape1)) {
            if (this.radius>this.shape1.getRadius()) {
                s = this.shape1.clone();
                s.setRadius(this.radius - this.shape1.getRadius());
                offset1.push(s);
            }
        }
        if (isCircleShape(this.shape2) || isArcShape(this.shape2)) {
            if (this.radius>this.shape2.getRadius()) {
                s = this.shape2.clone();
                s.setRadius(this.radius - this.shape2.getRadius());
                offset2.push(s);
            }
        }

        var centerPoints = [];
        for (i=0; i<offset1.length; i++) {
            for (k=0; k<offset2.length; k++) {
                s = offset2[k];
                if (isFunction(s.data)) {
                    s = s.data();
                }
                ips = offset1[i].getIntersectionPoints(s, false);
                centerPoints = centerPoints.concat(ips);
            }
        }

        this.candidates = [];
        var circle = undefined;
        for (i=0; i<centerPoints.length; i++) {
            var c = new RCircle(centerPoints[i], this.radius);
            this.candidates.push(c);
        }
    }

    if (this.candidates.length===0) {
        if (!preview) {
            this.error = qsTr("No solution");
        }
        return undefined;
    }

    // no position yet: return all candidates for preview:
    if (isNull(this.pos)) {
        return this.candidates;
    }

    return [ ShapeAlgorithms.getClosestShape(this.candidates, this.pos) ];
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
//    var a;

//    if (isVector(this.center)) {
//        if (isArcShape(this.shape1)) {
//            a = this.shape1.getCenter().getAngleTo(this.center);
//            if (!this.shape1.isAngleWithinArc(a)) {
//                ret.push(new RCircle(this.shape1.getCenter(), this.shape1.getRadius()));
//            }
//        }
//        if (isArcShape(this.shape2)) {
//            a = this.shape2.getCenter().getAngleTo(this.center);
//            if (!this.shape2.isAngleWithinArc(a)) {
//                ret.push(new RCircle(this.shape2.getCenter(), this.shape2.getRadius()));
//            }
//        }
//    }

    if (!isNull(this.pos)) {
        return this.candidates;
    }

    return ret;
};
