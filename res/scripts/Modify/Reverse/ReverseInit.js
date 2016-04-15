function init(basePath) {
    var action = new RGuiAction(qsTranslate("Reverse", "&Reverse"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setRequiresSelection(true);
    action.setScriptFile(basePath + "/Reverse.js");
    action.setIcon(basePath + "/Reverse.svg");
    action.setDefaultShortcut(new QKeySequence("r,v"));
    action.setDefaultCommands(["reverse"]);
    action.setNoState();
    action.setGroupSortOrder(13450);
    action.setSortOrder(100);
    action.setWidgetNames(["ModifyMenu", "ModifyToolBar", "!ModifyToolsPanel"]);
}
