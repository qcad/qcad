function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectByHandle", "By Handle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectByHandle.js");
    action.setDefaultShortcut(new QKeySequence("t,h"));
    action.setGroupSortOrder(53100);
    action.setSortOrder(100);
    action.setWidgetNames(["MiscSelectMenu", "MiscSelectToolBar", "MiscSelectToolsPanel"]);
}
