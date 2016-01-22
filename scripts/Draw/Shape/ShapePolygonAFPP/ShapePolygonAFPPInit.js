function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapePolygonAFPP", "Polygo&n (Side, Side)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapePolygonAFPP.js");
    action.setIcon(basePath + "/ShapePolygonAFPP.svg");
    action.setStatusTip(qsTranslate("ShapePolygonAFPP", "Draw regular polygon from middle points of two opposite sides or two opposite corners"));
    action.setDefaultShortcuts([new QKeySequence("p,g,4")]);
    action.setDefaultCommands(["polygonss", "pg4"]);
    action.setGroupSortOrder(11520);
    action.setSortOrder(400);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel", "ShapeMatrixPanel"]);
}
