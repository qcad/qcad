function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseCPP", "&Ellipse (Center, Point, Ratio)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseCPP.js");
    action.setIcon(basePath + "/EllipseCPP.svg");
    action.setStatusTip(qsTranslate("EllipseCPP", "Draw full ellipse from center, major point and ratio"));
    action.setDefaultShortcut(new QKeySequence("e,p"));
    action.setDefaultCommands(["ellipse", "ep"]);
    action.setGroupSortOrder(9100);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel", "EllipseMatrixPanel"]);
}
