function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapSelectionCenter", "Center of &Selection"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapSelectionCenter.js");
    action.setIcon(basePath + "/SnapSelectionCenter.svg");
    action.setDefaultShortcut(new QKeySequence("s,k"));
    action.setDefaultCommands(["snapselectioncenter", "sk"]);
    //action.setGroup("snaps");
    action.setNoState(true);
    action.setOverride();
    action.setGroupSortOrder(15560);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
