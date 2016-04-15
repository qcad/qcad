function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapXManual", "&X/Y from Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapXManual.js");
    action.setIcon(basePath + "/SnapXManual.svg");
    action.setDefaultShortcut(new QKeySequence(".,x"));
    action.setDefaultCommands([".x"]);
    action.setOverride();
    action.setNoState();
    action.setGroupSortOrder(15550);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);
};
