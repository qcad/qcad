function init(basePath) {
    var action = new RGuiAction(qsTranslate("Paste", "&Paste"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setAllowInterrupt();
    action.setScriptFile(basePath + "/Paste.js");
    action.setIcon(basePath + "/Paste.svg");
    action.setDefaultShortcuts([
        new QKeySequence(QKeySequence.Paste),
        new QKeySequence("p,s")
    ]);
    action.setDefaultCommands(["paste", "ps"]);
    action.setGroupSortOrder(2300);
    action.setSortOrder(300);
    action.setWidgetNames(["EditMenu", "EditToolBar", "EditToolsPanel", "EditMatrixPanel"]);
}
