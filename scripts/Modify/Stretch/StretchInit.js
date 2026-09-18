function init(basePath) {
    var action = new RGuiAction(qsTranslate("Stretch", "&Stretch"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Stretch.js");
    action.setDefaultShortcut(new QKeySequence("s,s"));
    action.setDefaultCommands(["stretch", "ss"]);
    action.setGroupSortOrder(13200);
    action.setSortOrder(400);
    action.setWidgetNames(["ModifyTrimMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
