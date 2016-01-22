function init(basePath) {
    var action = new RGuiAction(qsTranslate("BreakOut", "&Break out Segment"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/BreakOut.js");
    action.setIcon(basePath + "/BreakOut.svg");
    action.setDefaultShortcut(new QKeySequence("d,2"));
    action.setDefaultCommands(["break", "breakout", "d2"]);
    action.setGroupSortOrder(13400);
    action.setSortOrder(200);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
