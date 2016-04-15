function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineVertical", "&Vertical Line"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineVertical.js");
    action.setIcon(basePath + "/LineVertical.svg");
    action.setStatusTip(qsTranslate("LineVertical", "Draw vertical line"));
    action.setDefaultShortcut(new QKeySequence("l,v"));
    action.setDefaultCommands(["linevertical", "lv"]);
    action.setGroupSortOrder(6100);
    action.setSortOrder(400);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel", "LineMatrixPanel"]);
}
