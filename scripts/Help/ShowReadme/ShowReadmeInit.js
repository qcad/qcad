function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShowReadme", "Show &Readme"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/ShowReadme.js");
    // action.setIcon(basePath + "/ShowReadme.svg");
    action.setSortOrder(110);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false);
}
