function init(basePath) {
    var action = new RGuiAction(qsTranslate("Point1P", "Single &Point"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/Point1P.js");
    action.setIcon(basePath + "/Point1P.svg");
    action.setStatusTip(qsTranslate("Point1P", "Draw single point"));
    action.setDefaultShortcut(new QKeySequence("p,o"));
    action.setDefaultCommands(["point"]);
    action.setSortOrder(100);
    EAction.addGuiActionTo(action, Point, true, true, true);
}
