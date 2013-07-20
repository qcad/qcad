function init(basePath) {
    // disabled for now:
    return;

    var action = new RGuiAction(qsTranslate("Circle3T", "3 T&angents"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Circle3T.js");
    action.setIcon(basePath + "/Circle3T.svg");
    action.setStatusTip(qsTranslate("Circle3T", "Draw circle tangential to tree entities"));
    action.setDefaultShortcut(new QKeySequence("c,t,3"));
    action.setDefaultCommands(["circletangent3", "ct3"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Circle, true, true, true);
}
