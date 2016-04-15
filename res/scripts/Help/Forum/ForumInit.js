function init(basePath) {
    var action = new RGuiAction(qsTranslate("Forum", "&Forum"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/Forum.js");
    action.setNoState();
    action.setGroupSortOrder(110200);
    action.setSortOrder(300);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
