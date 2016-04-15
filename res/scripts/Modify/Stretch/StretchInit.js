function init(basePath) {
    var action = new RGuiAction(qsTranslate("Stretch", "&Stretch"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Stretch.js");
    action.setIcon(basePath + "/Stretch.svg");
    action.setDefaultShortcut(new QKeySequence("s,s"));
    action.setDefaultCommands(["stretch", "ss"]);
    action.setGroupSortOrder(13200);
    action.setSortOrder(400);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
