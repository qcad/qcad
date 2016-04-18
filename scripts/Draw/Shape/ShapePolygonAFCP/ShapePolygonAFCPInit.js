function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapePolygonAFCP", "Pol&ygon (Center, Side)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapePolygonAFCP.js");
    action.setIcon(basePath + "/ShapePolygonAFCP.svg");
    action.setStatusTip(qsTranslate("ShapePolygonAFCP", "Draw regular polygon from center and middle point of side"));
    action.setDefaultShortcuts([new QKeySequence("p,g,3")]);
    action.setDefaultCommands(["polygoncs", "pg3"]);
    action.setGroupSortOrder(11520);
    action.setSortOrder(300);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel", "ShapeMatrixPanel"]);
}
