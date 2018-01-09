function init(basePath) {
    var action = new RGuiAction(qsTranslate("Delete", "&Delete"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setAllowInterrupt();
    action.setScriptFile(basePath + "/Delete.js");
    action.setIcon(basePath + "/Delete.svg");
    action.setDefaultShortcuts([
       new QKeySequence("Delete"),
       new QKeySequence("Backspace"),
       new QKeySequence("e,r")
    ]);
    action.setDefaultCommands(["delete", "er"]);
    action.setNoState();
    action.setGroupSortOrder(2200);
    action.setSortOrder(100);
    action.setWidgetNames(["EditMenu", "EditToolBar", "EditToolsPanel", "EditMatrixPanel"]);
}
