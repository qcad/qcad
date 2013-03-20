function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineRelativeAngle", "R&elative Angle"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineRelativeAngle.js");
    action.setIcon(basePath + "/LineRelativeAngle.svg");
    action.setStatusTip(qsTranslate("LineRelativeAngle", "Draw line with relative angle to base entity"));
    action.setDefaultShortcut(new QKeySequence("l,r"));
    action.setDefaultCommands(["linerelativeangle", "lr"]);
    action.setSortOrder(1200);
    EAction.addGuiActionTo(action, Line, true, true, true, true);
}
