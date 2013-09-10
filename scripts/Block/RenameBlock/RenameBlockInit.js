function init(basePath) {
    var action = new RGuiAction(qsTranslate("RenameBlock", "Re&name Block"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RenameBlock.js");
    action.setIcon(basePath + "/RenameBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,n"));
    action.setDefaultCommands(["blockrename", "bn"]);
    action.setSortOrder(210);
    EAction.addGuiActionTo(action, Block, true, true);
}
