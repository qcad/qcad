function init(basePath) {
    var action = new RGuiAction(qsTranslate("Cut", "&Cut"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Cut.js");
    action.setIcon(basePath + "/Cut.svg");
    action.setDefaultShortcuts([
        new QKeySequence(QKeySequence.Cut),
        new QKeySequence("c,t")
    ]);
    action.setDefaultCommands(["cut", "ct"]);
    action.setNoState();
    action.setGroupSortOrder(2300);
    action.setSortOrder(100);
    action.setWidgetNames(["EditMenu", "EditToolBar", "EditToolsPanel"]);
}
