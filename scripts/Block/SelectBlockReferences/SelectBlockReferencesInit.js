function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectBlockReferences", "&Select Block References"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectBlockReferences.js");
    action.setDefaultShortcuts([
                            new QKeySequence("b,k")
                        ]);
    action.setDefaultCommands(["blockselect", "selectblock", "bk"]);
    action.setGroupSortOrder(14400);
    action.setSortOrder(100);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
