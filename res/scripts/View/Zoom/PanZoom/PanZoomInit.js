function init(basePath) {
    var action = new RGuiAction(qsTranslate("PanZoom", "&Pan Zoom"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PanZoom.js");
    action.setIcon(basePath + "/PanZoom.svg");
    action.setDefaultShortcut(new QKeySequence("z,p"));
    action.setDefaultCommands(["zoompan", "zp"]);
    action.setGroupSortOrder(3300);
    action.setSortOrder(700);
    action.setWidgetNames(["ZoomMenu", "ViewToolBar", "ZoomToolsPanel", "ZoomMatrixPanel"]);
}
