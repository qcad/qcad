function init(basePath) {
    var action = new RGuiAction(qsTranslate("PrintPreview", "Print Pre&view"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    // attaching to document would break context menu (FS#1695):
    action.setForceGlobal(true);
    action.setScriptFile(basePath + "/PrintPreview.js");
    action.setIcon(basePath + "/PrintPreview.svg");
    action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.ShiftModifier + Qt.Key_P));
    action.setDefaultCommands(["printpreview"]);
    action.setStatusTip(qsTranslate("PrintPreview", "Preview how current drawing would be printed"));
    action.setGroupSortOrder(1600);
    action.setSortOrder(100);
    action.setWidgetNames(["FileMenu", "FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
