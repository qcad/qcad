function init(basePath) {
    var action = new RGuiAction(qsTranslate("InsertBlock", "&Insert Block"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/InsertBlock.js");
    action.setIcon(basePath + "/InsertBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,i"));
    action.setDefaultCommands(["blockinsert", "bi"]);
    action.setSortOrder(3000);
    EAction.addGuiActionTo(action, Block, true, false, false, true);
}
