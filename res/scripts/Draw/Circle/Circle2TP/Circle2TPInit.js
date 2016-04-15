function init(basePath) {
    var action = new RGuiAction(qsTranslate("Circle2TP", "2 Tan&gents and Point"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Circle2TP.js");
    action.setIcon(basePath + "/Circle2TP.svg");
    action.setStatusTip(qsTranslate("Circle2TP", "Draw circle tangential to two entities, through point"));
    action.setDefaultShortcut(new QKeySequence("c,t,2"));
    action.setDefaultCommands(["circletangent2", "ct2"]);
    action.setGroupSortOrder(8500);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawCircleMenu", "CircleToolBar", "CircleToolsPanel", "CircleMatrixPanel"]);
}
