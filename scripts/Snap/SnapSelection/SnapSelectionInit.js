function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapSelection", "&Selection Reference Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapSelection.js");
    action.setDefaultShortcut(new QKeySequence("s,k"));
    action.setDefaultCommands(["snapselectioncenter", "sk"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15560);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
