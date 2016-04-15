function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapMiddleManual", "&Middle Manual"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapMiddleManual.js");
    action.setIcon(basePath + "/SnapMiddleManual.svg");
    action.setDefaultShortcut(new QKeySequence("s,n"));
    action.setDefaultCommands(["snapintersectionmiddlemanual", "sn"]);
    action.setGroup("snaps");
    action.setOverride();
    action.setGroupSortOrder(15150);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
