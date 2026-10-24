/**
 * LayerFoldBench.js
 *
 * Benchmark: time required to fold (collapse) / unfold (expand) a parent
 * layer with sub layers in the QCAD Professional layer list, through the
 * same code path the GUI uses (RLayerListProQt.updateItemCollapsed):
 *
 *   - "untyped":  RAddObjectOperation without transaction type
 *                 (current path of the LayerListPro widget)
 *   - "typed":    transaction type RTransaction.LayerCollapseStatusChange
 *                 (optimized path, only run if the enum exists)
 *   - "widget":   the actual QTreeWidget item expand / collapse on the
 *                 LayerListPro widget (fires itemExpanded / itemCollapsed)
 *
 * The script builds its own example drawing:
 *   - parent layer "bench_parent" with N_CHILDREN sub layers
 *     ("bench_parent ... child0", ...)
 *   - N_LINES lines, half spread over the sub layers, half on "bench_static"
 *
 * Run with the full GUI so real scenes / views are attached:
 *
 *   cd qcad/release   (or wherever the app bundle lives)
 *   ./QCAD-Pro.app/Contents/MacOS/QCAD-Pro -allow-multiple-instances \
 *       -exec /abs/path/to/benchmarks/LayerFoldBench.js -quit
 *
 * Results are printed to stderr as lines starting with "BENCH;".
 * PNG snapshots of the first fold/unfold cycle of each scenario are saved
 * next to this script (bench_fold_<scenario>_<state>.png) for correctness
 * comparison across code changes.
 */

// configuration:
var N_LINES = 100000;        // plain line entities (half on sub layers)
var N_CHILDREN = 4;          // number of sub layers of "bench_parent"
var N_CYCLES = 4;            // fold/unfold cycles per scenario

function benchLog(msg) {
    qWarning("BENCH;" + msg);
}

function processAllEvents() {
    // deliver paint / update events:
    for (var i=0; i<4; i++) {
        QCoreApplication.processEvents();
    }
}

function LayerFoldBench() {
}

