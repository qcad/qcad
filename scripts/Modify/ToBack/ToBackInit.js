function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToBack", "Send to Bac&k"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/ToBack.js");
    action.setIcon(basePath + "/ToBack.svg");
    action.setDefaultShortcut(new QKeySequence("m,b"));
    action.setDefaultCommands(["toback", "mb"]);
    action.setSortOrder(6100);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
    EAction.addGuiActionTo(action, Modify, true, true, true);
}
