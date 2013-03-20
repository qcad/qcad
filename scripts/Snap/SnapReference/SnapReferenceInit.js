function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapReference", "&Reference"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapReference.js");
    action.setIcon(basePath + "/SnapReference.svg");
    action.setDefaultShortcut(new QKeySequence("s,r"));
    action.setDefaultCommands(["snapreference", "sr"]);
    action.setSortOrder(800);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
