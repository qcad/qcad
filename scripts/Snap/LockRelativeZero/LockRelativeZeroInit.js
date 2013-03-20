function init(basePath) {
    var action = new RGuiAction(qsTranslate("LockRelativeZero", "&Lock Relative Zero"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LockRelativeZero.js");
    action.setIcon(basePath + "/LockRelativeZero.svg");
    action.setDefaultShortcut(new QKeySequence("r,l"));
    action.setDefaultCommands(["lockrelativezero", "rl"]);
    action.setSortOrder(4100);
//    var appWin = EAction.getMainWindow();
//    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
