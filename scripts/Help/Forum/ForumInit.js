function init(basePath) {
    var action = new RGuiAction(qsTranslate("Forum", "&Forum"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/Forum.js");
    action.setSortOrder(500);
    action.setNoState();
    EAction.addGuiActionTo(action, Help, true, false, false);
}
