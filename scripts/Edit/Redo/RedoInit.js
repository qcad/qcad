function init(basePath) {
    var action = new RGuiAction(qsTranslate("Redo", "&Redo"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresRedoableTransaction(true);
    action.setScriptFile(basePath + "/Redo.js");
    action.setDefaultShortcuts([
       new QKeySequence(QKeySequence.Redo),
       new QKeySequence("u,u")
    ]);
    action.setDefaultCommands(["redo", "uu"]);
    action.setIcon(basePath + "/Redo.svg");
    action.setSortOrder(200);
    action.setNoState();
    EAction.addGuiActionTo(action, Edit, true, true, false);
    var appWin = EAction.getMainWindow();
    appWin.addTransactionListener(action);
}
