function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineHorizontal", "&Horizontal Line"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineHorizontal.js");
    action.setIcon(basePath + "/LineHorizontal.svg");
    action.setStatusTip(qsTranslate("LineHorizontal", "Draw horizontal line"));
    action.setDefaultShortcut(new QKeySequence("l,h"));
    action.setDefaultCommands(["linehorizontal", "lh"]);
    action.setGroupSortOrder(6100);
    action.setSortOrder(300);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel", "LineMatrixPanel"]);
}
