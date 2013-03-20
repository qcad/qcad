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

include("../Block.js");
 

/**
 * This action handles the user interaction to insert a block
 * from the block list into the drawing.
 */
function InsertBlock(guiAction) {
    Block.call(this, guiAction);
    this.setUiOptions("InsertBlock.ui");

    this.blockReference = new RBlockReferenceData();
    this.blockReference.setPosition(new RVector(0.0,0.0));
    this.blockReference.setScaleFactors(new RVector(1.0,1.0));
    this.blockReference.setRotation(0.0);
}

InsertBlock.State = {
    SettingPosition : 0
};

InsertBlock.prototype = new Block();

InsertBlock.includeBasePath = includeBasePath;

InsertBlock.prototype.beginEvent = function() {
    Block.prototype.beginEvent.call(this);

    var blockId = Block.getActiveBlockId();
    if (blockId===RBlock.INVALID_ID) {
        this.terminate();
        return;
    }

    this.blockReference.setReferencedBlockId(blockId);

    this.setState(InsertBlock.State.SettingPosition);
};

InsertBlock.prototype.setState = function(state) {
    Block.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPos = qsTr("Position");
    this.setCommandPrompt(trPos);
    this.setLeftMouseTip(trPos);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

InsertBlock.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var pos = event.getModelPosition();

    this.blockReference.setPosition(pos);

    if (preview) {
        di.previewOperation(this.getOperation(true));
    }
    else {
        var op = this.getOperation(false);
        if (!isNull(op)) {
            di.applyOperation(op);
            di.setRelativeZero(pos);
        }
    }
};

InsertBlock.prototype.getOperation = function(preview) {
    var entity = new RBlockReferenceEntity(
        this.getDocument(),
        this.blockReference
    );

    return new RAddObjectOperation(entity);
};

InsertBlock.prototype.slotKeepProportionsChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var scaleYCombo = optionsToolBar.findChild("ScaleY");
    var scaleYLabel = optionsToolBar.findChild("ScaleYLabel");
    var keepProportionsSwitch = optionsToolBar.findChild("KeepProportions");

    if (value===true) {
        scaleYCombo.enabled = false;
        scaleYLabel.enabled = false;
        keepProportionsSwitch.icon = new QIcon(InsertBlock.includeBasePath + "/KeepProportionsOn.svg");
    }
    else {
        scaleYCombo.enabled = true;
        scaleYLabel.enabled = true;
        keepProportionsSwitch.icon = new QIcon(InsertBlock.includeBasePath + "/KeepProportionsOff.svg");
    }
}

InsertBlock.prototype.slotScaleXChanged = function(value) {
    var optionsToolBar = EAction.getOptionsToolBar();
    var keepProportionsSwitch = optionsToolBar.findChild("KeepProportions");
    var keepProportions = keepProportionsSwitch.checked;

    var scaleX = RMath.eval(value);
    if (!RMath.getError().isEmpty()) {
        return;
    }
    var scaleY = this.blockReference.getScaleFactors().y;

    // if keep proportions is checked, adjust y scale proportionally to x scale:
    if (keepProportions) {
        var previousScaleX = this.blockReference.getScaleFactors().x;
        var factor = scaleX / previousScaleX;
        scaleY = scaleY * factor;

        var scaleYCombo = optionsToolBar.findChild("ScaleY");
        scaleYCombo.setEditText("%1".arg(scaleY));
    }

    this.blockReference.setScaleFactors(new RVector(scaleX, scaleY));
};

InsertBlock.prototype.slotScaleYChanged = function(value) {
    var scaleY = RMath.eval(value);
    if (RMath.getError().isEmpty()) {
        this.blockReference.setScaleFactors(new RVector(this.blockReference.getScaleFactors().x, scaleY));
    } else {
        this.blockReference.setScaleFactors(new RVector(this.blockReference.getScaleFactors().x, 1.0));
    }
};

InsertBlock.prototype.slotRotationChanged = function(value) {
    var rotation = RMath.eval(value);
    if (RMath.getError().isEmpty()) {
        this.blockReference.setRotation(RMath.deg2rad(rotation));
    } else {
        this.blockReference.setRotation(0);
    }
};

InsertBlock.prototype.slotFlipHorizontal = function() {
    this.blockReference.flipHorizontal();
    this.updateOptionsToolBar();
};

InsertBlock.prototype.slotFlipVertical = function() {
    this.blockReference.flipVertical();
    this.updateOptionsToolBar();
};

InsertBlock.prototype.updateOptionsToolBar = function() {
    var optionsToolBar = EAction.getOptionsToolBar();

    var rotationCombo = optionsToolBar.findChild("Rotation");
    var scaleXCombo = optionsToolBar.findChild("ScaleX");
    var scaleYCombo = optionsToolBar.findChild("ScaleY");

    rotationCombo.setEditText("%1".arg(RMath.rad2deg(this.blockReference.getRotation())));
    scaleXCombo.setEditText("%1".arg(this.blockReference.getScaleFactors().x));
    scaleYCombo.setEditText("%1".arg(this.blockReference.getScaleFactors().y));
}

