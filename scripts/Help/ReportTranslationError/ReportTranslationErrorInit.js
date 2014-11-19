function init(basePath) {
    var action = new RGuiAction(
        qsTranslate("ReportTranslationError", "Report &Translation Error"),
        RMainWindowQt.getMainWindow()
    );
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ReportTranslationError.js");
    action.setNoState();
    action.setGroupSortOrder(110200);
    action.setSortOrder(600);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
