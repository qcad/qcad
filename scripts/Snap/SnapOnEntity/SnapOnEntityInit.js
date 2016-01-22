function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapOnEntity", "&On Entity"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapOnEntity.js");
    action.setIcon(basePath + "/SnapOnEntity.svg");
    action.setDefaultShortcut(new QKeySequence("s,t"));
    action.setDefaultCommands(["snaponentity", "st"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15100);
    action.setSortOrder(400);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
