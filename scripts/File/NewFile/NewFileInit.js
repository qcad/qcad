function init(basePath) {
    var action = new RGuiAction(qsTranslate("NewFile", "&New"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/NewFile.js");
    action.setIcon(basePath + "/NewFile.svg");
    action.setDefaultShortcuts([
        new QKeySequence(QKeySequence.New),
        // new tab (as known from browsers):
        new QKeySequence("Ctrl+T")
    ]);
    action.setDefaultCommands(["new"]);
    action.setNoState();
    action.setGroupSortOrder(1000);
    action.setSortOrder(100);
    action.setWidgetNames(["FileMenu", "FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
