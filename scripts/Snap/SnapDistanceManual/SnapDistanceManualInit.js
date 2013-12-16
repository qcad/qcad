function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapDistanceManual", "&Distance Manual"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapDistanceManual.js");
    action.setIcon(basePath + "/SnapDistanceManual.svg");
    action.setStatusTip(qsTranslate("SnapDistanceManual", "Snap distance between 2 points"));
    action.setDefaultShortcut(new QKeySequence("s,h"));
    action.setDefaultCommands(["snapdistancemanual", "sh"]);
    action.setSortOrder(910);
    action.setGroup("snaps");
    action.setOverride();
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
