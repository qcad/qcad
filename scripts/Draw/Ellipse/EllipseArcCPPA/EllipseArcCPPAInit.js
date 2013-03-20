function init(basePath) {
    var action = new RGuiAction(qsTranslate("EllipseArcCPPA", "&Ellipse Arc"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/EllipseArcCPPA.js");
    action.setIcon(basePath + "/EllipseArcCPPA.svg");
    action.setStatusTip(qsTranslate("EllipseArcCPPA", "Draw ellipse arc from center, major point, ratio and angles"));
    action.setDefaultShortcut(new QKeySequence("e,a"));
    action.setDefaultCommands(["ellipsearc", "ea"]);
    action.setSortOrder(200);
    EAction.addGuiActionTo(action, Ellipse, true, true, true);
}
