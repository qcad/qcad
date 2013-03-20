function init(basePath) {
    var action = new RGuiAction(qsTranslate("Save", "&Save"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Save.js");
    action.setIcon(basePath + "/Save.svg");
    action.setDefaultShortcut(new QKeySequence(QKeySequence.Save));
    action.setDefaultCommands(["save"]);
    action.setSortOrder(1000);
    action.setNoState();
    EAction.addGuiActionTo(action, File, true, true, false, true);
}
