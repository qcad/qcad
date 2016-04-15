function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectLayer", "&Select Layer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectLayer.js");
    action.setIcon(basePath + "/SelectLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,+"));
    action.setDefaultCommands(["layerselect", "selectlayer", "y+"]);
    action.setGroupSortOrder(17400);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
