function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectLayerByEntity", "(De-)Select La&yer"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectLayerByEntity.js");
    action.setIcon(basePath + "/SelectLayerByEntity.svg");
    action.setStatusTip(qsTranslate("SelectLayerByEntity", "(De-)Select all entities on the same layer"));
    action.setDefaultShortcut(new QKeySequence("t,l"));
    action.setDefaultCommands(["selectlayerbyentity", "tl"]);
    action.setGroupSortOrder(4300);
    action.setSortOrder(300);
    action.setWidgetNames(["SelectMenu", "SelectToolBar", "SelectToolsPanel", "SelectMatrixPanel"]);
}
