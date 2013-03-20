function init(basePath) {
    var action = new RGuiAction(qsTranslate("ArcConcentric", "&Concentric (with Distance)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ArcConcentric.js");
    action.setIcon(basePath + "/ArcConcentric.svg");
    action.setStatusTip(qsTranslate("ArcConcentric", "Draw concentric arc"));
    action.setDefaultShortcut(new QKeySequence("a,c"));
    action.setDefaultCommands(["arcconcentric", "ac"]);
    action.setSortOrder(500);
    EAction.addGuiActionTo(action, Arc, true, true, true, true);
}
