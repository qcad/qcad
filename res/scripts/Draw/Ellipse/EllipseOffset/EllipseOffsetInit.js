function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseOffset", "&Parallel Curve (with Distance)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseOffset.js");
    action.setIcon(basePath + "/EllipseOffset.svg");
    action.setStatusTip(qsTranslate("EllipseOffset", "Draw parallel curve to ellipse"));
    action.setDefaultShortcut(new QKeySequence("e,c"));
    action.setDefaultCommands(["ellipseoffset", "ec"]);
    action.setGroupSortOrder(9160);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel", "EllipseMatrixPanel"]);
}
