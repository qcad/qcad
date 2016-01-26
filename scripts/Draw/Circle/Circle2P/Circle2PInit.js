function init(basePath) {
    var action = new RGuiAction(qsTranslate("Circle2P", "&2 Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Circle2P.js");
    action.setIcon(basePath + "/Circle2P.svg");
    action.setStatusTip(qsTranslate("Circle2P", "Draw circle from 2 diametrically opposite points"));
    action.setDefaultShortcut(new QKeySequence("c,2"));
    action.setDefaultCommands(["circle2p", "c2"]);
    action.setGroupSortOrder(8300);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawCircleMenu", "CircleToolBar", "CircleToolsPanel", "CircleMatrixPanel"]);
}
