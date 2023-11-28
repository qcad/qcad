function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapYManual", "&Y/X from Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapYManual.js");
    action.setDefaultShortcut(new QKeySequence(".,y"));
    action.setDefaultCommands([".y"]);
    action.setOverride();
    action.setGroupSortOrder(15550);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);
};
