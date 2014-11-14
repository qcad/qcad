function init(basePath) {
    var action = new RGuiAction(qsTranslate("RemoveLayer", "&Remove Layer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RemoveLayer.js");
    action.setIcon(basePath + "/RemoveLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,r"));
    action.setDefaultCommands(["layerremove", "yr"]);
    action.setGroupSortOrder(14300);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel"]);
}
