function init(basePath) {
    var action = new RGuiAction(qsTranslate("Copy", "&Copy"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Copy.js");
    action.setIcon(basePath + "/Copy.svg");
    action.setDefaultShortcuts([
        new QKeySequence(QKeySequence.Copy),
        new QKeySequence("c,p")
    ]);
    action.setDefaultCommands(["copy", "cp"]);
    action.setSortOrder(700);
    action.setNoState();
    EAction.addGuiActionTo(action, Edit, true, true, false);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
