function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictOrthogonal", "Restrict &Orthogonally"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictOrthogonal.js");
    action.setIcon(basePath + "/RestrictOrthogonal.svg");
    action.setDefaultShortcut(new QKeySequence("e,o"));
    action.setDefaultCommands(["restrictorthogonal", "eo"]);
    action.setSortOrder(3100);
    action.setGroup("snaprestrictions");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
