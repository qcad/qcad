function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectBlockReferences", "&Select Block References"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectBlockReferences.js");
    action.setIcon(basePath + "/SelectBlockReferences.svg");
    action.setDefaultShortcut(new QKeySequence("b,+"));
    action.setDefaultCommands(["blockselect", "selectblock", "b+"]);
    action.setGroupSortOrder(14400);
    action.setSortOrder(100);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
