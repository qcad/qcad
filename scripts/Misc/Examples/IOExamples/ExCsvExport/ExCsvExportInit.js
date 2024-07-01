function init(basePath) {
    var action = new RGuiAction(qsTranslate("ExCsvExport", "&Export CSV"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExCsvExport.js");
    action.setGroupSortOrder(71120);
    action.setSortOrder(300);
    action.setWidgetNames(["IOExamplesMenu"]);
}
