function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapEnd", "&End"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapEnd.js");
    action.setIcon(basePath + "/SnapEnd.svg");
    action.setDefaultShortcut(new QKeySequence("s,e"));
    action.setDefaultCommands(["snapend", "se"]);
    action.setSortOrder(300);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
