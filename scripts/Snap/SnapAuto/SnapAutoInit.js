function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapAuto", "&Auto"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapAuto.js");
    action.setIcon(basePath + "/SnapAuto.svg");
    action.setDefaultShortcut(new QKeySequence("s,a"));
    action.setDefaultCommands(["snapauto", "sa"]);
    action.setGroup("snaps");
    action.setGroupDefault(true);
    action.setNoState(true);
    action.setGroupSortOrder(15400);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
