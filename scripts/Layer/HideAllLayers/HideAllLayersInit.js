function init(basePath) {
    var action = new RGuiAction(qsTranslate("HideAllLayers", "&Hide all Layers"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/HideAllLayers.js");
    action.setIcon(basePath + "/HideAllLayers.svg");
    action.setDefaultShortcut(new QKeySequence("y,h"));
    action.setDefaultCommands(["layerhideall", "yh"]);
    action.setGroupSortOrder(14100);
    action.setSortOrder(400);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel"]);
}
