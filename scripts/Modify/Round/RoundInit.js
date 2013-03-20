function init(basePath) {
    var action = new RGuiAction(qsTranslate("Round", "&Round"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Round.js");
    action.setIcon(basePath + "/Round.svg");
    action.setDefaultShortcut(new QKeySequence("r,n"));
    action.setDefaultCommands(["round", "rn"]);
    action.setSortOrder(2100);
    EAction.addGuiActionTo(action, Modify, true, true, true);
}
