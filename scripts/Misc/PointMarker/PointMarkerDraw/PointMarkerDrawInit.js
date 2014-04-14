function init(basePath) {
    if (!hasPlugin("DWG")) {
        return;
    }

    var action = new RGuiAction(qsTranslate("PointMarkerDraw", "&Point Marker with Label"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointMarkerDraw.js");
    action.setIcon(basePath + "/PointMarkerDraw.svg");
    action.setStatusTip(qsTranslate("PointMarkerDraw", "Draw point marker with label"));
    action.setDefaultShortcut(new QKeySequence("p,k"));
    action.setDefaultCommands(["pointmarker"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, PointMarker, true, true, true, true);
}
