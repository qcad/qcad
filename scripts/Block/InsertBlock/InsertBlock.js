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

    this.blockReferenceData = new RBlockReferenceData();
    this.blockReferenceData.setPosition(new RVector(0.0,0.0));
    this.blockReferenceData.setScaleFactors(new RVector(1.0,1.0));
    this.blockReferenceData.setRotation(0.0);
    this.attributes = {};
    this.attributeTags = [];
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

    this.blockReferenceData.setReferencedBlockId(blockId);

    var i, label, edit, sep, a;
    var optionsToolBar = EAction.getOptionsToolBar();

    // hide attribute widgets by default:
//    a = optionsToolBar.findChild("LastSeparator");
//    a.visible = false;
    for (i=1; i<4; i++) {
        label = optionsToolBar.findChild("LabelAttribute%1".arg(i));
        edit = optionsToolBar.findChild("Attribute%1".arg(i));
        label.text = "";
        edit.text = "";

        optionsToolBar.findChild("LabelAttribute%1Action".arg(i)).visible = false;
        optionsToolBar.findChild("Attribute%1Action".arg(i)).visible = false;
        optionsToolBar.findChild("SeparatorAttribute%1Action".arg(i)).visible = false;
    }

    // add block attribute inputs to options tool bar:
    var doc = this.getDocument();
    if (!isNull(doc)) {
        var ids = doc.queryBlockEntities(blockId);
        var idx = 0;
        for (i=0; i<ids.length; i++) {
            var id = ids[i];
            var e = doc.queryEntityDirect(id);
            if (!isAttributeDefinitionEntity(e)) {
                continue;
            }

            var tag = e.getTag();
            var prompt = e.getPrompt();
            var value = e.getEscapedText();

            // show attribute widgets:
            optionsToolBar.findChild("LabelAttribute%1Action".arg(idx+1)).visible = true;
            a = optionsToolBar.findChild("Attribute%1Action".arg(idx+1)).visible = true;
            a = optionsToolBar.findChild("SeparatorAttribute%1Action".arg(idx+1)).visible = true;

            label = optionsToolBar.findChild("LabelAttribute%1".arg(idx+1));
            label.text = prompt;
//            a = optionsToolBar.findChild("LabelAttribute%1Action".arg(idx+1));
//            a.visible = true;

            edit = optionsToolBar.findChild("Attribute%1".arg(idx+1));
            edit.text = value;
            //edit.show();

            // make sure reset button resets to attribute definition default:
            edit.setProperty("defaultValue", value);

            this.attributeTags[idx] = tag;
            idx++;

            // only allow editing of max. 3 attributes in tool bar:
            if (idx>=3) {
                break;
            }
        }
    }

    this.setState(InsertBlock.State.SettingPosition);
};

//InsertBlock.prototype.initUiOptions = function(resume) {
//    var i, label, edit;
//    var optionsToolBar = EAction.getOptionsToolBar();

//    for (i=1; i<4; i++) {
//        label = optionsToolBar.findChild("LabelAttribute%1Action".arg(i));
//        edit = optionsToolBar.findChild("Attribute%1Action".arg(i));
//        label.visible = false;
//        //label.enabled = false;
//        //label.text = "";
//        edit.enabled = false;
//        edit.text = "";
//    }
//};

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

    this.blockReferenceData.setPosition(pos);

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
    var doc = this.getDocument();
    var op = new RAddObjectsOperation();

    var blockRef = new RBlockReferenceEntity(
        doc,
        this.blockReferenceData
    );
    op.addObject(blockRef);
    var blockRefId = doc.getStorage().getMaxObjectId();

    // create attribute for each attribute definition in block:
    if (!isNull(doc)) {
        var blockId = this.blockReferenceData.getReferencedBlockId();
        var ids = doc.queryBlockEntities(blockId);
        for (var i=0; i<ids.length; i++) {
            var id = ids[i];
            var e = doc.queryEntity(id);
            if (!isAttributeDefinitionEntity(e)) {
                continue;
            }
            var att = new RAttributeEntity(
                doc,
                new RAttributeData(e.getData(), blockRefId, e.getTag())
            );
            blockRef.applyTransformationTo(att);

            // assign values to attributes:
            var tag = att.getTag();
            if (!isNull(this.attributes[tag])) {
                att.setText(this.attributes[tag]);
            }

            op.addObject(att);
        }
    }

    return op;
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
    var scaleY = this.blockReferenceData.getScaleFactors().y;

    // if keep proportions is checked, adjust y scale proportionally to x scale:
    if (keepProportions) {
        var previousScaleX = this.blockReferenceData.getScaleFactors().x;
        var factor = scaleX / previousScaleX;
        scaleY = scaleY * factor;

        var scaleYCombo = optionsToolBar.findChild("ScaleY");
        scaleYCombo.setEditText("%1".arg(scaleY));
    }

    this.blockReferenceData.setScaleFactors(new RVector(scaleX, scaleY));
};

InsertBlock.prototype.slotScaleYChanged = function(value) {
    var scaleY = RMath.eval(value);
    if (RMath.getError().isEmpty()) {
        this.blockReferenceData.setScaleFactors(new RVector(this.blockReferenceData.getScaleFactors().x, scaleY));
    } else {
        this.blockReferenceData.setScaleFactors(new RVector(this.blockReferenceData.getScaleFactors().x, 1.0));
    }
};

InsertBlock.prototype.slotRotationChanged = function(value) {
    var rotation = RMath.eval(value);
    if (RMath.getError().isEmpty()) {
        this.blockReferenceData.setRotation(RMath.deg2rad(rotation));
    } else {
        this.blockReferenceData.setRotation(0);
    }
};

InsertBlock.prototype.slotFlipHorizontal = function() {
    this.blockReferenceData.flipHorizontal();
    this.updateOptionsToolBar();
};

InsertBlock.prototype.slotFlipVertical = function() {
    this.blockReferenceData.flipVertical();
    this.updateOptionsToolBar();
};

InsertBlock.prototype.updateOptionsToolBar = function() {
    var optionsToolBar = EAction.getOptionsToolBar();

    var rotationCombo = optionsToolBar.findChild("Rotation");
    var scaleXCombo = optionsToolBar.findChild("ScaleX");
    var scaleYCombo = optionsToolBar.findChild("ScaleY");

    rotationCombo.setEditText("%1".arg(RMath.rad2deg(this.blockReferenceData.getRotation())));
    scaleXCombo.setEditText("%1".arg(this.blockReferenceData.getScaleFactors().x));
    scaleYCombo.setEditText("%1".arg(this.blockReferenceData.getScaleFactors().y));
};

InsertBlock.prototype.slotReset = function() {
    Block.prototype.slotReset.call(this);
    var optionsToolBar = EAction.getOptionsToolBar();
    var scaleYCombo = optionsToolBar.findChild("ScaleY");
    scaleYCombo.setEditText("1");
};

InsertBlock.prototype.slotAttribute1Changed = function(value) {
    if (isNull(this.attributeTags[0])) {
        return;
    }

    this.attributes[this.attributeTags[0]] = value;
    this.updatePreview(true);
};

InsertBlock.prototype.slotAttribute2Changed = function(value) {
    if (isNull(this.attributeTags[1])) {
        return;
    }

    this.attributes[this.attributeTags[1]] = value;
    this.updatePreview(true);
};

