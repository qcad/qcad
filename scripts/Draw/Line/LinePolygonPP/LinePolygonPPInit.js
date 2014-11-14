function init(basePath) {
    var action = new RGuiAction(qsTranslate("LinePolygonPP", "Polygo&n (Two Corners)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LinePolygonPP.js");
    action.setIcon(basePath + "/LinePolygonPP.svg");
    action.setStatusTip(qsTranslate("LinePolygonPP", "Draw regular polygon from two corner points"));
    action.setDefaultShortcut(new QKeySequence("p,g,2"));
    action.setDefaultCommands(["linepolygon2", "polygon2", "pg2"]);
    action.setGroupSortOrder(6700);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel"]);
}
