function init(basePath) {
    var action = new RGuiAction(qsTranslate("Stretch", "&Stretch"),  RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Stretch.js");
    action.setIcon(basePath + "/Stretch.svg");
    action.setDefaultShortcut(new QKeySequence("s,s"));
    action.setDefaultCommands(["stretch", "ss"]);
    action.setSortOrder(1300);
    EAction.addGuiActionTo(action, Modify, true, true, true);
}
