function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectLayer", "&Select Layer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectLayer.js");
    action.setIcon(basePath + "/SelectLayer.svg");
    action.setDefaultShortcuts([new QKeySequence("y,+"), new QKeySequence("y,c")]);
    action.setDefaultCommands(["layerselect", "selectlayer", "y+", "yc"]);
    action.setGroupSortOrder(17400);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
