function init(basePath) {
    var action = new RGuiAction(qsTranslate("ZoomIn", "Zoom &In"), RMainWindowQt.getMainWindow());
    action.setRequiresDocument(true);
    action.setScriptFile(basePath + "/ZoomIn.js");
    action.setIcon(basePath + "/ZoomIn.svg");
    action.setDefaultShortcuts([
        new QKeySequence("+"),
        new QKeySequence(QKeySequence.ZoomIn)
    ]);
    action.setDefaultCommands(["zoomin"]);
    action.setSortOrder(100);
    action.setNoState();
    EAction.addGuiActionTo(action, View, true, true, false, true);
}
