function init(basePath) {
    var action = new RGuiAction(qsTranslate("Mirror", "&Mirror"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Mirror.js");
    action.setIcon(basePath + "/Mirror.svg");
    action.setDefaultShortcut(new QKeySequence("m,i"));
    action.setDefaultCommands(["mirror", "mi"]);
    action.setGroupSortOrder(13100);
    action.setSortOrder(400);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
