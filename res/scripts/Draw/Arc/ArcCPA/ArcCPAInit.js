function init(basePath) {
    var action = new RGuiAction(qsTranslate("ArcCPA", "&Center, Point, Angles"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ArcCPA.js");
    action.setIcon(basePath + "/ArcCPA.svg");
    action.setStatusTip(qsTranslate("ArcCPA", "Draw arc from center, point on arc and angles"));
    action.setDefaultShortcut(new QKeySequence("a,r"));
    action.setDefaultCommands(["arcc", "ar"]);
    action.setGroupSortOrder(7100);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawArcMenu", "ArcToolBar", "ArcToolsPanel", "ArcMatrixPanel"]);
}
