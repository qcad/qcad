function init(basePath) {
    var action = new RGuiAction(qsTranslate("WindowZoom", "&Window Zoom"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/WindowZoom.js");
    action.setIcon(basePath + "/WindowZoom.svg");
    action.setDefaultShortcut(new QKeySequence("z,w"));
    action.setDefaultCommands(["zoomwindow", "zw"]);
    action.setGroupSortOrder(3300);
    action.setSortOrder(600);
    action.setWidgetNames(["ZoomMenu", "ViewToolBar", "ZoomToolsPanel", "ZoomMatrixPanel"]);
}
