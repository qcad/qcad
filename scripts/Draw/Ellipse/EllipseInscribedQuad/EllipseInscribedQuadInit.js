function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseInscribedQuad", "Inscribed in Quadrilateral"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseInscribedQuad.js");
    action.setIcon(basePath + "/EllipseInscribedQuad.svg");
    action.setStatusTip(qsTranslate("EllipseInscribedQuad", "Draw ellipse inscribed in quadrilateral"));
    action.setDefaultShortcut(new QKeySequence("e,q"));
    action.setDefaultCommands(["ellipseinscribedquad", "eq"]);
    action.setGroupSortOrder(9200);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawEllipseMenu", "EllipseToolBar", "EllipseToolsPanel", "EllipseMatrixPanel"]);
}
