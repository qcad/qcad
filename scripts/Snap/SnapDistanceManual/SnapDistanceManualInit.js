function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapDistanceManual", "&Distance Manual"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapDistanceManual.js");
    action.setIcon(basePath + "/SnapDistanceManual.svg");
    action.setStatusTip(qsTranslate("SnapDistanceManual", "Snap distance between 2 points"));
    action.setDefaultShortcut(new QKeySequence("s,h"));
    action.setDefaultCommands(["snapdistancemanual", "sh"]);
    action.setGroup("snaps");
    action.setOverride();
    action.setGroupSortOrder(15200);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
