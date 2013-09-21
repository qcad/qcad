function init(basePath) {
    var action = new RGuiAction(qsTranslate("RemoveBlock", "&Remove Block"), RMainWindowQt.getMainWindow());
    action.setToolTip(qsTranslate("RemoveBlock", "Delete selected block"));
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/RemoveBlock.js");
    action.setIcon(basePath + "/RemoveBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,r"));
    action.setDefaultCommands(["blockremove", "br"]);
    action.setSortOrder(2000);
    EAction.addGuiActionTo(action, Block, true, true, false, true);
}
