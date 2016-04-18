function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapIntersectionManual", "&Intersection Manual"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapIntersectionManual.js");
    action.setIcon(basePath + "/SnapIntersectionManual.svg");
    action.setDefaultShortcut(new QKeySequence("s,y"));
    action.setDefaultCommands(["snapintersectionmanual", "sy"]);
    action.setGroup("snaps");
    action.setOverride();
    action.setGroupSortOrder(15300);
    action.setSortOrder(200);
    action.setWidgetNames(["SnapMenu", "SnapToolBar", "SnapToolsPanel", "SnapMatrixPanel"]);

    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
}
