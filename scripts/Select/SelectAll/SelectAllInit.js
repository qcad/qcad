function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectAll", "Select &All"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectAll.js");
    action.setIcon(basePath + "/SelectAll.svg");
    action.setStatusTip(qsTranslate("SelectAll", "Select all visible entities"));
    action.setDefaultShortcuts([
        new QKeySequence("t,a"),
        new QKeySequence(QKeySequence.SelectAll)
    ]);
    action.setDefaultCommands(["selectall", "ta"]);
    action.setNoState();
    action.setSortOrder(200);
    EAction.addGuiActionTo(action, Select, true, true, true);
}
