function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapCoordinate", "&Coordinate"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapCoordinate.js");
    action.setIcon(basePath + "/SnapCoordinate.svg");
    action.setDefaultShortcut(new QKeySequence("s,x"));
    action.setDefaultCommands(["snapcoordinate", "sx"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15500);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
