function init(basePath) {
    var action = new RGuiAction(qsTranslate("BrowseAddOns", "Browse for Add-ons"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/BrowseAddOns.js");
    action.setSortOrder(350);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false);
}
