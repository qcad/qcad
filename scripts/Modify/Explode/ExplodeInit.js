function init(basePath) {
    var action = new RGuiAction(qsTranslate("Explode", "&Explode"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Explode.js");
    action.setIcon(basePath + "/Explode.svg");
    action.setDefaultShortcut(new QKeySequence("x,p"));
    action.setDefaultCommands(["explode", "xp"]);
    action.setSortOrder(4000);
    EAction.addGuiActionTo(action, Modify, true, true, true);
    EAction.addGuiActionTo(action, Block, true, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
