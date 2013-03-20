function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineRectangle", "&Rectangle"),
        RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineRectangle.js");
    action.setIcon(basePath + "/LineRectangle.svg");
    action.setDefaultShortcut(new QKeySequence("r,e"));
    action.setStatusTip(qsTranslate("LineRectangle", "Draw rectangle from two corners"));
    action.setDefaultCommands(["rectangle", "linerectangle", "rect", "re"]);
    action.setSortOrder(500);
    EAction.addGuiActionTo(action, Line, true, true, true, true);
}
