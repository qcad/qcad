function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapCenter", "&Center"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapCenter.js");
    action.setIcon(basePath + "/SnapCenter.svg");
    action.setDefaultShortcut(new QKeySequence("s,c"));
    action.setDefaultCommands(["snapcenter", "sc"]);
    action.setSortOrder(500);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
