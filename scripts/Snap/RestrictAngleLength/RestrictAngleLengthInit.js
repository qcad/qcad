function init(basePath) {
    var action = new RGuiAction(qsTranslate("RestrictAngleLength", "Restrict &Angle or Length"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RestrictAngleLength.js");
    action.setIcon(basePath + "/RestrictAngleLength.svg");
    action.setDefaultShortcut(new QKeySequence("e,g"));
    action.setDefaultCommands(["restrictanglelength", "eg"]);
    action.setSortOrder(3400);
    action.setGroup("snaprestrictions");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
