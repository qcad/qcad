function init(basePath) {
    var action = new RGuiAction(qsTranslate("CopyWithReference", "&Copy with Reference"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/CopyWithReference.js");
    action.setIcon(basePath + "/CopyWithReference.svg");
    action.setDefaultShortcuts([
        new QKeySequence("Ctrl+Shift+C"),
        new QKeySequence("r,c")
    ]);
    action.setDefaultCommands(["copywithreference", "rc"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Edit, true, true, false);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
