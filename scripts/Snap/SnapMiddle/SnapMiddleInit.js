function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapMiddle", "&Middle"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapMiddle.js");
    action.setIcon(basePath + "/SnapMiddle.svg");
    action.setDefaultShortcut(new QKeySequence("s,m"));
    action.setDefaultCommands(["snapmiddle", "sm"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15150);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
