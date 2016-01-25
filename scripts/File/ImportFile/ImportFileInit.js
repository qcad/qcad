function init(basePath) {
    var action = new RGuiAction(qsTranslate("ImportFile", "&Import"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ImportFile.js");
    action.setIcon(basePath + "/ImportFile.svg");
    action.setDefaultShortcut(new QKeySequence(Qt.ShiftModifier + Qt.ControlModifier + Qt.Key_I));
    action.setDefaultCommands(["import"]);
    action.setGroupSortOrder(1000);
    action.setSortOrder(500);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
