function init(basePath) {
    var action = new RGuiAction(qsTranslate("Rotate2", "Rotate T&wo"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Rotate2.js");
    action.setIcon(basePath + "/Rotate2.svg");
    action.setDefaultShortcut(new QKeySequence("r,2"));
    action.setDefaultCommands(["rotate2", "r2"]);
    action.setSortOrder(600);
    EAction.addGuiActionTo(action, Modify, true, true, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
