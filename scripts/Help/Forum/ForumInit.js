function init(basePath) {
    var action = new RGuiAction(qsTranslate("Forum", "&Forum"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/Forum.js");
    // action.setIcon(basePath + "/Forum.svg");
    action.setSortOrder(210);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false);
}
