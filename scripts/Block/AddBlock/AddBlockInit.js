function init(basePath) {
    var action = new RGuiAction(qsTranslate("AddBlock", "&Add Block"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AddBlock.js");
    action.setIcon(basePath + "/AddBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,a"));
    action.setDefaultCommands(["blockadd", "ba"]);
    action.setStatusTip(qsTranslate("AddBlock", "Add new empty block"));
    action.setSortOrder(30);
    EAction.addGuiActionTo(action, Block, true, true);
}
