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
include("scripts/sprintf.js");

/**
 * \class PointMarkDraw
 * \brief Point marker with label (block with block attribute).
 * \ingroup ecma_misc_pointmark
 */
function PointMarkDraw(guiAction) {
    EAction.call(this, guiAction);

    this.label = "";
    this.pos = RVector.invalid;
    this.benchmarkPos = new RVector(0,0);
    this.benchmarkCounter = 1;
    this.pointCounter = 1;
    this.benchmarkHandle = RObject.INVALID_ID;
    this.autoAppendCounter = true;
    this.textHeight = 10;
}

PointMarkDraw.State = {
    SettingBenchmarkPosition : 0,
    SettingPointPosition : 1
};
PointMarkDraw.dataPath = "libraries/default/Tools/PointMark";

PointMarkDraw.prototype = new EAction();
PointMarkDraw.includeBasePath = includeBasePath;

PointMarkDraw.prototype.beginEvent = function() {
    // load bench mark:
    this.diBM = new RDocumentInterface(new RDocument(new RMemoryStorage(), new RSpatialIndexNavel()));
    this.diBM.importFile(PointMarkDraw.dataPath + "/benchmark.dxf");

    // load point symbol:
    this.diPoint = new RDocumentInterface(new RDocument(new RMemoryStorage(), new RSpatialIndexNavel()));
    this.diPoint.importFile(PointMarkDraw.dataPath + "/point.dxf");

    var doc = this.getDocument();
    if (isNull(doc)) {
        this.terminate();
        return;
    }

    EAction.prototype.beginEvent.call(this);

    var benchmarkIds = PointMark.queryAllMarkIds(doc, 'b');
    if (benchmarkIds.length===0) {
        // no benchmarks yet, start with adding a benchmark:
        this.setState(PointMarkDraw.State.SettingBenchmarkPosition);
    }
    else {
        var blockRef = doc.queryObjectDirect(benchmarkIds[benchmarkIds.length-1]);
        if (isNull(blockRef) || !isBlockReferenceEntity(blockRef)) {
            this.setState(PointMarkDraw.State.SettingBenchmarkPosition);
        }
        else {
            // got already a benchmark, start with adding points:
            this.benchmarkHandle = blockRef.getHandle();
            this.setState(PointMarkDraw.State.SettingPointPosition);
        }
    }

    //this.showUiOptions();

//    var optionsToolBar = EAction.getOptionsToolBar();
//    if (isNull(optionsToolBar)) {
//        return;
//    }
//    optionsToolBar.findChild("Benchmark").setProperty("Loaded", true);
};

