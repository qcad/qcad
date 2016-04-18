function init(basePath) {
    var action = new RGuiAction(qsTranslate("EditHatch", "Edit &Hatch"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EditHatch.js");
    action.setIcon(basePath + "/EditHatch.svg");
    action.setDefaultShortcut(new QKeySequence("m,h"));
    action.setDefaultCommands(["edithatch", "modifyhatch", "mh"]);
    action.setGroupSortOrder(13500);
    action.setSortOrder(200);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
