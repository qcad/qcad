function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapAuto", "&Auto"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapAuto.js");
    action.setIcon(basePath + "/SnapAuto.svg");
    action.setDefaultShortcut(new QKeySequence("s,a"));
    action.setDefaultCommands(["snapauto", "sa"]);
    action.setSortOrder(1200);
    action.setGroup("snaps");
    action.setGroupDefault(true);
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
