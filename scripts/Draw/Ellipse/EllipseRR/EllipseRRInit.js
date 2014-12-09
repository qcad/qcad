function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseRR", "Ellipse with &Radii"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseRR.js");
    action.setIcon(basePath + "/EllipseRR.svg");
    action.setDefaultShortcut(new QKeySequence("e,d"));
    action.setStatusTip(qsTranslate("EllipseRR", "Draw ellipse with position, major radius and minor radius"));
    action.setDefaultCommands(["ellipseradii", "ed"]);
    action.setGroupSortOrder(11510);
    action.setSortOrder(300);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel"]);
}
