function init(basePath) {
    var action = new RGuiAction(qsTranslate("Counter", "&Counter"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Counter.js");
    action.setIcon(basePath + "/Counter.svg");
    action.setStatusTip(qsTranslate("Counter", "Auto increment number"));
    action.setDefaultShortcut(new QKeySequence("c,1,2"));
    action.setDefaultCommands(["counter", "c12"]);
    action.setGroupSortOrder(54100);
    action.setSortOrder(200);
    action.setWidgetNames(["MiscDrawMenu", "MiscDrawToolBar", "MiscDrawToolsPanel", "MiscDrawMatrixPanel"]);
}
