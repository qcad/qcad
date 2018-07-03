function init(basePath) {
    var action = new RGuiAction(qsTranslate("Duplicate", "&Duplicate"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Duplicate.js");
    action.setIcon(basePath + "/Duplicate.svg");
    action.setDefaultShortcut(new QKeySequence("d,p"));
    action.setDefaultCommands(["duplicate", "dp"]);
    action.setNoState();
    action.setGroupSortOrder(2300);
    action.setSortOrder(500);
    action.setWidgetNames(["EditMenu", "!EditToolBar", "EditToolsPanel", "EditMatrixPanel"]);
}
