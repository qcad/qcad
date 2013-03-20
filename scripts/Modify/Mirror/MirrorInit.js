function init(basePath) {
    var action = new RGuiAction(qsTranslate("Mirror", "&Mirror"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Mirror.js");
    action.setIcon(basePath + "/Mirror.svg");
    action.setDefaultShortcut(new QKeySequence("m,i"));
    action.setDefaultCommands(["mirror", "mi"]);
    action.setSortOrder(400);
    EAction.addGuiActionTo(action, Modify, true, true, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
