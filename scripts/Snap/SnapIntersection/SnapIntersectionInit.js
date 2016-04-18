function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapIntersection", "&Intersection"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapIntersection.js");
    action.setIcon(basePath + "/SnapIntersection.svg");
    action.setDefaultShortcut(new QKeySequence("s,i"));
    action.setDefaultCommands(["snapintersection", "si"]);
    action.setGroup("snaps");
    action.setNoState(true);
    action.setGroupSortOrder(15300);
    action.setSortOrder(100);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
