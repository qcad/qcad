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

include("../PointMarker.js");

/**
 * \class PointMarkerDraw
 * \brief Point marker with label (block with block attribute).
 * \ingroup ecma_misc_pointmarker
 */
function PointMarkerDraw(guiAction) {
    EAction.call(this, guiAction);

    this.label = "";
    this.pos = new RVector(0,0);
    this.benchmarkPos = new RVector(0,0);
    this.benchmarkCounter = -1;
    this.pointCounter = -1;
    this.benchmarkHandle = RObject.INVALID_ID;
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
PointMarkerDraw.labelLayerName = "pt_layer";
PointMarkerDraw.dataPath = "libraries/default/Tools/PointMarker";

PointMarkerDraw.prototype = new EAction();
PointMarkerDraw.includeBasePath = includeBasePath;

PointMarkerDraw.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    // init benchmark counter:
    this.benchmarkCounter = 1;
    this.pointCounter = 1;
    var doc = this.getDocument();
    var markIds = PointMarker.queryAllMarks(doc);
    for (var i=0; i<markIds.length; i++) {
        var id = markIds[i];
        var blockRef = doc.queryEntityDirect(id);
        if (isNull(blockRef)) {
            continue;
        }

        // get handle:
        var handle = blockRef.getCustomProperty("QCAD", "benchmark", undefined);
        if (isNull(handle)) {
            continue;
        }
        handle = parseInt(handle, 16);

        // get label:
        var label = PointMarker.getMarkerLabel(doc, blockRef.getId());
        var matches = label.match(/\d+$/);
        if (matches.length!==1) {
            continue;
        }

        // parse label number:
        var num = parseInt(matches[0]);

        // block ref is a benchmark:
        if (handle===blockRef.getHandle()) {
            // bench mark (refers to itself as benchmark):
            this.benchmarkCounter = Math.max(this.benchmarkCounter, num+1);
        }
//        else {
//            this.pointCounter = Math.max(this.pointCounter, num);
//        }
    }

    // load bench mark:
    this.diBM = new RDocumentInterface(new RDocument(new RMemoryStorage(), new RSpatialIndexNavel()));
    this.diBM.importFile(PointMarkerDraw.dataPath + "/benchmark.dxf");

    // load point symbol:
    this.diPoint = new RDocumentInterface(new RDocument(new RMemoryStorage(), new RSpatialIndexNavel()));
    this.diPoint.importFile(PointMarkerDraw.dataPath + "/point.dxf");

    // start with setting the bechmark (origin):
    this.setState(PointMarkerDraw.State.SettingOrigin);
};

PointMarkerDraw.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case PointMarkerDraw.State.SettingOrigin:
        var trPos = qsTr("Benchmark (Origin)");
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

PointMarkerDraw.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    this.pos = event.getModelPosition();
    var op, i, transaction, objIds, objId, obj;

    switch (this.state) {
    case PointMarkerDraw.State.SettingOrigin:
        this.benchmarkPos = this.pos;
        //this.updateLabel(this.diBM, true, preview);

        // insert bench mark symbol with label:
        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            transaction = di.applyOperation(op);
            di.setRelativeZero(this.pos);

            objIds = transaction.getAffectedObjects();
            for (i=0; i<objIds.length; i++) {
                objId = objIds[i];
                obj = doc.queryObjectDirect(objId);
                if (isBlockReferenceEntity(obj)) {
                    this.benchmarkHandle = "0x" + obj.getHandle().toString(16);
                    // benchmark refers to itself as benchmark:
                    obj.setCustomProperty("QCAD", "benchmark", this.benchmarkHandle);
                }
            }

            this.setState(PointMarkerDraw.State.SettingPosition);
        }
        break;

    case PointMarkerDraw.State.SettingPosition:
        // insert point symbol with label:
        //this.updateLabel(this.diPoint, false, preview);

        // insert point mark:
        if (preview) {
            this.updatePreview();
        }
        else {
            op = this.getOperation(false);
            transaction = di.applyOperation(op);
            objIds = transaction.getAffectedObjects();
            for (i=0; i<objIds.length; i++) {
                objId = objIds[i];
                obj = doc.queryObjectDirect(objId);
                if (isBlockReferenceEntity(obj)) {
                    // point mark refers to benchmark:
                    obj.setCustomProperty("QCAD", "benchmark", this.benchmarkHandle);
                }
            }
        }
        break;
    }
};

/**
 * Finds the block attribute in the given document interface and adjusts its text.
 */
PointMarkerDraw.prototype.updateLabel = function(di, benchmark, preview) {
    var doc = di.getDocument();
    var ids = doc.queryAllEntities();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = doc.queryEntityDirect(id);
        if (isAttributeEntity(entity)) {
            var data = entity.getData();
            data.setText(this.getLabel(benchmark, preview));
            entity.setData(data);
            break;
        }
    }
}

PointMarkerDraw.prototype.getLabel = function(benchmark, preview) {
    var optionsToolBar = EAction.getOptionsToolBar();
    if (isNull(optionsToolBar)) {
        return "";
    }

    var te = optionsToolBar.findChild("Label");
    var ret = te.text;

    if (this.autoAppendCounter) {
        if (benchmark) {
            ret += this.benchmarkCounter;
            if (!preview) {
                this.benchmarkCounter++;
            }
        }
        else {
            ret += this.pointCounter;
            if (!preview) {
                this.pointCounter++;
            }
        }
    }

    return ret;
};

PointMarkerDraw.prototype.getOperation = function(preview) {
    var op;

    switch (this.state) {
    case PointMarkerDraw.State.SettingOrigin:
        this.updateLabel(this.diBM, true, preview);
        op = new RPasteOperation(this.diBM.getDocument());
        break;
    case PointMarkerDraw.State.SettingPosition:
        this.updateLabel(this.diPoint, true, preview);
        op = new RPasteOperation(this.diPoint.getDocument());
        break;
    default:
        return undefined;
    }

    op.setOffset(this.pos);
    op.setOverwriteBlocks(false);

    return op;
};

PointMarkerDraw.prototype.slotLabelChanged = function(value) {
    this.updatePreview(true);
};

PointMarkerDraw.prototype.slotAutoAppendCounterChanged = function(value) {
    this.autoAppendCounter = value;
    this.updatePreview(true);
};

PointMarkerDraw.prototype.slotTextHeightChanged = function(value) {
    this.textHeight = value;
    this.updatePreview(true);
};
