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

include("Draw.js");

/**
 * \class DrawBasedOnThreeCircles
 * \brief Base class for drawing tools that draw something based on 
 * three given circles or arcs.
 * \ingroup ecma_misc_draw
 */
function DrawBasedOnThreeCircles(guiAction) {
    EAction.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.pos2 = undefined;
    this.entity3 = undefined;
    this.shape3 = undefined;
    this.pos3 = undefined;
}

DrawBasedOnThreeCircles.prototype = new EAction();

DrawBasedOnThreeCircles.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1,
    ChoosingShape3 : 2
};

DrawBasedOnThreeCircles.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(DrawBasedOnThreeCircles.State.ChoosingShape1);
};

DrawBasedOnThreeCircles.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case DrawBasedOnThreeCircles.State.ChoosingShape1:
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.entity3 = undefined;
        this.shape3 = undefined;
        this.center = undefined;
        var trFirstEntity = qsTr("First arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case DrawBasedOnThreeCircles.State.ChoosingShape2:
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.entity3 = undefined;
        this.shape3 = undefined;
        this.center = undefined;
        var trSecondEntity = qsTr("Second arc or circle");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case DrawBasedOnThreeCircles.State.ChoosingShape3:
        this.entity3 = undefined;
        this.shape3 = undefined;
        this.center = undefined;
        var trThirdEntity = qsTr("Third arc or circle");
        this.setCommandPrompt(trThirdEntity);
        this.setLeftMouseTip(trThirdEntity);
        this.setRightMouseTip(EAction.trBack);
        break;
    }
};

DrawBasedOnThreeCircles.prototype.escapeEvent = function() {
    switch (this.state) {
    case DrawBasedOnThreeCircles.State.ChoosingShape1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DrawBasedOnThreeCircles.State.ChoosingShape2:
        this.setState(DrawBasedOnThreeCircles.State.ChoosingShape1);
        break;

    case DrawBasedOnThreeCircles.State.ChoosingShape3:
        this.setState(DrawBasedOnThreeCircles.State.ChoosingShape2);
        break;
    }
};

DrawBasedOnThreeCircles.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    var shape = entity.getClosestSimpleShape(pos);

    if (!isArcShape(shape) &&
        !isCircleShape(shape)) {

        if (!preview) {
            EAction.warnNotArcCircle();
        }
        return;
    }

    switch (this.state) {
    case DrawBasedOnThreeCircles.State.ChoosingShape1:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(DrawBasedOnThreeCircles.State.ChoosingShape2);
        }
        break;

    case DrawBasedOnThreeCircles.State.ChoosingShape2:
        this.entity2 = entity;
        this.shape2 = shape;
        this.pos2 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(DrawBasedOnThreeCircles.State.ChoosingShape3);
        }
        break;

    case DrawBasedOnThreeCircles.State.ChoosingShape3:
        this.entity3 = entity;
        this.shape3 = shape;
        this.pos3 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(DrawBasedOnThreeCircles.State.ChoosingShape1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

DrawBasedOnThreeCircles.prototype.getOperation = function(preview) {
    var shapes = this.getShapes(preview);

    if (isNull(shapes)) {
        return undefined;
    }

    var doc = this.getDocument();
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());

    for (var i=0; i<shapes.length; i++) {
        var entity = shapeToEntity(doc, shapes[i]);
        if (!isEntity(entity)) {
            continue;
        }
        op.addObject(entity);
    }

    return op;
};

/**
 * Implemented by child classes.
 */
DrawBasedOnThreeCircles.prototype.getShapes = function(preview) {
    return undefined;
};

DrawBasedOnThreeCircles.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    if (isEntity(this.entity3)) {
        ret.push(this.entity3.getId());
    }
    return ret;
};

