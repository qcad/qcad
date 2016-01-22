function init(basePath) {
    var action = new RGuiAction(qsTranslate("CreateLibraryItem", "&Create Library Item"), RMainWindowQt.getMainWindow());
    var tip = qsTranslate("CreateLibraryItem", "Create library item from selection");
    action.setToolTip(tip);
    action.setStatusTip(tip);
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/CreateLibraryItem.js");
    action.setIcon(basePath + "/CreateLibraryItem.svg");
    action.setDefaultShortcut(new QKeySequence("b,t"));
    action.setDefaultCommands(["librarycreate", "bt"]);
    action.setGroupSortOrder(14600);
    action.setSortOrder(100);
    action.setWidgetNames(["BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
