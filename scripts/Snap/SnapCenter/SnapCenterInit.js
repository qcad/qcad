function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapCenter", "&Center"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapCenter.js");
    action.setIcon(basePath + "/SnapCenter.svg");
    action.setDefaultShortcut(new QKeySequence("s,c"));
    action.setDefaultCommands(["snapcenter", "sc"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15100);
    action.setSortOrder(600);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
