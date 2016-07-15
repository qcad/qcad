function init(basePath) {
    var action = new RGuiAction(qsTranslate("DeselectLayer", "&Deselect Layer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DeselectLayer.js");
    action.setIcon(basePath + "/DeselectLayer.svg");
    action.setDefaultShortcuts([new QKeySequence("y,-"), new QKeySequence("y,d")]);
    action.setDefaultCommands(["layerdeselect", "deselectlayer", "y-", "yd"]);
    action.setGroupSortOrder(17400);
    action.setSortOrder(200);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
