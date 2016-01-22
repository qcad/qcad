function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapDistance", "&Distance"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapDistance.js");
    action.setIcon(basePath + "/SnapDistance.svg");
    action.setDefaultShortcut(new QKeySequence("s,d"));
    action.setDefaultCommands(["snapdistance", "sd"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15200);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
