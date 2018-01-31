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
 * \class LineRadicalAxis
 * \brief Point at the power center of three chosen circles.
 * \ingroup ecma_misc_draw
 */
function LineRadicalAxis(guiAction) {
    EAction.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;
    this.entity2 = undefined;
    this.shape2 = undefined;
    this.pos2 = undefined;

    this.setUiOptions("LineRadicalAxis.ui");
}

LineRadicalAxis.prototype = new EAction();

LineRadicalAxis.State = {
    ChoosingShape1 : 0,
    ChoosingShape2 : 1
};

LineRadicalAxis.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(LineRadicalAxis.State.ChoosingShape1);
};

LineRadicalAxis.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineRadicalAxis.State.ChoosingShape1:
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        var trFirstEntity = qsTr("First arc or circle");
        this.setCommandPrompt(trFirstEntity);
        this.setLeftMouseTip(trFirstEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case LineRadicalAxis.State.ChoosingShape2:
        this.entity2 = undefined;
        this.shape2 = undefined;
        var trSecondEntity = qsTr("Second arc or circle");
        this.setCommandPrompt(trSecondEntity);
        this.setLeftMouseTip(trSecondEntity);
        this.setRightMouseTip(EAction.trBack);
        break;
    }
};

LineRadicalAxis.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineRadicalAxis.State.ChoosingShape1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case LineRadicalAxis.State.ChoosingShape2:
        this.setState(LineRadicalAxis.State.ChoosingShape1);
        break;
    }
};

LineRadicalAxis.prototype.pickEntity = function(event, preview) {
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
    case LineRadicalAxis.State.ChoosingShape1:
        this.entity1 = entity;
        this.shape1 = shape;
        this.pos1 = pos;

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(LineRadicalAxis.State.ChoosingShape2);
        }
        break;

    case LineRadicalAxis.State.ChoosingShape2:
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
                this.setState(LineRadicalAxis.State.ChoosingShape1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

LineRadicalAxis.prototype.getOperation = function(preview) {
    var shape = this.getLineRadicalAxis(preview);

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

LineRadicalAxis.prototype.getLineRadicalAxis = function(preview) {
    if (isNull(this.shape1) || isNull(this.shape2)) {
        return undefined;
    }

    return Apollonius.getRadicalAxis(this.shape1.data(), this.shape2.data());
};

LineRadicalAxis.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};

