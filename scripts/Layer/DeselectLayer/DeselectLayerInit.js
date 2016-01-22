function init(basePath) {
    var action = new RGuiAction(qsTranslate("DeselectLayer", "&Deselect Layer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectLayer.js");
    action.setIcon(basePath + "/DeselectLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,-"));
    action.setDefaultCommands(["layerdeselect", "deselectlayer", "y-"]);
    action.setGroupSortOrder(17400);
    action.setSortOrder(200);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
