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
 * \class CircleT2P
 * \brief Circle tangential to entity, through 2 points.
 * \ingroup ecma_draw_circle
 */
function CircleT2P(guiAction) {
    Circle.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;
    this.pos2 = undefined;
    this.pos3 = undefined;
    this.pos4 = undefined;

    this.candidates = undefined;
}

CircleT2P.prototype = new Circle();

CircleT2P.State = {
    ChoosingShape : 0,
    SettingPoint1 : 1,
    SettingPoint2 : 2,
    ChoosingSolution : 3
};

CircleT2P.prototype.beginEvent = function() {
    Circle.prototype.beginEvent.call(this);

    this.setState(CircleT2P.State.ChoosingShape);
};

CircleT2P.prototype.setState = function(state) {
    Circle.prototype.setState.call(this, state);

    var di = this.getDocumentInterface();

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case CircleT2P.State.ChoosingShape:
        di.setClickMode(RAction.PickEntity);
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.pos1 = undefined;
        this.pos2 = undefined;
        this.pos3 = undefined;
        this.pos4 = undefined;
        this.candidates = undefined;
        var trFirstEntity = qsTr("Line, arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case CircleT2P.State.SettingPoint1:
        di.setClickMode(RAction.PickCoordinate);
        this.pos2 = undefined;
        this.pos3 = undefined;
        this.pos4 = undefined;
        this.candidates = undefined;
        var trFirstPoint = qsTr("First point on circle line");
        this.setCommandPrompt(trFirstPoint);
        this.setLeftMouseTip(trFirstPoint);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;

    case CircleT2P.State.SettingPoint2:
        di.setClickMode(RAction.PickCoordinate);
        this.pos3 = undefined;
        this.pos4 = undefined;
        this.candidates = undefined;
        var trSecondPoint = qsTr("Second point on circle line");
        this.setCommandPrompt(trSecondPoint);
        this.setLeftMouseTip(trSecondPoint);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;

    case CircleT2P.State.ChoosingSolution:
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

CircleT2P.prototype.escapeEvent = function() {
    switch (this.state) {
    case CircleT2P.State.ChoosingShape:
        EAction.prototype.escapeEvent.call(this);
        break;

    case CircleT2P.State.SettingPoint1:
        this.setState(CircleT2P.State.ChoosingShape);
        break;

    case CircleT2P.State.SettingPoint2:
        this.setState(CircleT2P.State.SettingPoint1);
        break;

    case CircleT2P.State.ChoosingSolution:
        this.setState(CircleT2P.State.SettingPoint2);
        break;
    }
};

CircleT2P.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();
    var shape = undefined;

    if (this.state!==CircleT2P.State.ChoosingSolution) {
        if (isNull(entity)) {
            return;
        }

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

    switch (this.state) {
    case CircleT2P.State.ChoosingShape:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(CircleT2P.State.SettingPoint1);
        }
        break;

    case CircleT2P.State.ChoosingSolution:
        this.pos4 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(CircleT2P.State.ChoosingShape);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

CircleT2P.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var pos = event.getModelPosition();

    switch (this.state) {
    case CircleT2P.State.SettingPoint1:
        this.pos2 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(CircleT2P.State.SettingPoint2);
        }
        break;

    case CircleT2P.State.SettingPoint2:
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
                    this.setState(CircleT2P.State.ChoosingShape);
                }
                // multiple solutions:
                else {
                    this.setState(CircleT2P.State.ChoosingSolution);
                }
            }
            // no solution:
            else {
                this.setState(CircleT2P.State.ChoosingShape);
                this.error = qsTr("No solution");
            }
        }
        break;

    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

CircleT2P.prototype.getOperation = function(preview) {
    var shapes = this.getShapes(preview);

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

CircleT2P.prototype.getShapes = function(preview) {
    if (isNull(this.shape1) || isNull(this.pos2) || isNull(this.pos3)) {
        return undefined;
    }

    if (isNull(this.candidates)) {
        var point1 = new RPoint(this.pos2);
        var point2 = new RPoint(this.pos3);

        this.candidates = Apollonius.getSolutions(this.shape1.data(), point1, point2);

        // filter out lines:
        this.candidates = ShapeAlgorithms.getCircleShapes(this.candidates);
    }

    if (isNull(this.candidates) || this.candidates.length===0) {
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

CircleT2P.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    return ret;
};

CircleT2P.prototype.getAuxPreview = function() {
    if (isNull(this.shape1) || isNull(this.pos2) || isNull(this.pos3)) {
        return [];
    }

    if (!isNull(this.pos4)) {
        return this.candidates;
    }

    return [];
};
