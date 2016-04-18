function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimOrdinate", "&Ordinate (X/Y)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimOrdinate.js");
    action.setIcon(basePath + "/DimOrdinate.svg");
    action.setStatusTip(qsTranslate("DimOrdinate", "Draw ordinate dimension"));
    action.setDefaultShortcut(new QKeySequence("d,o"));
    action.setDefaultCommands(["dimordinate", "do"]);
    action.setGroupSortOrder(12200);
    action.setSortOrder(100);
    action.setWidgetNames(["DimensionMenu", "DimensionToolBar", "DimensionToolsPanel", "DimensionMatrixPanel"]);
}
