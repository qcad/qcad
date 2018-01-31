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

include("scripts/EAction.js");
include("scripts/Apollonius.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class PointPole
 * \ingroup ecma_misc_draw
 *
 * \brief Point at the power center of three chosen circles.
 */
function PointPole(guiAction) {
    EAction.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.pos2 = undefined;
}

PointPole.prototype = new EAction();

PointPole.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1
};

PointPole.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(PointPole.State.ChoosingShape1);
};

PointPole.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case PointPole.State.ChoosingShape1:
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        var trFirstEntity = qsTr("Arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case PointPole.State.ChoosingShape2:
        this.entity2 = undefined;
        this.shape2 = undefined;
        var trSecondEntity = qsTr("Line");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;
    }
};

PointPole.prototype.escapeEvent = function() {
    switch (this.state) {
    case PointPole.State.ChoosingShape1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case PointPole.State.ChoosingShape2:
        this.setState(PointPole.State.ChoosingShape1);
        break;
    }
};

PointPole.prototype.pickEntity = function(event, preview) {
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

    switch (this.state) {
    case PointPole.State.ChoosingShape1:
        if (!isArcShape(shape) &&
            !isCircleShape(shape)) {

            if (!preview) {
                EAction.warnNotArcCircle();
            }
            return;
        }
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(PointPole.State.ChoosingShape2);
        }
        break;

    case PointPole.State.ChoosingShape2:
        if (!isLineBasedShape(shape)) {

            if (!preview) {
                EAction.warnNotLine();
            }
            return;
        }
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
                this.setState(PointPole.State.ChoosingShape1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

PointPole.prototype.getOperation = function(preview) {
    var shape = this.getPointPole(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();
    var entity = shapeToEntity(doc, shape);

    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

PointPole.prototype.getPointPole = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2)) {
        return undefined;
    }

    var pole = Apollonius.getPole(this.shape1.data(), this.shape2.data());

    if (isNull(pole)) {
        return undefined;
    }

    return new RPoint(pole);
};

PointPole.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};

