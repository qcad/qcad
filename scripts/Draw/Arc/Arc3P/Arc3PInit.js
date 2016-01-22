function init(basePath) {
    var action = new RGuiAction(qsTranslate("Arc3P", "&3 Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Arc3P.js");
    action.setIcon(basePath + "/Arc3P.svg");
    action.setStatusTip(qsTranslate("Arc3P", "Draw arc from 3 points"));
    action.setDefaultShortcut(new QKeySequence("a,3"));
    action.setDefaultCommands(["arc3", "a3"]);
    action.setGroupSortOrder(7250);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawArcMenu", "ArcToolBar", "ArcToolsPanel", "ArcMatrixPanel"]);
}
