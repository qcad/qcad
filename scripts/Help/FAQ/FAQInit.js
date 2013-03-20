function init(basePath) {
    var action = new RGuiAction(qsTranslate("FAQ", "FA&Qs (online)"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/FAQ.js");
    // action.setIcon(basePath + "/FAQ.svg");
    action.setSortOrder(200);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false, true);
}
