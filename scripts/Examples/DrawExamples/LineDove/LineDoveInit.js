function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineDove", "&Dovetail joint"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineDove.js");
    action.setIcon(basePath + "/LineDove.svg");
    action.setDefaultShortcut(new QKeySequence("r,v"));
    action.setStatusTip(qsTranslate("LineDove", "Draw a dovetail joint"));
    action.setDefaultCommands(["dovetail"]);
    action.setSortOrder(500);
    EAction.addGuiActionTo(action, DrawExamples, true, true, true, true);
}
