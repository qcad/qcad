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

include("scripts/File/SvgImport/SvgImport.js");
include("../BlockInsert.js");

/**
 * \class InsertBlockItem
 * \brief Called when a block is inserted from the part library.
 * \ingroup ecma_edit
 */
function InsertBlockItem(guiAction) {
    BlockInsert.call(this, guiAction);
    if (!isNull(guiAction)) {
        this.setUiOptions("InsertBlockItem.ui");
    }

    this.diItem = undefined;
    this.docItem = undefined;

    this.blockName = undefined;
    this.scale = 1.0;
    this.rotation = 0.0;

    this.flipHorizontal = false;
    this.flipVertical = false;
    this.toCurrentLayer = false;
    this.overwriteLayers = false;
    this.overwriteBlocks = false;

    this.attributes = {};
    this.attributeTags = [];
}

InsertBlockItem.State = {
    SettingPosition : 0
};

InsertBlockItem.prototype = new BlockInsert();

InsertBlockItem.prototype.beginEvent = function() {
    // part library item is loaded into this document:
    var ms = new RMemoryStorage();
    var si = new RSpatialIndexNavel();
    this.docItem = new RDocument(ms, si);
    this.diItem = new RDocumentInterface(this.docItem);

    // TODO refactor
    BlockInsert.prototype.beginEvent.call(this);

    var url = this.guiAction.data();
    this.diItem.importUrl(url, false);

    this.blockName = new QFileInfo(url.path()).completeBaseName();

    // fix block name if necessary:
    this.blockName = fixSymbolTableName(this.blockName);

    // invalid block name characters:
    if (isNull(this.blockName)) {
        var doc = this.getDocument();
        var c = 1;
        while (isNull(this.blockName) || doc.hasBlock(this.blockName)) {
            this.blockName = 'block_' + c++;
        }
        EAction.handleUserMessage(qsTr("Adjusted invalid block name to '%1'").arg(this.blockName));
    }

    if (this.docItem.hasBlock(this.blockName)) {
        // 20140520:
        // if the item contains a block with the same name as the file base name,
        // insert without creating a new block:
        this.blockName = undefined;
    }

    // init block attribute inputs to options tool bar:
    // assign values to attributes:
    var first = true;
    var optionsToolBar = EAction.getOptionsToolBar();
    var ids = this.docItem.queryAllEntities();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var attDef = this.docItem.queryEntity(id);
        if (!isAttributeDefinitionEntity(attDef)) {
            continue;
        }

        if (first) {
            this.showAttributeControls(true);
            first = false;
        }

        var tag = attDef.getTag();
        var prompt = attDef.getPrompt();
        var defaultValue = attDef.getEscapedText();

        var tagCombo = optionsToolBar.findChild("AttributeTag");
        tagCombo.addItem(prompt, [tag, defaultValue]);
    }

    this.setState(InsertBlockItem.State.SettingPosition);
};

InsertBlockItem.prototype.initUiOptions = function(resume) {
    BlockInsert.prototype.initUiOptions.call(this, resume);
    var optionsToolBar = EAction.getOptionsToolBar();

    var combo = optionsToolBar.findChild("Scale");
    combo.setCompleter(null);
    combo = optionsToolBar.findChild("Rotation");
    combo.setCompleter(null);
};

InsertBlockItem.prototype.setState = function(state) {
    BlockInsert.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPos = qsTr("Position");
    this.setCommandPrompt(trPos);
    this.setLeftMouseTip(trPos);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

InsertBlockItem.prototype.finishEvent = function() {
    this.diItem.destroy();
    BlockInsert.prototype.finishEvent.call(this);
};

InsertBlockItem.prototype.generate = function() {
    return;
};

InsertBlockItem.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    this.generate();

    var operation = new RPasteOperation(this.docItem);

    operation.setOffset(event.getModelPosition());
    if (!isNull(this.blockName)) {
        operation.setBlockName(this.blockName);
    }
    operation.setScale(this.scale);
    operation.setRotation(this.rotation);
    operation.setFlipHorizontal(this.flipHorizontal);
    operation.setFlipVertical(this.flipVertical);
    operation.setToCurrentLayer(this.toCurrentLayer);
    operation.setOverwriteLayers(this.overwriteLayers);
    operation.setOverwriteBlocks(this.overwriteBlocks);

    // assign values to attributes:
    var ids = this.docItem.queryAllEntities();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var attDef = this.docItem.queryEntity(id);
        if (!isAttributeDefinitionEntity(attDef)) {
            continue;
        }

        var tag = attDef.getTag();
        if (!isNull(this.attributes[tag])) {
            operation.setAttribute(tag, this.attributes[tag]);
        }
    }

    if (preview) {
        di.previewOperation(operation);
    }
    else {
        di.applyOperation(operation);
        di.clearPreview();
        di.repaintViews();
    }
};

//InsertBlockItem.prototype.coordinateEventPreview = function(event) {
//    var di = this.getDocumentInterface();
//    this.operation.setOffset(event.getModelPosition());
//    di.previewOperation(this.operation);
//};

InsertBlockItem.prototype.slotScaleChanged = function(value) {
    var scale = RMath.eval(value);
    if (RMath.getError() === "") {
        this.scale = scale;
    } else {
        this.scale = 1.0;
    }
};

InsertBlockItem.prototype.slotRotationChanged = function(value) {
    var rotation = RMath.eval(value);
    if (RMath.getError() === "") {
        this.rotation = RMath.deg2rad(rotation);
    } else {
        this.rotation = 0.0;
    }
};

InsertBlockItem.prototype.slotFlipHorizontalChanged = function(value) {
    this.flipHorizontal = value;
};

InsertBlockItem.prototype.slotFlipVerticalChanged = function(value) {
    this.flipVertical = value;
};

InsertBlockItem.prototype.slotToCurrentLayerChanged = function(value) {
    this.toCurrentLayer = value;
};

InsertBlockItem.prototype.slotOverwriteLayersChanged = function(value) {
    this.overwriteLayers = value;
};

InsertBlockItem.prototype.slotOverwriteBlocksChanged = function(value) {
    this.overwriteBlocks = value;
};
