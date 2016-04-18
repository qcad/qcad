function init(basePath) {
    var action = new RGuiAction(qsTranslate("Arc2PL", "&2 Points and Length"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Arc2PL.js");
    action.setIcon(basePath + "/Arc2PL.svg");
    action.setStatusTip(qsTranslate("Arc2PL", "Draw arc from 2 points and length"));
    action.setDefaultShortcut(new QKeySequence("a,l"));
    action.setDefaultCommands(["arclength", "al"]);
    action.setGroupSortOrder(7200);
    action.setSortOrder(300);
    action.setWidgetNames(["DrawArcMenu", "ArcToolBar", "ArcToolsPanel", "ArcMatrixPanel"]);
}
