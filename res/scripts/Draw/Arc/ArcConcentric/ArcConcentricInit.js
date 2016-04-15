function init(basePath) {
    var action = new RGuiAction(qsTranslate("ArcConcentric", "&Concentric (with Distance)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ArcConcentric.js");
    action.setIcon(basePath + "/ArcConcentric.svg");
    action.setStatusTip(qsTranslate("ArcConcentric", "Draw concentric arc"));
    action.setDefaultShortcut(new QKeySequence("a,c"));
    action.setDefaultCommands(["arcconcentric", "ac"]);
    action.setGroupSortOrder(7300);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawArcMenu", "ArcToolBar", "ArcToolsPanel", "ArcMatrixPanel"]);
}
