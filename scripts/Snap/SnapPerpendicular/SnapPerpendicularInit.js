function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapPerpendicular", "&Perpendicular"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapPerpendicular.js");
    action.setIcon(basePath + "/SnapPerpendicular.svg");
    action.setDefaultShortcut(new QKeySequence("s,u"));
    action.setDefaultCommands(["snapperpendicular", "su"]);
    action.setSortOrder(450);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
