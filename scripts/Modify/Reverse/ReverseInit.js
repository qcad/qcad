function init(basePath) {
    var action = new RGuiAction(qsTranslate("Reverse", "&Reverse"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Reverse.js");
    action.setIcon(basePath + "/Reverse.svg");
    action.setDefaultShortcut(new QKeySequence("r,v"));
    action.setDefaultCommands(["reverse"]);
    action.setSortOrder(4100);
    action.setNoState();
    EAction.addGuiActionTo(action, Modify, true, false, false, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
