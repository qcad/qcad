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

include("scripts/EAction.js");
include("scripts/ShapeAlgorithms.js");
include("scripts/Draw/Line/Line.js");

/**
 * \class Offset
 * \brief Parallel lines, concentric arcs, circles, equidistant ellipses, splines, polylines.
 * \ingroup ecma_modify
 */
function Offset(guiAction) {
    EAction.call(this, guiAction);

    this.distance = undefined;
    this.number = undefined;
    this.entity = undefined;
    this.shape = undefined;
    this.pos = undefined;
    this.lineType = undefined;

    if (!isNull(guiAction)) {
        this.setUiOptions("Offset.ui");
    }
}

Offset.prototype = new EAction();

Offset.State = {
    ChoosingEntity : 0
};

Offset.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(Offset.State.ChoosingEntity);
};

Offset.prototype.initState = function() {
    EAction.prototype.initState.call(this);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Offset.State.ChoosingEntity:
        this.setLeftMouseTip(qsTr("Choose line, arc, circle or ellipse"));
        break;
    }

    this.setRightMouseTip(EAction.trCancel);
};

Offset.prototype.escapeEvent = function() {
    switch (this.state) {
    case Offset.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    }
};

Offset.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        this.entity = undefined;
        return;
    }

    switch (this.state) {
    case Offset.State.ChoosingEntity:
        var shape = getClosestSimpleShape(entity, pos);

        if (isLineBasedShape(shape) ||
            isArcShape(shape) ||
            isCircleShape(shape) ||
            isEllipseShape(shape)) {

            this.entity = entity;
            this.shape = shape;
            this.pos = pos;
        }
        else {
            if (!preview) {
                EAction.warnNotLineArcCircleEllipse();
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

Offset.prototype.getOperation = function(preview) {
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

    var doc = this.getDocument();
    var e;
    var op = new RAddObjectsOperation();
    op.setText(this.getToolTitle());
    for (var i=0; i<parallels.length; ++i) {
        if (isLineBasedShape(parallels[i]) && !isNull(this.lineType)) {
            e = Line.createLineEntity(doc, parallels[i].getStartPoint(), parallels[i].getEndPoint(), this.lineType);
        }
        else {
            e = shapeToEntity(doc, parallels[i]);
        }

        op.addObject(e);
    }
    return op;
};

Offset.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

Offset.prototype.slotDistanceChanged = function(value) {
    this.distance = value;
    this.updatePreview(true);
};

Offset.prototype.slotNumberChanged  = function(value) {
    this.number = value;
    this.updatePreview(true);
};

