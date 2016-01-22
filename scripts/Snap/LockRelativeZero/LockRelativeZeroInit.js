function init(basePath) {
    var action = new RGuiAction(qsTranslate("LockRelativeZero", "&Lock Relative Zero"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LockRelativeZero.js");
    action.setIcon(basePath + "/LockRelativeZero.svg");
    action.setDefaultShortcut(new QKeySequence("r,l"));
    action.setDefaultCommands(["lockrelativezero", "rl"]);
    action.setGroupSortOrder(15800);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);
}
