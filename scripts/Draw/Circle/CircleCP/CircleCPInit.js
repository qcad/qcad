function init(basePath) {
    var action = new RGuiAction(qsTranslate("CircleCP", "&Center, Point"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/CircleCP.js");
    action.setIcon(basePath + "/CircleCP.svg");
    action.setStatusTip(qsTranslate("CircleCP", "Draw circle from center and point on circle"));
    action.setDefaultShortcut(new QKeySequence("c,i"));
    action.setDefaultCommands(["circle", "ci"]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Circle, true, true, true);
}
