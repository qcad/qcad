function init(basePath) {
    var action = new RGuiAction(qsTranslate("PdfExport", "P&DF Export"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/PdfExport.js");
    action.setIcon(basePath + "/PdfExport.svg");
    action.setDefaultShortcut(new QKeySequence("x,d"));
    action.setDefaultCommands(["pdf"]);
    action.setStatusTip(qsTranslate("PdfExport", "Exports the current drawing as PDF"));
    action.setSortOrder(2500);
    EAction.addGuiActionTo(action, File, true, false, false, true);
}
