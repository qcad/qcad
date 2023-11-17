function init(basePath) {
    var action = new RGuiAction(qsTranslate("PrintCurrentView", "Print &Current View"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setForceGlobal(true);
    action.setScriptFile(basePath + "/PrintCurrentView.js");
    action.setDefaultShortcut(new QKeySequence("Ctrl+Alt+P"));
    action.setDefaultCommands(["printview"]);
    action.setStatusTip(qsTranslate("PrintCurrentView", "Print current view"));
    action.setGroupSortOrder(1600);
    action.setSortOrder(250);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
