function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToBack", "Send to Bac&k"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/ToBack.js");
    action.setIcon(basePath + "/ToBack.svg");
    action.setDefaultShortcut(new QKeySequence("m,b"));
    action.setDefaultCommands(["toback", "mb"]);
    action.setGroupSortOrder(13600);
    action.setSortOrder(200);
    action.setWidgetNames(["ModifyDrawOrderMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