PointMarkDraw.prototype.initUiOptions = function(resume) {
    var dock = PointMark.getDock();
    if (isNull(dock)) {
        return;
    }
    dock.visible = true;

    var optionsToolBar = EAction.getOptionsToolBar();
    if (isNull(optionsToolBar)) {
        return;
    }
    var benchmarkCombo = optionsToolBar.findChild("Benchmark");
    if (isNull(benchmarkCombo)) {
        return;
    }
    benchmarkCombo.blockSignals(true);
    benchmarkCombo.clear();
    //benchmarkCombo.setProperty("Loaded", true);

    var doc = this.getDocument();
    var markIds = PointMark.queryAllMarkIds(doc);
    var i, id, blockRef, handle, label;

    // init benchmark counter and combo box:
    this.benchmarkCounter = 1;
    this.pointCounter = 1;
    for (i=0; i<markIds.length; i++) {
        id = markIds[i];
        blockRef = doc.queryEntityDirect(id);
        if (isNull(blockRef)) {
            continue;
        }

        // get benchmark handle as int:
        handle = PointMark.getBenchmarkHandle(blockRef);
        if (handle===RObject.INVALID_HANDLE) {
            continue;
        }

        // get label:
        label = PointMark.getMarkLabelText(doc, blockRef.getId());

        var matches = label.match(/\d+$/);
        var num;
        if (!isNull(matches) && matches.length===1) {
            // parse label number:
            num = parseInt(matches[0], 10);
        }
        else {
            // no number in label: ignore:
            num = -1;
        }

        // block ref is a benchmark
        // (refers to itself as benchmark):
        if (handle===blockRef.getHandle()) {
            this.benchmarkCounter = Math.max(this.benchmarkCounter, num+1);

            if (benchmarkCombo.findData(handle)===-1) {
                benchmarkCombo.addItem(label, handle);
                benchmarkCombo.model().sort(0);
            }
            continue;
        }

        if (handle!==this.benchmarkHandle) {
            continue;
        }

        // block ref is a point that refers to the selected
        // bench mark:
        this.pointCounter = Math.max(this.pointCounter, num+1);
    }

//    var treeWidget = PointMark.getTreeWidget();
//    if (!isNull(treeWidget)) {
//        for (i=0; i<treeWidget.topLevelItemCount; i++) {
//            var item = treeWidget.topLevelItem(i);
//            if (item.data(0, Qt.UserRole)===this.benchmarkHandle) {
//                treeWidget.setCurrentItem(item);
//            }
//        }
//    }

    benchmarkCombo.currentIndex = benchmarkCombo.findData(this.benchmarkHandle);
    benchmarkCombo.blockSignals(false);
};

PointMarkDraw.prototype.initState = function(state) {
    EAction.prototype.initState.call(this, state);

    this.setCrosshairCursor();
    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);

    var appWin = RMainWindowQt.getMainWindow();

    switch (this.state) {
    case PointMarkDraw.State.SettingBenchmarkPosition:
        this.pointCounter = 1;
        var trBM = qsTr("Benchmark (Origin)");
        this.setCommandPrompt(trBM);
        this.setLeftMouseTip(trBM);
        this.setRightMouseTip(EAction.trCancel);
        this.setUiOptions("PointMarkDrawBenchmark.ui");
        //PointMarkDraw.showBenchmarkLabelControls();
        break;

    case PointMarkDraw.State.SettingPointPosition:
        var trPos = qsTr("Position");
        this.setCommandPrompt(trPos);
        this.setLeftMouseTip(trPos);
        this.setRightMouseTip(EAction.trBack);
        this.setUiOptions("PointMarkDraw.ui");
        //debugger;
        //PointMarkDraw.showPointLabelControls();
        break;
    }

    this.hideUiOptions(true);
    //this.optionWidgetActions = undefined;
    this.showUiOptions();
    this.initUiOptions(false);

    EAction.showSnapTools();
};

PointMarkDraw.prototype.escapeEvent = function() {
    switch (this.state) {
    case PointMarkDraw.State.SettingBenchmarkPosition:
        EAction.prototype.escapeEvent.call(this);
        break;

    case PointMarkDraw.State.SettingPointPosition:
        EAction.prototype.escapeEvent.call(this);
        //this.setState(PointMarkDraw.State.SettingBenchmarkPosition);
        break;
    }
};

PointMarkDraw.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    this.pos = event.getModelPosition();
    var op, i, transaction, objIds, objId, obj;

    switch (this.state) {
    case PointMarkDraw.State.SettingBenchmarkPosition:
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
            //var leader = undefined;
            for (i=0; i<objIds.length; i++) {
                objId = objIds[i];
                obj = doc.queryObjectDirect(objId);
                if (isBlockReferenceEntity(obj) && obj.getBlockId()===doc.getCurrentBlockId()) {
                    // benchmark refers to itself as benchmark:
                    this.benchmarkHandle = obj.getHandle();
                    PointMark.setBenchmarkHandle(obj, this.benchmarkHandle);
                    PointMarkDraw.setBenchmark(obj.getHandle());
                }
                //if (isLeaderEntity(obj)) {
                //}
            }
            //this.linkLeader(doc, objIds);

            // update combo box with possible benchmarks to use as origin:
            this.initUiOptions();
            this.setState(PointMarkDraw.State.SettingPointPosition);
        }
        break;

    case PointMarkDraw.State.SettingPointPosition:
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
                if (isBlockReferenceEntity(obj) && obj.getBlockId()===doc.getCurrentBlockId()) {
                    // point mark refers to benchmark:
                    PointMark.setBenchmarkHandle(obj, this.benchmarkHandle);
                    break;
                }
            }
            //this.linkLeader(doc, objIds);
        }
        break;
    }
};

