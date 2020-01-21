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
 * \class Circle3T
 * \brief Circle tangential to three entities (lines, arcs, circles).
 * \ingroup ecma_draw_circle
 */
function Circle3T(guiAction) {
    Circle.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;

    this.entity2 = undefined;
    this.shape2 = undefined;
    this.pos2 = undefined;

    this.entity3Id = undefined;
    this.entity3 = undefined;
    this.shape3 = undefined;
    this.pos3 = undefined;

    this.pos4 = undefined;

    this.candidates = undefined;
}

Circle3T.prototype = new Circle();

Circle3T.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1,
    ChoosingShape3 : 2,
    ChoosingSolution : 3
};

Circle3T.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(Circle3T.State.ChoosingShape1);
};

Circle3T.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    var di = this.getDocumentInterface();
    this.setCrosshairCursor();
    di.setClickMode(RAction.PickEntity);

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Circle3T.State.ChoosingShape1:
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.entity3 = undefined;
        this.entity3Id = undefined;
        this.shape3 = undefined;
        this.candidates = undefined;
        this.pos4 = undefined;
        var trFirstEntity = qsTr("First line, arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Circle3T.State.ChoosingShape2:
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.entity3 = undefined;
        this.entity3Id = undefined;
        this.shape3 = undefined;
        this.candidates = undefined;
        this.pos4 = undefined;
        var trSecondEntity = qsTr("Second line, arc or circle");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case Circle3T.State.ChoosingShape3:
        this.entity3 = undefined;
        this.entity3Id = undefined;
        this.shape3 = undefined;
        this.candidates = undefined;
        this.pos4 = undefined;
        var trThirdEntity = qsTr("Third line, arc or circle");
        this.setCommandPrompt(trThirdEntity);
        this.setLeftMouseTip(trThirdEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case Circle3T.State.ChoosingSolution:
        this.pos4 = undefined;
        var trSolution = qsTr("Choose solution");
        this.setCommandPrompt(trSolution);
        this.setLeftMouseTip(trSolution);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    this.simulateMouseMoveEvent();
};

Circle3T.prototype.escapeEvent = function() {
    switch (this.state) {
    case Circle3T.State.ChoosingShape1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Circle3T.State.ChoosingShape2:
        this.setState(Circle3T.State.ChoosingShape1);
        break;

    case Circle3T.State.ChoosingShape3:
        this.setState(Circle3T.State.ChoosingShape2);
        break;

    case Circle3T.State.ChoosingSolution:
        this.setState(Circle3T.State.ChoosingShape3);
        break;
    }
};

Circle3T.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();
    var shape = undefined;

    if (this.state!==Circle3T.State.ChoosingSolution) {
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
    case Circle3T.State.ChoosingShape1:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Circle3T.State.ChoosingShape2);
        }
        break;

    case Circle3T.State.ChoosingShape2:
        this.entity2 = entity;
        this.shape2 = shape;
        this.pos2 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(Circle3T.State.ChoosingShape3);
        }
        break;

    case Circle3T.State.ChoosingShape3:
        // optimization breaks when choosing three segments of the same polyline:
        //if (entityId!==this.entity3Id) {
            this.candidates = undefined;
        //}

        this.entity3 = entity;
        this.entity3Id = entityId;
        this.shape3 = shape;
        this.pos3 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op) && !isNull(this.candidates)) {
                // only one solution:
                if (this.candidates.length===1) {
                    di.applyOperation(op);
                    this.setState(Circle3T.State.ChoosingShape1);
                }
                // multiple solutions:
                else {
                    this.setState(Circle3T.State.ChoosingSolution);
                }
            }
            // no solution:
            else {
                this.setState(Circle3T.State.ChoosingShape1);
                this.error = qsTr("No solution");
            }
        }
        break;

    case Circle3T.State.ChoosingSolution:
        this.pos4 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(Circle3T.State.ChoosingShape1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Circle3T.prototype.getOperation = function(preview) {
    var shapes = this.getShapes(preview);

    if (isNull(shapes)) {
        return undefined;
    }

    var doc = this.getDocument();

    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    for (var i=0; i<shapes.length; i++) {
        var s = shapes[i];
        if  (isFunction(s.data)) {
            s = s.data();
        }
        var entity = new RCircleEntity(doc, new RCircleData(s));
        op.addObject(entity);
    }

    return op;
};

Circle3T.prototype.getShapes = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2) || isNull(this.shape3)) {
        return undefined;
    }

    var i,k,ips;

    if (isNull(this.candidates)) {
        Apollonius.constructionShapes = [];

        this.candidates = Apollonius.getSolutions(this.shape1.data(), this.shape2.data(), this.shape3.data());
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

Circle3T.prototype.getHighlightedEntities = function() {
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


Circle3T.prototype.getAuxPreview = function() {
    if (isNull(this.shape1) || isNull(this.shape2) || isNull(this.shape3)) {
        return [];
    }

    if (!isNull(this.pos4)) {
        return this.candidates;
    }

    return [];
};
