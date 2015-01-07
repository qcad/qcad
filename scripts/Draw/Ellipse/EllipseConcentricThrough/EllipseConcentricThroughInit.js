function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseConcentricThrough", "Parallel Curve (&through Point)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseConcentricThrough.js");
    action.setIcon(basePath + "/EllipseConcentricThrough.svg");
    action.setStatusTip(qsTranslate("EllipseConcentricThrough", "Draw parallel curve to ellipse through point"));
    action.setDefaultShortcut(new QKeySequence("e,g"));
    action.setDefaultCommands(["ellipseconcentricthrough", "eg"]);
    action.setGroupSortOrder(9160);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel"]);
}
