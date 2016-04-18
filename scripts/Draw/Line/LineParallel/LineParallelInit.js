function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineParallel", "Para&llel (with Distance)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineParallel.js");
    action.setIcon(basePath + "/LineParallel.svg");
    action.setStatusTip(qsTranslate("LineParallel", "Draw parallel to existing line or concentric arc, circle"));
    action.setDefaultShortcuts([ new QKeySequence("l,p"), new QKeySequence("p,a") ]);
    action.setDefaultCommands([
        "lineparallel", "lineoffset",
        "parallel", "par",
        "lp", "pa"
    ]);
    action.setGroupSortOrder(6400);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel", "LineMatrixPanel"]);
}
