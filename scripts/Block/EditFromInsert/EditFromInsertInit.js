function init(basePath) {
    var menu = Block.getMenu();
    var action = new RGuiAction(qsTranslate("EditFromInsert", "E&dit Block from Reference"), RMainWindowQt.getMainWindow());
    action.setToolTip(qsTranslate("EditFromInsert", "Edit block based on chosen block reference"));
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EditFromInsert.js");
    action.setIcon(basePath + "/EditFromInsert.svg");
    action.setDefaultShortcut(new QKeySequence("b,d"));
    action.setDefaultCommands(["blockeditfromreference", "bd"]);
    action.setSortOrder(70);
    EAction.addGuiActionTo(action, Block, true, false, false);
}
