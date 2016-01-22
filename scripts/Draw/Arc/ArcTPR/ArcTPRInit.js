function init(basePath) {
    var action = new RGuiAction(qsTranslate("ArcTPR", "&Tangent, Point, Radius"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ArcTPR.js");
    action.setIcon(basePath + "/ArcTPR.svg");
    action.setStatusTip(qsTranslate("ArcTPR", "Draw arc tangential to entity, through point with radius"));
    action.setDefaultShortcut(new QKeySequence("a,t"));
    action.setDefaultCommands(["arctangentpointradius", "at"]);
    action.setGroupSortOrder(7400);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawArcMenu", "ArcToolBar", "ArcToolsPanel", "ArcMatrixPanel"]);
}
