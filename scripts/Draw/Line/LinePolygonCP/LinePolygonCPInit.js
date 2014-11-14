function init(basePath) {
    var action = new RGuiAction(qsTranslate("LinePolygonCP", "Pol&ygon (Center, Point)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LinePolygonCP.js");
    action.setIcon(basePath + "/LinePolygonCP.svg");
    action.setStatusTip(qsTranslate("LinePolygonCP", "Draw regular polygon from center and corner point"));
    action.setDefaultShortcut(new QKeySequence("p,g,1"));
    action.setDefaultCommands(["linepolygon", "polygon", "pg1"]);
    action.setGroupSortOrder(6700);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel"]);
}
