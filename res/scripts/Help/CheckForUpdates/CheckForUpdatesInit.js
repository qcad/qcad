function init(basePath) {
    if (RSettings.hasQuitFlag()) {
        return;
    }

    var action = new RGuiAction(qsTranslate("CheckForUpdates", "Check for &Updates..."), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/CheckForUpdates.js");
    action.setNoState();
    action.setGroupSortOrder(110300);
    action.setSortOrder(100);
    action.setWidgetNames(["HelpMenu", "!HelpToolBar"]);
}
