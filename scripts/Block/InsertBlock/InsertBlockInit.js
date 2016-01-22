function init(basePath) {
    var action = new RGuiAction(qsTranslate("InsertBlock", "&Insert Block"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InsertBlock.js");
    action.setIcon(basePath + "/InsertBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,i"));
    action.setDefaultCommands(["blockinsert", "minsert", "insert", "bi"]);
    action.setGroupSortOrder(14500);
    action.setSortOrder(100);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
