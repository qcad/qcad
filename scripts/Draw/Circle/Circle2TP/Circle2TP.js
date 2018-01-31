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

include("../Circle.js");
include("scripts/Apollonius.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class Circle2TP
 * \brief Circle tangential to two entities and through point.
 * \ingroup ecma_draw_circle
 */
function Circle2TP(guiAction) {
    Circle.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.pos2 = undefined;
    this.pos3 = undefined;
    this.pos4 = undefined;

    this.candidates = undefined;
}

Circle2TP.prototype = new Circle();

Circle2TP.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1,
    SettingPoint : 2,
    ChoosingSolution : 3
};

Circle2TP.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(Circle2TP.State.ChoosingShape1);
};

Circle2TP.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    var di = this.getDocumentInterface();

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Circle2TP.State.ChoosingShape1:
        di.setClickMode(RAction.PickEntity);
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.pos4 = undefined;
        this.candidates = undefined;
        var trFirstEntity = qsTr("First line, arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Circle2TP.State.ChoosingShape2:
        di.setClickMode(RAction.PickEntity);
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.pos4 = undefined;
        this.candidates = undefined;
        var trSecondEntity = qsTr("Second line, arc or circle");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case Circle2TP.State.SettingPoint:
        di.setClickMode(RAction.PickCoordinate);
        this.pos3 = undefined;
        this.pos4 = undefined;
        this.candidates = undefined;
        var trPoint = qsTr("Point on circle line");
        this.setCommandPrompt(trPoint);
        this.setLeftMouseTip(trPoint);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;

    case Circle2TP.State.ChoosingSolution:
        di.setClickMode(RAction.PickEntity);
        this.pos4 = undefined;
        var trSolution = qsTr("Choose solution");
        this.setCommandPrompt(trSolution);
        this.setLeftMouseTip(trSolution);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    this.simulateMouseMoveEvent();
};

Circle2TP.prototype.escapeEvent = function() {
    switch (this.state) {
    case Circle2TP.State.ChoosingShape1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Circle2TP.State.ChoosingShape2:
        this.setState(Circle2TP.State.ChoosingShape1);
        break;

    case Circle2TP.State.SettingPoint:
        this.setState(Circle2TP.State.ChoosingShape2);
        break;

    case Circle2TP.State.ChoosingSolution:
        this.setState(Circle2TP.State.SettingPoint);
        break;
    }
};

Circle2TP.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();
    var shape = undefined;

    if (this.state!==Circle2TP.State.ChoosingSolution) {
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
    case Circle2TP.State.ChoosingShape1:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Circle2TP.State.ChoosingShape2);
        }
        break;

    case Circle2TP.State.ChoosingShape2:
        this.entity2 = entity;
        this.shape2 = shape;
        this.pos2 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Circle2TP.State.SettingPoint);
        }
        break;

    case Circle2TP.State.ChoosingSolution:
        this.pos4 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(Circle2TP.State.ChoosingShape1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Circle2TP.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var pos = event.getModelPosition();

    switch (this.state) {
    case Circle2TP.State.SettingPoint:
        if (isNull(this.pos3) || !pos.equalsFuzzy(this.pos3)) {
            this.candidates = undefined;
        }

        this.pos3 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                // only one solution:
                if (this.candidates.length===1) {
                    di.applyOperation(op);
                    this.setState(Circle2TP.State.ChoosingShape1);
                }
                // multiple solutions:
                else {
                    op.destroy();
                    this.setState(Circle2TP.State.ChoosingSolution);
                }
            }
            // no solution:
            else {
                this.setState(Circle2TP.State.ChoosingShape1);
                this.error = qsTr("No solution");
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Circle2TP.prototype.getOperation = function(preview) {
    var shape = this.getShapes(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    for (var i=0; i<shape.length; i++) {
        var entity = new RCircleEntity(doc, new RCircleData(shape[i]));
        op.addObject(entity);
    }

    return op;
};

Circle2TP.prototype.getShapes = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2) || isNull(this.pos3)) {
        return undefined;
    }

    if (isNull(this.candidates)) {
        var shape3 = new RPoint(this.pos3);
        this.candidates = Apollonius.getSolutions(this.shape1.data(), this.shape2.data(), shape3);

        // filter out lines:
        this.candidates = ShapeAlgorithms.getCircleShapes(this.candidates);
    }

    if (this.candidates.length===0) {
        if (!preview) {
            this.error = qsTr("No solution");
        }
        return undefined;
    }

    // no position yet: return all candidates for preview:
    if (isNull(this.pos4)) {
        return this.candidates;
    }

    return [ ShapeAlgorithms.getClosestShape(this.candidates, this.pos4) ];
};

Circle2TP.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};

Circle2TP.prototype.getAuxPreview = function() {
    if (isNull(this.shape1) || isNull(this.shape2) || isNull(this.pos3)) {
        return [];
    }

    if (!isNull(this.pos4)) {
        return this.candidates;
    }

    return [];
};
