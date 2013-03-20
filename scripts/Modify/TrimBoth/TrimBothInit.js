function init(basePath) {
    var action = new RGuiAction(qsTranslate("TrimBoth", "Trim &Both"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/TrimBoth.js");
    action.setIcon(basePath + "/TrimBoth.svg");
    action.setDefaultShortcut(new QKeySequence("t,m"));
    action.setDefaultCommands(["trim2", "extend2", "tm"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Modify, true, true, true);
}
