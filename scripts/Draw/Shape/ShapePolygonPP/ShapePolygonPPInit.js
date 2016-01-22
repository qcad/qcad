function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapePolygonPP", "Polygo&n (2 Points of Side)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapePolygonPP.js");
    action.setIcon(basePath + "/ShapePolygonPP.svg");
    action.setStatusTip(qsTranslate("ShapePolygonPP", "Draw regular polygon from end points of one side"));
    action.setDefaultShortcuts([new QKeySequence("p,g,2"), new QKeySequence("h,p")]);
    action.setDefaultCommands(["linepolygon2", "polygon2", "pg2"]);
    action.setGroupSortOrder(11520);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel", "ShapeMatrixPanel"]);
}
