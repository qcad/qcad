function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapCoordinatePolar", "&Polar Coordinate"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapCoordinatePolar.js");
    action.setIcon(basePath + "/SnapCoordinatePolar.svg");
    action.setDefaultShortcut(new QKeySequence("s,o"));
    action.setDefaultCommands(["snappolar", "so"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15500);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
