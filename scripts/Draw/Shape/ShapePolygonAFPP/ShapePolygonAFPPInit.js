function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapePolygonAFPP", "Polygo&n (Side, Side)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapePolygonAFPP.js");
    action.setIcon(basePath + "/ShapePolygonAFPP.svg");
    action.setStatusTip(qsTranslate("ShapePolygonAFPP", "Draw regular polygon from middle points of two sides"));
    action.setDefaultShortcuts([new QKeySequence("p,g,4")]);
    action.setDefaultCommands(["polygonss", "pg4"]);
    action.setGroupSortOrder(11530);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel"]);
}
