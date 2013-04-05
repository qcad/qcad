function init(basePath) {
    var action = new RGuiAction(qsTranslate("Website", "Visit &Website"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/Website.js");
    action.setSortOrder(300);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false, true);
}
