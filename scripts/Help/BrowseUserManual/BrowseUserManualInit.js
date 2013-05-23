function init(basePath) {
    var action = new RGuiAction(qsTranslate("BrowseUserManual", "Browse User Manual"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/BrowseUserManual.js");
    action.setSortOrder(100);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false);
}
