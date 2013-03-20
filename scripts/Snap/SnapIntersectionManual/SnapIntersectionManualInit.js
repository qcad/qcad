function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapIntersectionManual", "&Intersection Manual"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapIntersectionManual.js");
    action.setIcon(basePath + "/SnapIntersectionManual.svg");
    action.setDefaultShortcut(new QKeySequence("s,y"));
    action.setDefaultCommands(["snapintersectionmanual", "sy"]);
    action.setSortOrder(1100);
    action.setGroup("snaps");
    action.setOverride();
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true);
}
