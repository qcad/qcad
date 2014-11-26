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

include("../Edit.js");

/**
 * \class Paste
 * \brief Pastes the clipboard contents into the centawin.
 * The target point is specified by the user.
 * \ingroup ecma_edit
 */
function Paste(guiAction) {
    Edit.call(this, guiAction);
    this.setUiOptions("Paste.ui");

    this.offset = new RVector(0,0);
    this.scale = 1.0;
    this.rotation = 0.0;
    this.flipHorizontal = false;
    this.flipVertical = false;
    this.toCurrentLayer = false;
    this.overwriteLayers = false;
    this.overwriteBlocks = false;

    this.State = {
        SettingPosition : 0
    };
}

Paste.prototype = new Edit();

Paste.prototype.beginEvent = function() {
    Edit.prototype.beginEvent.call(this);

    this.di = this.getDocumentInterface();
    this.setState(this.State.SettingPosition);
};

Paste.prototype.initUiOptions = function(resume, optionsToolBar) {
    Edit.prototype.initUiOptions.call(this, resume, optionsToolBar);
    //var optionsToolBar = EAction.getOptionsToolBar();

    var combo = optionsToolBar.findChild("Scale");
    combo.setCompleter(null);
    combo = optionsToolBar.findChild("Rotation");
    combo.setCompleter(null);
};

Paste.prototype.setState = function(state) {
    Edit.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.di.setClickMode(RAction.PickCoordinate);
    var appWin = RMainWindowQt.getMainWindow();
    var trPosition = qsTr("Position");
    this.setCommandPrompt(trPosition);
    this.setLeftMouseTip(trPosition);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

Paste.prototype.pickCoordinate = function(event, preview) {
    this.offset = event.getModelPosition();
    if (preview) {
        this.updatePreview();
    }
    else {
        this.di.applyOperation(this.getOperation());
        this.di.clearPreview();
        this.di.repaintViews();
    }
};

Paste.prototype.getOperation = function(preview) {
    var op = new RPasteOperation(RDocument.getClipboard());
    op.setOffset(this.offset);
    op.setScale(this.scale);
    op.setRotation(this.rotation);
    op.setFlipHorizontal(this.flipHorizontal);
    op.setFlipVertical(this.flipVertical);
    op.setToCurrentLayer(this.toCurrentLayer);
    op.setOverwriteLayers(this.overwriteLayers);
    op.setOverwriteBlocks(this.overwriteBlocks);
    return op;
}

Paste.prototype.getAuxPreview = function() {
    var ret = [];
    var unitFactor = RUnit.convert(1.0, RDocument.getClipboard().getUnit(), this.getDocument().getUnit());
    var boundary = this.getOperation().getBoundary(unitFactor);
    ret.push(boundary);
    return ret;
}

Paste.prototype.slotScaleChanged = function(value) {
    var scale = RMath.eval(value);
    if (RMath.getError()==="") {
        this.scale = scale;
    } else {
        this.scale = 1;
    }
};

Paste.prototype.slotRotationChanged = function(value) {
    var rotation = RMath.eval(value);
    if (RMath.getError()==="") {
        this.rotation = RMath.deg2rad(rotation);
    } else {
        this.rotation = 0;
    }
};

Paste.prototype.slotFlipHorizontalChanged = function(value) {
    this.flipHorizontal = value;
};

Paste.prototype.slotFlipVerticalChanged = function(value) {
    this.flipVertical = value;
};

Paste.prototype.slotToCurrentLayerChanged = function(value) {
    this.toCurrentLayer = value;
};

Paste.prototype.slotOverwriteLayersChanged = function(value) {
    this.overwriteLayers = value;
};

Paste.prototype.slotOverwriteBlocksChanged = function(value) {
    this.overwriteBlocks = value;
};

