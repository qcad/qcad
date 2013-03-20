function init(basePath) {
    var action = new RGuiAction(qsTranslate("Delete", "&Delete"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Delete.js");
    action.setIcon(basePath + "/Delete.svg");
    action.setDefaultShortcuts([
       new QKeySequence("Delete"),
       new QKeySequence("Backspace"),
       new QKeySequence("e,r")
    ]);
    action.setDefaultCommands(["delete", "er"]);
    action.setSortOrder(400);
    action.setNoState();
    EAction.addGuiActionTo(action, Edit, true, true, false, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
