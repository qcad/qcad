function init(basePath) {
    var action = new RGuiAction(qsTranslate("AutoTrim", "Auto &Trim"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AutoTrim.js");
    action.setIcon(basePath + "/AutoTrim.svg");
    action.setDefaultShortcut(new QKeySequence("a,x"));
    action.setDefaultCommands(["autotrim", "ax"]);
    action.setSortOrder(3150);
    EAction.addGuiActionTo(action, Modify, true, true, true);
}
