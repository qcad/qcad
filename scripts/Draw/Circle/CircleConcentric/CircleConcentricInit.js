function init(basePath) {
    var action = new RGuiAction(qsTranslate("CircleConcentric", "&Concentric (with Distance)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/CircleConcentric.js");
    action.setStatusTip(qsTranslate("CircleConcentric", "Draw concentric circle"));
    action.setDefaultShortcut(new QKeySequence("c,c"));
    action.setDefaultCommands(["circleconcentric", "cc"]);
    action.setGroupSortOrder(8400);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawCircleMenu", "CircleToolBar", "CircleToolsPanel", "CircleMatrixPanel"]);
}
