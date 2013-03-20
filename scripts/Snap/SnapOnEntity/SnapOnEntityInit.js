function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapOnEntity", "&On Entity"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapOnEntity.js");
    action.setIcon(basePath + "/SnapOnEntity.svg");
    action.setDefaultShortcut(new QKeySequence("s,t"));
    action.setDefaultCommands(["snaponentity", "st"]);
    action.setSortOrder(400);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
