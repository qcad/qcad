function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictOff", "Restrictions &Off"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictOff.js");
    action.setIcon(basePath + "/RestrictOff.svg");
    action.setDefaultShortcut(new QKeySequence("e,n"));
    action.setDefaultCommands(["restrictoff", "en"]);
    action.setSortOrder(3000);
    action.setGroup("snaprestrictions");
    action.setGroupDefault(true);
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true, true);
}
