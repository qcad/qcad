function init(basePath) {
    var menu = Block.getMenu();
    var action = new RGuiAction(qsTranslate("EditMainDrawing", "&Return to Main Drawing"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EditMainDrawing.js");
    action.setDefaultShortcut(new QKeySequence("e,m"));
    action.setDefaultCommands(["editmain","em"]);
    action.setIcon(basePath + "/EditMainDrawing.svg");
    action.setSortOrder(65);
    EAction.addGuiActionTo(action, Block, true, true);
}
