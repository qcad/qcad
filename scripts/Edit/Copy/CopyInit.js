function init(basePath) {
    var action = new RGuiAction(qsTranslate("Copy", "&Copy"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setAllowInterrupt();
    action.setScriptFile(basePath + "/Copy.js");
    action.setIcon(basePath + "/Copy.svg");
    action.setDefaultShortcuts([
        new QKeySequence(QKeySequence.Copy),
        new QKeySequence("c,p")
    ]);
    action.setDefaultCommands(["copy", "cp"]);
    action.setNoState();
    action.setGroupSortOrder(2300);
    action.setSortOrder(200);
    action.setWidgetNames(["EditMenu", "!EditToolBar", "EditToolsPanel", "EditMatrixPanel"]);
}
