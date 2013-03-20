function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapGrid", "&Grid"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapGrid.js");
    action.setIcon(basePath + "/SnapGrid.svg");
    action.setDefaultShortcut(new QKeySequence("s,g"));
    action.setDefaultCommands(["snapgrid", "sg"]);
    action.setSortOrder(200);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
