function init(basePath) {
    var action = new RGuiAction(qsTranslate("ZoomToSelection", "Zoom to &Selection"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/ZoomToSelection.js");
    action.setIcon(basePath + "/ZoomToSelection.svg");
    action.setDefaultShortcut(new QKeySequence("z,s"));
    action.setDefaultCommands(["zoomselection", "zs"]);
    action.setGroupSortOrder(3300);
    action.setSortOrder(400);
    action.setWidgetNames(["ZoomMenu", "ViewToolBar", "ZoomToolsPanel", "ZoomMatrixPanel"]);
}
