function init(basePath) {
    var action = new RGuiAction(qsTranslate("Batch2Pdf", "&Batch2Pdf visible layout blocks"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Batch2Pdf.js");
    action.setStatusTip(qsTranslate("Batch2Pdf", "&Batch2Pdf visible layout blocks"));
    action.setDefaultShortcut(new QKeySequence("2,P,F"));
    action.setDefaultCommands(["batch2pdf", "b2pdf"]);
    action.setGroupSortOrder(52100);
    action.setSortOrder(500);
    action.setWidgetNames(["MiscIOMenu", "MiscIOToolBar", "MiscIOToolsPanel"]);
}
