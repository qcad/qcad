function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapePolygonCP", "Pol&ygon (Center, Corner)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapePolygonCP.js");
    action.setIcon(basePath + "/ShapePolygonCP.svg");
    action.setStatusTip(qsTranslate("ShapePolygonCP", "Draw regular polygon from center and corner point"));
    action.setDefaultShortcuts([new QKeySequence("p,g,1"), new QKeySequence("h,c")]);
    action.setDefaultCommands(["linepolygon", "polygon", "pg1"]);
    action.setGroupSortOrder(11520);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel", "ShapeMatrixPanel"]);
}
