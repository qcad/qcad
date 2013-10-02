function init(basePath) {
    var action = new RGuiAction(qsTranslate("Quit", "&Quit"),
        RMainWindowQt.getMainWindow());
    if (RS.getSystemId() == "osx") {
        action.disableIcon();
    }
    action.setRequiresDocument(false);
    action.setScriptFile(basePath + "/Quit.js");
    action.setDefaultShortcut(new QKeySequence(QKeySequence.Quit));
    action.setDefaultCommands(["quit", "exit"]);
    action.checkable = false;
    action.setSortOrder(9990);
    var appWin = EAction.getMainWindow();
    action.triggered.connect(appWin, "quit");
    EAction.addGuiActionTo(action, File, true, false, false, true);
}
