function init(basePath) {
    var action = new RGuiAction(qsTranslate("RenameBlock", "Re&name Block"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RenameBlock.js");
    action.setIcon(basePath + "/RenameBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,n"));
    action.setDefaultCommands(["blockrename", "bn"]);
    action.setGroupSortOrder(14350);
    action.setSortOrder(200);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
