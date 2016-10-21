function init(basePath) {
    var action = new RGuiAction(qsTranslate("HatchFromBoundary", "&Hatch"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/HatchFromBoundary.js");
    action.setIcon(basePath + "/HatchFromBoundary.svg");
    action.setStatusTip(qsTranslate("Hatch", "Draw hatch or solid fill"));
    action.setDefaultShortcut(new QKeySequence("h,a"));
    action.setDefaultCommands(["hatch", "ha"]);
    action.setGroupSortOrder(30);
    action.setSortOrder(300);
    action.setWidgetNames(["DrawMenu", "DrawToolBar", "MainToolsPanel", "DrawMatrixPanel"]);
}
