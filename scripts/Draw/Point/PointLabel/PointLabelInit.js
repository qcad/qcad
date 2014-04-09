function init(basePath) {
    if (!hasPlugin("DWG")) {
        return;
    }

    var action = new RGuiAction(qsTranslate("PointLabel", "&Point Marker with Label"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointLabel.js");
    action.setIcon(basePath + "/PointLabel.svg");
    action.setStatusTip(qsTranslate("PointLabel", "Draw point marker with label"));
    action.setDefaultShortcut(new QKeySequence("p,k"));
    action.setDefaultCommands(["pointmarker"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, Point, true, true, true, true);
}
