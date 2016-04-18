function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimRadial", "&Radial"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimRadial.js");
    action.setIcon(basePath + "/DimRadial.svg");
    action.setStatusTip(qsTranslate("DimRadial", "Draw radial dimension"));
    action.setDefaultShortcut(new QKeySequence("d,r"));
    action.setDefaultCommands(["dimrad", "dimradial", "dr"]);
    action.setGroupSortOrder(12300);
    action.setSortOrder(100);
    action.setWidgetNames(["DimensionMenu", "DimensionToolBar", "DimensionToolsPanel", "DimensionMatrixPanel"]);
}
