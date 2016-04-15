function init(basePath) {
    var action = new RGuiAction(qsTranslate("CircleConcentricThrough", "Concentric (&through Point)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/CircleConcentricThrough.js");
    action.setIcon(basePath + "/CircleConcentricThrough.svg");
    action.setStatusTip(qsTranslate("CircleConcentricThrough", "Draw concentric circle through point"));
    action.setDefaultShortcut(new QKeySequence("c,g"));
    action.setDefaultCommands(["circleconcentricthrough", "cg"]);
    action.setGroupSortOrder(8400);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawCircleMenu", "CircleToolBar", "CircleToolsPanel", "CircleMatrixPanel"]);
}
