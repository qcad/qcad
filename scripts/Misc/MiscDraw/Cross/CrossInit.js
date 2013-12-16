function init(basePath) {
    var action = new RGuiAction(qsTranslate("Cross", "Centreline Cross"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Cross.js");
    action.setIcon(basePath + "/Cross.svg");
    action.setStatusTip(qsTranslate("Cross", "Draw centreline cross in Arc, Circle or Ellipses"));
    action.setDefaultShortcut(new QKeySequence("c,s"));
    action.setDefaultCommands(["cross", "cs"]);
    action.setSortOrder(310);
    EAction.addGuiActionTo(action, MiscDraw, true, true);
}
