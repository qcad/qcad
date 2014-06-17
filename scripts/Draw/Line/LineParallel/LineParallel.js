/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
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

include("../Line.js");
include("scripts/ShapeAlgorithms.js");

/**
 * \class LineParallel
 * \brief Line parallel to existing line with distance.
 * \ingroup ecma_draw_line
 */
function LineParallel(guiAction) {
    Line.call(this, guiAction);

    this.distance = undefined;
    this.number = undefined;
    this.entity = undefined;
    this.shape = undefined;
    this.pos = undefined;

    if (!isNull(guiAction)) {
        this.setUiOptions("LineParallel.ui");
    }
}

LineParallel.prototype = new Line();

LineParallel.State = {
    ChoosingEntity : 0
};

LineParallel.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineParallel.State.ChoosingEntity);

    var ot = EAction.getOptionsToolBar();
    var l = ot.findChild("label");
    var w = ot.findChild("Distance");
    l.setBuddy(w);
};

LineParallel.prototype.initState = function() {
    Line.prototype.initState.call(this);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineParallel.State.ChoosingEntity:
        this.setLeftMouseTip(qsTr("Choose line, arc or circle"));
        break;
    }

    this.setRightMouseTip(EAction.trCancel);
};

LineParallel.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineParallel.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

LineParallel.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        this.entity = undefined;
        return;
    }

    //if (preview) {
    //    di.highlightEntity(entityId);
    //}

    switch (this.state) {
    case LineParallel.State.ChoosingEntity:
        var shape = entity.getClosestShape(pos);

        if (isLineBasedShape(shape) ||
            isArcShape(shape) ||
            isCircleShape(shape)) {

            this.entity = entity;
            this.shape = shape;
            this.pos = pos;
        }
        else {
            if (!preview) {
                EAction.warnNotLineArcCircle();
                break;
            }
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                if (!isNull(this.error)) {
                    EAction.handleUserWarning(this.error);
                }
            }
        }
        break;
    }
};

LineParallel.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || isNull(this.entity) ||
        !isNumber(this.distance) || !isNumber(this.number) ||
        !isShape(this.shape)) {

        return undefined;
    }

    var parallels = ShapeAlgorithms.getOffsetShapes(this.shape, this.distance, this.number, this.pos);
    if (!preview) {
        this.error = ShapeAlgorithms.error;
    }

    if (isNull(parallels)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    for (var i=0; i<parallels.length; ++i) {
        op.addObject(shapeToEntity(this.getDocument(), parallels[i]));
    }
    return op;
};

LineParallel.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

LineParallel.prototype.slotDistanceChanged = function(value) {
    this.distance = value;
    this.updatePreview(true);
};

LineParallel.prototype.slotNumberChanged  = function(value) {
    this.number = value;
    this.updatePreview(true);
};

