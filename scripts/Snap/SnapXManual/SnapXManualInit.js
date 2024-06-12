function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapXManual", "&X/Y from Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapXManual.js");
    action.setDefaultShortcut(new QKeySequence("p,x"));
    action.setDefaultCommands(["px"]);
    action.setOverride();
    action.setGroupSortOrder(15550);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);
};
