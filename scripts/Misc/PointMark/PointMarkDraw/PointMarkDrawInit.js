function init(basePath) {
    if (!hasPlugin("DWG")) {
        return;
    }

    var action = new RGuiAction(qsTranslate("PointMarkDraw", "&Add Point Marks"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PointMarkDraw.js");
    action.setIcon(basePath + "/PointMarkDraw.svg");
    action.setStatusTip(qsTranslate("PointMarkDraw", "Draw bench mark and point marks"));
    action.setDefaultShortcut(new QKeySequence("p,k"));
    action.setDefaultCommands(["pointmark"]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, PointMark, true, true, true, true);
}
