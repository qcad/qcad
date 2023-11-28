function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimVertical", "&Vertical"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimVertical.js");
    action.setStatusTip(qsTranslate("DimVertical", "Draw vertical dimension"));
    action.setDefaultShortcut(new QKeySequence("d,v"));
    action.setDefaultCommands(["dimver", "dimvertical", "dv"]);
    action.setGroupSortOrder(12100);
    action.setSortOrder(400);
    action.setWidgetNames(["DimensionMenu", "DimensionToolBar", "DimensionToolsPanel", "DimensionMatrixPanel"]);
}
