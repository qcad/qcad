function postInit(basePath) {
    var action = new RGuiAction(qsTranslate("Reset", "&Reset / Idle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Reset.js");
    action.setIcon(basePath + "/Reset.svg");
    action.setDefaultShortcut(new QKeySequence("q,q"));
    action.setDefaultCommands(["reset", "qq"]);
    action.setSortOrder(10100);
    EAction.addGuiActionTo(action, Edit, true, false, false);

    var tb = EAction.getToolBar(qsTranslate("Reset", "Reset"), "ResetToolBar");
    action.addToToolBar(tb);
}
