/**
 * Copyright (c) 2011-2016 by Andrew Mustun. All rights reserved.
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
    this.clickPos1 = undefined;

    this.entity2 = undefined;
    this.shape2 = undefined;
    this.clickPos2 = undefined;

    this.trim = true;

    this.requiresPoint = false;
    this.chooseSolution = false;
    this.posPoint = undefined;
    this.posSolution = undefined;
}

ModifyCorner.prototype = new Modify();

ModifyCorner.State = {
    ChoosingEntity1 : 0,
    ChoosingEntity2 : 1,
    SettingPoint : 2,
    ChoosingSolution : 3
};

ModifyCorner.prototype.beginEvent = function() {
    Modify.prototype.beginEvent.call(this);

    this.setState(ModifyCorner.State.ChoosingEntity1);
};

ModifyCorner.prototype.setState = function(state) {
    Modify.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case ModifyCorner.State.ChoosingEntity1:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.entity1 = undefined;
        this.shape1 = undefined;
        this.clickPos1 = undefined;
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.clickPos2 = undefined;
        this.posSolution = undefined;
        this.posPoint = undefined;
        var trEntity1 = qsTr("Choose first entity");
        this.setCommandPrompt(trEntity1);
        this.setLeftMouseTip(trEntity1);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case ModifyCorner.State.ChoosingEntity2:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.entity2 = undefined;
        this.shape2 = undefined;
        this.clickPos2 = undefined;
        var trEntity2 = qsTr("Choose second entity");
        this.setCommandPrompt(trEntity2);
        this.setLeftMouseTip(trEntity2);
        this.setRightMouseTip(EAction.trBack);
        break;

    case ModifyCorner.State.SettingPoint:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.posSolution = undefined;
        this.posPoint = undefined;
        var trPoint = qsTr("Set point");
        this.setCommandPrompt(trPoint);
        this.setLeftMouseTip(trPoint);
        this.setRightMouseTip(EAction.trBack);
        break;

    case ModifyCorner.State.ChoosingSolution:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.posSolution = undefined;
        var trSolution = qsTr("Choose solution");
        this.setCommandPrompt(trSolution);
        this.setLeftMouseTip(trSolution);
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

    case ModifyCorner.State.SettingPoint:
        this.setState(ModifyCorner.State.ChoosingEntity2);
        break;

    case ModifyCorner.State.ChoosingSolution:
        if (this.requiresPoint) {
            this.setState(ModifyCorner.State.SettingPoint);
        }
        else {
            this.setState(ModifyCorner.State.ChoosingEntity2);
        }
        break;
    }
};

ModifyCorner.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();
    var op;

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

        var shape = entity.getClosestSimpleShape(pos);

        if (this.isShapeSupported(shape)) {

            //qDebug("entity1:", entity);
            //qDebug("entity1:", entity.getId());
            this.entity1 = entity;
            this.shape1 = shape;
            this.clickPos1 = pos;

            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(ModifyCorner.State.ChoosingEntity2);
            }
        }
        else {
            if (!preview) {
                this.warnUnsupportedShape();
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

        var shape = entity.getClosestSimpleShape(pos);

        if (this.isShapeSupported(shape)) {

            this.entity2 = entity;
            this.shape2 = shape;
            this.clickPos2 = event.getModelPosition();

            if (preview) {
                this.updatePreview();
            }
            else {
                if (this.requiresPoint) {
                    this.setState(ModifyCorner.State.SettingPoint);
                }
                else if (this.chooseSolution) {
                    this.setState(ModifyCorner.State.ChoosingSolution);
                }
                else {
                    op = this.getOperation(false);
                    if (!isNull(op)) {
                        di.applyOperation(op);
                        this.setState(ModifyCorner.State.ChoosingEntity1);
                    }
                }
            }
        }
        else {
            this.entity2 = undefined;
            this.shape2 = undefined;
            if (preview) {
                this.updatePreview();
            }
            else {
                this.warnUnsupportedShape();
            }
        }
        break;

    case ModifyCorner.State.ChoosingSolution:
        this.posSolution = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                this.setState(ModifyCorner.State.ChoosingEntity1);
            }
        }
        break;
    }
};

ModifyCorner.prototype.isShapeSupported = function(shape) {
    return isLineBasedShape(shape) || isArcShape(shape) || isCircleShape(shape);
};

ModifyCorner.prototype.warnUnsupportedShape = function() {
    EAction.warnNotLineArcCircle();
};

ModifyCorner.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case ModifyCorner.State.SettingPoint:
        this.posPoint = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            if (this.chooseSolution) {
                this.setState(ModifyCorner.State.ChoosingSolution);
            }
            else {
                var op = this.getOperation(false);
                if (!isNull(op)) {
                    di.applyOperation(op);
                }
                this.setState(ModifyCorner.State.ChoosingEntity1);
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
