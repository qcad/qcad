function init(basePath) {
    var action = new RGuiAction(qsTranslate("CloseFile", "&Close"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/CloseFile.js");
    action.setIcon(basePath + "/CloseFile.svg");
    if (RS.getSystemId()!=="linux" || RSettings.isQt(5)) {
        action.setDefaultShortcut(new QKeySequence(QKeySequence.Close));
    }
    action.setDefaultCommands(["close"]);
    action.setNoState();
    action.setGroupSortOrder(1100);
    action.setSortOrder(300);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
