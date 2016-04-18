function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapeRectangleSize", "Rectangle with &Size"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapeRectangleSize.js");
    action.setIcon(basePath + "/ShapeRectangleSize.svg");
    action.setDefaultShortcut(new QKeySequence("r,s"));
    action.setStatusTip(qsTranslate("ShapeRectangleSize", "Draw rectangle with position and size"));
    action.setDefaultCommands(["rectanglesize", "linerectanglesize", "rs"]);
    action.setGroupSortOrder(11510);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel", "ShapeMatrixPanel"]);
}
