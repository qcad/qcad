function init(basePath) {
    var action = new RGuiAction(qsTranslate("Translate", "&Move / Copy"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Translate.js");
    action.setIcon(basePath + "/Translate.svg");
    action.setStatusTip(qsTranslate("Translate", "Move or copy entities once or multiple times"));
    action.setDefaultShortcut(new QKeySequence("m,v"));
    action.setDefaultCommands(["move", "mv"]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Modify, true, true, true);
    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);
}
