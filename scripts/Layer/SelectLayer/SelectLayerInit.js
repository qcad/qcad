function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectLayer", "&Select Layer Entities"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectLayer.js");
    action.setDefaultShortcut(new QKeySequence("y,c"));
    action.setDefaultCommands(["layerselect", "selectlayer", "yc"]);
    action.setGroupSortOrder(14400);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
