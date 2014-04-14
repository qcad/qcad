function init(basePath) {
    if (!hasPlugin("DWG")) {
        return;
    }

    var action = new RGuiAction(qsTranslate("PointMarkExport", "&Export Point Marks"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointMarkExport.js");
    action.setIcon(basePath + "/PointMarkExport.svg");
    action.setStatusTip(qsTranslate("PointMarkExport", "Export point mark as CSV file"));
    action.setDefaultShortcut(new QKeySequence("p,x"));
    action.setDefaultCommands(["pointmarkexport"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Point, true, true, true);
}
