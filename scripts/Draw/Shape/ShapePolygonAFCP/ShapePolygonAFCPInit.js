function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapePolygonAFCP", "Pol&ygon (Center, Side)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapePolygonAFCP.js");
    action.setIcon(basePath + "/ShapePolygonAFCP.svg");
    action.setStatusTip(qsTranslate("ShapePolygonAFCP", "Draw regular polygon from center and side"));
    action.setDefaultShortcuts([new QKeySequence("p,g,3")]);
    action.setDefaultCommands(["polygoncs", "pg3"]);
    action.setGroupSortOrder(11530);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel"]);
}
