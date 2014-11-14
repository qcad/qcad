function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineRectangle", "&Rectangle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineRectangle.js");
    action.setIcon(basePath + "/LineRectangle.svg");
    action.setDefaultShortcut(new QKeySequence("r,e"));
    action.setStatusTip(qsTranslate("LineRectangle", "Draw rectangle from two corners"));
    action.setDefaultCommands(["rectangle", "linerectangle", "rect", "re"]);
    action.setGroupSortOrder(6200);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawLineMenu", "LineToolBar", "LineToolsPanel"]);
}
