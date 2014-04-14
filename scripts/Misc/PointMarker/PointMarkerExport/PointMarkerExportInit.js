function init(basePath) {
    if (!hasPlugin("DWG")) {
        return;
    }

    var action = new RGuiAction(qsTranslate("PointMarkerExport", "&Export Point Markers"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointMarkerExport.js");
    action.setIcon(basePath + "/PointMarkerExport.svg");
    action.setStatusTip(qsTranslate("PointMarkerExport", "Export point marker as CSV file"));
    action.setDefaultShortcut(new QKeySequence("p,x"));
    action.setDefaultCommands(["pointmarkerexport"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Point, true, true, true);
}
