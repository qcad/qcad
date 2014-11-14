function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShowAllLayers", "&Show all Layers"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShowAllLayers.js");
    action.setIcon(basePath + "/ShowAllLayers.svg");
    action.setDefaultShortcut(new QKeySequence("y,s"));
    action.setDefaultCommands(["layershowall", "ys"]);
    action.setGroupSortOrder(14100);
    action.setSortOrder(200);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel"]);
}

