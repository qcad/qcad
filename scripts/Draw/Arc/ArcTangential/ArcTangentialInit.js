function init(basePath) {
    var action = new RGuiAction(qsTranslate("ArcTangential", "&Tangentially Connected"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ArcTangential.js");
    action.setIcon(basePath + "/ArcTangential.svg");
    action.setStatusTip(qsTranslate("ArcTangential", "Draw arc tangential to base entity"));
    action.setDefaultShortcut(new QKeySequence("a,n"));
    action.setDefaultCommands(["arctangential", "an"]);
    action.setGroupSortOrder(7400);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawArcMenu", "ArcToolBar", "ArcToolsPanel", "ArcMatrixPanel"]);
}
