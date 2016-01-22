function init(basePath) {
    var action = new RGuiAction(qsTranslate("Line2P", "Line from &2 Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Line2P.js");
    action.setIcon(basePath + "/Line2P.svg");
    action.setStatusTip(qsTranslate("Line2P", "Draw single line or sequence of lines"));
    action.setDefaultShortcut(new QKeySequence("l,i"));
    action.setDefaultCommands(["line", "ln", "li", "l"]);
    action.setGroupSortOrder(6100);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel", "LineMatrixPanel"]);
}
