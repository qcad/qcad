function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShapeRectangle", "&Rectangle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShapeRectangle.js");
    action.setIcon(basePath + "/ShapeRectangle.svg");
    action.setDefaultShortcut(new QKeySequence("r,e"));
    action.setStatusTip(qsTranslate("ShapeRectangle", "Draw rectangle from two corners"));
    action.setDefaultCommands(["rectangle", "linerectangle", "rect", "re"]);
    action.setGroupSortOrder(11510);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawShapeMenu", "ShapeToolBar", "ShapeToolsPanel"]);
}
