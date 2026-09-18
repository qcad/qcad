function init(basePath) {
    var action = new RGuiAction(qsTranslate("Divide", "&Divide"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Divide.js");
    action.setDefaultShortcut(new QKeySequence("d,i"));
    action.setDefaultCommands(["divide", "di"]);
    action.setGroupSortOrder(13400);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyTrimMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
