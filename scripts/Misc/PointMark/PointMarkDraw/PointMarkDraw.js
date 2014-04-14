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

include("../PointMark.js");

/**
 * \class PointMarkDraw
 * \brief Point marker with label (block with block attribute).
 * \ingroup ecma_misc_pointmark
 */
function PointMarkDraw(guiAction) {
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
        this.setUiOptions("PointMarkDraw.ui");
    }
}

PointMarkDraw.State = {
    SettingOrigin : 0,
    SettingPosition : 1
};
PointMarkDraw.labelLayerName = "pt_layer";
PointMarkDraw.dataPath = "libraries/default/Tools/PointMark";

PointMarkDraw.prototype = new EAction();
PointMarkDraw.includeBasePath = includeBasePath;

PointMarkDraw.prototype.beginEvent = function() {
    EAction.prototype.beginEvent.call(this);

    // init benchmark counter:
    this.benchmarkCounter = 1;
    this.pointCounter = 1;
    var doc = this.getDocument();
    var markIds = PointMark.queryAllMarks(doc);
    for (var i=0; i<markIds.length; i++) {
        var id = markIds[i];
        var blockRef = doc.queryEntityDirect(id);
        if (isNull(blockRef)) {
            continue;
        }

        // get benchmark handle as int:
        var handle = PointMark.getBenchmarkHandle(blockRef);
        if (handle===RObject.INVALID_HANDLE) {
            continue;
        }

        // get label:
        var label = PointMark.getMarkerLabel(doc, blockRef.getId());
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
    this.diBM.importFile(PointMarkDraw.dataPath + "/benchmark.dxf");

    // load point symbol:
    this.diPoint = new RDocumentInterface(new RDocument(new RMemoryStorage(), new RSpatialIndexNavel()));
    this.diPoint.importFile(PointMarkDraw.dataPath + "/point.dxf");

    // start with setting the bechmark (origin):
    this.setState(PointMarkDraw.State.SettingOrigin);
};

PointMarkDraw.prototype.setState = function(state) {
    EAction.prototype.setState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case PointMarkDraw.State.SettingOrigin:
        var trPos = qsTr("Benchmark (Origin)");
        this.setCommandPrompt(trPos);
        this.setLeftMouseTip(trPos);
        this.setRightMouseTip(EAction.trCancel);
        break;
    case PointMarkDraw.State.SettingPosition:
        var trPos = qsTr("Position");
        this.setCommandPrompt(trPos);
        this.setLeftMouseTip(trPos);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

PointMarkDraw.prototype.escapeEvent = function() {
    switch (this.state) {
    case PointMarkDraw.State.SettingOrigin:
        EAction.prototype.escapeEvent.call(this);
        break;

    case PointMarkDraw.State.SettingPosition:
        this.setState(PointMarkDraw.State.SettingOrigin);
        break;
    }
};

PointMarkDraw.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    this.pos = event.getModelPosition();
    var op, i, transaction, objIds, objId, obj;

    switch (this.state) {
    case PointMarkDraw.State.SettingOrigin:
        this.benchmarkPos = this.pos;

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

            this.setState(PointMarkDraw.State.SettingPosition);
        }
        break;

    case PointMarkDraw.State.SettingPosition:
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
PointMarkDraw.prototype.updateLabel = function(di, benchmark, preview) {
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

/**
 * \return Complete label for next marker.
 * \param benchmark True for benchmarks (origins).
 * \param preview False for final call (increments counter).
 */
PointMarkDraw.prototype.getLabel = function(benchmark, preview) {
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

PointMarkDraw.prototype.getOperation = function(preview) {
    var op;

    switch (this.state) {
    case PointMarkDraw.State.SettingOrigin:
        this.updateLabel(this.diBM, true, preview);
        op = new RPasteOperation(this.diBM.getDocument());
        break;
    case PointMarkDraw.State.SettingPosition:
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

PointMarkDraw.prototype.slotLabelChanged = function(value) {
    this.updatePreview(true);
};

PointMarkDraw.prototype.slotAutoAppendCounterChanged = function(value) {
    this.autoAppendCounter = value;
    this.updatePreview(true);
};

PointMarkDraw.prototype.slotTextHeightChanged = function(value) {
    this.textHeight = value;
    this.updatePreview(true);
};
