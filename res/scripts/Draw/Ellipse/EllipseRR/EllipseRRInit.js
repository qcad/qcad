function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseRR", "Ellipse with &Radii"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseRR.js");
    action.setIcon(basePath + "/EllipseRR.svg");
    action.setDefaultShortcut(new QKeySequence("e,i"));
    action.setStatusTip(qsTranslate("EllipseRR", "Draw ellipse with position and radii"));
    action.setDefaultCommands(["ellipseradii", "ei"]);
    action.setGroupSortOrder(9150);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel", "EllipseMatrixPanel"]);
}
