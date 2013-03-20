function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapCoordinatePolar", "&Polar Coordinate"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapCoordinatePolar.js");
    action.setIcon(basePath + "/SnapCoordinatePolar.svg");
    action.setDefaultShortcut(new QKeySequence("s,o"));
    action.setDefaultCommands(["snappolar", "so"]);
    action.setSortOrder(2100);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
