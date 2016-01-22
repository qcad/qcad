function init(basePath) {
    var action = new RGuiAction(qsTranslate("Circle2PR", "&2 Points and Radius"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Circle2PR.js");
    action.setIcon(basePath + "/Circle2PR.svg");
    action.setStatusTip(qsTranslate("Circle2PR", "Draw circle from 2 points and radius"));
    action.setDefaultShortcut(new QKeySequence("c,d"));
    action.setDefaultCommands(["circleradius", "cd"]);
    action.setGroupSortOrder(8200);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawCircleMenu", "CircleToolBar", "CircleToolsPanel", "CircleMatrixPanel"]);
}
