function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineFreehand", "&Freehand Line"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineFreehand.js");
    action.setIcon(basePath + "/LineFreehand.svg");
    action.setStatusTip(qsTranslate("LineFreehand", "Draw freehand line"));
    action.setDefaultShortcut(new QKeySequence("l,f"));
    action.setDefaultCommands(["linefree", "freehand", "lf"]);
    action.setSortOrder(1600);
    EAction.addGuiActionTo(action, Line, true, true, true, true);
}
