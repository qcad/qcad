function init(basePath) {
    var action = new RGuiAction(qsTranslate("Circle2TR", "2 &Tangents and Radius"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Circle2TR.js");
    action.setIcon(basePath + "/Circle2TR.svg");
    action.setStatusTip(qsTranslate("Circle2TR", "Draw circle tangential to two entities with given radius"));
    action.setDefaultShortcut(new QKeySequence("c,t"));
    action.setDefaultCommands(["circletangent2", "ct"]);
    action.setSortOrder(1000);
    EAction.addGuiActionTo(action, Circle, true, true, true, true);
}
