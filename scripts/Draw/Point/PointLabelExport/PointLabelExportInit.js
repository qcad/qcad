function init(basePath) {
    if (!hasPlugin("DWG")) {
        return;
    }

    var action = new RGuiAction(qsTranslate("PointLabelExport", "&Export Point Markers"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointLabelExport.js");
    action.setIcon(basePath + "/PointLabelExport.svg");
    action.setStatusTip(qsTranslate("PointLabelExport", "Export point marker as CSV file"));
    action.setDefaultShortcut(new QKeySequence("p,x"));
    action.setDefaultCommands(["pointmarkerexport"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Point, true, true, true);
}
