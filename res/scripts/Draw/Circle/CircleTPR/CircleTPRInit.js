function init(basePath) {
    var action = new RGuiAction(qsTranslate("CircleTPR", "&Tangent, Point, Radius"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/CircleTPR.js");
    action.setIcon(basePath + "/CircleTPR.svg");
    action.setStatusTip(qsTranslate("CircleTPR", "Draw circle tangential to entity, through point with radius"));
    action.setDefaultShortcut(new QKeySequence("c,t,p"));
    action.setDefaultCommands(["circletangentpointradius", "ctp"]);
    action.setGroupSortOrder(8500);
    action.setSortOrder(150);
    action.setWidgetNames(["DrawCircleMenu", "CircleToolBar", "CircleToolsPanel", "CircleMatrixPanel"]);
}
