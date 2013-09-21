function init(basePath) {
    var menu = Block.getMenu();
    var action = new RGuiAction(qsTranslate("HideAllBlocks", "&Hide All"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/HideAllBlocks.js");
    action.setIcon(basePath + "/HideAllBlocks.svg");
    action.setDefaultShortcut(new QKeySequence("b,h"));
    action.setDefaultCommands(["blockhideAll"]);
    action.setSortOrder(300);
    EAction.addGuiActionTo(action, Block, true, true);
}
