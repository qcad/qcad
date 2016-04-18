function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShowAllBlocks", "&Show All Blocks"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShowAllBlocks.js");
    action.setIcon(basePath + "/ShowAllBlocks.svg");
    action.setDefaultShortcut(new QKeySequence("b,s"));
    action.setDefaultCommands(["blockshowAll", "bs"]);
    action.setGroupSortOrder(14100);
    action.setSortOrder(200);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
