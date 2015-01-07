function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseConcentric", "&Parallel Curve (with Distance)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseConcentric.js");
    action.setIcon(basePath + "/EllipseConcentric.svg");
    action.setStatusTip(qsTranslate("EllipseConcentric", "Draw concentric curve to ellipse"));
    action.setDefaultShortcut(new QKeySequence("e,c"));
    action.setDefaultCommands(["ellipseconcentric", "ec"]);
    action.setGroupSortOrder(9160);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel"]);
}
