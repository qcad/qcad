function init(basePath) {
    var action = new RGuiAction(qsTranslate("AddBlock", "&Add Empty Block"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AddBlock.js");
    action.setIcon(basePath + "/AddBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,a"));
    action.setDefaultCommands(["blockadd", "ba"]);
    action.setStatusTip(qsTranslate("AddBlock", "Add new empty block"));
    action.setGroupSortOrder(14200);
    action.setSortOrder(100);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
