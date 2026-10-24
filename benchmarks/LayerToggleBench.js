/**
 * LayerToggleBench.js
 *
 * Benchmark: time required to toggle the visibility (off + frozen) of a
 * layer with many entities, through the same code paths the GUI uses:
 *
 *   - "untyped":  RModifyObjectsOperation without transaction type
 *                 (path of scripts/Layer/ToggleLayerVisibility, menu action)
 *   - "typed":    transaction type RTransaction.LayerVisibilityStatusChange
 *                 (path of the LayerListPro widget in QCAD Pro)
 *
 * The script builds its own example drawing:
 *   - N_LINES lines, half on layer "bench_toggle", half on "bench_static"
 *   - N_REFS_TOGGLE references of a block containing lines on "bench_toggle"
 *   - N_REFS_STATIC references of a block containing lines on "bench_static"
 *
 * Run with the full GUI so real scenes / views are attached:
 *
 *   cd qcad/release   (or wherever the app bundle lives)
 *   ./QCAD-Pro.app/Contents/MacOS/QCAD-Pro -allow-multiple-instances \
 *       -exec /abs/path/to/benchmarks/LayerToggleBench.js -quit
 *
 * Results are printed to stderr as lines starting with "BENCH;".
 * PNG snapshots of the first off/on cycle of each scenario are saved
 * next to this script (bench_<scenario>_<state>.png) for correctness
 * comparison across code changes.
 */

// configuration:
var N_LINES = 100000;        // plain line entities (half on toggled layer)
var N_REFS_TOGGLE = 500;     // refs of block with entities on toggled layer
var N_REFS_STATIC = 500;     // refs of block with entities on static layer
var N_BLOCK_LINES = 10;      // lines inside each block definition
var N_CYCLES = 4;            // off/on cycles per scenario

function benchLog(msg) {
    qWarning("BENCH;" + msg);
}

function processAllEvents() {
    // deliver paint / update events:
    for (var i=0; i<4; i++) {
        QCoreApplication.processEvents();
    }
}

function LayerToggleBench() {
}

