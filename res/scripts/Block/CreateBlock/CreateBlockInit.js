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
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "MainToolsPanel", "DrawMatrixPanel"]);
}
