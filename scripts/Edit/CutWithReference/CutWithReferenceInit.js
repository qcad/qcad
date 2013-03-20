function init(basePath) {
    var action = new RGuiAction(qsTranslate("CutWithReference", "&Cut with Reference"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/CutWithReference.js");
    action.setIcon(basePath + "/CutWithReference.svg");
    action.setDefaultShortcuts([
        new QKeySequence("Ctrl+Shift+X"),
        new QKeySequence("r,t")
    ]);
    action.setDefaultCommands(["cutwithreference", "rt"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, Edit, true, true, false, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
