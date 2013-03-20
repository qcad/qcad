function init(basePath) {
    var menu = Snap.getMenu();
    var tb = Snap.getToolBar();

    var action = new RGuiAction(qsTranslate("SnapCoordinate", "&Coordinate"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapCoordinate.js");
    action.setIcon(basePath + "/SnapCoordinate.svg");
    action.setDefaultShortcut(new QKeySequence("s,x"));
    action.setDefaultCommands(["snapcoordinate", "sx"]);
    action.setSortOrder(2000);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true, true);
}
