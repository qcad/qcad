function init(basePath) {
    var action = new RGuiAction(qsTranslate("ZoomOut", "Zoom &Out"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ZoomOut.js");
    action.setIcon(basePath + "/ZoomOut.svg");
    action.setDefaultShortcuts([
        new QKeySequence("-"),
        new QKeySequence(QKeySequence.ZoomOut)
    ]);
    action.setDefaultCommands(["zoomout"]);
    action.setNoState();
    action.setGroupSortOrder(3300);
    action.setSortOrder(200);
    action.setWidgetNames(["ZoomMenu", "ViewToolBar", "ZoomToolsPanel", "ZoomMatrixPanel"]);
}
