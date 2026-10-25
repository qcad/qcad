/**
 * QuickMoveBench.js
 *
 * Benchmark: time required to move a large selection with the keyboard
 * arrow keys (Edit > Quick Modify > Move Right, etc.) through the same
 * code paths the GUI uses:
 *
 *   - "op":     di.applyOperation(RMoveSelectionOperation) only
 *               (transaction + scene regen, no GUI event processing)
 *   - "action": the real MoveRight action (slotTrigger) followed by
 *               processing of all pending events (property editor
 *               update, repaint, ...)
 *
 * The script builds its own example drawing of N_LINES lines (+ N_ARCS
 * arcs, N_TEXTS texts, N_HATCHES hatches, N_REFS block references) and
 * selects everything.
 *
 * Correctness checks (PNG snapshots next to this script, compare with cmp):
 *   bench_move_after.png / bench_move_regen.png: view after the moves
 *       (scene translated in place) vs. after a full scene regeneration
 *   bench_move_initial.png / bench_move_undone.png: view before any move
 *       vs. after undoing all moves
 *
 * Run with the full GUI so real scenes / views / widgets are attached:
 *
 *   cd qcad/release
 *   ./QCAD-Pro.app/Contents/MacOS/QCAD-Pro -allow-multiple-instances \
 *       -exec /abs/path/to/benchmarks/QuickMoveBench.js -quit
 *
 * Results are printed to stderr as lines starting with "BENCH;".
 */

var N_LINES = 20000;
var N_ARCS = 2000;
var N_TEXTS = 500;
var N_HATCHES = 50;
var N_REFS = 50;
var N_MOVES = 10;

function benchLog(msg) {
    qWarning("BENCH;" + msg);
}

function processAllEvents() {
    for (var i=0; i<4; i++) {
        QCoreApplication.processEvents();
    }
}

// process events for the given wall clock time (delayed repaints, timers):
function pumpEvents(ms) {
    var t = Date.now();
    while (Date.now()-t < ms) {
        QCoreApplication.processEvents();
    }
}

function QuickMoveBench() {
}

