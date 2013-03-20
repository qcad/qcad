function init(basePath) {
    var action = new RGuiAction(qsTranslate("SplineControlPoints", "&Spline (Control Points)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SplineControlPoints.js");
    action.setIcon(basePath + "/SplineControlPoints.svg");
    action.setStatusTip(qsTranslate("SplineControlPoints", "Draw spline from control points"));
    action.setDefaultShortcut(new QKeySequence("s,p"));
    action.setDefaultCommands(["spline", "sp"]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Spline, true, true, true);
}
