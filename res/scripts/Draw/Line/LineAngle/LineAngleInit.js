function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineAngle", "Line from &Angle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineAngle.js");
    action.setIcon(basePath + "/LineAngle.svg");
    action.setStatusTip(qsTranslate("LineAngle", "Draw line at a given absolute angle"));
    action.setDefaultShortcut(new QKeySequence("l,a"));
    action.setDefaultCommands(["lineangle", "la"]);
    action.setGroupSortOrder(6100);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel", "LineMatrixPanel"]);
}
