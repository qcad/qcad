function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseDD", "Ellipse with &Diameters"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseDD.js");
    action.setIcon(basePath + "/EllipseDD.svg");
    action.setDefaultShortcut(new QKeySequence("e,d"));
    action.setStatusTip(qsTranslate("EllipseDD", "Draw ellipse with position and diameters"));
    action.setDefaultCommands(["ellipsediameters", "ed"]);
    action.setGroupSortOrder(9150);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel", "EllipseMatrixPanel"]);
}
