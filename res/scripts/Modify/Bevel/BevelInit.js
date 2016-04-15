function init(basePath) {
    var action = new RGuiAction(qsTranslate("Bevel", "&Chamfer / Bevel"),  RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Bevel.js");
    action.setIcon(basePath + "/Bevel.svg");
    action.setDefaultShortcut(new QKeySequence("c,h"));
    action.setDefaultCommands(["bevel", "chamfer", "ch"]);
    action.setGroupSortOrder(13300);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
