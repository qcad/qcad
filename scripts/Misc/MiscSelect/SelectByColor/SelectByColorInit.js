function init(basePath) {
    var action = new RGuiAction(qsTranslate("SelectByColor", "By Color"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SelectByColor.js");
    action.setStatusTip(qsTr("Select all objects of a color"));
    action.setDefaultShortcut(new QKeySequence("t,f"));
    action.setGroupSortOrder(73100);
    action.setSortOrder(400);
    action.setWidgetNames(["MiscSelectMenu", "MiscSelectToolBar", "MiscSelectToolsPanel"]);
}
