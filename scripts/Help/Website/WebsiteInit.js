function init(basePath) {
    var action = new RGuiAction(qsTranslate("Website", "Visit &Website"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/Website.js");
    action.setNoState();
    action.setGroupSortOrder(110200);
    action.setSortOrder(100);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
