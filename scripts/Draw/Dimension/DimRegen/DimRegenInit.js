function init(basePath) {
    var action = new RGuiAction(qsTranslate("DimRegen", "&Reset Label Position"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/DimRegen.js");
    action.setIcon(basePath + "/DimRegen.svg");
    action.setDefaultShortcut(new QKeySequence("d,s"));
    action.setDefaultCommands(["dimregen", "ds"]);
    action.setNoState();
    action.setGroupSortOrder(12500);
    action.setSortOrder(100);
    action.setWidgetNames(["DimensionMenu", "DimensionToolBar", "!DimensionToolsPanel"]);
}
