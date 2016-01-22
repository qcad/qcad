function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimRotated", "&Rotated (Linear)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/DimRotated.js");
    action.setIcon(basePath + "/DimRotated.svg");
    action.setStatusTip(qsTranslate("DimRotated", "Draw linear dimension at a fixed angle"));
    action.setDefaultShortcut(new QKeySequence("d,l"));
    action.setDefaultCommands(["dimlinear", "dimrotated", "dl"]);
    action.setGroupSortOrder(12100);
    action.setSortOrder(200);
    action.setWidgetNames(["DimensionMenu", "DimensionToolBar", "DimensionToolsPanel", "DimensionMatrixPanel"]);
}
