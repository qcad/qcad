function init(basePath) {
    var action = new RGuiAction(qsTranslate("LockAllLayers", "&Lock All Layers"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LockAllLayers.js");
    action.setIcon(basePath + "/LockAllLayers.svg");
    action.setDefaultShortcut(new QKeySequence("y,k"));
    action.setDefaultCommands(["layerlockall", "yk"]);
    action.setGroupSortOrder(14150);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}

