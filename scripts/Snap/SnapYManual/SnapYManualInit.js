function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapYManual", "&Y/X from Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapYManual.js");
    action.setDefaultShortcut(new QKeySequence("p,y"));
    action.setDefaultCommands(["py"]);
    action.setOverride();
    action.setGroupSortOrder(15550);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);
};
