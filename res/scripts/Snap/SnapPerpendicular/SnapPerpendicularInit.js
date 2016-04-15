function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapPerpendicular", "&Perpendicular"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapPerpendicular.js");
    action.setIcon(basePath + "/SnapPerpendicular.svg");
    action.setDefaultShortcut(new QKeySequence("s,u"));
    action.setDefaultCommands(["snapperpendicular", "su"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15100);
    action.setSortOrder(500);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
