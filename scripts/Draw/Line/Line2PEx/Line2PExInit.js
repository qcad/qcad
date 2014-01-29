function init(basePath) {
    var action = new RGuiAction(qsTranslate("Line2PEx", "Line from &2 Points"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Line2PEx.js");
    action.setIcon(basePath + "/Line2PEx.svg");
    action.setStatusTip(qsTranslate("Line2PEx", "Draw single line or sequence of lines"));
    action.setDefaultShortcut(new QKeySequence("l,x"));
    action.setDefaultCommands(["linex", "lnx", "lix", "lx"]);
    action.setSortOrder(110);
    EAction.addGuiActionTo(action, Line, true, true, true);
}
