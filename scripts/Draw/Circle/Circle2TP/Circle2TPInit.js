function init(basePath) {
    var action = new RGuiAction(qsTranslate("Circle2TP", "Point, 2 Tan&gents"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Circle2TP.js");
    action.setIcon(basePath + "/Circle2TP.svg");
    action.setStatusTip(qsTranslate("Circle2TP", "Draw circle tangential to two entities, through point"));
    action.setDefaultShortcut(new QKeySequence("c,t,2"));
    action.setDefaultCommands(["circletangent2", "ct2"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Circle, true, true, true);
}
