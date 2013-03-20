function init(basePath) {
    var action = new RGuiAction(qsTranslate("Scale", "&Scale"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Scale.js");
    action.setIcon(basePath + "/Scale.svg");
    action.setDefaultShortcut(new QKeySequence("s,z"));
    action.setDefaultCommands(["scale", "sz"]);
    action.setSortOrder(300);
    EAction.addGuiActionTo(action, Modify, true, true, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
