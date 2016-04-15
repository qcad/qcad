function init(basePath) {
    var action = new RGuiAction(qsTranslate("RemoveBlock", "&Remove Block"), RMainWindowQt.getMainWindow());
    action.setToolTip(qsTranslate("RemoveBlock", "Delete selected block"));
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RemoveBlock.js");
    action.setIcon(basePath + "/RemoveBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,r"));
    action.setDefaultCommands(["blockremove", "br"]);
    action.setGroupSortOrder(14300);
    action.setSortOrder(100);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
