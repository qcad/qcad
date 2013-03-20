function init(basePath) {
    var action = new RGuiAction(qsTranslate("LineRectangleSize", "Rectangle with &Size"), RMainWindowQt
            .getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/LineRectangleSize.js");
    action.setIcon(basePath + "/LineRectangleSize.svg");
    action.setDefaultShortcut(new QKeySequence("r,s"));
    action.setStatusTip(qsTranslate("LineRectangleSize", "Draw rectangle with position and size"));
    action.setDefaultCommands(["rectanglesize", "linerectanglesize", "rs"]);
    action.setSortOrder(600);
    EAction.addGuiActionTo(action, Line, true, true, true);
}
