function init(basePath) {
    var action = new RGuiAction(qsTranslate("PdfExport", "P&DF Export"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setForceGlobal(true);
    action.setScriptFile(basePath + "/PdfExport.js");
    action.setIcon(basePath + "/PdfExport.svg");
    action.setDefaultShortcut(new QKeySequence("x,d"));
    action.setDefaultCommands(["pdf"]);
    action.setStatusTip(qsTranslate("PdfExport", "Exports the current drawing as PDF"));
    action.setGroupSortOrder(1500);
    action.setSortOrder(100);
    action.setWidgetNames(["FileMenu", "!FileToolBar", "FileToolsPanel", "FileMatrixPanel"]);
}
