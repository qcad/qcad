function init(basePath) {
    var menu = Block.getMenu();
    var action = new RGuiAction(qsTranslate("EditBlock", "&Edit Block"), RMainWindowQt.getMainWindow());
    var tip = qsTranslate("EditBlock", "Edit contents of selected block");
    action.setStatusTip(tip);
    action.setToolTip(tip);
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EditBlock.js");
    action.setIcon(basePath + "/EditBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,e"));
    action.setDefaultCommands(["blockedit","be"]);
    action.setSortOrder(220);
    EAction.addGuiActionTo(action, Block, true, true);
}
