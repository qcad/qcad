function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineTangent1", "&Tangent (Point, Circle)"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineTangent1.js");
    action.setIcon(basePath + "/LineTangent1.svg");
    action.setStatusTip(qsTranslate("LineTangent1", "Draw tangent (point, circle)"));
    action.setDefaultShortcut(new QKeySequence("l,t,1"));
    action.setDefaultCommands(["linetangent", "tangent", "lt1"]);
    action.setGroupSortOrder(6500);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel", "LineMatrixPanel"]);
}