//PointMarkDraw.prototype.linkLeader = function(doc, objIds) {
//    var objId, obj;
//    var blockRefHandle = undefined;
//    var attributeHandle = undefined;
//    var leader = undefined;

//    for (var i=0; i<objIds.length; i++) {
//        objId = objIds[i];
//        obj = doc.queryObjectDirect(objId);

//        if (isLeaderEntity(obj)) {
//            leader = obj;
//        }

//        if (isBlockReferenceEntity(obj)) {
//            blockRefHandle = obj.getHandle();
//        }
//        if (isAttributeEntity(obj)) {
//            attributeHandle = obj.getHandle();
//        }
//    }

//    if (isNull(leader) || isNull(blockRefHandle) || isNull(attributeHandle)) {
//        return;
//    }

//    PointMark.setFromHandle(leader, attributeHandle);
//    PointMark.setToHandle(leader, blockRefHandle);
//};

/**
 * Finds the block attribute in the given document interface and adjusts its text.
 */
PointMarkDraw.prototype.updateLabel = function(diSrc, benchmark, preview) {
    var doc = this.getDocument();
    var scale = isNull(doc) ? 1.0 : doc.getVariable("PointMarkScale", 1.0);
    if (scale<1.0e-6) {
        scale = 1.0;
    }
    //var labelSize = isNull(doc) ? 1.0 : doc.getVariable("PointMarkLabelSize", 1.0) / scale;

    var docSrc = diSrc.getDocument();
    var ids = docSrc.queryAllEntities();
    for (var i=0; i<ids.length; i++) {
        var id = ids[i];
        var entity = docSrc.queryEntityDirect(id);
        if (isAttributeEntity(entity)) {
            var data = entity.getData();
            data.setText(this.getLabel(benchmark, preview));
            //data.setTextHeight(labelSize);
            entity.setData(data);
            break;
        }
    }
};

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

    var te = optionsToolBar.findChild(benchmark ? "BenchmarkLabel" : "PointLabel");
    if (isNull(te)) {
        return "";
    }

    var ret = te.text;

    if (this.autoAppendCounter) {
        var num = "";
        if (benchmark) {
            //num = sprintf("%03d", this.benchmarkCounter);
            num = this.benchmarkCounter.toString();
            if (!preview) {
                this.benchmarkCounter++;
            }
        }
        else {
            //num = sprintf("%03d", this.pointCounter);
            num = this.pointCounter.toString();
            if (!preview) {
                this.pointCounter++;
            }
        }
        ret += num;
    }

    return ret;
};

/**
 * \return Paste operation for benchmark symbol or point symbol with label.
 */
PointMarkDraw.prototype.getOperation = function(preview) {
    if (!isValidVector(this.pos)) {
        return undefined;
    }
    var doc = this.getDocument();
    if (isNull(doc)) {
        return undefined;
    }

    var op;

    switch (this.state) {
    case PointMarkDraw.State.SettingBenchmarkPosition:
        this.updateLabel(this.diBM, true, preview);
        op = new RPasteOperation(this.diBM.getDocument());
        break;
    case PointMarkDraw.State.SettingPointPosition:
        this.updateLabel(this.diPoint, false, preview);
        op = new RPasteOperation(this.diPoint.getDocument());
        break;
    default:
        return undefined;
    }

    op.setOffset(this.pos);
    op.setOverwriteBlocks(false);
    op.setToCurrentLayer(false);
    // update symbols (TODO):
    //op.setOverwriteBlocks(true);
    op.setScale(doc.getVariable("PointMarkScale", 1.0));
    op.setBlockName(doc.getTempBlockName());
    op.setLayerName("pt_layer");

    return op;
};

