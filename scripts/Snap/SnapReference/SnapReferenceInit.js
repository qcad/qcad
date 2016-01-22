function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapReference", "&Reference"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapReference.js");
    action.setIcon(basePath + "/SnapReference.svg");
    action.setDefaultShortcut(new QKeySequence("s,r"));
    action.setDefaultCommands(["snapreference", "sr"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15100);
    action.setSortOrder(700);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
