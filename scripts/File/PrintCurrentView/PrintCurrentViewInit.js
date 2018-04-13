function init(basePath) {
    var action = new RGuiAction(qsTranslate("PrintCurrentView", "Print &Current View"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setForceGlobal(true);
    action.setScriptFile(basePath + "/PrintCurrentView.js");
    action.setIcon(basePath + "/PrintCurrentView.svg");
    action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.AltModifier + Qt.Key_P));
    action.setDefaultCommands(["printview"]);
    action.setStatusTip(qsTranslate("PrintCurrentView", "Print current view"));
    action.setGroupSortOrder(1600);
    action.setSortOrder(250);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
