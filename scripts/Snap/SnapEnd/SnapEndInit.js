function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapEnd", "&End"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapEnd.js");
    action.setIcon(basePath + "/SnapEnd.svg");
    action.setDefaultShortcut(new QKeySequence("s,e"));
    action.setDefaultCommands(["snapend", "se"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15100);
    action.setSortOrder(300);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
