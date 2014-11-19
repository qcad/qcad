function init(basePath) {
    var action = new RGuiAction(qsTranslate("ReportBug", "Report &Bug"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ReportBug.js");
    action.setNoState();
    action.setGroupSortOrder(110200);
    action.setSortOrder(500);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
