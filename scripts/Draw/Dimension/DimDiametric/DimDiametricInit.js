function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimDiametric", "&Diametric"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimDiametric.js");
    action.setIcon(basePath + "/DimDiametric.svg");
    action.setStatusTip(qsTranslate("DimDiametric", "Draw diametric dimension"));
    action.setDefaultShortcut(new QKeySequence("d,d"));
    action.setDefaultCommands(["dimdia", "dimdiametric", "dd"]);
    action.setGroupSortOrder(12300);
    action.setSortOrder(200);
    action.setWidgetNames(["DimensionMenu", "DimensionToolBar", "DimensionToolsPanel", "DimensionMatrixPanel"]);
}
