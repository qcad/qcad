function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineBisector", "Angle &Bisector"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineBisector.js");
    action.setIcon(basePath + "/LineBisector.svg");
    action.setStatusTip(qsTranslate("LineBisector", "Draw angle bisector, trisector, ..."));
    action.setDefaultShortcut(new QKeySequence("l,b"));
    action.setDefaultCommands(["linebisector", "bisector", "lb"]);
    action.setSortOrder(700);
    EAction.addGuiActionTo(action, Line, true, true, true, true);
}
