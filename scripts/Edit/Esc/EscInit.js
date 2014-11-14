function init(basePath) {
    var action = new RGuiAction(qsTranslate("Esc", "&Escape"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Esc.js");
    action.setDefaultShortcut(new QKeySequence("Escape"));
    action.setDefaultCommands(["escape"]);
    action.setOverride();
    action.setNoState();
    action.setGroupSortOrder(2700);
    action.setSortOrder(100);
    action.setWidgetNames(["EditMenu"]);
}
