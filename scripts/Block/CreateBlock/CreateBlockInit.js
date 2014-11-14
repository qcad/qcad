function init(basePath) {
    var action = new RGuiAction(qsTranslate("CreateBlock", "&Create Block from Selection"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/CreateBlock.js");
    action.setIcon(basePath + "/CreateBlock.svg");
    action.setDefaultShortcut(new QKeySequence("b,c"));
    action.setDefaultCommands(["blockcreate", "bc"]);
    action.setGroupSortOrder(14200);
    action.setGroupSortOrderOverride("MainToolsPanel", 40);
    action.setSortOrder(100);
    action.setSortOrderOverride("MainToolsPanel", 300);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "MainToolsPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addSelectionListener(action);

//    action.setGroupSortOrder(40);
//    action.setSortOrder(300);
//    action.setWidgetNames(["BlockMenu", "BlockToolBar", "MainToolsPanel"]);

//    var ctb = EAction.getMainCadToolBarPanel();
//    if (!isNull(ctb)) {
//        // sort order override for cad tool bar only:
//        //action.setProperty("SortOrderCadToolBar", 2200);
//        CadToolBarPanel.prototype.addAction.call(ctb, action);
//    }
}
