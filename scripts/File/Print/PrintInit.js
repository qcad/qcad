function init(basePath) {
    var action = new RGuiAction(qsTranslate("Print", "&Print") + "…", RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setForceGlobal(true);
    action.setScriptFile(basePath + "/Print.js");
    action.setDefaultShortcut(new QKeySequence("Ctrl+P"));
    action.setDefaultCommands(["print"]);
    action.setStatusTip(qsTranslate("Print", "Print current drawing"));
    action.setGroupSortOrder(1600);
    action.setSortOrder(200);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
