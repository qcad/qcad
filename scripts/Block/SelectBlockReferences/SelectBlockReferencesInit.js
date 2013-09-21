function init(basePath) {
    var menu = Block.getMenu();
    var action = new RGuiAction(qsTranslate("SelectBlockReferences", "&Select Block References"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectBlockReferences.js");
    action.setIcon(basePath + "/SelectBlockReferences.svg");
    action.setDefaultShortcut(new QKeySequence("b,l"));
    action.setDefaultCommands(["blockselect", "selectblock", "bl"]);
    action.setSortOrder(2800);
    EAction.addGuiActionTo(action, Block, true, true, false, true);
}
