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
 * \class PointMarkerDraw
 * \brief Point marker with label (block with block attribute)).
 * \ingroup ecma_draw_point
 */
function PointMarkerDraw(guiAction) {
    EAction.call(this, guiAction);

    this.label = "";
    this.benchmark = new RVector(0,0);
    this.benchmarkName = "";
    this.autoAppendCounter = true;
    this.textHeight = 10;

    if (!isNull(guiAction)) {
        this.setUiOptions("PointMarkerDraw.ui");
    }
}

PointMarkerDraw.State = {
    SettingOrigin : 0,
    SettingPosition : 1
};
//PointMarkerDraw.labelBlockName = "qcad_point_label";
PointMarkerDraw.labelLayerName = "qcad_point_label";
PointMarkerDraw.dataPath = "libraries/default/Tools/PointMarker";

PointMarkerDraw.prototype = new EAction();
PointMarkerDraw.includeBasePath = includeBasePath;

PointMarkerDraw.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    // load bench mark:
    this.diBM = new RDocumentInterface(new RDocument(new RMemoryStorage(), new RSpatialIndexNavel()));
    this.diBM.importFile(PointMarkerDraw.dataPath + "/benchmark.dxf");

    // load point symbol:
    this.diPoint = new RDocumentInterface(new RDocument(new RMemoryStorage(), new RSpatialIndexNavel()));
    this.diPoint.importFile(PointMarkerDraw.dataPath + "/point.dxf");

//    // fill block definition:
//    var op = new RAddObjectsOperation();

//    // point:
//    var point = new RPointEntity(this.docBlock, new RPointData(new RVector(0,0)));
//    op.addObject(point);

//    // text label:
//    var attDef = new RAttributeDefinitionEntity(
//        this.docBlock,
//        new RAttributeDefinitionData(
//            this.getTextData(""),
//            "label",                 // tag
//            "Label"                  // prompt
//        )
//    );
//    op.addObject(attDef);
//    this.diBlock.applyOperation(op);

    this.setState(PointMarkerDraw.State.SettingOrigin);
};

PointMarkerDraw.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case PointMarkerDraw.State.SettingOrigin:
        var trPos = qsTr("Origin");
        this.setCommandPrompt(trPos);
        this.setLeftMouseTip(trPos);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case PointMarkerDraw.State.SettingPosition:
        var trPos = qsTr("Position");
        this.setCommandPrompt(trPos);
        this.setLeftMouseTip(trPos);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

PointMarkerDraw.prototype.escapeEvent = function() {
    switch (this.state) {
    case PointMarkerDraw.State.SettingOrigin:
        EAction.prototype.escapeEvent.call(this);
        break;

    case PointMarkerDraw.State.SettingPosition:
        this.setState(PointMarkerDraw.State.SettingOrigin);
        break;
    }
};

//PointMarkerDraw.prototype.coordinateEvent = function(event) {
PointMarkerDraw.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var pos = event.getModelPosition();
    var op;

    switch (this.state) {
    case PointMarkerDraw.State.SettingOrigin:
        this.benchmark = pos;
        //this.updateLabel(this.diBM);
        this.benchmarkName = this.getLabel();

        // insert bench mark symbol with label:
        op = new RPasteOperation(this.diBM.getDocument());
        op.setAttribute("label", this.benchmarkName);
        op.setOffset(pos);
        //op.setBlockName("_benchmark");
        op.setOverwriteBlocks(false);
        if (preview) {
            di.previewOperation(op);
        }
        else {
            di.applyOperation(op);
            di.setRelativeZero(pos);
            this.setState(PointMarkerDraw.State.SettingPosition);
        }
        break;

    case PointMarkerDraw.State.SettingPosition:
        // insert point symbol with label:
        //this.updateLabel(this.diPoint);

        // set custom property that points to benchmark:
        var ids = doc.queryAllEntities();
        for (var i=0; i<ids.length; i++) {
            var id = ids[i];
            var entity = doc.queryEntityDirect(id);
            if (isBlockReferenceEntity(entity)) {
//                var data = entity.getData();
//                data.setText(this.label);
//                entity.setData(data);
                entity.setCustomProperty("QCAD", "benchmark", this.benchmarkName);
                break;
            }
        }

        // insert point mark:
        op = new RPasteOperation(this.diPoint.getDocument());
        op.setAttribute("label", this.getLabel());
        op.setOffset(pos);
        //op.setBlockName("_point");
        op.setOverwriteBlocks(false);
        if (preview) {
            di.previewOperation(op);
        }
        else {
            di.applyOperation(op);
            // leave relative zero at origin
            //var blockRef = doc.queryEntity(doc.getStorage().getMaxObjectId());
            //if (!isNull(blockRef)) {
                //blockRef.setCustomProperty("QCAD", "benchmark", this.benchmarkName);
                //op = new RAddObjectOperation(blockRef);
            //}
        }
        break;
    }


