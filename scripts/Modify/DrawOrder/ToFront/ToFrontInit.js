function init(basePath) {
    var action = new RGuiAction(qsTranslate("ToFront", "Bring to &Front"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/ToFront.js");
    action.setIcon(basePath + "/ToFront.svg");
    action.setDefaultShortcut(new QKeySequence("m,f"));
    action.setDefaultCommands(["tofront", "mf"]);
    action.setGroupSortOrder(13600);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyDrawOrderMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
