function init(basePath) {
    var action = new RGuiAction(qsTranslate("CircleCD", "Center, &Diameter"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/CircleCD.js");
    action.setIcon(basePath + "/CircleCD.svg");
    action.setStatusTip(qsTranslate("CircleCD", "Draw circle from center and diameter"));
    action.setDefaultShortcut(new QKeySequence("c,a"));
    action.setDefaultCommands(["circlediameter", "ca"]);
    action.setGroupSortOrder(8150);
    action.setSortOrder(200);
    action.setWidgetNames(["DrawCircleMenu", "CircleToolBar", "CircleToolsPanel", "CircleMatrixPanel"]);
}
