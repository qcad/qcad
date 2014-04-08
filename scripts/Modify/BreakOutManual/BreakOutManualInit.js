function init(basePath) {
    var action = new RGuiAction(qsTranslate("BreakOutManual", "&Break out Manual"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/BreakOutManual.js");
    action.setIcon(basePath + "/BreakOutManual.svg");
    action.setDefaultShortcut(new QKeySequence("b,2"));
    action.setDefaultCommands(["brk", "b2"]);
    action.setSortOrder(3120);
    EAction.addGuiActionTo(action, Modify, true, true, true);
}
