function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToggleLayerVisibility", "&Toggle Visibility"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ToggleLayerVisibility.js");
    action.setIcon(basePath + "/ToggleLayerVisibility.svg");
    action.setDefaultShortcut(new QKeySequence("y,v"));
    action.setDefaultCommands(["layertogglevisibility", "yv"]);
    action.setGroupSortOrder(14100);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
