function init(basePath) {
    var action = new RGuiAction(qsTranslate("BrowseUserManual", "Browse User Manual"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/BrowseUserManual.js");
    action.setIcon(basePath + "/BrowseUserManual.svg");
    action.setNoState();
    action.setGroupSortOrder(110100);
    action.setSortOrder(100);
    action.setWidgetNames(["HelpMenu", "HelpToolBar"]);
}