//    operation.setOffset(event.getModelPosition());
//    if (!isNull(this.blockName)) {
//        operation.setBlockName(this.blockName);
//    }
//    operation.setScale(this.scale);
//    operation.setRotation(this.rotation);
//    operation.setFlipHorizontal(this.flipHorizontal);
//    operation.setFlipVertical(this.flipVertical);
//    operation.setToCurrentLayer(this.toCurrentLayer);
//    operation.setOverwriteLayers(this.overwriteLayers);
//    operation.setOverwriteBlocks(this.overwriteBlocks);

    // add block if it does not exists already:
    //var block = this.addBlockDefinition();
    //var blockId = doc.getBlockId(PointMarkerDraw.labelBlockName);

    //if (blockId===RObject.INVALID_ID) {
    //    return;
    //}

    // add block reference:
//    var op = new RAddObjectsOperation();
//    var blockRef = new RBlockReferenceEntity(
//        doc,
//        new RBlockReferenceData(
//            blockId,
//            pos,
//            new RVector(1,1),
//            0
//        )
//    );
//    op.addObject(blockRef);

//    var blockRefId = doc.getStorage().getMaxObjectId();

    // add block attribute:
//    var att = new RAttributeEntity(
//        doc,
//        new RAttributeData(this.getTextData(this.label), blockRefId, "label")
//    );
//    blockRef.applyTransformationTo(att);

    // assign values to attributes:
    //att.setText(this.label);
//    op.addObject(att);

//    di.applyOperation(op);
};

/**
 * Finds the block attribute in the
 */
//PointMarkerDraw.prototype.updateLabel = function(di) {
//    var doc = di.getDocument();
//    var ids = doc.queryAllEntities();
//    for (var i=0; i<ids.length; i++) {
//        var id = ids[i];
//        var entity = doc.queryEntityDirect(id);
//        if (isTextEntity(entity)) {
//            var data = entity.getData();
//            data.setText(this.label);
//            entity.setData(data);
//            break;
//        }
//    }
//}

PointMarkerDraw.prototype.getLabel = function() {
    var ret = this.label;
    if (this.autoAppendCounter) {
        ret += "01";
    }
    return ret;
};

PointMarkerDraw.prototype.getOperation = function(preview) {
    return undefined;

    var op = new RPasteOperation(this.docBlock);

    op.setOffset(event.getModelPosition());
    //if (!isNull(this.blockName)) {
        op.setBlockName(PointMarkerDraw.labelBlockName);
    //}
//    op.setScale(this.scale);
//    op.setRotation(this.rotation);
//    op.setFlipHorizontal(this.flipHorizontal);
//    op.setFlipVertical(this.flipVertical);
//    op.setToCurrentLayer(this.toCurrentLayer);
//    op.setOverwriteLayers(this.overwriteLayers);
//    op.setOverwriteBlocks(this.overwriteBlocks);

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
            op.setAttribute(tag, this.attributes[tag]);
        }
    }

    return op;
};

/*
PointMarkerDraw.prototype.addBlockDefinition = function(di) {
    var op;
    //var di = this.getDocumentInterface();
    //var doc = this.getDocument();
    var doc = di.getDocument();

    var block = doc.queryBlock(PointMarkerDraw.labelBlockName);
    if (!isNull(block)) {
        return block;
    }

    // create block definition:
    block = new RBlock(doc, PointMarkerDraw.labelBlockName, new RVector(0,0));
    op = new RAddObjectOperation(block);
    di.applyOperation(op);

    var previousBlockName = doc.queryCurrentBlock().getName();

    // activate new block definition:
    di.setCurrentBlock(PointMarkerDraw.labelBlockName);

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
*/

PointMarkerDraw.prototype.getTextData = function(label) {
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

PointMarkerDraw.prototype.slotLabelChanged = function(value) {
    this.label = value;
    //this.updatePreview(true);
};

PointMarkerDraw.prototype.slotAutoAppendCounterChanged = function(value) {
    this.autoAppendCounter = value;
    //this.updatePreview(true);
};

PointMarkerDraw.prototype.slotTextHeightChanged = function(value) {
    this.textHeight = value;
    //this.updatePreview(true);
};
