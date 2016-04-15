function init(basePath) {
    var action = new RGuiAction(qsTranslate("ZoomIn", "Zoom &In"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ZoomIn.js");
    action.setIcon(basePath + "/ZoomIn.svg");
    action.setDefaultShortcuts([
        new QKeySequence("+"),
        // workaround for Qt 5.5 bug / convenience:
        new QKeySequence("="),
        new QKeySequence(QKeySequence.ZoomIn)
    ]);
    action.setDefaultCommands(["zoomin"]);
    action.setNoState();
    action.setGroupSortOrder(3300);
    action.setSortOrder(100);
    action.setWidgetNames(["ZoomMenu", "ViewToolBar", "ZoomToolsPanel", "ZoomMatrixPanel"]);
}
