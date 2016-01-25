function init(basePath) {
    var action = new RGuiAction(qsTranslate("Save", "&Save"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Save.js");
    action.setIcon(basePath + "/Save.svg");
    action.setDefaultShortcut(new QKeySequence(QKeySequence.Save));
    action.setDefaultCommands(["save"]);
    action.setNoState();
    action.setGroupSortOrder(1100);
    action.setSortOrder(100);
    action.setWidgetNames(["FileMenu", "FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
