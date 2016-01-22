function init(basePath) {
    var action = new RGuiAction(qsTranslate("SplineControlPoints", "&Spline (Control Points)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SplineControlPoints.js");
    action.setIcon(basePath + "/SplineControlPoints.svg");
    action.setStatusTip(qsTranslate("SplineControlPoints", "Draw spline from control points"));
    action.setDefaultShortcut(new QKeySequence("s,p"));
    action.setDefaultCommands(["spline", "sp"]);
    action.setGroupSortOrder(10100);
    action.setSortOrder(100);
    action.setWidgetNames(["SplineMenu", "SplineToolBar", "SplineToolsPanel", "SplineMatrixPanel"]);
}
