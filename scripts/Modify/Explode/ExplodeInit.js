function init(basePath) {
    var action = new RGuiAction(qsTranslate("Explode", "&Explode"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Explode.js");
    action.setIcon(basePath + "/Explode.svg");
    action.setDefaultShortcut(new QKeySequence("x,p"));
    action.setDefaultCommands(["explode", "xp"]);
    action.setGroupSortOrder(13550);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel", "BlockMenu", "BlockToolBar", "BlockToolsPanel", "BlockMatrixPanel"]);
}
