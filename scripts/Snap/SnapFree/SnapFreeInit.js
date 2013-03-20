function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapFree", "&Free"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapFree.js");
    action.setIcon(basePath + "/SnapFree.svg");
    action.setDefaultShortcut(new QKeySequence("s,f"));
    action.setDefaultCommands(["snapfree", "sf"]);
    action.setSortOrder(100);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
