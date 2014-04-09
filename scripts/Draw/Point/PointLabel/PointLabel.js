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

/**
 * \class PointLabel
 * \brief Point marker with label (block with block attribute)).
 * \ingroup ecma_draw_point
 */
function PointLabel(guiAction) {
    EAction.call(this, guiAction);

    this.label = "";

    if (!isNull(guiAction)) {
        this.setUiOptions("PointLabel.ui");
    }
}

PointLabel.State = {
    SettingPosition : 0
};
PointLabel.labelBlockName = "qcad_point_label";

PointLabel.prototype = new EAction();

PointLabel.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    this.setState(PointLabel.State.SettingPosition);
};

PointLabel.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    var trPos = qsTr("Position");
    this.setCommandPrompt(trPos);
    this.setLeftMouseTip(trPos);
    this.setRightMouseTip(EAction.trCancel);
    EAction.showSnapTools();
};

PointLabel.prototype.coordinateEvent = function(event) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var pos = event.getModelPosition();
    di.setRelativeZero(pos);

    // add block if it does not exists already:
    //debugger;
    var block = this.addBlockDefinition();
    var blockId = doc.getBlockId(PointLabel.labelBlockName);

    if (blockId===RObject.INVALID_ID) {
        return;
    }

    // add block reference:
    var op = new RAddObjectsOperation();
    var blockRef = new RBlockReferenceEntity(
        doc,
        new RBlockReferenceData(
            blockId,
            pos,
            new RVector(1,1),
            0
        )
    );
    op.addObject(blockRef);

    var blockRefId = doc.getStorage().getMaxObjectId();

    // add block attribute:
    var att = new RAttributeEntity(
        doc,
        new RAttributeData(this.getTextData(this.label), blockRefId, "label")
    );
    blockRef.applyTransformationTo(att);

    // assign values to attributes:
    //att.setText(this.label);
    op.addObject(att);

    di.applyOperation(op);
};

PointLabel.prototype.addBlockDefinition = function() {
    var op;
    var di = this.getDocumentInterface();
    var doc = this.getDocument();

    var block = doc.queryBlock(PointLabel.labelBlockName);
    if (!isNull(block)) {
        return block;
    }

    // create block definition:
    block = new RBlock(doc, PointLabel.labelBlockName, new RVector(0,0));
    op = new RAddObjectOperation(block);
    di.applyOperation(op);

    var previousBlockName = doc.queryCurrentBlock().getName();

    // activate new block definition:
    di.setCurrentBlock(PointLabel.labelBlockName);

    // fill block definition:
    op = new RAddObjectsOperation();

    // point:
    var point = new RPointEntity(doc, new RPointData(new RVector(0,0)));
    op.addObject(point);

    // text label:
    var attDef = new RAttributeDefinitionEntity(
        doc,
        new RAttributeDefinitionData(
            this.getTextData(""),
            "label",                 // tag
            "Label"                  // prompt
        )
    );
    op.addObject(attDef);
    di.applyOperation(op);

    // switch back to previous block:
    di.setCurrentBlock(previousBlockName);

    return block;
};

PointLabel.prototype.getTextData = function(label) {
    return new RTextBasedData(
        new RVector(0,2),    // position
        new RVector(0,2),    // alignment point
        2.0,                 // height
        100.0,               // text width (ignored for now)
        RS.VAlignBottom,     // alignments
        RS.HAlignCenter,
        RS.LeftToRight,
        RS.Exact,
        1.0,                 // line spacing factor
        label,               // the text
        "Standard",          // font
        false,               // bold
        false,               // italic
        0.0,                 // angle
        true                 // simple text without formatting
    );
};

PointLabel.prototype.slotLabelChanged = function(value) {
    this.label = value;
    //this.updatePreview(true);
};
