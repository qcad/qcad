function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineParallelThrough", "Par&allel (through Point)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineParallelThrough.js");
    action.setIcon(basePath + "/LineParallelThrough.svg");
    action.setStatusTip(qsTranslate("LineParallelThrough", "Draw parallel line or concentric arc or circle through a given point"));
    action.setDefaultShortcut(new QKeySequence("l,g"));
    action.setDefaultCommands(["lineparallelthrough", "lineoffsetthrough", "parallelthrough", "lg"]);
    action.setGroupSortOrder(6400);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel", "LineMatrixPanel"]);
}