PointMarkDraw.prototype.slotPointLabelChanged = function(value) {
    this.updatePreview(true);
};

PointMarkDraw.prototype.slotBenchmarkLabelChanged = function(value) {
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

PointMarkDraw.prototype.slotBenchmarkChanged = function(value) {
    if (value===-1) {
        return;
    }

    var benchmarkCombo = PointMarkDraw.getBenchmarkCombo();
    if (isNull(benchmarkCombo)) {
        return;
    }

    this.benchmarkHandle = benchmarkCombo.itemData(value);
    this.initUiOptions(false);
    this.updatePreview(true);

    // keep selection in tree widget in sync:
    var treeWidget = PointMark.getTreeWidget();
    if (isNull(treeWidget) || !treeWidget.visible) {
        return;
    }

    for (var i=0; i<treeWidget.topLevelItemCount; i++) {
        var item = treeWidget.topLevelItem(i);
        if (item.data(0, Qt.UserRole)!==this.benchmarkHandle) {
            continue;
        }

        treeWidget.blockSignals(true);
        treeWidget.setCurrentItem(item);
        treeWidget.blockSignals(false);
        break;
    }
};

PointMarkDraw.prototype.slotAddBenchmark = function() {
    var benchmarkCombo = PointMarkDraw.getBenchmarkCombo();
    if (isNull(benchmarkCombo)) {
        return;
    }
    benchmarkCombo.currentIndex = -1;

    this.setState(PointMarkDraw.State.SettingBenchmarkPosition);
};

PointMarkDraw.getBenchmarkCombo = function() {
    var optionsToolBar = EAction.getOptionsToolBar();
    if (isNull(optionsToolBar)) {
        return undefined;
    }
    return optionsToolBar.findChild("Benchmark");
};

PointMarkDraw.setBenchmark = function(handle) {
    var benchmarkCombo = PointMarkDraw.getBenchmarkCombo();
    if (isNull(benchmarkCombo)) {
        return;
    }

    var idx = benchmarkCombo.findData(handle);
    if (idx!==-1) {
        benchmarkCombo.currentIndex = idx;
    }
};

PointMarkDraw.getBenchmark = function() {
    var benchmarkCombo = PointMarkDraw.getBenchmarkCombo();
    if (isNull(benchmarkCombo)) {
        return undefined;
    }

    if (benchmarkCombo.currentIndex===-1) {
        return undefined;
    }

    return benchmarkCombo.itemData(benchmarkCombo.currentIndex);
};

//PointMarkDraw.showBenchmarkLabelControls = function() {
//    PointMarkDraw.showControls([/*"SPointLabel",*/ "LPointLabel", "PointLabel"], false);
//    PointMarkDraw.showControls([/*"SBenchmarkLabel",*/ "LBenchmarkLabel", "BenchmarkLabel"], true);
//};

//PointMarkDraw.showPointLabelControls = function() {
//    PointMarkDraw.showControls([/*"SBenchmarkLabel",*/ "LBenchmarkLabel", "BenchmarkLabel"], false);
//    PointMarkDraw.showControls([/*"SPointLabel",*/ "LPointLabel", "PointLabel"], true);
//};

//PointMarkDraw.showControls = function(names, show) {
//    var optionsToolBar = EAction.getOptionsToolBar();
//    if (isNull(optionsToolBar)) {
//        return;
//    }
//    for (var i=0; i<names.length; i++) {
//        var w = optionsToolBar.findChild(names[i]);
//        if (isNull(w)) {
//            debugger;
//            continue;
//        }

//        w.visible = show;
//    }
//};
