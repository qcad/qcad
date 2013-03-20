function init(basePath) {
    var action = new RGuiAction(qsTranslate("Undo", "&Undo"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresUndoableTransaction(true);
    action.setScriptFile(basePath + "/Undo.js");
    action.setIcon(basePath + "/Undo.svg");
    action.setDefaultShortcuts([
       new QKeySequence(QKeySequence.Undo),
       new QKeySequence("o,o")
    ]);
    action.setDefaultCommands(["undo", "oops"]);
    action.setSortOrder(100);
    action.setNoState();
    EAction.addGuiActionTo(action, Edit, true, true, false);
    var appWin = EAction.getMainWindow();
    appWin.addTransactionListener(action);
}
