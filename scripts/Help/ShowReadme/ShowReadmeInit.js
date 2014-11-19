function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShowReadme", "Show &Readme"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ShowReadme.js");
    action.setNoState();
    action.setGroupSortOrder(110100);
    action.setSortOrder(200);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
