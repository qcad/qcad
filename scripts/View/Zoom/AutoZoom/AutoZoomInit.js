function init(basePath) {
    var action = new RGuiAction(qsTranslate("AutoZoom", "&Auto Zoom"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AutoZoom.js");
    action.setIcon(basePath + "/AutoZoom.svg");
    action.setDefaultShortcut(new QKeySequence("z,a"));
    action.setDefaultCommands(["zoomauto", "za"]);
    action.setNoState();
    action.setGroupSortOrder(3300);
    action.setSortOrder(300);
    action.setWidgetNames(["ZoomMenu", "ViewToolBar", "ZoomToolsPanel", "ZoomMatrixPanel"]);
}
