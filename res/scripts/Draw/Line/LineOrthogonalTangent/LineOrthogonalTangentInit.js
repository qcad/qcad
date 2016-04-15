function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineOrthogonalTangent", "Orthogonal / Tange&nt"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineOrthogonalTangent.js");
    action.setIcon(basePath + "/LineOrthogonalTangent.svg");
    action.setStatusTip(qsTranslate("LineOrthogonalTangent", "Draw line orthogonal to line and tangent to circle, arc or ellipse"));
    action.setDefaultShortcut(new QKeySequence("l,n"));
    action.setDefaultCommands(["lineorthogonaltangent", "orthotangent"]);
    action.setGroupSortOrder(6500);
    action.setSortOrder(300);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel", "LineMatrixPanel"]);
}
