function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictHorizontal", "Restrict &Horizontally"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictHorizontal.js");
    action.setIcon(basePath + "/RestrictHorizontal.svg");
    action.setDefaultShortcut(new QKeySequence("e,h"));
    action.setDefaultCommands(["restricthorizontal", "eh"]);
    action.setSortOrder(3200);
    action.setGroup("snaprestrictions");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
