function init(basePath) {
    var action = new RGuiAction(qsTranslate("ExXmlImport", "&Import XML"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ExXmlImport.js");
    action.setGroupSortOrder(71120);
    action.setSortOrder(100);
    action.setWidgetNames(["IOExamplesMenu"]);
}
