function init(basePath) {
    var action = new RGuiAction(qsTranslate("Text", "&Text") + "…", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Text.js");
    action.setStatusTip(qsTranslate("Text", "Draw text"));
    action.setDefaultShortcut(new QKeySequence("t,e"));
    action.setDefaultCommands(["text", "te"]);
    action.setGroupSortOrder(30);
    action.setSortOrder(100);
    action.setWidgetNames(["DrawMenu", "DrawToolBar", "MainToolsPanel", "DrawMatrixPanel"]);
}
