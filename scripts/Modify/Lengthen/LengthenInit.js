function init(basePath) {
    var action = new RGuiAction(qsTranslate("Lengthen", "&Lengthen / Shorten"), 
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Lengthen.js");
    action.setIcon(basePath + "/Lengthen.svg");
    action.setDefaultShortcut(new QKeySequence("l,e"));
    action.setDefaultCommands(["lengthen", "shorten", "trimamount", "le"]);
    action.setGroupSortOrder(13200);
    action.setSortOrder(300);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "ModifyToolsPanel", "ModifyMatrixPanel"]);
}
