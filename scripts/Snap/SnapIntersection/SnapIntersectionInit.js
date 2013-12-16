function init(basePath) {
    var action = new RGuiAction(qsTranslate("SnapIntersection", "&Intersection"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/SnapIntersection.js");
    action.setIcon(basePath + "/SnapIntersection.svg");
    action.setDefaultShortcut(new QKeySequence("s,i"));
    action.setDefaultCommands(["snapintersection", "si"]);
    action.setSortOrder(1000);
    action.setGroup("snaps");
    action.setNoState(true);
    var appWin = EAction.getMainWindow();
    appWin.addFocusListener(action);
    EAction.addGuiActionTo(action, Snap, true, true, true, true);
}
