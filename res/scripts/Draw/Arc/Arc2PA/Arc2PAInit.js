function init(basePath) {
    var action = new RGuiAction(qsTranslate("Arc2PA", "&2 Points and Angle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Arc2PA.js");
    action.setIcon(basePath + "/Arc2PA.svg");
    action.setStatusTip(qsTranslate("Arc2PA", "Draw arc from 2 points and angle"));
    action.setDefaultShortcut(new QKeySequence("a,2"));
    action.setDefaultCommands(["arc2", "a2"]);
    action.setGroupSortOrder(7200);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawArcMenu", "ArcToolBar", "ArcToolsPanel", "ArcMatrixPanel"]);
}