LayerToggleBench.run = function() {
    var appWin = RMainWindowQt.getMainWindow();

    // fresh document:
    var newAction = RGuiAction.getByScriptFile("scripts/File/NewFile/NewFile.js");
    if (!isNull(newAction)) {
        newAction.slotTrigger();
        processAllEvents();
    }

    var di = EAction.getDocumentInterface();
    var doc = di.getDocument();
    if (isNull(di) || isNull(doc)) {
        benchLog("error=no document interface");
        return;
    }

    var ltId = doc.getLinetypeId("CONTINUOUS");

    // create layers:
    var op = new RAddObjectsOperation();
    op.addObject(new RLayer(doc, "bench_toggle", false, false, new RColor(255,0,0), ltId, RLineweight.Weight025));
    op.addObject(new RLayer(doc, "bench_static", false, false, new RColor(0,128,0), ltId, RLineweight.Weight025));
    di.applyOperation(op);

    var toggleLayerId = doc.getLayerId("bench_toggle");
    var staticLayerId = doc.getLayerId("bench_static");

    // create block definitions:
    var t0 = Date.now();

    var blockToggle = new RBlock(doc, "bench_block_toggle", new RVector(0,0));
    var blockStatic = new RBlock(doc, "bench_block_static", new RVector(0,0));
    op = new RAddObjectsOperation();
    op.addObject(blockToggle);
    op.addObject(blockStatic);
    di.applyOperation(op);

    var blockToggleId = doc.getBlockId("bench_block_toggle");
    var blockStaticId = doc.getBlockId("bench_block_static");

    op = new RAddObjectsOperation();
    var i, e;
    for (i=0; i<N_BLOCK_LINES; i++) {
        e = new RLineEntity(doc, new RLineData(new RVector(0,i), new RVector(5,i)));
        e.setLayerId(toggleLayerId);
        e.setBlockId(blockToggleId);
        op.addObject(e, false);

        e = new RLineEntity(doc, new RLineData(new RVector(0,i), new RVector(5,i)));
        e.setLayerId(staticLayerId);
        e.setBlockId(blockStaticId);
        op.addObject(e, false);
    }
    di.applyOperation(op);

    // create plain line entities in model space:
    var modelSpaceId = doc.getModelSpaceBlockId();
    var cols = Math.ceil(Math.sqrt(N_LINES));
    op = new RAddObjectsOperation();
    for (i=0; i<N_LINES; i++) {
        var x = (i % cols) * 10;
        var y = Math.floor(i / cols) * 10;
        e = new RLineEntity(doc, new RLineData(new RVector(x,y), new RVector(x+8,y+8)));
        e.setLayerId((i % 2 === 0) ? toggleLayerId : staticLayerId);
        e.setBlockId(modelSpaceId);
        op.addObject(e, false);
    }
    di.applyOperation(op);

    // create block references (on static layer, right of the line field):
    op = new RAddObjectsOperation();
    var refX = cols * 10 + 100;
    for (i=0; i<N_REFS_TOGGLE; i++) {
        e = new RBlockReferenceEntity(doc, new RBlockReferenceData(blockToggleId, new RVector(refX, i*15), new RVector(1,1), 0.0));
        e.setLayerId(staticLayerId);
        op.addObject(e, false);
    }
    for (i=0; i<N_REFS_STATIC; i++) {
        e = new RBlockReferenceEntity(doc, new RBlockReferenceData(blockStaticId, new RVector(refX+50, i*15), new RVector(1,1), 0.0));
        e.setLayerId(staticLayerId);
        op.addObject(e, false);
    }
    di.applyOperation(op);

    benchLog("setup;entities=" + (N_LINES + N_REFS_TOGGLE + N_REFS_STATIC) +
             ";setupMs=" + (Date.now()-t0));

    di.autoZoom();
    processAllEvents();

    // initial full paint (baseline for repaint cost):
    t0 = Date.now();
    di.regenerateScenes();
    processAllEvents();
    benchLog("fullRegenAndPaint;ms=" + (Date.now()-t0));

    var snapshotDir = new QFileInfo(LayerToggleBench.scriptPath).absolutePath();

    function saveSnapshot(name) {
        try {
            var view = EAction.getGraphicsView();
            if (isNull(view)) {
                return;
            }
            var buffer = view.getBuffer();
            buffer.save(snapshotDir + "/bench_" + name + ".png", "PNG", 50);
        } catch (ex) {
            benchLog("snapshotError=" + ex);
        }
    }

    function toggle(typed, off) {
        var layer = doc.queryLayer("bench_toggle");
        layer.setFrozen(off);
        layer.setOff(off);
        var op = new RModifyObjectsOperation();
        if (typed) {
            op.setTransactionType(RTransaction.LayerVisibilityStatusChange);
        }
        op.addObject(layer);
        var ta = Date.now();
        di.applyOperation(op);
        var tb = Date.now();
        processAllEvents();
        var tc = Date.now();
        return [tb-ta, tc-tb];
    }

    var scenarios = [ ["untyped", false], ["typed", true] ];
    for (var s=0; s<scenarios.length; s++) {
        var name = scenarios[s][0];
        var typed = scenarios[s][1];
        for (var c=0; c<N_CYCLES; c++) {
            var rOff = toggle(typed, true);
            if (c===0) { saveSnapshot(name + "_off"); }
            var rOn = toggle(typed, false);
            if (c===0) { saveSnapshot(name + "_on"); }
            benchLog("scenario=" + name + ";cycle=" + c +
                     ";offApply=" + rOff[0] + ";offPaint=" + rOff[1] +
                     ";onApply=" + rOn[0] + ";onPaint=" + rOn[1]);
        }
    }

    // scenario 3: the real GUI action (menu / shortcut path),
    // toggles visibility of the current layer:
    di.setCurrentLayer("bench_toggle");
    processAllEvents();
    var toggleAction = RGuiAction.getByScriptFile("scripts/Layer/ToggleLayerVisibility/ToggleLayerVisibility.js");
    if (isNull(toggleAction)) {
        benchLog("error=ToggleLayerVisibility action not found");
    }
    else {
        for (var c2=0; c2<N_CYCLES; c2++) {
            var ta = Date.now();
            toggleAction.slotTrigger();   // off
            processAllEvents();
            var tb = Date.now();
            if (c2===0) { saveSnapshot("action_off"); }
            toggleAction.slotTrigger();   // on
            processAllEvents();
            var tc = Date.now();
            if (c2===0) { saveSnapshot("action_on"); }
            benchLog("scenario=action;cycle=" + c2 +
                     ";offTotal=" + (tb-ta) + ";onTotal=" + (tc-tb));
        }
    }

    // undo / redo correctness for the typed transaction:
    toggleAction.slotTrigger();   // off
    processAllEvents();
    di.undo();                    // should restore "on" state
    processAllEvents();
    saveSnapshot("undo_on");
    di.redo();                    // back to "off" state
    processAllEvents();
    saveSnapshot("redo_off");
    di.undo();                    // leave document in "on" state
    processAllEvents();

    benchLog("done");
};

// remember where this script lives (for snapshots):
LayerToggleBench.scriptPath = LayerToggleBench.includeBasePath;

if (typeof(LayerToggleBench.scriptPath)==="undefined" || isNull(LayerToggleBench.scriptPath)) {
    LayerToggleBench.scriptPath = "/Users/andrew/data/QCAD4/qcad/benchmarks/LayerToggleBench.js";
}

LayerToggleBench.run();
