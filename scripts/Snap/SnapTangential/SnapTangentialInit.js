function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapTangential", "&Tangential"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapTangential.js");
    action.setIcon(basePath + "/SnapTangential.svg");
    action.setDefaultShortcut(new QKeySequence("s,b"));
    action.setDefaultCommands(["snaptangential", "sb"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15100);
    action.setSortOrder(550);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
