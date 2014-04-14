function init(basePath) {
    if (!hasPlugin("DWG")) {
        return;
    }

    var action = new RGuiAction(qsTranslate("PointMarkDraw", "&Point Mark with Label"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointMarkDraw.js");
    action.setIcon(basePath + "/PointMarkDraw.svg");
    action.setStatusTip(qsTranslate("PointMarkDraw", "Draw point mark with label"));
    action.setDefaultShortcut(new QKeySequence("p,k"));
    action.setDefaultCommands(["pointmark"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, PointMark, true, true, true, true);
}
