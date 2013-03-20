function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToFront", "Bring to &Front"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/ToFront.js");
    action.setIcon(basePath + "/ToFront.svg");
    action.setDefaultShortcut(new QKeySequence("m,f"));
    action.setDefaultCommands(["tofront", "mf"]);
    action.setSortOrder(6000);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
    EAction.addGuiActionTo(action, Modify, true, true, true, true);
}
