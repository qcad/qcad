function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapMiddleManual", "&Middle Manual"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapMiddleManual.js");
    action.setIcon(basePath + "/SnapMiddleManual.svg");
    action.setDefaultShortcut(new QKeySequence("s,n"));
    action.setDefaultCommands(["snapintersectionmiddlemanual", "sn"]);
    action.setSortOrder(700);
    action.setGroup("snaps");
    action.setOverride();
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
