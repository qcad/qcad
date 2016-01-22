function init(basePath) {
    var action = new RGuiAction(qsTranslate("Divide", "&Divide"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Divide.js");
    action.setIcon(basePath + "/Divide.svg");
    action.setDefaultShortcut(new QKeySequence("d,i"));
    action.setDefaultCommands(["divide", "di"]);
    action.setGroupSortOrder(13400);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
