function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapDistance", "&Distance"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapDistance.js");
    action.setIcon(basePath + "/SnapDistance.svg");
    action.setDefaultShortcut(new QKeySequence("s,d"));
    action.setDefaultCommands(["snapdistance", "sd"]);
    action.setSortOrder(900);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true, true);
}
