function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictAngleLength", "Restrict &Angle and Length"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictAngleLength.js");
    action.setIcon(basePath + "/RestrictAngleLength.svg");
    action.setDefaultShortcut(new QKeySequence("e,a"));
    action.setDefaultCommands(["restrictanglelength", "ea"]);
    action.setSortOrder(3400);
    action.setGroup("snaprestrictions");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
