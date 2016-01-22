function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseOffsetThrough", "Parallel Curve (&through Point)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseOffsetThrough.js");
    action.setIcon(basePath + "/EllipseOffsetThrough.svg");
    action.setStatusTip(qsTranslate("EllipseOffsetThrough", "Draw parallel curve to ellipse through point"));
    action.setDefaultShortcut(new QKeySequence("e,g"));
    action.setDefaultCommands(["ellipseoffsetthrough", "eg"]);
    action.setGroupSortOrder(9160);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel", "EllipseMatrixPanel"]);
}
