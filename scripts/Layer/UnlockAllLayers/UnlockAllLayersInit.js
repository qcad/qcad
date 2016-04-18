function init(basePath) {
    var action = new RGuiAction(qsTranslate("UnlockAllLayers", "&Unlock All Layers"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/UnlockAllLayers.js");
    action.setIcon(basePath + "/UnlockAllLayers.svg");
    action.setDefaultShortcut(new QKeySequence("y,n"));
    action.setDefaultCommands(["layerunlockall", "yn"]);
    action.setGroupSortOrder(14150);
    action.setSortOrder(200);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}

