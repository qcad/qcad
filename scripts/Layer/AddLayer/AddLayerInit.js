function init(basePath) {
    var action = new RGuiAction(qsTranslate("AddLayer", "&Add Layer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AddLayer.js");
    action.setIcon(basePath + "/AddLayer.svg");
    action.setDefaultShortcut(new QKeySequence("y,a"));
    action.setDefaultCommands(["layeradd", "ya"]);
    action.setGroupSortOrder(14200);
    action.setSortOrder(100);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
