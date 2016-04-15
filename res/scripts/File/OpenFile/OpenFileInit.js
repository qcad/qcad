function init(basePath) {
    var action = new RGuiAction(qsTranslate("OpenFile", "&Open"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/OpenFile.js");
    action.setIcon(basePath + "/OpenFile.svg");
    action.setDefaultShortcut(new QKeySequence(QKeySequence.Open));
    action.setDefaultCommands(["open"]);
    action.setStatusTip(qsTranslate("OpenFile", "Open an existing drawing"));
    action.setNoState();
    action.setGroupSortOrder(1000);
    action.setSortOrder(300);
    action.setWidgetNames(["FileMenu", "FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
