function init(basePath) {
    var action = new RGuiAction(qsTranslate("Divide", "&Divide"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Divide.js");
    action.setIcon(basePath + "/Divide.svg");
    action.setDefaultShortcut(new QKeySequence("d,i"));
    action.setDefaultCommands(["divide", "di"]);
    action.setSortOrder(3000);
    EAction.addGuiActionTo(action, Modify, true, true, true, true);
}
