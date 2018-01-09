function init(basePath) {
    var action = new RGuiAction(qsTranslate("CopyWithReference", "&Copy with Reference"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setAllowInterrupt();
    action.setScriptFile(basePath + "/CopyWithReference.js");
    action.setIcon(basePath + "/CopyWithReference.svg");
    action.setDefaultShortcuts([
        new QKeySequence("Ctrl+Shift+C"),
        new QKeySequence("r,c")
    ]);
    action.setDefaultCommands(["copywithreference", "rc"]);
    action.setGroupSortOrder(2300);
    action.setSortOrder(250);
    action.setWidgetNames(["EditMenu", "EditToolBar", "EditToolsPanel", "EditMatrixPanel"]);
}
