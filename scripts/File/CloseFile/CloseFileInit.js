function init(basePath) {
    var action = new RGuiAction(qsTranslate("CloseFile", "&Close"), RMainWindowQt.getMainWindow());
    if (RSettings.getQtVersion() >= 0x060000) {
        action.setRequiresDocument(false);
    }
    else {
        action.setRequiresDocument(true);
    }
    action.setScriptFile(basePath + "/CloseFile.js");
    if (RS.getSystemId()!=="linux" || RSettings.isQt(5)) {
        action.setDefaultShortcut(new QKeySequence(QKeySequence.Close));
    }
    action.setDefaultCommands(["close"]);
    action.setNoState();
    action.setGroupSortOrder(1100);
    action.setSortOrder(300);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
