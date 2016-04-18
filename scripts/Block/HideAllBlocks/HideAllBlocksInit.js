function init(basePath) {
    var action = new RGuiAction(qsTranslate("HideAllBlocks", "&Hide All Blocks"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/HideAllBlocks.js");
    action.setIcon(basePath + "/HideAllBlocks.svg");
    action.setDefaultShortcut(new QKeySequence("b,h"));
    action.setDefaultCommands(["blockhideAll"]);
    action.setGroupSortOrder(14100);
    action.setSortOrder(300);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
