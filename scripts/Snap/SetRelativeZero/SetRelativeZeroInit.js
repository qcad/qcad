function init(basePath) {
    var action = new RGuiAction(qsTranslate("SetRelativeZero", "Set &Relative Zero"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SetRelativeZero.js");
    action.setIcon(basePath + "/SetRelativeZero.svg");
    action.setDefaultShortcut(new QKeySequence("r,z"));
    action.setDefaultCommands(["setrelativezero", "rz"]);
    action.setSortOrder(4000);
//    var appWin = EAction.getMainWindow();
//    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true, true);
}
