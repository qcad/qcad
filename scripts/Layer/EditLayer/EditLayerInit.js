function init(basePath) {
    var action = new RGuiAction(qsTranslate("EditLayer", "&Edit Layer") + "…", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EditLayer.js");
    action.setDefaultShortcut(new QKeySequence("y,e"));
    action.setDefaultCommands(["layeredit", "ye"]);
    action.setGroupSortOrder(14300);
    action.setSortOrder(200);
    action.setWidgetNames(["LayerMenu", "LayerToolBar", "LayerToolsPanel", "LayerMatrixPanel"]);
}
