function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineRectangleSize", "Rectangle with &Size"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineRectangleSize.js");
    action.setIcon(basePath + "/LineRectangleSize.svg");
    action.setDefaultShortcut(new QKeySequence("r,s"));
    action.setStatusTip(qsTranslate("LineRectangleSize", "Draw rectangle with position and size"));
    action.setDefaultCommands(["rectanglesize", "linerectanglesize", "rs"]);
    action.setGroupSortOrder(6200);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel"]);
}
