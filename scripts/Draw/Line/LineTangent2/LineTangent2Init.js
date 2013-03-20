function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineTangent2", "Tan&gent (Two Circles)"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineTangent2.js");
    action.setIcon(basePath + "/LineTangent2.svg");
    action.setStatusTip(qsTranslate("LineTangent2", "Draw tangent (circle, circle)"));
    action.setDefaultShortcut(new QKeySequence("l,t,2"));
    action.setDefaultCommands(["linetangent2", "tangent2", "lt2"]);
    action.setSortOrder(1100);
    EAction.addGuiActionTo(action, Line, true, true, true);
}
