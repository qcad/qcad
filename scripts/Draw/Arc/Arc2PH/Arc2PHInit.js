function init(basePath) {
    var action = new RGuiAction(qsTranslate("Arc2PH", "2 Points and &Height"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Arc2PH.js");
    action.setIcon(basePath + "/Arc2PH.svg");
    action.setStatusTip(qsTranslate("Arc2PH", "Draw arc from 2 points and height"));
    action.setDefaultShortcut(new QKeySequence("a,h"));
    action.setDefaultCommands(["archeight", "ah"]);
    action.setGroupSortOrder(7200);
    action.setSortOrder(400);
    action.setWidgetNames(["DrawArcMenu", "ArcToolBar", "ArcToolsPanel", "ArcMatrixPanel"]);
}
