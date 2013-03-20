function init(basePath) {
    var action = new RGuiAction(qsTranslate("ShowAllBlocks", "&Show all"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ShowAllBlocks.js");
    action.setIcon(basePath + "/ShowAllBlocks.svg");
    action.setDefaultShortcut(new QKeySequence("b,s"));
    action.setDefaultCommands(["blockshowAll", "bs"]);
    action.setSortOrder(10);
    EAction.addGuiActionTo(action, Block, true, true, false);
}
