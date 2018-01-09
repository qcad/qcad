function init(basePath) {
    var action = new RGuiAction(qsTranslate("Cut", "&Cut"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setAllowInterrupt();
    action.setScriptFile(basePath + "/Cut.js");
    action.setIcon(basePath + "/Cut.svg");
    action.setDefaultShortcuts([
        new QKeySequence(QKeySequence.Cut)
    ]);
    action.setDefaultCommands(["cut"]);
    action.setNoState();
    action.setGroupSortOrder(2300);
    action.setSortOrder(100);
    action.setWidgetNames(["EditMenu", "!EditToolBar", "EditToolsPanel", "EditMatrixPanel"]);
}
