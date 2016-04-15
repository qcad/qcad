function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapGrid", "&Grid"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapGrid.js");
    action.setIcon(basePath + "/SnapGrid.svg");
    action.setDefaultShortcut(new QKeySequence("s,g"));
    action.setDefaultCommands(["snapgrid", "sg"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15000);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
