function init(basePath) {
    var menu = Block.getMenu();
    var action = new RGuiAction(
        qsTranslate("CreateBlock", "&Create Block from Selection"),
        RMainWindowQt.getMainWindow()
    );
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/CreateBlock.js");
    action.setIcon(basePath + "/CreateBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,c"));
    action.setDefaultCommands(["blockcreate", "bc"]);
    action.setSortOrder(110);
    EAction.addGuiActionTo(action, Block, true);

    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);

    var ctb = EAction.getMainCadToolBarPanel();
    if (!isNull(ctb)) {
        // sort order override for cad tool bar only:
        action.setProperty("SortOrderCadToolBar", 2200);
        CadToolBarPanel.prototype.addAction.call(ctb, action);
    }
}
