function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseInscribedQuad", "Inscribed in Quadrilateral"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseInscribedQuad.js");
    action.setIcon(basePath + "/EllipseInscribedQuad.svg");
    action.setStatusTip(qsTranslate("EllipseInscribedQuad", "Draw ellipse inscribed in quadrilateral"));
    action.setDefaultShortcut(new QKeySequence("e,q"));
    action.setDefaultCommands(["ellipseinscribedquad", "eq"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, Ellipse, true, true, true, true);
}
