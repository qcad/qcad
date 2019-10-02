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

include("scripts/Draw/Ellipse/Ellipse.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class EllipseInscribedQuad
 * \brief Circle tangential to three entities (lines, arcs, circles).
 * \ingroup ecma_draw_circle
 */
function EllipseInscribedQuad(guiAction) {
    Ellipse.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;

    this.entity2 = undefined;
    this.shape2 = undefined;
    this.pos2 = undefined;

    this.entity3 = undefined;
    this.shape3 = undefined;
    this.pos3 = undefined;

    this.entity4 = undefined;
    this.shape4 = undefined;
    this.pos4 = undefined;
}

EllipseInscribedQuad.prototype = new Ellipse();

EllipseInscribedQuad.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1,
    ChoosingShape3 : 2,
    ChoosingShape4 : 3
};

EllipseInscribedQuad.prototype.beginEvent = function() {
    Ellipse.prototype.beginEvent.call(this);

    this.setState(EllipseInscribedQuad.State.ChoosingShape1);
};

EllipseInscribedQuad.prototype.setState = function(state) {
    Ellipse.prototype.setState.call(this, state);

    var di = this.getDocumentInterface();
    this.setCrosshairCursor();
    di.setClickMode(RAction.PickEntity);

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case EllipseInscribedQuad.State.ChoosingShape1:
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.entity3 = undefined;
        this.shape3 = undefined;
        this.entity4 = undefined;
        this.shape4 = undefined;
        this.pos4 = undefined;
        var trFirstEntity = qsTr("First line");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case EllipseInscribedQuad.State.ChoosingShape2:
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.entity3 = undefined;
        this.shape3 = undefined;
        this.entity4 = undefined;
        this.shape4 = undefined;
        this.pos4 = undefined;
        var trSecondEntity = qsTr("Second line");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case EllipseInscribedQuad.State.ChoosingShape3:
        this.entity3 = undefined;
        this.entity3Id = undefined;
        this.shape3 = undefined;
        this.entity4 = undefined;
        this.shape4 = undefined;
        this.pos4 = undefined;
        var trThirdEntity = qsTr("Third line");
        this.setCommandPrompt(trThirdEntity);
        this.setLeftMouseTip(trThirdEntity);
        this.setRightMouseTip(EAction.trBack);
        break;

    case EllipseInscribedQuad.State.ChoosingShape4:
        this.entity4 = undefined;
        this.shape4 = undefined;
        this.pos4 = undefined;
        var trFourthEntity = qsTr("Fourth line");
        this.setCommandPrompt(trFourthEntity);
        this.setLeftMouseTip(trFourthEntity);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    this.simulateMouseMoveEvent();
};

EllipseInscribedQuad.prototype.escapeEvent = function() {
    switch (this.state) {
    case EllipseInscribedQuad.State.ChoosingShape1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case EllipseInscribedQuad.State.ChoosingShape2:
        this.setState(EllipseInscribedQuad.State.ChoosingShape1);
        break;

    case EllipseInscribedQuad.State.ChoosingShape3:
        this.setState(EllipseInscribedQuad.State.ChoosingShape2);
        break;

    case EllipseInscribedQuad.State.ChoosingShape4:
        this.setState(EllipseInscribedQuad.State.ChoosingShape3);
        break;
    }
};

EllipseInscribedQuad.prototype.pickEntity = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();
    var shape = undefined;

    if (!isNull(entity)) {
        shape = entity.getClosestSimpleShape(pos);

        if (!isLineBasedShape(shape)) {
            if (!preview) {
                EAction.warnNotLine();
                return;
            }
            shape = undefined;
        }
    }

    switch (this.state) {
    case EllipseInscribedQuad.State.ChoosingShape1:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(EllipseInscribedQuad.State.ChoosingShape2);
        }
        break;

    case EllipseInscribedQuad.State.ChoosingShape2:
        this.entity2 = entity;
        this.shape2 = shape;
        this.pos2 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(EllipseInscribedQuad.State.ChoosingShape3);
        }
        break;

    case EllipseInscribedQuad.State.ChoosingShape3:
        this.entity3 = entity;
        this.shape3 = shape;
        this.pos3 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(EllipseInscribedQuad.State.ChoosingShape4);
        }
        break;


    case EllipseInscribedQuad.State.ChoosingShape4:
        this.entity4 = entity;
        this.shape4 = shape;
        this.pos4 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(EllipseInscribedQuad.State.ChoosingShape1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

EllipseInscribedQuad.prototype.getOperation = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2) ||
        isNull(this.shape3) || isNull(this.shape4)) {
        return undefined;
    }

    var shape = ShapeAlgorithms.createEllipseInscribedFromLines(
        this.shape1, this.shape2, this.shape3, this.shape4);
    if (isNull(shape)) {
        return undefined;
    }

    if (isEllipseShape(shape)) {
        shape = RShape.ellipseToArcCircleEllipse(shape);
    }

    shape = Ellipse.postProcess(shape);

    var doc = this.getDocument();
    var e = shapeToEntity(doc, shape);
    if (isNull(e)) {
        return undefined;
    }

    return new RAddObjectOperation(e, this.getToolTitle());
};

EllipseInscribedQuad.prototype.getHighlightedEntities = function() {
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
    if (isEntity(this.entity4)) {
        ret.push(this.entity4.getId());
    }
    return ret;
};

EllipseInscribedQuad.prototype.getAuxPreview = function() {
    if (isNull(this.shape1) || isNull(this.shape2) ||
        isNull(this.shape3) || isNull(this.shape4)) {
        return [];
    }
    var quad = ShapeAlgorithms.getQuadrilateral(
        this.shape1, this.shape2, this.shape3, this.shape4);
    if (isNull(quad)) {
        return [];
    }

    var edges = [];
    for (var i=0; i<4; i++) {
        edges[i] = new RLine(quad[i], quad[(i+1)%4]);
    }
    return edges;
};
