function init(basePath) {
    var action = new RGuiAction(qsTranslate("TrimBoth", "Trim &Both"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/TrimBoth.js");
    action.setIcon(basePath + "/TrimBoth.svg");
    action.setDefaultShortcut(new QKeySequence("t,m"));
    action.setDefaultCommands(["trim2", "extend2", "tm"]);
    action.setGroupSortOrder(13200);
    action.setSortOrder(200);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
