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

include("scripts/Edit/Edit.js");

/**
 * \class Paste
 * \brief Pastes the clipboard contents into the drawing.
 * The target point is specified by the user.
 * \ingroup ecma_edit
 */
function Paste(guiAction) {
    Edit.call(this, guiAction);
    this.setUiOptions(Paste.includeBasePath + "/Paste.ui");

    this.boundary = undefined;
    this.offset = new RVector(0,0);
    this.scale = 1.0;
    this.rotation = 0.0;
    this.flipHorizontal = false;
    this.flipVertical = false;
    this.toCurrentLayer = false;
    this.overwriteLayers = false;
    this.overwriteBlocks = false;
    this.sourceDocument = RDocument.getClipboard();
}

Paste.prototype = new Edit();
Paste.includeBasePath = includeBasePath;

Paste.State = {
    SettingPosition : 0
};

Paste.getPreferencesCategory = function() {
    return [qsTr("Edit"), qsTr("Paste")];
};

Paste.prototype.beginEvent = function() {
    // always reset paste options to defaults:
    if (RSettings.getBoolValue("Paste/ResetOnToolStart", false)===true) {
        RSettings.setValue("Paste/Scale", 1.0, true);
        RSettings.setValue("Paste/Rotation", 0.0, true);
        RSettings.setValue("Paste/FlipHorizontal", false, true);
        RSettings.setValue("Paste/FlipVertical", false, true);
        RSettings.setValue("Paste/OverwriteBlocks", false, true);
        RSettings.setValue("Paste/OverwriteLayers", false, true);
        RSettings.setValue("Paste/ToCurrentLayer", false, true);
    }

    Edit.prototype.beginEvent.call(this);

    this.di = this.getDocumentInterface();
    this.setState(Paste.State.SettingPosition);
};

Paste.prototype.initUiOptions = function(resume, optionsToolBar) {
    Edit.prototype.initUiOptions.call(this, resume, optionsToolBar);

    var combo = optionsToolBar.findChild("Scale");
    if (!isNull(combo)) {
        combo.setCompleter(null);
    }
    combo = optionsToolBar.findChild("Rotation");
    if (!isNull(combo)) {
        combo.setCompleter(null);
    }
};

Paste.prototype.setState = function(state) {
    Edit.prototype.setState.call(this, state);

    if (this.state===Paste.State.SettingPosition) {
        this.setCrosshairCursor();
        this.di.setClickMode(RAction.PickCoordinate);
        var trPosition = qsTr("Position");
        this.setCommandPrompt(trPosition);
        this.setLeftMouseTip(trPosition);
        this.setRightMouseTip(EAction.trCancel);
        EAction.showSnapTools();
    }
};

Paste.prototype.pickCoordinate = function(event, preview) {
    if (this.state===Paste.State.SettingPosition) {
        this.offset = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation();
            if (!isNull(op)) {
                this.di.applyOperation(op);
                this.di.clearPreview();
                this.di.setRelativeZero(this.offset);
                this.di.repaintViews();
                this.postInsertion();
            }
        }
    }
};

/**
 * Called after every insert. Can be used by inheriting classes to increment a
 * counter, preprocess the inserted document, etc.
 */
Paste.prototype.postInsertion = function() {
};

/**
 * Called to perform additional initialization of the RPasteOperation.
 */
Paste.prototype.initOperation = function(op) {
};

Paste.prototype.getOperation = function(preview) {
    if (!isVector(this.offset) || !isNumber(this.scale) || !isNumber(this.rotation)) {
        return undefined;
    }

    var op = new RPasteOperation(this.sourceDocument);
    op.setText(this.getToolTitle());
    op.setOffset(this.offset);
    op.setScale(this.scale);
    op.setRotation(this.rotation);
    op.setFlipHorizontal(this.flipHorizontal);
    op.setFlipVertical(this.flipVertical);
    op.setToCurrentLayer(this.toCurrentLayer);
    op.setOverwriteLayers(this.overwriteLayers);
    op.setOverwriteBlocks(this.overwriteBlocks);
    this.initOperation(op);
    var unitFactor = RUnit.convert(1.0, this.sourceDocument.getUnit(), this.getDocument().getUnit());
    this.boundary = op.getBoundary(unitFactor);
    return op;
};

Paste.prototype.getAuxPreview = function() {
    var ret = [];
    if (!isNull(this.boundary)) {
        ret.push(this.boundary);
    }
    return ret;
};

Paste.prototype.slotScaleChanged = function(value) {
    this.scale = value;
    this.updatePreview(true);
};

Paste.prototype.slotRotationChanged = function(value) {
    this.rotation = value;
    this.updatePreview(true);
};

Paste.prototype.slotFlipHorizontalChanged = function(value) {
    this.flipHorizontal = value;
    this.updatePreview(true);
};

Paste.prototype.slotFlipVerticalChanged = function(value) {
    this.flipVertical = value;
    this.updatePreview(true);
};

Paste.prototype.slotToCurrentLayerChanged = function(value) {
    this.toCurrentLayer = value;
    this.updatePreview(true);
};

Paste.prototype.slotOverwriteLayersChanged = function(value) {
    this.overwriteLayers = value;
    this.updatePreview(true);
};

Paste.prototype.slotOverwriteBlocksChanged = function(value) {
    this.overwriteBlocks = value;
    this.updatePreview(true);
};

