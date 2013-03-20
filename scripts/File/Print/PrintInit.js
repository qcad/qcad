function init(basePath) {
    var action = new RGuiAction(qsTranslate("Print", "&Print"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Print.js");
    action.setIcon(basePath + "/Print.svg");
    action.setDefaultShortcut(new QKeySequence(Qt.ControlModifier + Qt.Key_P));
    action.setDefaultCommands(["print"]);
    action.setStatusTip(qsTranslate("Print", "Print current drawing"));
    action.setSortOrder(3100);
    EAction.addGuiActionTo(action, File, true, false, false);
}
