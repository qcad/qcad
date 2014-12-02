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

include("../LineParallel/LineParallel.js");

/**
 * \class LineParallelThrough
 * \brief Line parallel through position.
 * \ingroup ecma_draw_line
 */
function LineParallelThrough(guiAction) {
    LineParallel.call(this, guiAction);

    this.entity = undefined;
    this.shape = undefined;
    this.distance = undefined;

    if (!isNull(guiAction)) {
        this.setUiOptions(["../Line.ui", "LineParallelThrough.ui"]);
    }
}

LineParallelThrough.prototype = new LineParallel();

LineParallelThrough.State = {
    ChoosingEntity : 0,
    SettingPos : 1
};

LineParallelThrough.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineParallelThrough.State.ChoosingEntity);
};

LineParallelThrough.prototype.initState = function() {
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineParallelThrough.State.ChoosingEntity:
        this.entity = undefined;
        this.shape = undefined;
        this.distance = undefined;
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.setLeftMouseTip(qsTr("Choose line, arc or circle"));
        this.setRightMouseTip(EAction.trCancel);
        this.showAppropriateTools();
        break;
    case LineParallelThrough.State.SettingPos:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.setLeftMouseTip(qsTr("Specify point"));
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;
    }
};

LineParallelThrough.prototype.showAppropriateTools = function() {
    EAction.showLineTools();
};

LineParallelThrough.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineParallelThrough.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    case LineParallelThrough.State.SettingPos:
        this.setState(LineParallelThrough.State.ChoosingEntity);
        break;
    }
};

LineParallelThrough.prototype.pickEntity = function(event, preview) {
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
    case LineParallelThrough.State.ChoosingEntity:
        var shape = entity.getClosestShape(pos);

        if (isLineBasedShape(shape) ||
            isArcShape(shape) ||
            isCircleShape(shape)) {

            this.entity = entity;
            this.shape = shape;

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(LineParallelThrough.State.SettingPos);
            }
        }
        else {
            if (!preview) {
                EAction.warnNotLineArcCircle();
                break;
            }
        }
        break;
    }
};

LineParallelThrough.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case LineParallelThrough.State.SettingPos:
        this.pos = event.getModelPosition();
        this.distance = this.shape.getDistanceTo(this.pos, false);

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
        }
        break;
    }
};


