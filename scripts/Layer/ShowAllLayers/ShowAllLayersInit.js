function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShowAllLayers", "&Show All Layers"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShowAllLayers.js");
    action.setIcon(basePath + "/ShowAllLayers.svg");
    action.setDefaultShortcut(new QKeySequence("y,s"));
    action.setDefaultCommands(["layershowall", "ys"]);
    action.setGroupSortOrder(14120);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}

