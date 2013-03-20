function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictVertical", "Restrict &Vertically"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictVertical.js");
    action.setIcon(basePath + "/RestrictVertical.svg");
    action.setDefaultShortcut(new QKeySequence("e,v"));
    action.setDefaultCommands(["restrictvertical", "ev"]);
    action.setSortOrder(3300);
    action.setGroup("snaprestrictions");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
