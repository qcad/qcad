function init(basePath) {
    var action = new RGuiAction(qsTranslate("Esc", "&Escape"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Esc.js");
    action.setDefaultShortcut(new QKeySequence("Escape"));
    action.setDefaultCommands(["escape"]);
    action.setSortOrder(10000);
    action.setOverride();
    action.setNoState();
    EAction.addGuiActionTo(action, Edit, true, false, false, true);
}
