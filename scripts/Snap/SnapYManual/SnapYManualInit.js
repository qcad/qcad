function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapYManual", "&Y/X from Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapYManual.js");
    action.setIcon(basePath + "/SnapYManual.svg");
    action.setDefaultShortcut(new QKeySequence(".,y"));
    action.setDefaultCommands([".y"]);
    action.setOverride();
    action.setNoState();
    action.setGroupSortOrder(15550);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);
};
