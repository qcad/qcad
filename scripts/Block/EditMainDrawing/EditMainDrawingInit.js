function init(basePath) {
    var action = new RGuiAction(qsTranslate("EditMainDrawing", "&Return to Main Drawing"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EditMainDrawing.js");
    action.setDefaultShortcut(new QKeySequence("e,m"));
    action.setDefaultCommands(["editmain","em"]);
    action.setIcon(basePath + "/EditMainDrawing.svg");
    action.setGroupSortOrder(14350);
    action.setSortOrder(500);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
