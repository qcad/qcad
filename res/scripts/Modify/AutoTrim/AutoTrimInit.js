function init(basePath) {
    var action = new RGuiAction(qsTranslate("AutoTrim", "Auto &Trim"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/AutoTrim.js");
    action.setIcon(basePath + "/AutoTrim.svg");
    action.setDefaultShortcut(new QKeySequence("a,x"));
    action.setDefaultCommands(["autotrim", "ax"]);
    action.setGroupSortOrder(13400);
    action.setSortOrder(400);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
