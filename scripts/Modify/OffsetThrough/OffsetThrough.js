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

include("../Offset/Offset.js");

/**
 * \class OffsetThrough
 * \brief Offset through given position.
 * \ingroup ecma_modify
 */
function OffsetThrough(guiAction) {
    Offset.call(this, guiAction);

    this.entity = undefined;
    this.shape = undefined;
    this.distance = undefined;

    if (!isNull(guiAction)) {
        this.setUiOptions("OffsetThrough.ui");
    }
}

OffsetThrough.prototype = new Offset();

OffsetThrough.State = {
    ChoosingEntity : 0,
    SettingPos : 1
};

OffsetThrough.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(OffsetThrough.State.ChoosingEntity);
};

OffsetThrough.prototype.initState = function() {
    this.setCrosshairCursor();

    var tr;
    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case OffsetThrough.State.ChoosingEntity:
        this.entity = undefined;
        this.shape = undefined;
        this.distance = undefined;
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        tr = this.getLeftMouseTip();
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case OffsetThrough.State.SettingPos:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        tr = qsTr("Specify point");
        this.setLeftMouseTip(tr);
        this.setCommandPrompt(tr);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;
    }
};

OffsetThrough.prototype.escapeEvent = function() {
    switch (this.state) {
    case OffsetThrough.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    case OffsetThrough.State.SettingPos:
        this.setState(OffsetThrough.State.ChoosingEntity);
        break;
    }
};

OffsetThrough.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        this.entity = undefined;
        return;
    }

    switch (this.state) {
    case OffsetThrough.State.ChoosingEntity:
        var shape;
        if (this.segmentMode) {
            //  parallel to polyline segment:
            shape = entity.getClosestSimpleShape(pos);
        }
        else {
            shape = entity.getClosestShape(pos);
        }

        if (this.isShapeSupported(shape)) {
            this.entity = entity;
            this.shape = shape;

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(OffsetThrough.State.SettingPos);
            }
        }
        else {
            if (!preview) {
                this.warnUnsupportedShape();
                break;
            }
        }
        break;
    }
};

OffsetThrough.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case OffsetThrough.State.SettingPos:
        this.pos = event.getModelPosition();
        this.distance = this.getDistance(this.pos, this.shape);

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

OffsetThrough.prototype.getDistance = function(pos, shape) {
    return shape.getDistanceTo(pos, false);
};