QuickMoveBench.run = function() {
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

    var t0 = Date.now();
    var op = new RAddObjectsOperation();
    var i, e;
    var cols = Math.ceil(Math.sqrt(N_LINES));
    for (i=0; i<N_LINES; i++) {
        var x = (i % cols) * 10;
        var y = Math.floor(i / cols) * 10;
        e = new RLineEntity(doc, new RLineData(new RVector(x,y), new RVector(x+8,y+8)));
        op.addObject(e, false);
    }
    for (i=0; i<N_ARCS; i++) {
        e = new RArcEntity(doc, new RArcData(new RVector(-20 - (i%50)*10, Math.floor(i/50)*10), 3, 0, Math.PI, false));
        op.addObject(e, false);
    }
    for (i=0; i<N_TEXTS; i++) {
        e = new RTextEntity(doc, new RTextData(new RVector((i%50)*10, -20 - Math.floor(i/50)*10), new RVector((i%50)*10, -20 - Math.floor(i/50)*10), 2.0, 5.0, RS.VAlignTop, RS.HAlignLeft, RS.LeftToRight, RS.Exact, 1.0, "T" + i, "Standard", false, false, 0.0, false));
        op.addObject(e, false);
    }
    for (i=0; i<N_HATCHES; i++) {
        var hx = -20 - (i%10)*15;
        var hy = -20 - Math.floor(i/10)*15;
        var hd = new RHatchData(false, 1.0, 0.0, "ANSI31");
        hd.newLoop();
        hd.addBoundary(new RLine(new RVector(hx,hy), new RVector(hx+10,hy)));
        hd.addBoundary(new RLine(new RVector(hx+10,hy), new RVector(hx+10,hy+10)));
        hd.addBoundary(new RLine(new RVector(hx+10,hy+10), new RVector(hx,hy+10)));
        hd.addBoundary(new RLine(new RVector(hx,hy+10), new RVector(hx,hy)));
        e = new RHatchEntity(doc, hd);
        op.addObject(e, false);
    }
    di.applyOperation(op);

    // block with a few lines, referenced N_REFS times:
    op = new RAddObjectsOperation();
    op.addObject(new RBlock(doc, "bench_block", new RVector(0,0)));
    di.applyOperation(op);
    var blockId = doc.getBlockId("bench_block");
    op = new RAddObjectsOperation();
    for (i=0; i<5; i++) {
        e = new RLineEntity(doc, new RLineData(new RVector(0,i), new RVector(5,i)));
        e.setBlockId(blockId);
        op.addObject(e, false);
    }
    di.applyOperation(op);
    op = new RAddObjectsOperation();
    for (i=0; i<N_REFS; i++) {
        e = new RBlockReferenceEntity(doc, new RBlockReferenceData(blockId, new RVector(-200 - (i%10)*10, Math.floor(i/10)*10), new RVector(1,1), 0.0));
        op.addObject(e, false);
    }
    di.applyOperation(op);

    benchLog("setup;entities=" + (N_LINES + N_ARCS + N_TEXTS + N_HATCHES + N_REFS) + ";setupMs=" + (Date.now()-t0));

    di.autoZoom();
    processAllEvents();

    var snapshotDir = new QFileInfo(QuickMoveBench.scriptPath).absolutePath();
    function saveSnapshot(name) {
        pumpEvents(500);
        try {
            // Qt based main view (other views, e.g. 3D views, have no getBuffer):
            var view = EAction.getGraphicsView();
            if (isNull(view) || typeof(view.getBuffer)!=="function") {
                benchLog("snapshotError=no Qt view with focus: " + view);
                return;
            }
            var buffer = view.getBuffer();
            buffer.save(snapshotDir + "/bench_move_" + name + ".png", "PNG", 50);
        } catch (ex) {
            benchLog("snapshotError=" + ex);
        }
    }

    t0 = Date.now();
    di.selectAll();
    processAllEvents();
    benchLog("selectAll;ms=" + (Date.now()-t0));

    var initialBox = doc.getBoundingBox();
    saveSnapshot("initial");

    // scenario 1: operation only:
    var m;
    for (m=0; m<N_MOVES; m++) {
        var mop = new RMoveSelectionOperation(new RVector(0,0), new RVector(1,0));
        mop.setTransactionGroup(-5);
        var ta = Date.now();
        di.applyOperation(mop);
        var tb = Date.now();
        processAllEvents();
        var tc = Date.now();
        benchLog("scenario=op;cycle=" + m + ";apply=" + (tb-ta) + ";events=" + (tc-tb));
    }

    // scenario 2: real action:
    var moveAction = RGuiAction.getByScriptFile("scripts/Pro/Edit/QuickModify/MoveRight/MoveRight.js");
    if (isNull(moveAction)) {
        moveAction = RGuiAction.getByScriptFile(":scripts/Pro/Edit/QuickModify/MoveRight/MoveRight.js");
    }
    if (isNull(moveAction)) {
        benchLog("error=MoveRight action not found");
    }
    else {
        for (m=0; m<N_MOVES; m++) {
            var ta2 = Date.now();
            moveAction.slotTrigger();
            var tb2 = Date.now();
            processAllEvents();
            var tc2 = Date.now();
            benchLog("scenario=action;cycle=" + m + ";trigger=" + (tb2-ta2) + ";events=" + (tc2-tb2));
        }
    }

    // scenario 3: burst of key presses without event processing in between
    // (simulates key auto-repeat faster than the app can keep up):
    if (!isNull(moveAction)) {
        var tb3 = Date.now();
        for (m=0; m<N_MOVES; m++) {
            moveAction.slotTrigger();
        }
        var tm3 = Date.now();
        processAllEvents();
        var te3 = Date.now();
        benchLog("scenario=burst;moves=" + N_MOVES + ";triggers=" + (tm3-tb3) + ";events=" + (te3-tm3) + ";perMove=" + ((te3-tb3)/N_MOVES).toFixed(1));
    }

    // correctness: scene translated in place vs. full regeneration:
    saveSnapshot("after");
    di.regenerateScenes();
    processAllEvents();
    saveSnapshot("regen");

    // undo all moves, view must match the initial view:
    var tu = Date.now();
    var undos = 0;
    while (doc.isUndoAvailable() && !doc.getBoundingBox().equalsFuzzy(initialBox) && undos<1000) {
        di.undo();
        undos++;
    }
    processAllEvents();
    benchLog("undo;count=" + undos + ";ms=" + (Date.now()-tu) + ";boxRestored=" + doc.getBoundingBox().equalsFuzzy(initialBox));
    saveSnapshot("undone");

    doc.setModified(false);
    benchLog("done");
};

// remember where this script lives (for snapshots):
QuickMoveBench.scriptPath = QuickMoveBench.includeBasePath;
if (typeof(QuickMoveBench.scriptPath)==="undefined" || isNull(QuickMoveBench.scriptPath)) {
    QuickMoveBench.scriptPath = "/Users/andrew/data/QCAD4/qcad/benchmarks/QuickMoveBench.js";
}

QuickMoveBench.run();
