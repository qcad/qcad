function init(basePath) {
    var action = new RGuiAction(qsTranslate("Round", "&Round"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Round.js");
    action.setIcon(basePath + "/Round.svg");
    action.setDefaultShortcut(new QKeySequence("r,n"));
    action.setDefaultCommands(["round", "rn"]);
    action.setGroupSortOrder(13300);
    action.setSortOrder(200);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
