function init(basePath) {
    var action = new RGuiAction(qsTranslate("FAQ", "FA&Qs (online)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/FAQ.js");
    action.setNoState();
    action.setGroupSortOrder(110200);
    action.setSortOrder(200);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
