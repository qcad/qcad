function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapePolygonCP", "Pol&ygon (Center, Point)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapePolygonCP.js");
    action.setIcon(basePath + "/ShapePolygonCP.svg");
    action.setStatusTip(qsTranslate("ShapePolygonCP", "Draw regular polygon from center and corner point"));
    action.setDefaultShortcut(new QKeySequence("p,g,1"));
    action.setDefaultCommands(["linepolygon", "polygon", "pg1"]);
    action.setGroupSortOrder(6700);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel"]);
}
