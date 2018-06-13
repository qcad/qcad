function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToggleLayerLock", "&Toggle Lock Status"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ToggleLayerLock.js");
    action.setIcon(basePath + "/ToggleLayerLock.svg");
    action.setDefaultShortcut(new QKeySequence("y,l"));
    action.setDefaultCommands(["layertogglelock", "yl"]);
    action.setGroupSortOrder(14100);
    action.setSortOrder(250);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
