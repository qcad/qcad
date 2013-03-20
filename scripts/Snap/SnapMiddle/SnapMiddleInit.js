function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapMiddle", "&Middle"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapMiddle.js");
    action.setIcon(basePath + "/SnapMiddle.svg");
    action.setDefaultShortcut(new QKeySequence("s,m"));
    action.setDefaultCommands(["snapmiddle", "sm"]);
    action.setSortOrder(600);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
