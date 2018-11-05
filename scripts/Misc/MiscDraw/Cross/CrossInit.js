function init(basePath) {
    var action = new RGuiAction(qsTranslate("Cross", "Centerline Cross"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Cross.js");
    action.setIcon(basePath + "/Cross.svg");
    action.setStatusTip(qsTranslate("Cross", "Draw centerline cross in arcs, circles or ellipses"));
    action.setDefaultShortcut(new QKeySequence("c,s"));
    action.setDefaultCommands(["cross", "cs"]);
    action.setGroupSortOrder(54100);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
