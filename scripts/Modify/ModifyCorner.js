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

include("Modify.js");

/**
 * \class ModifyCorner
 * \brief Base class for modification tools that operate on a corner
 * (Bevel, Round).
 */
function ModifyCorner(guiAction) {
    Modify.call(this, guiAction);

    this.entity1 = undefined;
    this.shape1 = undefined;
    this.pos1 = undefined;

    this.entity2 = undefined;
    this.shape2 = undefined;
    this.pos2 = undefined;

    this.trim = true;
}

ModifyCorner.prototype = new Modify();

ModifyCorner.State = {
    ChoosingEntity1 : 0,
    ChoosingEntity2 : 1
};

ModifyCorner.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(ModifyCorner.State.ChoosingEntity1);
};

ModifyCorner.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickEntity);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ModifyCorner.State.ChoosingEntity1:
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.pos1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.pos2 = undefined;
        var trEntity1 = qsTr("Choose first entity");
        this.setCommandPrompt(trEntity1);
        this.setLeftMouseTip(trEntity1);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ModifyCorner.State.ChoosingEntity2:
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.pos2 = undefined;
        var trEntity2 = qsTr("Choose second entity");
        this.setCommandPrompt(trEntity2);
        this.setLeftMouseTip(trEntity2);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    this.simulateMouseMoveEvent();
};

ModifyCorner.prototype.escapeEvent = function() {
    switch (this.state) {
    case ModifyCorner.State.ChoosingEntity1:
        Modify.prototype.escapeEvent.call(this);
        break;

    case ModifyCorner.State.ChoosingEntity2:
        this.setState(ModifyCorner.State.ChoosingEntity1);
        break;
    }
};

ModifyCorner.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    switch (this.state) {
    case ModifyCorner.State.ChoosingEntity1:
        if (isNull(entity)) {
            this.entity1 = undefined;
            this.shape1 = undefined;
            if (preview) {
                this.updatePreview();
            }
            return;
        }

        var shape = entity.getClosestShape(pos);

        if (isLineBasedShape(shape) ||
            isArcShape(shape) ||
            isCircleShape(shape)) {

            this.entity1 = entity;
            this.shape1 = shape;
            this.pos1 = pos;

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(ModifyCorner.State.ChoosingEntity2);
            }
        }
        else {
            if (!preview) {
                EAction.warnNotLineArcCircle();
            }
        }
        break;

    case ModifyCorner.State.ChoosingEntity2:
        if (isNull(entity)) {
            this.entity2 = undefined;
            this.shape2 = undefined;
            if (preview) {
                this.updatePreview();
            }
            return;
        }

        var shape = entity.getClosestShape(pos);

        if (isLineBasedShape(shape) ||
            isArcShape(shape) ||
            isCircleShape(shape)) {

            this.entity2 = entity;
            this.shape2 = shape;
            this.pos2 = event.getModelPosition();

            if (preview) {
                this.updatePreview();
            }
            else {
                di.applyOperation(this.getOperation(false));

                this.setState(ModifyCorner.State.ChoosingEntity1);
            }
        }
        else {
            this.entity2 = undefined;
            this.shape2 = undefined;
            if (preview) {
                this.updatePreview();
            }
            else {
                EAction.warnNotLineArcCircle();
            }
        }
        break;
    }
};

ModifyCorner.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity1)) {
        ret.push(this.entity1.getId());
    }
    if (isEntity(this.entity2)) {
        ret.push(this.entity2.getId());
    }
    return ret;
};

ModifyCorner.prototype.slotTrimChanged = function(value) {
    this.trim = value;
};
