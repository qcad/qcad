function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapeRectanglePP", "&Rectangle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapeRectanglePP.js");
    action.setIcon(basePath + "/ShapeRectanglePP.svg");
    action.setDefaultShortcut(new QKeySequence("r,e"));
    action.setStatusTip(qsTranslate("ShapeRectanglePP", "Draw rectangle from two corners"));
    action.setDefaultCommands(["rectangle", "linerectangle", "rect", "re"]);
    action.setGroupSortOrder(11510);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel", "ShapeMatrixPanel"]);
}
