function init(basePath) {
    var action = new RGuiAction(qsTranslate("Rotate", "&Rotate"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Rotate.js");
    action.setIcon(basePath + "/Rotate.svg");
    action.setDefaultShortcut(new QKeySequence("r,o"));
    action.setDefaultCommands(["rotate", "ro"]);
    action.setGroupSortOrder(13100);
    action.setSortOrder(200);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
