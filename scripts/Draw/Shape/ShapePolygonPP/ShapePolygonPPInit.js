function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapePolygonPP", "Polygo&n (Two Corners)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapePolygonPP.js");
    action.setIcon(basePath + "/ShapePolygonPP.svg");
    action.setStatusTip(qsTranslate("ShapePolygonPP", "Draw regular polygon from two corner points"));
    action.setDefaultShortcuts([new QKeySequence("p,g,2"), new QKeySequence("h,p")]);
    action.setDefaultCommands(["linepolygon2", "polygon2", "pg2"]);
    action.setGroupSortOrder(11520);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel"]);
}
