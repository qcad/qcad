function init(basePath) {
    var action = new RGuiAction(qsTranslate("BrowseAddOns", "Browse for Add-ons"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/BrowseAddOns.js");
    action.setNoState();
    action.setGroupSortOrder(110200);
    action.setSortOrder(400);
    action.setWidgetNames(["HelpMenu"]);
}
