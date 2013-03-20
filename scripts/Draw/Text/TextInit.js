function init(basePath) {
    var action = new RGuiAction(qsTranslate("Text", "&Text"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Text.js");
    action.setIcon(basePath + "/Text.svg");
    action.setStatusTip(qsTranslate("Text", "Draw text"));
    action.setDefaultShortcut(new QKeySequence("t,e"));
    action.setDefaultCommands(["text", "te"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, Draw, true, false, true, true);
}