LayerFoldBench.run = function() {
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
    var sep = RLayer.getHierarchySeparator();

    // create parent layer, sub layers and an independent static layer:
    var op = new RAddObjectsOperation();
    op.addObject(new RLayer(doc, "bench_parent", false, false, new RColor(255,0,0), ltId, RLineweight.Weight025));
    var i;
    for (i=0; i<N_CHILDREN; i++) {
        op.addObject(new RLayer(doc, "bench_parent" + sep + "child" + i, false, false, new RColor(0,0,255), ltId, RLineweight.Weight025));
    }
    op.addObject(new RLayer(doc, "bench_static", false, false, new RColor(0,128,0), ltId, RLineweight.Weight025));
    di.applyOperation(op);

    var childLayerIds = [];
    for (i=0; i<N_CHILDREN; i++) {
        childLayerIds.push(doc.getLayerId("bench_parent" + sep + "child" + i));
    }
    var staticLayerId = doc.getLayerId("bench_static");

    // create plain line entities in model space, half on the sub layers,
    // half on the static layer:
    var t0 = Date.now();
    var modelSpaceId = doc.getModelSpaceBlockId();
    var cols = Math.ceil(Math.sqrt(N_LINES));
    op = new RAddObjectsOperation();
    for (i=0; i<N_LINES; i++) {
        var x = (i % cols) * 10;
        var y = Math.floor(i / cols) * 10;
        var e = new RLineEntity(doc, new RLineData(new RVector(x,y), new RVector(x+8,y+8)));
        if (i % 2 === 0) {
            e.setLayerId(childLayerIds[(i/2) % N_CHILDREN]);
        }
        else {
            e.setLayerId(staticLayerId);
        }
        e.setBlockId(modelSpaceId);
        op.addObject(e, false);
    }
    di.applyOperation(op);

    benchLog("setup;entities=" + N_LINES + ";setupMs=" + (Date.now()-t0));

    di.autoZoom();
    processAllEvents();

    // initial full paint (baseline for repaint cost):
    t0 = Date.now();
    di.regenerateScenes();
    processAllEvents();
    benchLog("fullRegenAndPaint;ms=" + (Date.now()-t0));

    var snapshotDir = new QFileInfo(LayerFoldBench.scriptPath).absolutePath();

    function saveSnapshot(name) {
        try {
            var view = EAction.getGraphicsView();
            if (isNull(view)) {
                return;
            }
            var buffer = view.getBuffer();
            buffer.save(snapshotDir + "/bench_fold_" + name + ".png", "PNG", 50);
        } catch (ex) {
            benchLog("snapshotError=" + ex);
        }
    }

    // same code path as RLayerListProQt.updateItemCollapsed:
    function fold(typed, collapsed) {
        var layer = doc.queryLayer("bench_parent");
        layer.setCollapsed(collapsed);
        var op = new RAddObjectOperation(layer);
        op.setText(collapsed ? "Layer collapsed" : "Layer expanded");
        if (typed) {
            op.setTransactionType(RTransaction.LayerCollapseStatusChange);
        }
        var ta = Date.now();
        di.applyOperation(op);
        var tb = Date.now();
        processAllEvents();
        var tc = Date.now();
        return [tb-ta, tc-tb];
    }

    var typedAvailable = (typeof(RTransaction.LayerCollapseStatusChange)!=="undefined" &&
                          !isNull(RTransaction.LayerCollapseStatusChange));
    benchLog("typedTransactionAvailable=" + typedAvailable);

    var scenarios = [ ["untyped", false] ];
    if (typedAvailable) {
        scenarios.push(["typed", true]);
    }
    for (var s=0; s<scenarios.length; s++) {
        var name = scenarios[s][0];
        var typed = scenarios[s][1];
        for (var c=0; c<N_CYCLES; c++) {
            var rFold = fold(typed, true);
            if (c===0) { saveSnapshot(name + "_folded"); }
            var rUnfold = fold(typed, false);
            if (c===0) { saveSnapshot(name + "_unfolded"); }
            benchLog("scenario=" + name + ";cycle=" + c +
                     ";foldApply=" + rFold[0] + ";foldPaint=" + rFold[1] +
                     ";unfoldApply=" + rUnfold[0] + ";unfoldPaint=" + rUnfold[1]);
        }
    }

    // scenario: the real widget interaction (collapse / expand the tree item),
    // fires itemCollapsed / itemExpanded on the LayerListPro widget:
    try {
        var layerList = appWin.findChild("LayerListPro");
        if (isNull(layerList)) {
            benchLog("error=LayerListPro widget not found");
        }
        else {
            var items = layerList.findItems("bench_parent", Qt.MatchExactly | Qt.MatchRecursive, LayerListPro.colName);
            if (items.length===0) {
                benchLog("error=bench_parent item not found in LayerListPro");
            }
            else {
                var item = items[0];
                for (var c2=0; c2<N_CYCLES; c2++) {
                    var ta = Date.now();
                    item.setExpanded(false);   // fold
                    processAllEvents();
                    var tb = Date.now();
                    if (c2===0) { saveSnapshot("widget_folded"); }
                    item.setExpanded(true);    // unfold
                    processAllEvents();
                    var tc = Date.now();
                    if (c2===0) { saveSnapshot("widget_unfolded"); }
                    benchLog("scenario=widget;cycle=" + c2 +
                             ";foldTotal=" + (tb-ta) + ";unfoldTotal=" + (tc-tb));
                }
            }
        }
    } catch (ex) {
        benchLog("widgetScenarioError=" + ex);
    }

    // undo / redo correctness (collapsed state is stored in an undoable
    // transaction; undo must restore the expanded state):
    var rFold2 = fold(typedAvailable, true);
    var layer = doc.queryLayer("bench_parent");
    benchLog("collapsedAfterFold=" + layer.isCollapsed());
    di.undo();
    processAllEvents();
    layer = doc.queryLayer("bench_parent");
    benchLog("collapsedAfterUndo=" + layer.isCollapsed());
    di.redo();
    processAllEvents();
    layer = doc.queryLayer("bench_parent");
    benchLog("collapsedAfterRedo=" + layer.isCollapsed());
    di.undo();
    processAllEvents();

    // avoid the save confirmation dialog on exit (blocks -quit):
    doc.setModified(false);

    benchLog("done");
};

// remember where this script lives (for snapshots):
LayerFoldBench.scriptPath = LayerFoldBench.includeBasePath;

if (typeof(LayerFoldBench.scriptPath)==="undefined" || isNull(LayerFoldBench.scriptPath)) {
    LayerFoldBench.scriptPath = "/Users/andrew/data/QCAD4/qcad/benchmarks/LayerFoldBench.js";
}

LayerFoldBench.run();
